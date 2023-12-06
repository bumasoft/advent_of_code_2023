//
// Created by Victor-Marian Busoi on 03.12.2023.
//
#include "bumasoft/standard.h"
#include "part_one.h"
#include "aoc.h"

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

uint64_t match_on_map(uint64_t src, vector_t* map) {
    for (size_t i = 0; i < map->length; i++) {
        vector_t *row = (vector_t *) _vector_get(map, i)._ptr;

        uint64_t dest_start = _vector_get(row, 0)._uint64;
        uint64_t src_start = _vector_get(row, 1)._uint64;
        uint64_t range = _vector_get(row, 2)._uint64;

        bool in_range = (src >= src_start && src < src_start + range);

        if (in_range) return dest_start + (src - src_start);
    }

    return src;
}

void solve_part_one(FILE* fp, vector_t* seeds, solution_t *solution) {
    SAFE_CALLOC(char*, buffer, BUFFER_LENGTH, sizeof(char));

    vector_t seed_to_soil_map = get_map(fp, buffer, "seed-to-soil");
    vector_t soil_to_fertilizer_map = get_map(fp, buffer, "soil-to-fertilizer");
    vector_t fertilizer_to_water_map = get_map(fp, buffer, "fertilizer-to-water");
    vector_t water_to_light_map = get_map(fp, buffer, "water-to-light");
    vector_t light_to_temp_map = get_map(fp, buffer, "light-to-temperature");
    vector_t temp_to_humidity_map = get_map(fp, buffer, "temperature-to-humidity");
    vector_t humidity_to_loc_map = get_map(fp, buffer, "humidity-to-location");

    uint64_t minimum = UINT64_MAX;

    for(size_t i = 0; i < seeds->length; i++) {
        uint64_t seed = _vector_get(seeds, i)._uint64;

        uint64_t soil_num = match_on_map(seed, &seed_to_soil_map);
        uint64_t fert_num = match_on_map(soil_num, &soil_to_fertilizer_map);
        uint64_t water_num = match_on_map(fert_num, &fertilizer_to_water_map);
        uint64_t light_num = match_on_map(water_num, &water_to_light_map);
        uint64_t temp_num = match_on_map(light_num, &light_to_temp_map);
        uint64_t humidity_num = match_on_map(temp_num, &temp_to_humidity_map);
        uint64_t location_num = match_on_map(humidity_num, &humidity_to_loc_map);

        printf("- Seed %llu, soil %llu, fertilizer %llu, water %llu, light %llu, temperature %llu, humidity %llu, location %llu\n\n", seed, soil_num, fert_num, water_num, light_num, temp_num, humidity_num, location_num);

        if (location_num < minimum) minimum = location_num;
    }

    solution->part_one = minimum;

    // Cleanup time:
    free(buffer);
    _vector_free(&seed_to_soil_map);
    _vector_free(&soil_to_fertilizer_map);
    _vector_free(&fertilizer_to_water_map);
    _vector_free(&water_to_light_map);
    _vector_free(&light_to_temp_map);
    _vector_free(&temp_to_humidity_map);
}