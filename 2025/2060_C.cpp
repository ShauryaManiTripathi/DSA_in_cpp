#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> freq(n + 1, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }
    int max_pairs = 0;
    if (k % 2 == 0 && k/2 <= n) {
        max_pairs += freq[k/2] / 2;
        freq[k/2] %= 2;
    }
    for (int i = 1; i <= min(k-1, n); i++) {
        if (k-i <= n && i < k-i) {
            int pairs = min(freq[i], freq[k-i]);
            max_pairs += pairs;
            freq[i] -= pairs;
            freq[k-i] -= pairs;
        }
    }
    
    cout<< max_pairs<<endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("/home/shaurya/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/shaurya/Desktop/DSA_in_cpp/output", "w", stdout);
#endif

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}