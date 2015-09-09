# Illustration how to embed TinyScheme within a C program

TinyScheme is a lightweight Scheme interpreter written by Dimitrios Souflis and Kevin Cozens. Please refer to the [project website](http://tinyscheme.sourceforge.net/home.html) for more detailed information about this specific scheme implementation.

This project is an out of the box illustration how to build the interpreter as a dynamic link library under an Unix operating system (Linux, BSD, Mac OS X).

### Build

    $ autoreconf -i
    $ ./configure
    $ make
    $ optional: make install (requires admin credentials)

### Run

    $ ./scheme

The sample program reads endlessly lines from stdin and evaluates them within a scheme interpreter instance. The output is currently not printed so you have to use e.g. (write (+ 1 2)) to get evaluation result printed to standard out.

2015-09-09, Otto Linnemann
