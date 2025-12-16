Solution Explanation

Problem Overview
----------------
We are given an n × n grid representing a path that a hero must travel from the top-left corner (0,0) to the bottom-right corner (n−1, n−1).

Each cell can contain:
- 'E' → Enemy
- 'H' → Healing spot
- '.' → Empty space

The hero has some health (H), which changes depending on what’s in each cell.

The goal is to find the maximum number of enemies the hero can defeat while still surviving and reaching the end of the grid.

If it’s impossible to reach the end, the program should output -1.


Input
-----
n        — grid size
Hstart   — starting health
Hcap     — maximum health
A        — damage taken per enemy
R        — health restored on healing cells
grid     — n lines of n characters ('E', 'H', or '.')


Output
------
Maximum number of enemies defeated, or -1 if impossible.


Algorithm Overview
------------------
The solution uses Breadth-First Search (BFS) with Dynamic Programming (DP).

BFS explores all possible paths (right and down).
DP keeps track of the best result (most enemies defeated) for each position and health state.


State Definition
----------------
Each state is represented by:

struct State { int i, j, h, defeated; };

Where:
i, j = current position
h = current health
defeated = enemies defeated so far

We also maintain a DP array:

best[i][j][h] = maximum enemies defeated at (i, j) with h health


Initialization
--------------
1. Start at (0, 0) with:
   health = min(Hstart, Hcap)
   defeated = 0

2. Apply the effect of the first cell:
   - 'H': heal by R (not above Hcap)
   - 'E': lose A health (if possible) and increment defeated

3. Push this initial state into the BFS queue.


BFS Exploration
---------------
At each step, the hero can move:
- Right → (i, j + 1)
- Down → (i + 1, j)

For each new cell:
1. Copy the current state.
2. Apply the effect of the new cell:
   - 'H': heal by R (up to Hcap)
   - 'E': if health ≥ A, fight (lose A health, defeated++). Otherwise, can’t continue.
3. If this new state gives more enemies defeated than any previously known result for (i, j, h), push it into the queue.


Ending Condition
----------------
Every time the BFS reaches (n−1, n−1), record the number of enemies defeated:
ans = max(ans, defeated)

If BFS finishes without reaching the end, output -1.


Complexity
----------
Time Complexity:  O(n² * Hcap)
Each (cell, health) pair is processed once.

Space Complexity: O(n² * Hcap)
For storing best results per state.


Example
-------
Input:
3 5 10 3 4
. E H
E . E
H H .

Walkthrough:
Step | Cell | Action         | Health | Enemies
1    | (0,0)| .              | 5      | 0
2    | (1,0)| E (fight)      | 2      | 1
3    | (2,0)| H (heal)       | 6      | 1
4    | (2,1)| H (heal)       | 10     | 1
5    | (2,2)| .              | 10     | 1

Output:
1


Summary
-------
Algorithm: BFS + DP
Goal: Maximize enemies defeated
Moves: Right, Down
States: (i, j, health, defeated)
Cell Effects: 'E' = −A HP, 'H' = +R HP
Output: Maximum enemies defeated or -1


Conclusion
----------
This program efficiently explores all valid paths through the grid using BFS with state tracking.
By recording the best outcomes per (position, health) pair, it finds the path that defeats the most enemies while still surviving to the end.
