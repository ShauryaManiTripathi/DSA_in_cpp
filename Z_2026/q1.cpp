#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n,m,k;
    cin>>n>>m>>k;
    int amxsqside=min(n,m);
    int a1=0,a2=0;
    int b1=amxsqside,b2=amxsqside;
    int c1=amxsqside,c2=0;
    int d1=0,d2=amxsqside;
    cout<<a1<<" "<<a2<<" "<<b1<<" "<<b1<<endl;
    cout<<c1<<" "<<c2<<" "<<d1<<" "<<d2<<endl;
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