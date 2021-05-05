use assert_cmd;
use std::env;

fn setup_command() -> assert_cmd::cmd::Command {
    assert_cmd::Command::cargo_bin("file-has").unwrap()
}

#[test]
fn fails_with_nonexistant_file() {
    setup_command()
        .arg("Great googly moogly!")
        .assert()
        .failure();
}

// Test most basic functionality
#[test]
fn basic_test() {
    let test_vectors = [
        ("a", "a", true),
        ("a", "b", false),
        ("a", "c", false),
        ("a", "ab", false),
        ("a", "ac", false),
        ("b", "a", false),
        ("b", "b", true),
        ("ab", "a", true),
        ("ab", "b", true),
        ("ab", "c", false),
        ("ab", "ab", true),
        ("ab", "ac", false),
        ("bc", "ac", false),
        ("bc", "bc", true),
        ("ac", "bc", false),
        ("ac", "c", true),
        ("ac", "ac", true),
        ("ac", "b", false),
    ];

    env::set_current_dir("samples").unwrap();
    for tv in &test_vectors {
        let assertion = setup_command().arg(tv.0).arg(tv.1).assert();
        if tv.2 {
            assertion.success();
        } else {
            assertion.failure();
        }
    }
    env::set_current_dir("..").unwrap();
}
