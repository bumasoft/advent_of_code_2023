mod ancillary;
use ancillary::*;
use std::env;
use std::process::ExitCode;

#[derive(Copy, Clone)]
struct SchematicNumber {
    number: u32,
    start: usize,
    end: usize,
    added: bool,
}

#[derive(Copy, Clone)]
struct SchematicSymbol {
    index: usize,
}
fn main() -> ExitCode {
    println!("**** Advent of Code, Day 3, 2023 ****\n");

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

    let mut schematic = file_to_lines(args.get(1).unwrap());

    if schematic.len() == 0 {
        eprintln!("Invalid data.");
        return ExitCode::FAILURE;
    }

    let mut sol: Solution = Solution {
        part_one: 0,
        part_two: 0,
    };

    let mut numbers: Vec<Vec<SchematicNumber>> = Vec::new();
    let mut symbols: Vec<Vec<SchematicSymbol>> = Vec::new();

    // Read schematic into a matrix structure, keeping track of numbers and symbols separately
    for i in 1..schematic.len() {
        let mut line = schematic.get(i - 1).unwrap().chars().peekable();

        let mut line_numbers: Vec<SchematicNumber> = Vec::new();
        let mut line_symbols: Vec<SchematicSymbol> = Vec::new();

        let mut start_idx = 0;
        while let Some(c) = line.peek() {
            if c.is_digit(10) {
                // greedily consume number
                let mut num = line.next().unwrap().to_digit(10).unwrap();
                let mut len = 0;
                while let Some(cn) = line.peek() {
                    if !cn.is_digit(10) {
                        break;
                    }
                    num = num * 10 + cn.to_digit(10).unwrap();
                    len += 1;
                    line.next();
                }

                line_numbers.push(SchematicNumber {
                    number: num,
                    start: start_idx,
                    end: start_idx + len,
                    added: false,
                });

                start_idx = start_idx + len + 1;
            } else if *c != '.' {
                // symbol detected

                line_symbols.push(SchematicSymbol { index: start_idx })
            }

            start_idx += 1;
            line.next();
        }

        numbers.push(line_numbers);
        symbols.push(line_symbols);
    }

    for i in 0..numbers.len() {
        for mut number in numbers[i].iter_mut() {
            if number.added {
                continue;
            }

            if symbols[i]
                .iter()
                .find(|ssym| {
                    (ssym.index == number.end + 1)
                        || (number.start > 0 && ssym.index == number.start - 1)
                })
                .is_some()
            {
                sol.part_one += number.number as u64;
                number.added = true;
            }
        }
    }

    println!("Part 1: {}", sol.part_one);
    println!("Part 2: {}\n", sol.part_two);

    ExitCode::SUCCESS
}
