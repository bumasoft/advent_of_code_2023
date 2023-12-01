use std::env;
use std::fs::read_to_string;
use std::io::{Error, ErrorKind};

fn update_digits(first_digit: &mut u32, last_digit: &mut u32, digit: u32) {
    if *first_digit == 255 {
        *first_digit = digit;
    }

    *last_digit = digit;
}

fn num_from_string(calibration: &String) -> u32 {
    let mut first_digit: u32 = 255;
    let mut last_digit: u32 = 255;

    let chars: Vec<char> = calibration.chars().collect();

    for i in 0..chars.len() {
        if !chars[i].is_digit(10) {
            // check for numbers spelled as letters
            match chars[i] {
                'o' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "one" {
                        update_digits(&mut first_digit, &mut last_digit, 1);
                    }
                }
                't' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "two" {
                        update_digits(&mut first_digit, &mut last_digit, 2);
                    } else if calibration.chars().skip(i).take(5).collect::<String>() == "three" {
                        update_digits(&mut first_digit, &mut last_digit, 3);
                    }
                }
                'f' => {
                    if calibration.chars().skip(i).take(4).collect::<String>() == "four" {
                        update_digits(&mut first_digit, &mut last_digit, 4);
                    } else if calibration.chars().skip(i).take(4).collect::<String>() == "five" {
                        update_digits(&mut first_digit, &mut last_digit, 5);
                    }
                }
                's' => {
                    if calibration.chars().skip(i).take(3).collect::<String>() == "six" {
                        update_digits(&mut first_digit, &mut last_digit, 6);
                    } else if calibration.chars().skip(i).take(5).collect::<String>() == "seven" {
                        update_digits(&mut first_digit, &mut last_digit, 7);
                    }
                }
                'e' => {
                    if calibration.chars().skip(i).take(5).collect::<String>() == "eight" {
                        update_digits(&mut first_digit, &mut last_digit, 8);
                    }
                }
                'n' => {
                    if calibration.chars().skip(i).take(4).collect::<String>() == "nine" {
                        update_digits(&mut first_digit, &mut last_digit, 9);
                    }
                }
                _ => {}
            }
            continue;
        }

        if first_digit == 255 {
            first_digit = chars[i].to_digit(10).unwrap();
        }

        last_digit = chars[i].to_digit(10).unwrap();
    }

    first_digit * 10 + last_digit
}

fn main() -> Result<(), Error> {
    println!("**** Advent of Code, Day 1, 2023 ****\n");

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Usage: calib filename");
        return Err(Error::new(
            ErrorKind::InvalidData,
            "Error: Input file not specified.",
        ));
    }

    let strings: Vec<String> = read_to_string(args.get(1).unwrap())?
        .lines()
        .map(String::from)
        .collect();

    let mut sum: u64 = 0;

    for calibration in strings {
        let num = num_from_string(&calibration);
        // println!("{} = {}", calibration, num); // For debugging
        sum += num as u64;
    }

    println!("\nSum of all the calibration values: {}", sum);

    Ok(())
}
