#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n;
    cin>>n;
    int arr[n];
    string s;
    cin>>s;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<unordered_set<int>> v(n);
    for(int i=0;i<n;i++){
        int temp=i;
        while(true){
            if(s[temp]=='0')v[temp].emplace(i);
            
        }
    }
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