//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "bumasoft/standard.h"
#include "solution.h"
#include "aoc.h"

#define NUM_MAPS 7
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/*
 * Reads a map from the input file and stores it into a matrix.
 * Starts by skipping any blank lines. Stops processing on blank line or EOF.
 */
vector_t get_map(FILE* fp, char* line_buffer, const char* map_id) {
    vector_t result = vector_init();

    while (fgets(line_buffer, BUFFER_LENGTH, fp)) {
        line_buffer = str_trim(line_buffer);
        if (line_buffer != NULL && strlen(line_buffer) > 0) break;
    }

    if (str_starts_with(line_buffer, map_id)) {
        while (fgets(line_buffer, BUFFER_LENGTH, fp)) {
            line_buffer = str_trim(line_buffer);
            if (line_buffer == NULL || strlen(line_buffer) == 0) break;

            // we allocate this on heap, otherwise it does not survive past return,
            // because the result vec just points to num_cells' memory address
            SAFE_MALLOC(vector_t*, num_cells, 1, sizeof(vector_t));

            *num_cells = str_split(line_buffer, " ");
            num_cells->to_u64(num_cells);

            result.push(&result, VEC_ITEM_PTR(num_cells));
        }
    }

    return result;
}

/*
 * Used for part 1.
 * Receives a source value and maps it to a destination value based on the specified map.
 */
uint64_t match_on_map(uint64_t src, vector_t* map) {
    for (size_t i = 0; i < map->length; i++) {
        vector_t *row = (vector_t *) _vector_get(map, i)._ptr;

        uint64_t dest_start = _vector_get(row, 0)._uint64;
        uint64_t src_start = _vector_get(row, 1)._uint64;
        int64_t diff = (int64_t) src_start - (int64_t) dest_start;
        uint64_t range = _vector_get(row, 2)._uint64;

        bool in_range = (src >= src_start && src < src_start + range);

        if (in_range) return src - diff;
    }

    return src;
}

/*
 * Used for part 1.
 * Recursively calls match_on_map on an array of maps, to find the solution.
 */
uint64_t match_recurse(uint64_t src, size_t total, vector_t* maps[total], size_t i) {
    uint64_t num = match_on_map(src, maps[i]);

    if (i == total - 1) return num;

    return  match_recurse(num, total, maps, i + 1);
}

/*
 * Used for part 2.
 * Receives a source value and a range and maps it to a vector of destination ranges
 * (a flat tuple array, where each odd index is a start number and the following even index is the range).
 */
vector_t match_range_on_map(uint64_t src, uint64_t src_range, vector_t* map) {
    vector_t result = vector_init();

    for (size_t i = 0; i < map->length; i++) {
        vector_t* row = (vector_t *) _vector_get(map, i)._ptr;

        uint64_t dest_start = _vector_get(row, 0)._uint64;
        uint64_t src_start = _vector_get(row, 1)._uint64;
        int64_t diff = (int64_t) src_start - (int64_t) dest_start;
        uint64_t range = _vector_get(row, 2)._uint64;

        uint64_t result_start = MAX(src, src_start);
        uint64_t result_range = MIN(src_range, range);

        bool in_range = src >= src_start && src + src_range <= src_start + range;

        if (in_range) {
            // inside the mapped range, simple case:
            result.push(&result, VEC_U64(result_start - diff));
            result.push(&result, VEC_U64(result_range));
        } else {
            // not fully inside, check for overlaps:
            if (src < src_start && src + src_range > src_start) {
                result.push(&result, VEC_U64(src_start - diff));
                result.push(&result, VEC_U64( src + src_range < src_start + range ? (src - src_start + src_range - 1) : range ));
            } else if (src >= src_start && src < src_start + range && src + src_range > src_start + range) {
                result.push(&result, VEC_U64(src - diff));
                result.push(&result, VEC_U64(src_start + range - src));
            };
        }
    }

    if (result.length == 0) {
        result.push(&result, VEC_U64(src));
        result.push(&result, VEC_U64(src_range));
    }

    return result;
}

void solve(FILE* fp, vector_t* seeds, solution_t *solution) {
    // Line buffer:
    SAFE_CALLOC(char*, buffer, BUFFER_LENGTH, sizeof(char));

    // Get all required maps:
    vector_t seed_to_soil_map = get_map(fp, buffer, "seed-to-soil");
    vector_t soil_to_fertilizer_map = get_map(fp, buffer, "soil-to-fertilizer");
    vector_t fertilizer_to_water_map = get_map(fp, buffer, "fertilizer-to-water");
    vector_t water_to_light_map = get_map(fp, buffer, "water-to-light");
    vector_t light_to_temp_map = get_map(fp, buffer, "light-to-temperature");
    vector_t temp_to_humidity_map = get_map(fp, buffer, "temperature-to-humidity");
    vector_t humidity_to_loc_map = get_map(fp, buffer, "humidity-to-location");

    // Put them into an array, so we can easily recurse:
    vector_t* maps[NUM_MAPS] = {&seed_to_soil_map, &soil_to_fertilizer_map,
                         &fertilizer_to_water_map, &water_to_light_map,
                         &light_to_temp_map, &temp_to_humidity_map,
                         &humidity_to_loc_map };

    uint64_t minimum = UINT64_MAX;

    /*
     * PART 1
     */
    for(size_t i = 0; i < seeds->length; i++) {
        uint64_t seed = _vector_get(seeds, i)._uint64;
        uint64_t location = match_recurse(seed, NUM_MAPS, maps, 0);

        if (location < minimum) minimum = location;
    }

    solution->part_one = minimum;

    /*
     * PART 2
     */
    if (seeds->length % 2 != 0) {
        fprintf(stderr, "Invalid seed array. Must be even length.");
        exit(EXIT_FAILURE);
    }

    minimum = UINT64_MAX;

    for (size_t i = 0; i < seeds->length - 1; i += 2) {
        uint64_t num = _vector_get(seeds, i)._uint64;
        uint64_t range = _vector_get(seeds, i + 1)._uint64;

        size_t k = 1;
        vector_t result = match_range_on_map(num, range, maps[0]);

        while(k < NUM_MAPS) {
            vector_t ranges = vector_init();

            for (size_t j = 0; j < result.length - 1; j += 2) {
                vector_t data = match_range_on_map(result.get(&result, j)._uint64, result.get(&result, j + 1)._uint64, maps[k]);
                ranges.append(&ranges, data);
            }
            result = ranges;
            k++;
        }

        /*
         * Final result array has the location ranges, so we just need to find the minimum:
         */
        for (size_t j = 0; j < result.length - 1; j += 2)
            if (result.get(&result, j)._uint64 < minimum)
                minimum = result.get(&result, j)._uint64;

        _vector_free(&result);
    }

    solution->part_two = minimum;

    // Cleanup time:
    free(buffer);
    _vector_free(&seed_to_soil_map);
    _vector_free(&soil_to_fertilizer_map);
    _vector_free(&fertilizer_to_water_map);
    _vector_free(&water_to_light_map);
    _vector_free(&light_to_temp_map);
    _vector_free(&temp_to_humidity_map);
}