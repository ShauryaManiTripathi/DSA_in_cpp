#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    ll n,m,r,c;
    cin>>n>>m>>r>>c;
    r--;c--;
    ll ans=0;
    //total element with column 0 below r,c
    ll wrappings=n-r-1;
    ll pos=m*r+c;
    ll total=n*m;
    ll nonwraps=total-pos-wrappings;
    ans=wrappings*m+nonwraps;
    ans--;
    cout<<ans<<endl;


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