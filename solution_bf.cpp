#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, Hstart, Hcap, A, R;
vector<vector<char>> grid;
int maxEnemies = -1;

void dfs(int i, int j, int health, int defeated) {
    if (i < 0 || j < 0 || i >= n || j >= n) return;

    char cell = grid[i][j];

    // Process current cell upon entering
    if (cell == 'H') {
        health = min(health + R, Hcap);
    } else if (cell == 'E') {
        if (health >= A) {
            health -= A;
            defeated++;
        } else {
            // Forced down to (i+1, j)
            int fi = i + 1, fj = j;
            if (fi >= n) return; // forced out of grid -> invalid

            char fc = grid[fi][fj];
            if (fc == 'H') {
                int fh = min(health + R, Hcap);
                dfs(fi, fj, fh, defeated);
                return;
            } else if (fc == 'E') {
                if (health < A) return; // can't defeat landing enemy -> invalid
                int fh = health - A;
                dfs(fi, fj, fh, defeated + 1);
                return;
            } else {
                // open cell 'O'
                dfs(fi, fj, health, defeated);
                return;
            }
        }
    }

    // If reached goal cell after processing
    if (i == n - 1 && j == n - 1) {
        maxEnemies = max(maxEnemies, defeated);
        return;
    }

    // Move down
    if (i + 1 < n) dfs(i + 1, j, health, defeated);

    // Move right (with wrapping to next row start)
    int ri = i;
    int rj = j + 1;
    if (rj >= n) { ri = i + 1; rj = 0; }
    if (ri < n) dfs(ri, rj, health, defeated);
}

int main() {
    cin >> n >> Hstart >> Hcap >> A >> R;
    grid.assign(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> grid[i][j];

    int H0 = min(Hstart, Hcap);
    // If starting cell is an enemy and we don't have enough health to fight,
    // the run is invalid (there is no prior move to force us down).
    if (grid[0][0] == 'E' && H0 < A) {
        cout << -1 << "\n";
        return 0;
    }

    dfs(0, 0, H0, 0);
    cout << (maxEnemies == -1 ? -1 : maxEnemies) << "\n";
    return 0;
}