#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, Hstart, Hcap, A, R;
vector<vector<char>> grid;
struct State { int i,j,h,defeated; };

int solve()
{
    int H0 = min(Hstart, Hcap);
    vector<vector<vector<int>>> best(n, vector<vector<int>>(n, vector<int>(Hcap+1, -1)));
    queue<State> q;
    int init_h = H0, init_def = 0;
    char sc = grid[0][0];
    if (sc == 'H') init_h = min(Hcap, init_h + R);
    else if (sc == 'E')
    {
        if (init_h < A) 
            return -1;
        init_h -= A; init_def = 1;
    }

    best[0][0][init_h] = init_def;
    q.push({0,0,init_h,init_def});
    int ans = -1;
    while(!q.empty())
    {
        auto s = q.front(); q.pop();
        int i=s.i, j=s.j, h=s.h, d=s.defeated;
        if (i==n-1 && j==n-1)
        { 
            ans = max(ans, d); 
            continue; 
        }
        int ri=i, rj=j+1;
        if (rj>=n)
        { 
            ri = i+1;
            rj = 0; 
        }
        if (ri < n)
        {
            int nh=h, nd=d;
            char c = grid[ri][rj];
            if (c=='H') 
                nh = min(Hcap, nh + R);
            else if (c=='E')
            {
                if (nh >= A)
                { 
                    nh -= A;
                    nd++; 
                }
                else 
                {
                    int fi = ri+1, fj = rj;
                    if (fi >= n)
                     { 
                         nh = -1; 
                    }
                    else
                    {
                        int fh = h, fd = d;
                        char fc = grid[fi][fj];
                        if (fc=='H') 
                            fh = min(Hcap, fh + R);
                        else if (fc=='E')
                        {
                            if (fh < A) 
                                fh = -1; 
                            else 
                            { 
                                fh -= A;
                                fd++; 
                            }
                        }
                        if (fh>=0 && best[fi][fj][fh] < fd)
                        { 
                            best[fi][fj][fh] = fd;
                            q.push({fi,fj,fh,fd});
                        }
                    }
                    nh = -1; 
                }
            }
            if (nh>=0 && best[ri][rj][nh] < nd)
            { 
                best[ri][rj][nh] = nd; 
                q.push({ri,rj,nh,nd}); 
            }
        }

        
        int di = i+1, dj = j;
        if (di < n)
        {
            int nh=h, nd=d;
            char c = grid[di][dj];
            if (c=='H')
                nh = min(Hcap, nh + R);
            else if (c=='E')
            {
                if (nh >= A){ nh -= A; nd++; }
                else 
                { 
                    nh = -1;
                }
            }
            if (nh>=0 && best[di][dj][nh] < nd)
            { 
                best[di][dj][nh] = nd;
                q.push({di,dj,nh,nd}); 
            }
        }
    }

    return ans;
}

int main(){
    cin >> n >> Hstart >> Hcap >> A >> R;
    grid.assign(n, vector<char>(n));
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) cin >> grid[i][j];
    cout << solve() << "\n";
    return 0;
}