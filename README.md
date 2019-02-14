# Linked-Lists implementation

This repo contains the solution to a simple linked list problem that I was asked to solve a while back. I find it a nice example of showing how to implement a given algorithim in two different languages (in this case C and Python). It also is a cool example of a few other things:

* Using C++ to test C (in order to take advantage of features in the excellent testing tool [Catch2](https://github.com/catchorg/Catch2).
* Why C is still a good choice over C++ at times (in this case, when considering how to implement a correct&mdash;and idiomatic&mdash;C++ 11 version, I found myself considering ever deeper questions like: "Does this require move semantics?", "What operators should be overloaded/implemented?" And a host of other things that are overkill for such a small problem.
* How a paradigm follows a language (i.e. the Python version is OO, while the C version is much more 'functional').
* A simple CMake implementation I can refer to (I was just learning how to use it when this code was written, so it makes for a good basic example).
* A simple example of using `entr` and `make` as a continuous testing implementation (in the python version)&mdash;something I really like because it's a language-indepdent way of providing such functionality to my projects.

# Problem

This is the original problem statement that the code in this repo is intended to solve:

<blockquote>
Solve this in python and C/C++. Correctness is the most important, effeciency is important but secondary.

You have a linked list that contains both a string and a pointer (C++) or a reference (Python) to 
a random element in the list.

Let's say we have the following list:

{{"Test1", ref=element_3}, {"Test2", ref=element_1}, {"Test3", ref=element_1}, {"Test4", ref=element_0}}

Note: multiple randoms can point to the same element, it's not guaranteed to be 1:1

What you need to do is make a deep copy of the list. The new list must be its own entity 
(i.e. not simply reference the first list), and the randoms must follow through, so 
if element 0's random references element 3, copy0's random reference must reference copy3.

There's two different cases of optimization here: one is processing time; this is very easy to 
solve in O(n^2), but harder to go more efficient. The other is memory: it's easy to use many temporary 
variables, but harder to use less temporary memory.
</blockquote>

# Problem Solution
This project contains two solutions to the above-referenced problem statement&mdash;one in Python and one in C. Both implement the same algorithm described as "Method 2" on this page:
https://www.tutorialcup.com/linked-list/clone-linked-list-next-random-pointer.htm

The algorithm copies a linked list with random ref links in time O(n) and constant space.

## Python
The python version (in the `./python` directory), takes an Object-Oriented approach, including the implementation of the "Sequence" interface (i.e. `__getitem__` and `__len__`) for ease of reading the tests and iteration. The tests are written using the `unittest` and the  `sure` library which adds some "matcher" syntactic-sugar.

### Install Requirements

* Python 3.6
* `pipenv`
* GNU `make` (probably any make will do)
* `entr` (just for the autotesting command)

### Installation
(I'm running Ubuntu 16.04 on my workstation)

I tested this on a clean EC2 instance (micro) running ubuntu 16.04, so I had to jump through some hoops on a clean box to get python3.6 working. On my workstation I use pyenv, but here's what I did on the test box. I also expect that the solution would work with python 3.5 (and possibly even 2.7) but I didn't try that:

* sudo add-apt-repository ppa:deadsnakes/ppa
* sudo apt-get update
* sudo apt-get install entr #optional
* sudo apt-get install python3.6
* sudo apt install python3-venv python3-pip
* python3.6 -m pip install --user pipenv
* pipenv install --dev


### Running tests

The tests can be run once by simply typing `make test` or run continuously via `find . -name '*.py' | entr -c make test` in the `./python` diretory.

### Running Code
A simple "main" is available to use the list, it can be run via `python main.py` in the './python' directory.

## C

The C version (in the `./c` directory), is based on two simple structs and some helper functions (defined in `c/include/list.h`).

### Install Requirements

* `cmake` > 3.5.1 
* `valgrind`
* `entr` (just for the `autotest` script)

### Installation
(again on clean ubuntu 16.04 box)

* sudo apt-get install cmake
* sudo apt-get install valgrind
* sudo apt-get install entr #optional
* `mkdir ./c/build
* `cd ./c/build && cmake ..`

### Running Tests

The tests are written using Catch2 (i.e in C++). Then can be run either via `make spec && ./spec` (in the `./c/build` directory) or using the `./autotest` script (which compiles and runs the tests on each file change).


### Running Code

A simple `main` program can be built and run via `make main && ./main` in the `./c/build` directory.
