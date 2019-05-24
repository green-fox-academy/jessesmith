use libc::{c_char};

#[repr(C)]
pub struct LinkedList {
    pub size: i32,
    pub head: *mut Node,
    pub tail: *mut Node,
}

#[repr(C)]
pub struct Node {
    pub data: Data,
    pub next: *mut Node,
}

#[repr(C)]
pub struct Data {
    pub number: f32,
    pub string: *const c_char,
}

#[no_mangle]
pub extern "C" fn size(list : &LinkedList) -> i32 {
    list.size
}
