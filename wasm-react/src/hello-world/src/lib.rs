use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub fn get_age() -> i32 {
    24
}

#[wasm_bindgen]
pub fn say_hello() -> String {
    "hello from rust".to_string()
}