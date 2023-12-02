pub const RED_TEXT: &str = "red";
pub const GREEN_TEXT: &str = "green";
pub const BLUE_TEXT: &str = "blue";
pub const MAX_RED_CUBES: u64 =  12;
pub const MAX_GREEN_CUBES: u64 = 13;
pub const MAX_BLUE_CUBES: u64= 14;

pub const NUM_COLORS: usize = 3;

#[derive(Clone, Copy)]
pub enum Color {
    RED = 0,
    GREEN,
    BLUE,
}

pub const MAX_CUBES: [u64; 3] = [MAX_RED_CUBES, MAX_GREEN_CUBES, MAX_BLUE_CUBES];