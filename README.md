# Lecture: Practical SAT Solving

Summer Term 2024

## Slides

- [Monday, April 15: Organisation, Introduction, Applications, Encodings, IPASIR](slides/l01-introduction.pdf)
- [Monday, April 22: Tractable Subclasses, Tseitin Encoding, Cardinality Constraints, Finite Domain Encodings](slides/l02-encodings.pdf)
- [Monday, April 29: Local Search, Resolution, DP Algorithm, DPLL Algorithm](slides/l03-algorithms.pdf)
- [Monday, May 6: Branching Heuristics, Restart Strategies, Backtracking, Clause Learning](l04-cdcl.pdf)

## Exercises

- [Tuesday, April 23: Assignment 1: Coloring and Sudoku Competitions, Pythagorean Triples, Tseitin Encoding](exercises/ex1.pdf)

## Code

The `code/src/util` directory contains a CNF file parser that is called when instantiating the class in `CNFFormula.h`, which can also read packed CNF files.
The parser uses `libarchive' (for unpacking CNF files), so to use it you need to **install libarchive** like this:

- For Ubuntu: `apt install libarchive-dev`
- For macOS: `brew install libarchive`

Using the included cmake build script `CMakeLists.txt`, you can build the programs we provide in the `code/` directory as follows:

```
cmake -S code -B code/build
cmake --build code/build
```

This builds the program `code/build/essential` from our last slide in the first lecture.
