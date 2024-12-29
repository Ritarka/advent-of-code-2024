use std::fs::File;
use std::io::{BufRead, BufReader};

fn main() {
    part1();
    part2();
}

fn part2() {
    let file = File::open("input.txt").expect("Unable to open file");
    let reader = BufReader::new(file);

    let mut counter = 0;

    for elem in reader.lines() {
        let line = elem.unwrap();
        let intervals: Vec<&str> = line.split(',').collect();

        let elemsa: Vec<&str> = intervals[0].split('-').collect();
        let elemsb: Vec<&str> = intervals[1].split('-').collect();

        let starta = elemsa[0].parse::<i32>().unwrap();
        let enda = elemsa[1].parse::<i32>().unwrap();
        let startb = elemsb[0].parse::<i32>().unwrap();
        let endb = elemsb[1].parse::<i32>().unwrap();

        if (starta >= startb && starta <= endb) || (enda >= startb && enda <= endb) 
            || ((starta >= startb && enda <= endb) || (startb >= starta && endb <= enda))
        {
            counter += 1;
            // println!("{starta} {startb} {enda} {endb}");
        }
    }


    println!("Overlapping Pairs: {counter}");
}

fn part1() {
    let file = File::open("input.txt").expect("Unable to open file");
    let reader = BufReader::new(file);

    let mut counter = 0;

    for elem in reader.lines() {
        let line = elem.unwrap();
        let intervals: Vec<&str> = line.split(',').collect();

        let elemsa: Vec<&str> = intervals[0].split('-').collect();
        let elemsb: Vec<&str> = intervals[1].split('-').collect();

        let starta = elemsa[0].parse::<i32>().unwrap();
        let enda = elemsa[1].parse::<i32>().unwrap();
        let startb = elemsb[0].parse::<i32>().unwrap();
        let endb = elemsb[1].parse::<i32>().unwrap();

        // println!("{starta} {startb} {enda} {endb}");
        if (starta >= startb && enda <= endb) || (startb >= starta && endb <= enda) {
            counter += 1;
        }
    }


    println!("Enclosing Pairs: {counter}");
}