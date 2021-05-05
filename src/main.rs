use std::process::{self};

use clap::{crate_version, App, Arg};

fn main() {
    let matches = App::new("file-has")
        .author("Dagan Martinez")
        .version(crate_version!())
        .about("Check if one binary file contains another")
        .arg(
            Arg::with_name("BIG")
                .help("Containing file")
                .required(true)
                .index(1),
        )
        .arg(
            Arg::with_name("SMALL")
                .help("Contained files")
                .required(true)
                .multiple(true)
                .index(2),
        )
        .get_matches();
    let big = matches.value_of("BIG").unwrap();
    let smalls: Vec<_> = matches.values_of("SMALL").unwrap().collect();

    match file_has::find(big, &smalls) {
        Ok(ok) => process::exit(if ok { 0 } else { 1 }),
        Err(err) => {
            eprintln!("Error: {}", err);
            process::exit(1);
        }
    }
}
