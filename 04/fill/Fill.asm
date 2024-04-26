// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

@start
M = 0

(LOOP)
    @KBD
    D = M

    @CLEAR 
    D;JEQ // jump if RAM[keyboard] == 0

    @FILL
    0;JMP // jump 

(CLEAR)
    @start
    D = M 
    @LOOP
    D;JLT
    @start
    D = M 
    @SCREEN
    A = A+D
    M = 0
    @start
    M = M-1
    @LOOP
    0;JMP

(FILL)
    @start
    D = M 
    @8192 // Max 8192
    D = D-A 
    @LOOP 
    D;JGE
    @start
    D = M 
    @SCREEN 
    A = A+D
    M = -1
    @start
    M = M+1
    @LOOP 
    0;JMP 

(END)
    @END
    0;JMP