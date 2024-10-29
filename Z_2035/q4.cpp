#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

// Helper function to count trailing zeros in binary representation
int countTrailingZeros(int num) {
    int count = 0;
    while (num > 0 && (num & 1) == 0) {
        count++;
        num >>= 1;
    }
    return count;
}

// Function to solve for a single prefix of length m
int solveSingle(vector<int>& prefix) {
    int m = prefix.size();
    vector<int> b = prefix;
    
    // Count total powers of 2 we can distribute
    int totalPowersOf2 = 0;
    for (int x : b) {
        totalPowersOf2 += countTrailingZeros(x);
    }
    
    // Remove all powers of 2 from numbers
    for (int i = 0; i < m; i++) {
        while (b[i] % 2 == 0) {
            b[i] /= 2;
        }
    }
    
    // Distribute powers of 2 to largest numbers from right to left
    vector<pair<int, int>> nums;
    for (int i = 0; i < m; i++) {
        nums.push_back({b[i], i});
    }
    sort(nums.rbegin(), nums.rend());
    
    // Calculate final sum
    int sum = 0;
    for (int i = 0; i < m; i++) {
        int idx = nums[i].second;
        int val = nums[i].first;
        
        // Add powers of 2 based on position from right
        int powers = (i < totalPowersOf2) ? 1 : 0;
        val = (val * (1LL << powers)) % MOD;
        sum = (sum + val) % MOD;
    }
    
    return sum;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Solve for each prefix
    for (int len = 1; len <= n; len++) {
        vector<int> prefix(a.begin(), a.begin() + len);
        cout << solveSingle(prefix) << " ";
    }
    cout << "\n";
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