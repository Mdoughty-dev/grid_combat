#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(static_cast<unsigned>(time(nullptr)));
    srand(time(0)); 
    int n = 25 + rand() % 500;         
    int H = 1 + rand() % 50;      
    int Hmax = 10 + rand() % 41;       
    int A = 1 + rand() % Hmax;         
    int R = 1 + rand() % Hmax;         // 
    cout << n << " " << H << " " << Hmax << " " << A << " " << R << "\n";
    string pool = "OHE";

    for (int i = 0; i < n; i++)
     {
        for (int j = 0; j < n; j++)
         {
            cout << pool[rand() % 3];
            if (j + 1 < n) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}

