# Illustration how to embed TinyScheme within a C program

TinyScheme is a lightweight Scheme interpreter written by Dimitrios Souflis and Kevin Cozens. Please refer to the [project website](http://tinyscheme.sourceforge.net/home.html) for more detailed information about this specific scheme implementation.

This project is an out of the box illustration how to build the interpreter as a dynamic link library under an Unix operating system (Linux, BSD, Mac OS X).

### Build and Install Shared Library

    $ autoreconf -i
    $ ./configure
    $ make
    $ make install (requires admin credentials)

### Build and Run Sample Application

    $ cd example
    $ autoreconf -i
    $ ./configure
    $ make
    $ ./tsrepl -c

The sample program reads endlessly lines from stdin and evaluates them within a scheme interpreter instance. Alternatively the repl can be started up in server mode by leaving out the option '-c'. Use the following line to connect remotely:

    $ telnet <host-addresse> 37146

2015-09-09, Otto Linnemann
