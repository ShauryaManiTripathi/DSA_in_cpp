#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 998244353;
using ll = long long;
 
ll solve_puzzle(int n, vector<int>& a) {
    vector<vector<ll>> curr(2, vector<ll>(n + 1));
    vector<vector<ll>> next(2, vector<ll>(n + 1));
    curr[0][0] = 1;
    
    for (int pos = 0; pos < n; pos++) {
        next[0].assign(n + 1, 0);
        next[1].assign(n + 1, 0);
        
        for (int prev_liar = 0; prev_liar < 2; prev_liar++) {
            for (int left_liars = 0; left_liars <= pos; left_liars++) {
                if (curr[prev_liar][left_liars] == 0) continue;
                
                ll ways = curr[prev_liar][left_liars];
                if (left_liars == a[pos]) {
                    next[0][left_liars] = (next[0][left_liars] + ways) % MOD;
                }
                if (prev_liar == 0) {
                    next[1][left_liars + 1] = (next[1][left_liars + 1] + ways) % MOD;
                }
            }
        }
        
        curr.swap(next);
    }
    
    // Sum all valid configurations
    ll result = 0;
    for (int is_liar = 0; is_liar < 2; is_liar++) {
        for (int liars = 0; liars <= n; liars++) {
            result = (result + curr[is_liar][liars]) % MOD;
        }
    }
    
    return result;
}
 
int main() {
#ifndef ONLINE_JUDGE
    freopen("/home/shaurya/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/shaurya/Desktop/DSA_in_cpp/output", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << solve_puzzle(n, a) << '\n';
    }
    
    return 0;
}