use std::fs::read_to_string;

pub struct Solution {
    pub part_one: u64,
    pub part_two: u64,
}
pub fn file_to_lines(filename: &String) -> Vec<String> {
    read_to_string(filename)
        .expect("Failed to read file.")
        .lines()
        .map(String::from)
        .collect()
}
