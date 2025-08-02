#include <bits/stdc++.h>
using namespace std;

// Type definitions
#define ll long long
#define ld long double
#define pii pair<int, int>
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pii>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n;
        cin >> n;
        vector<int> res;
        for (int i = 1; i <= n; i += 2) {
            res.push_back(i);
        }
        int start_even = (n % 2 == 0) ? n : n - 1;
        for (int i = start_even; i >= 2; i -= 2) {
            res.push_back(i);
        }
        for (int i = 0; i < n; ++i) {
            cout << res[i];
            if (i < n - 1) 
                cout << ' ';
        }
        cout << '\n';
    }


int main(int argc, char const *argv[])
{
#ifndef ONLINE_JUDGE
    freopen("/run/media/dekode/back/DSA_in_cpp/input", "r", stdin);
    freopen("/run/media/dekode/back/DSA_in_cpp/output", "w", stdout);
#endif  
    int t;
    cin >> t;  // Read number of test cases
    while (t--) {
        solve();  // Solve each test case
    }

    return 0;
}
