# Sudoku Solver

A high-performance C++ Sudoku solver that handles **9×9, 16×16, and 25×25** grids. Built around a backtracking algorithm optimised with **bitmask constraint tracking** and **Minimum Remaining Values (MRV)** heuristic to dramatically reduce the search space.

---

## How It Works

Vanilla backtracking on large Sudoku grids is slow — for a 25×25, naively checking every row, column, and box for each candidate is expensive. This solver uses two key optimisations to cut that cost down significantly.

### 1. Bitmask Constraint Tracking

Instead of scanning the grid to check whether a number is valid, three bitmasks are maintained — one per row, column, and box. Each bit position corresponds to a number: if bit `k` is set, number `k` is already placed.

```
Example: rowMask[2] = 0001001000100000
                             ^  ^  ^
                            17  9  5   ← already placed in row 2
```

Checking whether a number is safe becomes a single bitwise AND — O(1) instead of O(n).

```cpp
bool isSafe(row, col, num) {
    int bit = (1 << num);
    return !(rowMask[row] & bit) && !(colMask[col] & bit) && !(boxMask[box] & bit);
}
```

### 2. MRV (Minimum Remaining Values) Heuristic

Rather than filling cells left-to-right, top-to-bottom, the solver always picks the **most constrained empty cell** — the one with the fewest valid candidates. This prunes dead-end branches much earlier, which is especially impactful on larger grids.

```
Highly constrained cell (2 options) → try it first
Loosely constrained cell (12 options) → defer until forced
```

The candidate count is computed by OR-ing the three relevant bitmasks and counting unset bits — no inner grid scan required.

---

## Grid Sizes & Encoding

| Grid | Values | Encoding |
|------|--------|----------|
| 9×9  | 1–9    | Digits   |
| 16×16 | 1–16  | 1–9, A–G |
| 25×25 | 1–25  | 1–9, A–P |

The grid size is inferred automatically from the number of input tokens — no configuration needed.

Empty cells are represented as `0`.

---

## Input / Output

Input is read from **stdin** as a flat space/newline-separated sequence of values. The solver writes the completed grid to **stdout**, preserving the letter encoding for values above 9.

**Example — 9×9:**
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
...
```

**Run:**
```bash
g++ -O2 -o sudoku sudoku.cpp
./sudoku < puzzle.txt
```

---

## Performance

The bitmask + MRV combination makes a substantial difference on larger grids. On 25×25 puzzles, which have a search space orders of magnitude larger than 9×9, the solver still returns results in a fraction of a second for well-formed puzzles.

---

## Built With

- C++ (standard library only)
- Bitmask constraint propagation
- MRV heuristic (backtracking optimisation)
