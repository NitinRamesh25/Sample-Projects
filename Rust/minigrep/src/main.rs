use std::process;

use minigrep::CliArgs;

fn main() {
    let args = CliArgs::new().unwrap_or_else(|err| {
        println!("{}", err);
        process::exit(1);
    });

    if let Err(e) = minigrep::read_file(args) {
        println!("Application error: {}", e);
        process::exit(1);
    }
}
