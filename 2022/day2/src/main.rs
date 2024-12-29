use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;

fn main() {
    let file: File = File::open("test.txt").expect("File not found");
    let reader = BufReader::new(file);

    let mut score = 0;
    for line in reader.lines() {
        let _string = line.unwrap();
        let opp = &_string[..1];
        let you = &_string[2..];

        let conv = match opp {
            "A" => "X",
            "B" => "Y",
            "C" => "Z",
            _ => unreachable!("Bad onversion should never happen!")
        };

        let you_conv = match you {
            "Y" => {
                conv
            },
            "X" => {
                if conv == "X" {
                    "Z"
                } else if conv == "Y" {
                    "X"
                } else {
                    "Y"
                }
            },
            "Z" => {
                if conv == "X" {
                    "Y"
                } else if conv == "Y" {
                    "Z"
                } else {
                    "X"
                }
            },
            _ => unreachable!("Never here!")   
        };

        let base_points = match you_conv {
            "X" => 1,
            "Y" => 2,
            "Z" => 3,
            _ => unreachable!("Should never happen!")
        };

        let gained = match you {
            "X" => 0,
            "Y" => 3,
            "Z" => 6,
            _ => unreachable!("Should never happen!")
        };

        score += base_points + gained;

        println!("{conv} {you} {base_points} {gained}");
    }

    println!("Final Score: {score}");
}
