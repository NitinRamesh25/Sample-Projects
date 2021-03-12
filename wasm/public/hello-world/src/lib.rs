use js_sys;
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub fn say_hello() -> js_sys::JsString {
    return "hello world".into();
}

#[wasm_bindgen]
pub fn get_age() -> i32 {
    return 25;
}
