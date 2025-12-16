# Grid Combat Optimization

## Problem statement

You are given an `n x n` grid. Each cell contains one of three characters:
- `O` — open, nothing happens.
- `H` — health pickup: when entered the player gains `R` health (capped at `H_max`).
- `E` — enemy: when entered the player may attempt to fight.

The player starts at the top-left cell `(0,0)` and must reach the bottom-right cell `(n-1,n-1)` by repeatedly moving **right** or **down**. Moving right from the last column of a row wraps to the first column of the next row (i.e., a right move from `(i,n-1)` goes to `(i+1,0)`). The player begins with `Hstart` health (an integer, `0 ≤ Hstart
 ≤ Hcap`), where the input gives the starting health `Hstart` and a global health cap `H_cap` (with `Hstart ≤ H_cap`). Every enemy in the grid has the same fixed attack value `A` (a positive integer). Every health pickup restores exactly `R` health (integer, `R ≥ 0`), but the player's health cannot exceed `H_max`.

**Combat rule (forced-downward rule):**
- If the player moves into a cell with an enemy `E` and currently has health `≥ A`, the player defeats that enemy and loses `A` health.
- If the player moves into a cell with an enemy `E` and currently has health `< A`, the player **cannot** fight and is **immediately forced to move down one cell** (i.e., to `(i+1, j)`) if such a cell exists. That forced downward move happens instantly and does **not** consume an extra move beyond the downward step. The forced-down rule applies regardless of how the player arrived at the enemy cell (including after a right move that wrapped to the next row). If the forced-down cell is also an enemy and the player still does not have `≥ A` health, the run dies (invalid path). If the forced-down move would go outside the grid (i.e., you were on the last row), the run dies.

Your task: among all valid paths from `(0,0)` to `(n-1,n-1)` that respect movement and the forced-down rule, compute the **maximum number of enemies defeated**. If there is no valid path, print `-1`.

### Input format
n Hstart Hcap A R (next n lines) each line has n characters from {O,H,E}
- `1 ≤ n ≤ 500`
- `0 ≤ Hstart ≤ Hcap ≤ 5000`
- `1 ≤ A ≤ 5000`
- `0 ≤ R ≤ 5000`

### Output
A single integer: the maximum number of enemies defeated along a valid path, or `-1` if no valid path exists.

### Notes
- Health pickups are applied **when** the player enters their cell (including at the starting cell if it is `H`). Health is capped at `Hcap` after each pickup.
- When forced down from an enemy the landing cell is processed normally (it may be `O`, `H`, or `E`). If the landing cell is an `E` and still not fightable, the path is invalid.
-- The starting cell `(0,0)` is a special case: if it contains an enemy `E` and the player's starting health `Hstart < A`, the path is considered immediately invalid (there is no prior move that can produce a forced-down transition before entering the start), and the correct output is `-1`.

### Example
Input: 3 5 10 4 3 O E O H E H O O E
Output: 2

Explanation (one optimal path): Start (0,0) with 5 HP. Right to (0,1) is E and 5≥4 so defeat (HP→1, enemies=1). Right to (0,2) O. Down to (1,2) H (HP→4). Down to (2,2) E with HP=4≥4 defeat (HP→0, enemies=2). Reached end.
