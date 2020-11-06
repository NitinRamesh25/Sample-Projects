use rand::Rng;
use std::cmp::Ordering;
use std::io;

fn main() {
    println!("Welcome to guessing game");

    let secret_number = rand::thread_rng().gen_range(1, 101);

    loop {
        println!("Please enter a number");

        let mut guess = String::new();

        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read user input");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("you have guessed: {}", guess);

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small"),
            Ordering::Equal => {
                println!("You guessed correctly!");
                break;
            }
            Ordering::Greater => println!("Too big"),
        }
    }
}
