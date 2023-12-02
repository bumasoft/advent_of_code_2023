use std::env;
use std::fs::read_to_string;
use std::process::ExitCode;

const UNDEFINED_DIGIT: u32 = 255;

struct Solution {
    part_one: u64,
    part_two: u64,
}

fn update_digits(first_digit: &mut u32, last_digit: &mut u32, digit: u32) {
    if *first_digit == UNDEFINED_DIGIT {
        *first_digit = digit;
    }

    *last_digit = digit;
}

fn process_string(calibration: &String, sol: &mut Solution) {
    let mut first_digit_p1: u32 = UNDEFINED_DIGIT;
    let mut last_digit_p1: u32 = UNDEFINED_DIGIT;

    let mut first_digit_p2: u32 = UNDEFINED_DIGIT;
    let mut last_digit_p2: u32 = UNDEFINED_DIGIT;

    let chars: Vec<char> = calibration.chars().collect();

    for i in 0..chars.len() {
        if !chars[i].is_digit(10) {
            // check for numbers spelled as letters
            match chars[i] {
                'o' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "one" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 1);
                    }
                }
                't' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "two" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 2);
                    } else if calibration.chars().skip(i).take(5).collect::<String>() == "three" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 3);
                    }
                }
                'f' => {
                    if calibration.chars().skip(i).take(4).collect::<String>() == "four" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 4);
                    } else if calibration.chars().skip(i).take(4).collect::<String>() == "five" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 5);
                    }
                }
                's' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "six" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 6);
                    } else if calibration.chars().skip(i).take(5).collect::<String>() == "seven" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 7);
                    }
                }
                'e' => {
                    if calibration.chars().skip(i).take(5).collect::<String>() == "eight" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 8);
                    }
                }
                'n' => {
                    if calibration.chars().skip(i).take(4).collect::<String>() == "nine" {
                        update_digits(&mut first_digit_p2, &mut last_digit_p2, 9);
                    }
                }
                _ => {}
            }
            continue;
        }

        let digit = chars[i].to_digit(10).unwrap();

        update_digits(
            &mut first_digit_p1,
            &mut last_digit_p1,
            digit,
        );

        update_digits(
            &mut first_digit_p2,
            &mut last_digit_p2,
            digit,
        );
    }

    sol.part_one += (first_digit_p1 * 10 + last_digit_p1) as u64;
    sol.part_two += (first_digit_p2 * 10 + last_digit_p2) as u64;
}

fn main() -> ExitCode {
    println!("**** Advent of Code, Day 1, 2023 ****\n");

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

    let strings: Vec<String> = read_to_string(args.get(1).unwrap())
        .expect("Failed to read file.")
        .lines()
        .map(String::from)
        .collect();

    let mut sol = Solution {
      part_one: 0,
        part_two: 0,
    };

    for calibration in strings {
        process_string(&calibration, &mut sol);
    }

    println!("Part 1 answer: {}", sol.part_one);
    println!("Part 2 answer: {}", sol.part_two);

    ExitCode::SUCCESS
}
