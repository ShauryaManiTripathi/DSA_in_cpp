#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> prefixSum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + a[i];
    }
    map<ll,int> lastknownpos;
    cout<<endl;
    int count=0;int backborder=-1;
    for(int i=0;i<n+1;i++){
        if(lastknownpos.find(prefixSum[i])!=lastknownpos.end()){
            if(lastknownpos[prefixSum[i]]>backborder){
                count++;
                backborder=lastknownpos[prefixSum[i]];
            }
            lastknownpos.clear();
            lastknownpos[prefixSum[i]]=i;
        }
        else{
            lastknownpos[prefixSum[i]]=i;
        }
    }
    cout<<count<<endl;
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