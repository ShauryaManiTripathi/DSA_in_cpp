#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

void solve() {
    vector<int> a(5);
    cin >> a[0] >> a[1] >> a[3] >> a[4];
    int max_fib = 0;
    for (int a3 = -300; a3 <= 300; a3++) {
        a[2] = a3;
        int count = 0;
        
        if (a[2] == a[0] + a[1]) {
            count++;
        }
        
        if (a[3] == a[1] + a[2]) {
            count++;
        }
        if (a[4] == a[2] + a[3]) {
            count++;
        }
        
        max_fib = max(max_fib, count);
    }
    
    cout << max_fib << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}