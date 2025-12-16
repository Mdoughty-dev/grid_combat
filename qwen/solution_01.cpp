#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct State {
    int row, col, health, defeated;
    State(int r, int c, int h, int d) : row(r), col(c), health(h), defeated(d) {}
};

int main() {
    int n, H_start, H_max, A, R;
    cin >> n >> H_start >> H_max >> A >> R;

    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // dp[i][j][h] = max enemies defeated to reach (i,j) with health h
    // Health can be from 0 to H_max (inclusive)
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(H_max + 1, -1)));

    // Initialize start cell
    int start_health = H_start;
    if (grid[0][0] == 'H') {
        start_health = min(H_max, H_start + R);
    } else if (grid[0][0] == 'E') {
        if (H_start < A) {
            cout << -1 << endl;
            return 0;
        }
        start_health = H_start - A;
    } // else 'O': health remains H_start

    dp[0][0][start_health] = (grid[0][0] == 'E') ? 1 : 0;

    // BFS-like DP: iterate rows top to bottom, columns left to right
    // For each cell, try to come from left or above
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) continue;

            // Try coming from the left: (i, j-1) -> (i, j)
            if (j > 0) {
                for (int h = 0; h <= H_max; h++) {
                    if (dp[i][j-1][h] == -1) continue;

                    int new_health = h;
                    int new_defeated = dp[i][j-1][h];
                    bool valid = true;

                    // Process cell (i,j)
                    if (grid[i][j] == 'H') {
                        new_health = min(H_max, h + R);
                    } else if (grid[i][j] == 'E') {
                        if (h >= A) {
                            new_health = h - A;
                            new_defeated++;
                        } else {
                            // Forced down: move to (i+1, j) instantly
                            if (i + 1 >= n) {
                                valid = false;
                            } else {
                                // Simulate forced down to (i+1, j)
                                int forced_health = h;
                                int forced_defeated = new_defeated;

                                if (grid[i+1][j] == 'H') {
                                    forced_health = min(H_max, h + R);
                                } else if (grid[i+1][j] == 'E') {
                                    if (h >= A) {
                                        forced_health = h - A;
                                        forced_defeated++;
                                    } else {
                                        valid = false;
                                    }
                                } // else 'O': health remains h

                                if (valid) {
                                    // Update dp for (i+1, j)
                                    if (dp[i+1][j][forced_health] < forced_defeated) {
                                        dp[i+1][j][forced_health] = forced_defeated;
                                    }
                                }
                                continue; // skip normal (i,j) update
                            }
                        }
                    } // else 'O': health remains h

                    if (valid) {
                        if (dp[i][j][new_health] < new_defeated) {
                            dp[i][j][new_health] = new_defeated;
                        }
                    }
                }
            }

            // Try coming from above: (i-1, j) -> (i, j)
            if (i > 0) {
                for (int h = 0; h <= H_max; h++) {
                    if (dp[i-1][j][h] == -1) continue;

                    int new_health = h;
                    int new_defeated = dp[i-1][j][h];
                    bool valid = true;

                    // Process cell (i,j)
                    if (grid[i][j] == 'H') {
                        new_health = min(H_max, h + R);
                    } else if (grid[i][j] == 'E') {
                        if (h >= A) {
                            new_health = h - A;
                            new_defeated++;
                        } else {
                            // Forced down: move to (i+1, j) instantly
                            if (i + 1 >= n) {
                                valid = false;
                            } else {
                                // Simulate forced down to (i+1, j)
                                int forced_health = h;
                                int forced_defeated = new_defeated;

                                if (grid[i+1][j] == 'H') {
                                    forced_health = min(H_max, h + R);
                                } else if (grid[i+1][j] == 'E') {
                                    if (h >= A) {
                                        forced_health = h - A;
                                        forced_defeated++;
                                    } else {
                                        valid = false;
                                    }
                                } // else 'O': health remains h

                                if (valid) {
                                    // Update dp for (i+1, j)
                                    if (dp[i+1][j][forced_health] < forced_defeated) {
                                        dp[i+1][j][forced_health] = forced_defeated;
                                    }
                                }
                                continue; // skip normal (i,j) update
                            }
                        }
                    } // else 'O': health remains h

                    if (valid) {
                        if (dp[i][j][new_health] < new_defeated) {
                            dp[i][j][new_health] = new_defeated;
                        }
                    }
                }
            }

            // Try coming from left via wrap: (i-1, n-1) -> (i, 0) when j == 0
            if (j == 0 && i > 0) {
                for (int h = 0; h <= H_max; h++) {
                    if (dp[i-1][n-1][h] == -1) continue;

                    int new_health = h;
                    int new_defeated = dp[i-1][n-1][h];
                    bool valid = true;

                    // Process cell (i,0)
                    if (grid[i][0] == 'H') {
                        new_health = min(H_max, h + R);
                    } else if (grid[i][0] == 'E') {
                        if (h >= A) {
                            new_health = h - A;
                            new_defeated++;
                        } else {
                            // Forced down: move to (i+1, 0) instantly
                            if (i + 1 >= n) {
                                valid = false;
                            } else {
                                // Simulate forced down to (i+1, 0)
                                int forced_health = h;
                                int forced_defeated = new_defeated;

                                if (grid[i+1][0] == 'H') {
                                    forced_health = min(H_max, h + R);
                                } else if (grid[i+1][0] == 'E') {
                                    if (h >= A) {
                                        forced_health = h - A;
                                        forced_defeated++;
                                    } else {
                                        valid = false;
                                    }
                                } // else 'O': health remains h

                                if (valid) {
                                    // Update dp for (i+1, 0)
                                    if (dp[i+1][0][forced_health] < forced_defeated) {
                                        dp[i+1][0][forced_health] = forced_defeated;
                                    }
                                }
                                continue; // skip normal (i,0) update
                            }
                        }
                    } // else 'O': health remains h

                    if (valid) {
                        if (dp[i][0][new_health] < new_defeated) {
                            dp[i][0][new_health] = new_defeated;
                        }
                    }
                }
            }
        }
    }

    // Find max defeated at (n-1, n-1)
    int ans = -1;
    for (int h = 0; h <= H_max; h++) {
        if (dp[n-1][n-1][h] > ans) {
            ans = dp[n-1][n-1][h];
        }
    }

    cout << ans << endl;
    return 0;
}