# earfuck
A brainfuck interpreter that outputs sound.

# usage
Using the interpreter is easy. Just build the application with a C++ compiler (C++11 support **required**, C++14 **recommended**): 

    $ c++ --std=c++14 -Wall -Wextra -Werror core.cpp memory.cpp program.cpp -o bfinterpreter

Then simply run the application like so:

    $ ./bfinterpreter [options] instructions [stdin]

**Note that you should be wrapping the instructions and stdin with quotation marks to avoid accidentally entering a pipe.**

`instructions` is a required argument. Leave `stdin` empty if you have no stdin for the brainfuck program.

The currently viable options are:

- `-i` or `--instruction-file` &mdash; tells the program that `instructions` is a path leading to the file containing the brainfuck instructions.
- `-s` or `--stdin-file` &mdash; tells the program that `stdin` is a path leading to the file containing the brainfuck instructions.

Options can be added in any order, but the order of `instructions` and `stdin` is constant.

# TODO:

1. ...get the base interpreter working ✓
2. Add support for reading programs from files ✓
3. Adjust base interpreter to output to POSIX/WINAPI Beep() function
4. Utilize MIDI library or other sound engine to output sounds (perhaps even different timbres?)

# License
This entire project is licensed under the MIT License, a copy of which has been provided in the repository's root directory.
This is to provide you with more freedom to do what you want with the source, but *please* consider the community and contributing back when forking this project
