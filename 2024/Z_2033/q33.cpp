#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve_test_case(int n, vector<int>& a) {
    // Key insight: We only need to consider each position and its mirror position
    // For each pair, we can make a local optimal decision
    vector<int> b = a; // copy to work with
    
    // For each position i and (n-1-i), pick the best arrangement locally
    for(int i = 0; i < n/2; i++) {
        int j = n-1-i;
        
        // Current values at positions i and j
        int v1 = b[i], v2 = b[j];
        
        // Try both arrangements and count local disturbances
        // Original arrangement
        int dist1 = 0;
        if(i > 0 && b[i] == b[i-1]) dist1++;
        if(i < n-1 && b[i] == b[i+1]) dist1++;
        if(j > 0 && b[j] == b[j-1]) dist1++;
        if(j < n-1 && b[j] == b[j+1]) dist1++;
        
        // Swap values
        swap(b[i], b[j]);
        
        // Count disturbances after swap
        int dist2 = 0;
        if(i > 0 && b[i] == b[i-1]) dist2++;
        if(i < n-1 && b[i] == b[i+1]) dist2++;
        if(j > 0 && b[j] == b[j-1]) dist2++;
        if(j < n-1 && b[j] == b[j+1]) dist2++;
        
        // Keep the better arrangement
        if(dist1 <= dist2) {
            swap(b[i], b[j]); // swap back if original was better
        }
    }
    
    // Count final disturbances
    int result = 0;
    for(int i = 0; i < n-1; i++) {
        if(b[i] == b[i+1]) result++;
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++) {
            cin >> a[i];
        }
        cout << solve_test_case(n, a) << '\n';
    }
    
    return 0;
}