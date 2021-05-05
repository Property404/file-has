use anyhow::{anyhow, Result};
use std::fs::File;
use std::io::prelude::*;

fn find_bytes(big: &[u8], small: &[u8]) -> Option<(usize, usize)> {
    if big.len() < small.len() {
        return None;
    }

    for i in 0..big.len() {
        for j in 0..small.len() {
            if i + j >= big.len() || big[i + j] != small[j] {
                break;
            }

            if j == small.len() - 1 {
                return Some((i, i + small.len()));
            }
        }
    }

    None
}

fn get_bytes(path: &str) -> Result<Vec<u8>> {
    let fp = File::open(path);

    match fp {
        Ok(mut fp) => {
            let mut bytes = Vec::new();
            fp.read_to_end(&mut bytes)?;
            Ok(bytes)
        }
        Err(err) => Err(anyhow!("{}: {}", path, err)),
    }
}

pub fn find(big_path: &str, small_paths: &[&str]) -> Result<bool> {
    let big = get_bytes(big_path)?;
    let mut ok = true;

    for small_path in small_paths {
        let small = get_bytes(small_path)?;

        if big.len() < small.len() {
            eprintln!(
                "Warning: '{}'({} bytes) is bigger than '{}'({} bytes)",
                small_path,
                small.len(),
                big_path,
                big.len()
            );
        }

        if let Some((start, end)) = find_bytes(&big, &small) {
            println!("'{}': 0x{:x} - 0x{:x}", small_path, start, end);
        } else {
            println!("'{}': Not found in '{}'", small_path, big_path);
            ok = false;
        }
    }

    Ok(ok)
}
