Mojave-ASM
-

An assembly-like language VM

Mojave-ASM is basically just a little learning project for me to learn how to make a language in C++.
I made this following a tutorial on YouTube(https://www.youtube.com/watch?v=qJ0-pHmDiT4).

Using Mojave-ASM:
* Clone the repository into a folder.
* Use Visual Studio to open the .sln file, compile the project in Debug mode with a C++ language standard 20
* Run the following in the terminal, in the x64>Debug directory
`mojave-asm -rb -bytecode -file <your script file>`

Coding in it
-

This language depends on instructions, and there are current 6 of them:
* push #n
* add
* sub
* mul
* put
* hlt

push #n:
	Pushes the number (ex; '#3') to the stack

add:
	Pops two numbers off the top of the stack, adds them, then pushes them to the top of the stack

sub, mul:
	Same as add, but substracts or multiplies the numbers instead

put:
	Prints to number to the output, prefixed by "printreq"

hlt:
	Ends the program and prints whatever is at the top of the stack, prefixed by "Return code"

Example code - add 3 and 2, then multiply by 5, and halt the program.

```
push #5
push #2
push #3

add
mul

hlt
```