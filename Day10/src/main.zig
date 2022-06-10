const std = @import("std");
const print = std.log.info;
const ArrayList = std.ArrayList;


fn pass_by_val(a : anytype) ArrayList {
    return a;
}

pub fn main() anyerror!void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();
    defer _ = gpa.deinit();
    
    const problem = "1113222113";
    
    var list = std.ArrayList(u8).init(allocator);
    defer list.deinit();
    
    try list.appendSlice(problem);
    
    var temp = std.ArrayList(u8).init(allocator);
    defer temp.deinit();
    
    var i : u8 = 40;
    
    while(i != 0) : ( i -= 1){        
        var counter : u8 = 0;
        var current : u8 = list.items[0]; 
        for (list.items) |c| {
            if(c == current) { counter += 1; }
            else {
                try temp.append(counter + '0');
                try temp.append(current);
                counter = 1;
                current = c;    
            }
        }
        try temp.append(counter + '0');
        try temp.append(current);
        
        list.items.len = 0;
        try list.appendSlice(temp.items);
        temp.items.len = 0;
        
    }
    std.debug.print("{d}\n",.{list.items.len});
}


