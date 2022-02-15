import nico
import std/strutils

const COUNTER_SPEED = 0.05
const PART2 = false

when PART2:
    var grid : array[1000,array[1000,uint8]]
else:
    var grid : array[1000,array[1000,bool]]

var
    input = open("input")
    eof = false
    res = 0'u
    counter = 0.0

type Instruction = enum ON,OFF,TOGGLE

proc get_nums(input: string, ins : var Instruction,o: var array[4, uint]) = # because scanf kinda sucks, because it can't read string with space in it, imma do it my own way 
    var
        turn : bool = false
        arr_idx = 0
    for i,word in input.split({' ',','}).pairs():
        if word == "turn" and i == 0:
            turn = true
            continue
        elif i == 0: ins = TOGGLE;continue
        
        if turn:
            ins = if word == "on": ON else: OFF
            turn = false
        
        if i >= (if ins == TOGGLE: 1 else: 2) and word != "through":
            o[arr_idx] = parseUInt(word)
            inc arr_idx
            
proc turn_lights(ins : Instruction, val : array[4,uint]) = 
    when PART2:
        for y in val[1]..val[3]:
            for x in val[0]..val[2]:
                if   ins == ON:  grid[y][x] += 1
                elif ins == OFF: grid[y][x] = (if grid[y][x] >= 1: grid[y][x] - 1 else: 0)  
                else:            grid[y][x] += 2
    else:
        for y in val[1]..val[3]:
            for x in val[0]..val[2]:
                if   ins == ON:  grid[y][x] = true
                elif ins == OFF: grid[y][x] = false
                else:            grid[y][x] = not grid[y][x]

proc get_result() : uint = 
    for y in 0..999:
        for x in 0..999:
            when PART2:
                result += grid[y][x]
            else:
                result += (if grid[y][x]: 1 else: 0)
            
             
proc gameInit() = 
    setPalette(loadPalettePico8())


proc gameUpdate(dt: float32) =
    if not eof:
        if counter >= COUNTER_SPEED:
            counter = 0
            var line = input.readLine()
            if line == "":
                eof = true
                res = get_result()
            else:
                var values : array[4,uint]
                var ins : Instruction
                get_nums(line,ins,values)
                turn_lights(ins,values)
        
        counter += dt


proc gameDraw() = 
    cls()
    when PART2:
        for y in 0..999:
            for x in 0..999:
                let brightness = grid[y][x]
                if  brightness == 0: setColor(6)
                elif brightness == 1: setColor(15)
                elif brightness == 2: setColor(9)
                else: setColor(10)
                pset(x,y)
    else:
        for y in 0..999:
            for x in 0..999:
                if not grid[y][x]: setColor(6)
                else: setColor(10)
                pset(x,y)
    if eof:
        setColor(2)
        print("RESULT: " & $res,470,800)

nico.init("gerwy","advent-visual")

fixedSize(true)
integerScale(true)

nico.createWindow("Day 6", 1000,1000,1)
nico.run(gameInit,gameUpdate,gameDraw)

