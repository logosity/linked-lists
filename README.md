# Problem Solution
This project contains two solutions to the problem statement (copied into `./problem.txt` from the email) on in Python and one in C. Both implement the same algorithm described as "Method 2" on this page:
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

The C version (in the `./c` directory), is based on two simple structs and some helper functions (defined in `c/include/list.h`). and c  started off as a C++ version with 

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
