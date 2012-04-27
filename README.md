# Illustration how to embed TinyScheme within a C program

TinyScheme is a lightweight Scheme interpreter written by Dimitrios Souflis and Kevin Cozens. Please refer to the [project website](http://tinyscheme.sourceforge.net/home.html) for more detailed information about this specific scheme implementation.

This project is an out of the box illustration how to embeded the interpreter in a C application under an Unix operating system (Linux, BSD, Mac OS X).

### Build

    $ ./configure host
    $ make

### Run

    $ ./hello-scheme

The sample program reads endlessly lines from stdin and evaluates them within a scheme interpreter instance. The output is currently not printed so you have to use e.g. (write (+ 1 2)) to get evaluation result printed to standard out.


### Compile the repl of the original distribution (more elabortated repl)

The original version 1.40 of the source code is stored within the directory tinyscheme/src and can be compiled in the following way:

    $ cd tinyscheme/src
    $ make clean
    $ make

Invoke "scheme" for a more elaborated REPL. This source directory provides useful documentation, too.

2012-04-24, Otto Linnemann
