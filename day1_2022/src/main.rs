use std::fs::File;
use std::io::{self, prelude::*, BufReader};
use std::cmp::max;

fn main() {
    let file = File::open("input.txt").expect("File not found");
    let reader = BufReader::new(file);

    let mut top: u32 = 0;
    let mut sec: u32 = 0;
    let mut third: u32 = 0;

    let mut sum: u32 = 0;
    for line in reader.lines() {
        // println!("{}", line.expect("Line is bad?"));
        let string = line.expect("Bad String");
        if string.is_empty() {
            if sum > top {
                third = sec;
                sec = top;
                top = sum;
            } else if sum > sec {
                third = sec;
                sec = sum;
            } else if sum > third {
                third = sum;
            }
            sum = 0;
            continue;
        }
        let num: u32 = string.parse().unwrap();
        sum += num;
    }
    if sum > top {
        third = sec;
        sec = top;
        top = sum;
    } else if sum > sec {
        third = sec;
        sec = sum;
    } else if sum > third {
        third = sum;
    }

    let total = top + sec + third;

    println!("Maximum calories is {total}");

    // Ok(());
}
