const std = @import("std");
const print = std.debug.print;

fn is_valid(pass: [8]u8) bool {
    for(pass) |c|{
        if( c == 'l' or c == 'o' or c == 'i'){ return false; }
    }

    var curr :u8 = pass[0];
    var count :u8 = 1;
    
    var doubl_count :u8 = 0;
    
    var incrementing: bool = for(pass) |c,i| {
        if(i == 0){ continue; }
        if(c == curr + 1) {
            count += 1;
            curr = c;
        }
        else {
            count = 1;
            curr = c;
        }
        if(count == 3)      { break true; }
    }
    else false;
    
    var i :u8 = 1;
    curr = pass[0];
    var doubles: bool = while(i < 8) {
        if(pass[i-1] == pass[i]){ doubl_count += 1; i += 2; }
        else { i += 1; }
        if(doubl_count == 2) { break true; }
    }
    else false; 
    
    if(!incrementing or !doubles) return false;
    return true;
}

fn increment(pass: *[8]u8,n : u8) void {
    if(pass[n] == 'z'){
        pass[n] = 'a';
        increment(pass,n-1);
    }
    else{
        const t = pass[n] + 1;
        if( t == 'l' or t == 'o' or t == 'i'){ pass[n] += 2; }
        else{ pass[n] = t; }
    }
}


pub fn main() anyerror!void {
    const problem = "hxbxxyzz";
    var password : [8]u8 = problem.*;
    increment(&password,7);
    while(!is_valid(password)){ increment(&password,7); }
    print("{s}",.{password});
}

