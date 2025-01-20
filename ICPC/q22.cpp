#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<pair<int,int>,int>> constraints(k);
    for(int i = 0; i < k; i++) {
        cin >> constraints[i].first.first;
        cin >> constraints[i].first.second;
        cin >> constraints[i].second;
        constraints[i].first.first--;
        constraints[i].first.second--;
    }
    
    vector<int> ans(n);
    // For each position, keep track of which values can't be minimum in ranges covering it
    vector<set<int>> cantBeMin(n);
    
    // For each constraint (l,r,m), mark m as forbidden minimum for this range
    for(auto& c : constraints) {
        int l = c.first.first;
        int r = c.first.second;
        int m = c.second;
        for(int j = l; j <= r; j++) {
            cantBeMin[j].insert(m);
        }
    }
    
    // For each position, find smallest valid number larger than previous numbers
    int prevMax = 0;
    for(int i = 0; i < n; i++) {
        int val = prevMax + 1;
        // Try each value until we find one that works
        while(val <= n) {
            bool valid = true;
            // Check if this value could become a forbidden minimum
            for(auto& c : constraints) {
                if(i >= c.first.first && i <= c.first.second && // if position is in range
                   val <= prevMax && // if this could be minimum in its range
                   cantBeMin[i].count(val)) { // if this value is forbidden
                    valid = false;
                    break;
                }
            }
            if(valid) {
                ans[i] = val;
                prevMax = max(prevMax, val);
                break;
            }
            val++;
        }
        if(val > n) {
            cout << "-1\n";
            return;
        }
    }
    
    // Verify answer
    for(auto& c : constraints) {
        int minVal = *min_element(ans.begin() + c.first.first, 
                                ans.begin() + c.first.second + 1);
        if(minVal == c.second) {
            cout << "-1\n";
            return;
        }
    }
    
    for(int x : ans) cout << x << " ";
    cout << "\n";
}
int main(){
    solve();
}