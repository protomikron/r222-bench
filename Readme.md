# Overview

This repository explores different implementations of a brute-force based solver
for the 2x2x2 cube problem by enumerating all (3674160) configurations.

# Problem

The problem is described (https://github.com/protomikron/r222-bench)[here] and
currently there are implementations for

- Python3: r222.py
- C: r222.c
- Haskell: r222.hs
- Java: r222.java

Currently a configuration is encoded by storing all 6 * 4 == 24 faces.

# Build

Obviously you need the required language runtimes and compilers to run their
implementations - the following is tested on Ubuntu 16.04 and uses the classic
packaged versions:

    $ sudo apt-get install --yes ghc gcc python3 openjdk-9-jdk

After all requirements are satisfied, the following should work:

    $ make all

If you want to just build 1 language use the default source file extension:

    $ make hs

This will e.g. just build the Haskell implementation.

# Comments

## C

The C implementation uses a custom (unbalanced) binary tree and pre-allocates
memory before generating the game-tree. This is save as we can estimate the
memory requirements as we know all configurations and their minimal path length
(number of operations/half-moves) but could be interpreted as cheating as this
number is non-trivial to estimate without doing a prior run.

## Python3

This version should be very idiomatic and uses a simple dictionary.

## Haskell

The Haskell version uses a standard Map (`Strict` did not provide much better
results) and encodes a state in a ByteString. It is estimated that the `move`
function is a slow offender as on one hand `pack` is considered performance
sensitive and the List approach seems sub-optimal.

We also tested a version using pattern matching in the `move` function, however
this seemed to only work on Strings which were considerably slower than the
current ByteString implementation. Maybe improving the function

    move :: Config -> Op -> Config
    move cfg = pack . L.map (index cfg) . (ops!!)

would yield better results. In particular the current

    ByteString -> String -> ByteString

flow seems suspicious.

## Java

Similar to the Python3 version this implementation is straight-forward using
classic standard library data structures.

# Results

The tests were ran 5 times for every language with the following results:

    running hs [0] took 68.742317331 seconds
    running hs [1] took 69.021808699 seconds
    running hs [2] took 68.411426872 seconds
    running hs [3] took 68.851658527 seconds
    running hs [4] took 68.327745131 seconds
    running c [0] took 12.455148793 seconds
    running c [1] took 12.482969476 seconds
    running c [2] took 12.482962341 seconds
    running c [3] took 12.407298387 seconds
    running c [4] took 12.439827506 seconds
    running java [0] took 20.809336745 seconds
    running java [1] took 20.957757512 seconds
    running java [2] took 20.520265113 seconds
    running java [3] took 21.089419275 seconds
    running java [4] took 21.160947818 seconds
    running py [0] took 50.987568921 seconds
    running py [1] took 50.801845374 seconds
    running py [2] took 49.428210441 seconds
    running py [3] took 50.392358343 seconds
    running py [4] took 50.269593729 seconds

The machine had the following capabilities

- CPU: i5-2500K CPU @ 3.30GHz
- MEM: 16G

and runtimes:

- Linux: 4.10.0-33-generic
- GCC: gcc (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609
- Python3: Python 3.5.2
- Haskell: The Glorious Glasgow Haskell Compilation System, version 7.10.3
- Java: openjdk version "9-internal"

This Java version seems pretty weird btw. :) If you want to run the tests
yourself simply run:

    $ make bench

This may take some time.

# FAQ:

Q: Why?
A: Why not? But seriously the idea is to explore different strategies to build
   game trees in different languages.

# License

GPLv3
