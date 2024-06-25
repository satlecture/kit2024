# Lecture: Practical SAT Solving

Summer Term 2024, Computer Science, Karlsruhe Institute of Technology (KIT)

## Slides

- [Monday, April 15: Organisation, Introduction, Applications, Encodings, IPASIR](slides/l01-introduction.pdf)
- [Monday, April 22: Tractable Subclasses, Tseitin Encoding, Cardinality Constraints, Finite Domain Encodings](slides/l02-encodings.pdf)
- [Monday, April 29: Local Search, Resolution, DP Algorithm, DPLL Algorithm](slides/l03-algorithms.pdf)
- [Monday, May 6: Branching Heuristics, Restart Strategies, Backtracking, Clause Learning](slides/l04-heuristics.pdf)
- [Monday, May 13: Parallel SAT Solving 1: Puzzle nerds analogy, Search space partitioning, Portfolios, Clause sharing, Massively parallel basics](slides/l05-parallelsat.pdf) (slides 1-25)
- [Monday, May 27: Modern SAT Solving 2: Efficient Unit Propagation, Clause Forgetting, VSIDS, Community Structure, Preprocessing](slides/l06-cdcl.pdf)
- [Monday, June 3: Preprocessing: Subsumption, BVE, BCE, Gates](slides/l07-preprocessing.pdf)
- [Monday, June 10: Parallel SAT Solving 2: Mallob(Sat) deep dive and insights on distributed SAT solving](slides/l05-parallelsat.pdf) (slides 25-36 and 49)
- [Monday, June 17: MaxSat](slides/l09-maxsat.pdf)
- [Tuesday, June 18: Planning](slides/l10-planning.pdf)

## Exercises

- [Tuesday, April 23: Assignment 1 (Coloring and Sudoku Competitions, Pythagorean Triples, Tseitin Encoding)](exercises/ex1.pdf)
- [Tuesday, May 7: Assignment 2 (Tetris and Local Search Competitions, Resolution, Hidden Horn)](exercises/ex2.pdf)
- [Tuesday, June 4: Assignment 3 (Hidoku Competition, CDCL, BVE, BCE)](exercises/ex3.pdf)

## Slides and Code used in the Exercises

- [Cumulative Slideset](slides/exercises.pdf)
- Code Example: [SLUR Satisfier](code/src/slursat.cc)
- Code Example: [Trail Class with Propagate and Backtracking](code/src/trail.h)

## Repository

This page is generated from our [repository on GitHub](https://github.com/satlecture/kit2024)

## Code

The `code/src/util` directory contains a CNF file parser that is called when instantiating the class in `CNFFormula.h`, which can also read packed CNF files.
The parser uses `libarchive' (for unpacking CNF files), so to use it you need to **install libarchive** like this:

- For Ubuntu: `apt install libarchive-dev`
- For macOS: `brew install libarchive`

To build the programs from the lecture and exercises, invoke our build script `CMakeLists.txt` as follows:

```
cmake -S code -B code/build
cmake --build code/build
```
