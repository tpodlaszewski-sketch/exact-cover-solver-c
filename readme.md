# Exact Cover Problem Solver (Algorithm X)

A command-line solver for the NP-complete **Exact Cover** problem implemented in **C23**, based on Donald Knuth's **Algorithm X** (recursive depth-first backtracking).

## Overview

Given a collection $\mathcal{P}$ of subsets of a domain $S = \{1, \dots, d\}$, an exact cover is a subcollection $\mathcal{Q} \subseteq \mathcal{P}$ such that every element in $S$ belongs to to exactly one subset in $\mathcal{Q}$. Many combinatorial and constraint satisfaction problems (such as Sudoku, N-Queens, and pentomino tiling) can be reduced to finding an exact cover.

This program reads a character-encoded instance of the exact cover problem along with an output filter, computes all valid solutions using recursive trial-and-error search, and outputs the filtered solution strings.

---

## Input and Output Format

### Input
The input consists of lines of equal length $d$ ($d \le 300$):
1. **Filter line ($F$):** The first line contains only `+` and `-` characters, specifying which columns of the solution should be printed (`+`) and which should be omitted (`-`).
2. **Subset lines ($W_1, \dots, W_n$, where $n \le 200$):** Each subsequent line represents a subset $P_j \in \mathcal{P}$. An underscore (`_`) at index $k$ indicates that element $k \notin P_j$, while any other character indicates that $k \in P_j$ and provides the symbol to be placed at position $k$ in the resulting solution string.

### Output
For every valid exact cover $T \subseteq \{1, \dots, n\}$, the solver constructs a combined string $R$ of length $d$ satisfying:

$$\forall_{1 \le i \le d} \exists_{j \in T} \left( (W_j)_i = R_i \land \forall_{k \in T \setminus \{j\}} (W_k)_i = \text{'\_'} \right)$$

Characters at indices masked by `-` in the filter $F$ are removed from $R$, and each filtered solution is printed on a new line.

---

## Technical Highlights

* **Language Standard:** C23 (`-std=c23 -pedantic`).
* **Algorithm:** Donald Knuth's Algorithm X implemented via recursive backtracking with state pruning on conflicting columns.
* **Memory Safety & Sanitization:** Zero memory leaks verified under Valgrind (`--leak-check=full`), compiled with Undefined Behavior Sanitizer (`-fsanitize=undefined`) and stack protection (`-fstack-protector-strong`).

---

## Compilation and Usage

### Prerequisites
* **GCC** (with C23 support)
* **Valgrind** (optional, for memory verification)

### Building the Project

Compile the program with strict warning and sanitizer flags:

```bash
gcc -std=c23 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond \
    -Wfloat-equal -Wshadow -Wconversion -Wjump-misses-init \
    -Wlogical-not-parentheses -Wnull-dereference -Wvla -Werror \
    -fstack-protector-strong -fsanitize=undefined -fno-sanitize-recover \
    -g -fno-omit-frame-pointer -O1 main.c -o exact_cover