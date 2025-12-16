# idea.md — how the idea evolved

### Initial concept
Classic grid DP problem: move right/down to maximize a metric, here the number of enemies defeated, while managing a resource (health).

### Core twist: forced-downward rule
- Entering an enemy `E` requires health ≥ A to defeat it.  
- If health < A, the player is **forced to move down one cell** `(i+1,j)` if possible.  
- The landing cell is processed normally (`O`, `H`, or `E`).  
  - If the landing cell is an enemy and still cannot be defeated, the path is invalid.  
  - If the forced-down move would go outside the grid (bottom row), the path is invalid.  
- This creates path-dependent constraints: taking a health pickup early can unlock future fights that would otherwise be impossible.

### Start cell edge case
- If `(0,0)` is an enemy `E` and starting health `H < A`, the path is immediately invalid.  
- This matches the problem statement and ensures the starting scenario is handled consistently.

### Rejected variants
- Random enemy strengths → complicates testing; a single global A is sufficient.  
- Optional downward movement → reduces the strategic tension; forced movement is cleaner.  
- Multi-step forced fall → overly punishing; limiting to one row produces interesting constraints without cascading complexity.

### Final formulation rationale
- Fixed enemy strength `A` → keeps input compact and predictable.  
- Health pickups restore `R` with a cap at `Hcap` → simple arithmetic, no per-cell metadata.  
- Single-row forced-down → introduces tension without unbounded cascading.  

This combination produces a search-friendly but nontrivial problem: maximize enemies defeated under constrained movement, local resource thresholds, and the forced-down mechanic.

