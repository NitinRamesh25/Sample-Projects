use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub fn say_hello() -> String {
    "hello from rust".to_string()
}
