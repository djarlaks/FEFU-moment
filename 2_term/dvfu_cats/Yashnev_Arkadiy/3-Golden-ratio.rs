#![allow(unused)]

use std::io::{self, Read, Write, BufReader, BufRead};
use std::fs::{File};

fn main() -> io::Result<()> {
    let mut buf = String::new();
    let fin = File::open("input.txt")?;
    let mut fout = File::create("output.txt")?;
    let mut buf_reader = BufReader::new(fin);

    buf_reader.read_line(&mut buf)?;
    let size = buf.trim().parse::<usize>().unwrap();
    buf.clear();

    buf_reader.read_line(&mut buf)?;
    let nums = buf.trim().split_whitespace()
        .map(|n| n.parse::<i32>().unwrap());

    let min = |a, b| { a < b };
    let max = |a, b| { a > b };

    let mut top_nums = Heap::new(size, min);
    let mut bot_nums = Heap::new(size, max);
    for i in nums {
        if top_nums.data.len() > 0 {
            let top_min = top_nums.data[0];
            if i > top_min {
                top_nums.insert(i);
            } else {
                bot_nums.insert(i);
            }
        } else {
            bot_nums.insert(i);
        }

        while top_nums.data.len() > bot_nums.data.len() {
            bot_nums.insert(top_nums.extract());
        }

        while top_nums.data.len() + 1 < bot_nums.data.len() {
            top_nums.insert(bot_nums.extract());
        }

        fout.write(format!("{} ", bot_nums.data[0]).as_bytes());
    }

    Ok(())
}

struct Heap<T>
where
    T: Fn(i32, i32) -> bool,
{
    data: Vec<i32>,
    pred: T,
}

impl<T> Heap<T>
where 
    T: Fn(i32, i32) -> bool
{
    fn new(size: usize, pred: T) -> Self {
        let data = Vec::with_capacity(size);

        Self { data, pred }
    }

    fn insert(&mut self, elem: i32) {
        self.data.push(elem);
        let len = self.data.len() - 1;
        self.bubble_up(len);
    }

    fn bubble_up(&mut self, idx: usize) {
        if idx == 0 { return; }

        let parent = (idx - 1) / 2;

        if (self.pred)(self.data[idx], self.data[parent]) {        
            self.data.swap(idx, parent);
            self.bubble_up(parent);
        }
    }

    fn bubble_down(&mut self, idx: usize) {
        let l = 2 * idx + 1;
        let r = 2 * idx + 2;
        let size = self.data.len();
        let mut least = idx;
        
        if l < size && (self.pred)(self.data[l], self.data[least]) {
            least = l;
        }

        if r < size && (self.pred)(self.data[r], self.data[least]) {
            least = r;
        }
            
        if least != idx {
            self.data.swap(idx, least);
            self.bubble_down(least);
        }
    }
 
    fn extract(&mut self) -> i32 {
        let root = self.data[0];
        let last = self.data.pop().unwrap();
        self.data[0] = last;
        self.bubble_down(0);
        root
    }
}
