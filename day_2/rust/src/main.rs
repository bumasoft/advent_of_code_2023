mod ancillary;
mod game;
mod color_cubes;

use std::env;
use std::process::ExitCode;
use ancillary::*;
use game::solve_game;

fn main() -> ExitCode {
    println!("**** Advent of Code, Day 2, 2023 ****\n");

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Error: Input file not specified.");
        eprintln!(
            "Usage: {} filename",
            env::current_exe()
                .ok()
                .unwrap()
                .file_name()
                .unwrap()
                .to_str()
                .unwrap()
                .to_owned()
        );

        return ExitCode::FAILURE;
    }

    let games = file_to_lines(args.get(1).unwrap());

    let mut sol: Solution = Solution{
        part_one: 0,
        part_two: 0,
    };

    for game in games {
        solve_game(&game, &mut sol);
    }

    println!("Part 1. Sum of Ids: {}", sol.part_one);
    println!("Part 2. Sum of Powers of Minimum Set of Cubes: {}\n", sol.part_two);

    ExitCode::SUCCESS
}
