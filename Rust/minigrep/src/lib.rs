use std::{env, error::Error, fs};

pub struct CliArgs {
    query: String,
    file_name: String,
}

impl CliArgs {
    pub fn new() -> Result<CliArgs, &'static str> {
        let args: Vec<String> = env::args().collect();

        if args.len() != 3 {
            return Err("Insufficient arguments");
        }

        let query = args[1].clone();
        let file_name = args[2].clone();

        Ok(CliArgs { query, file_name })
    }
}

pub fn read_file(cli_args: CliArgs) -> Result<(), Box<dyn Error>> {
    let file_data = fs::read_to_string(cli_args.file_name)?;

    for line in search(&cli_args.query, &file_data) {
        println!("{}", line);
    }

    Ok(())
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();

    for line in contents.lines() {
        if line.contains(query) {
            results.push(line.trim());
        }
    }

    results
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
        Rust:
        safe, fast, productive.
        Pick three.
        ";

        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }
}
