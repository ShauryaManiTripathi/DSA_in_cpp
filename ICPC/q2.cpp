#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

bool isValid(vector<int>& arr, vector<pair<pair<int,int>,int>>& constraints) {
    for(auto& c : constraints) {
        int l = c.first.first;
        int r = c.first.second;
        int m = c.second;
        
        // Check if minimum in range [l,r] is not m
        int minVal = *min_element(arr.begin() + l, arr.begin() + r + 1);
        if(minVal == m) return false;
    }
    return true;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<pair<int,int>,int>> constraints(k);
    for(int i = 0; i < k; i++) {
        cin >> constraints[i].first.first;
        cin >> constraints[i].first.second;
        cin >> constraints[i].second;
        // Convert to 0-based indexing
        constraints[i].first.first--;
        constraints[i].first.second--;
    }
    
    // Try a simple descending array first
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    
    if(isValid(arr, constraints)) {
        for(int x : arr) cout << x << " ";
        cout << endl;
        return;
    }
    
    // If simple approach fails, try all permutations for first problematic range
    vector<int> nums(n);
    for(int i = 0; i < n; i++) nums[i] = i + 1;
    
    do {
        if(isValid(nums, constraints)) {
            for(int x : nums) cout << x << " ";
            cout << endl;
            return;
        }
    } while(next_permutation(nums.begin(), nums.end()));
    
    cout << "-1" << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}