use std::io::BufRead;
use std::io::prelude::*;
use std::fs::File;
use std::io::BufReader;
use std::collections::HashSet;

fn main() {
    part1();
    part2();
}

fn part2() {
    let file = File::open("input.txt").expect("Could not open file!");
    let reader = BufReader::new(file);

    let mut sum: u32 = 0;
    let mut i = 0;

    let mut set1 = HashSet::<char>::new();
    let mut set2 = HashSet::<char>::new();

    for line in reader.lines() {
        let info = line.unwrap();
        
        for c in info.chars() {
            if i == 0 {
                set1.insert(c);
            } else if i == 1 && set1.contains(&c) {
                set2.insert(c);
            } else if i == 2 && set2.contains(&c) {
                let ascii = (c.to_ascii_lowercase() as u32);
                if c >= 'a' && c <= 'z' {
                    sum += ascii - 96;
                } else {
                    sum += ascii - 96 + 26;
                }
                break;
            }
        }
        i += 1;
        if i == 3 {
            i = 0;
            set1.clear();
            set2.clear();
        }
    }

    println!("Badges Sum: {sum}");
}


fn part1() {
    let file = File::open("input.txt").expect("Could not open file!");
    let reader = BufReader::new(file);

    let mut sum: u32 = 0;
    for line in reader.lines() {
        let info = line.unwrap();
        let size = info.len();
        
        let mid = size / 2;
        let mut counter = 0;
        let mut set = HashSet::<char>::new();

        for c in info.chars() {
            if (counter < mid) {
                set.insert(c);
            } else {
                if (set.contains(&c)) {
                    let ascii = (c.to_ascii_lowercase() as u32);
                    if c >= 'a' && c <= 'z' {
                        sum += ascii - 96;
                    } else {
                        sum += ascii - 96 + 26;
                    }
                    println!("{c}: {sum} {ascii}");
                    break;
                }
            }
            counter += 1;
        }
    }

    println!("Final Sum: {sum}");
}
