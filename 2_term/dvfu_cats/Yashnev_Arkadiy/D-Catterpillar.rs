use std::fs::{File};
use std::io::{prelude::*};

#[derive(Clone, Copy, PartialEq, Eq)]
enum State {
    Descent = -1,
    Climb = 1,
    End = 0
}

fn main() -> std::io::Result<()> {
    let mut fin = File::open("input.txt")?;
    let mut fout = File::create("output.txt")?;
    
    let mut buf = String::new();
    fin.read_to_string(&mut buf)?;
    let input: Vec<usize> = buf.trim().split_whitespace()
        .map(|c| { c.parse().unwrap() }).collect();

    let time = solve(input[0], input[1], &input[2..]);

    fout.write(time.to_string().as_bytes())?;

    Ok(())
}

use State::*;
fn solve(l: usize, n: usize, heights: &[usize]) -> usize {
    let mut time = 0;
    let mut states = Vec::with_capacity(n);

    for i in 1..n {
        states.push(if heights[i - 1] < heights[i] { Climb } else { Descent });
    }
    states.push(End);

    let mut state_diff = *(&states[0..l].iter()
        .fold(0, |acc, x| acc + *x as i32));

    for head in l-1..n-1 {
        if state_diff >= 0 || states[head] == Climb { time += 1 };
        let head = head + 1;
        state_diff += states[head] as i32 - states[head - l] as i32;
    }

    time
}
