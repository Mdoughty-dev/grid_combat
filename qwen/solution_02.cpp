#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct State {
    int i, j, h;
    State(int i_, int j_, int h_) : i(i_), j(j_), h(h_) {}
};

int main() {
    int n, H_start, H_max, A, R;
    cin >> n >> H_start >> H_max >> A >> R;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // dp[i][j][h] = max enemies defeated to reach (i,j) with health h
    vector<vector<vector<int>>> dp(
        n, vector<vector<int>>(n, vector<int>(H_max + 1, -1))
    );

    // Helper function to update dp safely
    auto update = [&](int i, int j, int h, int val) {
        if (i < 0 || i >= n || j < 0 || j >= n || h < 0 || h > H_max) return;
        if (val > dp[i][j][h]) {
            dp[i][j][h] = val;
        }
    };

    // Process start cell (0,0)
    if (grid[0][0] == 'E') {
        if (H_start < A) {
            cout << -1 << endl;
            return 0;
        }
        int new_h = H_start - A;
        dp[0][0][new_h] = 1;
    } else if (grid[0][0] == 'H') {
        int new_h = min(H_max, H_start + R);
        dp[0][0][new_h] = 0;
    } else { // 'O'
        dp[0][0][H_start] = 0;
    }

    // Iterate in BFS order using queue to handle forced-down moves correctly
    queue<State> q;
    for (int h = 0; h <= H_max; ++h) {
        if (dp[0][0][h] != -1) {
            q.push(State(0, 0, h));
        }
    }

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        int i = cur.i, j = cur.j, h = cur.h;
        int defeated = dp[i][j][h];
        if (defeated == -1) continue;

        // Try moving right
        int ni = i, nj = j + 1;
        if (nj == n) {
            ni = i + 1;
            nj = 0;
        }
        if (ni < n) { // valid move
            int new_h = h;
            int new_defeated = defeated;
            bool valid = true;
            int forced_i = -1, forced_j = -1;

            // Process landing cell (ni, nj)
            if (grid[ni][nj] == 'H') {
                new_h = min(H_max, h + R);
            } else if (grid[ni][nj] == 'E') {
                if (h >= A) {
                    new_h = h - A;
                    new_defeated++;
                } else {
                    // Forced down: simulate moving to (ni+1, nj)
                    forced_i = ni + 1;
                    forced_j = nj;
                    if (forced_i >= n) {
                        valid = false;
                    } else {
                        // Process forced landing cell
                        if (grid[forced_i][forced_j] == 'H') {
                            new_h = min(H_max, h + R);
                        } else if (grid[forced_i][forced_j] == 'E') {
                            if (h >= A) {
                                new_h = h - A;
                                new_defeated++;
                            } else {
                                valid = false;
                            }
                        } // else 'O': h unchanged
                    }
                }
            } // else 'O': h unchanged

            if (valid) {
                int target_i = (forced_i == -1) ? ni : forced_i;
                int target_j = (forced_j == -1) ? nj : forced_j;
                if (dp[target_i][target_j][new_h] < new_defeated) {
                    dp[target_i][target_j][new_h] = new_defeated;
                    q.push(State(target_i, target_j, new_h));
                }
            }
        }

        // Try moving down
        ni = i + 1;
        nj = j;
        if (ni < n) {
            int new_h = h;
            int new_defeated = defeated;
            bool valid = true;
            int forced_i = -1, forced_j = -1;

            // Process landing cell (ni, nj)
            if (grid[ni][nj] == 'H') {
                new_h = min(H_max, h + R);
            } else if (grid[ni][nj] == 'E') {
                if (h >= A) {
                    new_h = h - A;
                    new_defeated++;
                } else {
                    // Forced down: simulate moving to (ni+1, nj)
                    forced_i = ni + 1;
                    forced_j = nj;
                    if (forced_i >= n) {
                        valid = false;
                    } else {
                        // Process forced landing cell
                        if (grid[forced_i][forced_j] == 'H') {
                            new_h = min(H_max, h + R);
                        } else if (grid[forced_i][forced_j] == 'E') {
                            if (h >= A) {
                                new_h = h - A;
                                new_defeated++;
                            } else {
                                valid = false;
                            }
                        } // else 'O': h unchanged
                    }
                }
            } // else 'O': h unchanged

            if (valid) {
                int target_i = (forced_i == -1) ? ni : forced_i;
                int target_j = (forced_j == -1) ? nj : forced_j;
                if (dp[target_i][target_j][new_h] < new_defeated) {
                    dp[target_i][target_j][new_h] = new_defeated;
                    q.push(State(target_i, target_j, new_h));
                }
            }
        }
    }

    int ans = -1;
    for (int h = 0; h <= H_max; ++h) {
        ans = max(ans, dp[n-1][n-1][h]);
    }

    cout << ans << endl;
    return 0;
}
