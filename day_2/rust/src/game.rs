use crate::ancillary::Solution;
use crate::color_cubes::*;
use crate::color_cubes::Color::{BLUE, GREEN, RED};

pub fn solve_game(game: &String, sol: &mut Solution) {
    if !game.starts_with("Game") || !game.contains(':') {
        return;
    }

    let split_string = game.split(':');
    let game_id_str = split_string.clone().nth(0).unwrap().replace("Game", "").trim().to_string();
    let draws = split_string.last().unwrap().trim().split(';');

    let game_id = game_id_str.parse::<u8>();

    if game_id.is_err() {
        return;
    }

    let mut possible  = true;

    let mut max_colors: [u64; NUM_COLORS] = [0; NUM_COLORS];

    draws.for_each(|draw| {
        draw.split(',').for_each(|text| {
            let color_draw = text.trim().replace("  ", " ");

            let tokens = color_draw.split(' ');

            match tokens.clone().last() {
                None => {},
                Some(draw_color) => {
                    let color_type = match draw_color {
                        RED_TEXT => RED,
                        GREEN_TEXT => GREEN,
                        BLUE_TEXT => BLUE,
                        &_ => {
                            panic!("Faulty data detected.");
                        }
                    };

                    if tokens.clone().nth(0).is_some() {
                        let draw_number = tokens.clone().nth(0).unwrap().trim().to_string().parse::<u64>().unwrap();

                        if draw_number > MAX_CUBES[color_type as usize] {
                            possible = false;
                        }

                        if draw_number > max_colors[color_type as usize] {
                            max_colors[color_type as usize] = draw_number;
                        }
                    }
                }
            }
        })

    });

    if possible {
        sol.part_one += game_id.unwrap() as u64;
    }

    sol.part_two += max_colors.iter().product::<u64>();
}