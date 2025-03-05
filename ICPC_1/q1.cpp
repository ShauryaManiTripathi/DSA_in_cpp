#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long k;
    cin >> n >> k;
    
    vector<long long> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if(k == 0) {
        long long result=a[0];
        for(int i = 1; i < n; i++) {
            result&=a[i];
        }
        if(result == 0) {
            cout << "YES"<<endl;
            cout<<n<<endl;
            for(int i = 0; i < n; i++) {
                cout << a[i]<<" ";
            }
            cout << "\n";
            return;
        }
        cout << "NO\n";
        return;
    }
    vector<pair<long long, int>> candidates;
    for(int i = 0; i < n; i++) {
        if((k & a[i]) == k) {
            candidates.push_back({a[i], i + 1});
        }
    }
    
    if(candidates.empty()) {
        cout << "NO\n";
        return;
    }
    long long result = (1LL << 30) - 1;
    vector<int> indices;
    
    for(auto [num, idx] : candidates) {
        result &= num;
        indices.push_back(idx);
        
        if(result == k) {
            cout << "YES\n";
            cout << indices.size() << "\n";
            for(int i = 0; i < indices.size(); i++) {
                cout << indices[i] << " \n"[i == indices.size()-1];
            }
            return;
        }
    }
    
    cout << "NO\n";
}

int main() {    
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}