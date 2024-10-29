#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n;
    cin>>n;
    vector<vector<int>> a(n,vector<int>(n));
    vector<int> minMainDiags(n+n-1,INT_MAX);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
            int temp=i-j+n-1;
            minMainDiags[temp]=min(minMainDiags[temp],a[i][j]);
        }
    }
    int sum=0;
    for(auto x:minMainDiags){
        if(x<0){
            sum+=(-1*x);
        }
    }
    cout<<sum<<endl;
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