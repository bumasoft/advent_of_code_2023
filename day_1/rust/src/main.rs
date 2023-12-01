use std::env;

fn main() {
    println!("**** Advent of Code, Day 1, 2023 ****\n");

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        println!("Error: input file not specified.");
        println!("Usage: calib filename\n");
    }

}
