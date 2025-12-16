#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct State {
    int i, j, h, defeated;
    State(int i_, int j_, int h_, int d_) : i(i_), j(j_), h(h_), defeated(d_) {}
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

    // Process start cell (0,0)
    if (grid[0][0] == 'E') {
        if (H_start < A) {
            cout << -1 << endl;
            return 0;
        }
        int h_after = H_start - A;
        dp[0][0][h_after] = 1;
    } else if (grid[0][0] == 'H') {
        int h_after = min(H_max, H_start + R);
        dp[0][0][h_after] = 0;
    } else { // 'O'
        dp[0][0][H_start] = 0;
    }

    // BFS traversal respecting movement and forced-down rules
    queue<State> q;
    for (int h = 0; h <= H_max; ++h) {
        if (dp[0][0][h] != -1) {
            q.push(State(0, 0, h, dp[0][0][h]));
        }
    }

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        int i = cur.i, j = cur.j, h = cur.h, defeated = cur.defeated;
        if (defeated != dp[i][j][h]) continue;

        // Move right
        int ni = i, nj = j + 1;
        if (nj == n) {
            ni = i + 1;
            nj = 0;
        }
        if (ni < n) {
            int new_h = h;
            int new_defeated = defeated;
            bool valid = true;
            int final_i = ni, final_j = nj;

            // Process cell (ni, nj)
            if (grid[ni][nj] == 'H') {
                new_h = min(H_max, h + R);
            } else if (grid[ni][nj] == 'E') {
                if (h >= A) {
                    new_h = h - A;
                    new_defeated++;
                } else {
                    // Forced down to (ni+1, nj)
                    final_i = ni + 1;
                    final_j = nj;
                    if (final_i >= n) {
                        valid = false;
                    } else {
                        // Process forced landing cell
                        if (grid[final_i][final_j] == 'H') {
                            new_h = min(H_max, h + R);
                        } else if (grid[final_i][final_j] == 'E') {
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

            if (valid && new_h >= 0 && new_h <= H_max) {
                if (dp[final_i][final_j][new_h] < new_defeated) {
                    dp[final_i][final_j][new_h] = new_defeated;
                    q.push(State(final_i, final_j, new_h, new_defeated));
                }
            }
        }

        // Move down
        int di = i + 1, dj = j;
        if (di < n) {
            int new_h = h;
            int new_defeated = defeated;
            bool valid = true;
            int final_i = di, final_j = dj;

            // Process cell (di, dj)
            if (grid[di][dj] == 'H') {
                new_h = min(H_max, h + R);
            } else if (grid[di][dj] == 'E') {
                if (h >= A) {
                    new_h = h - A;
                    new_defeated++;
                } else {
                    // Forced down to (di+1, dj)
                    final_i = di + 1;
                    final_j = dj;
                    if (final_i >= n) {
                        valid = false;
                    } else {
                        // Process forced landing cell
                        if (grid[final_i][final_j] == 'H') {
                            new_h = min(H_max, h + R);
                        } else if (grid[final_i][final_j] == 'E') {
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

            if (valid && new_h >= 0 && new_h <= H_max) {
                if (dp[final_i][final_j][new_h] < new_defeated) {
                    dp[final_i][final_j][new_h] = new_defeated;
                    q.push(State(final_i, final_j, new_h, new_defeated));
                }
            }
        }
    }

    int ans = -1;
    for (int h = 0; h <= H_max; ++h) {
        if (dp[n-1][n-1][h] > ans) {
            ans = dp[n-1][n-1][h];
        }
    }

    cout << ans << endl;
    return 0;
}