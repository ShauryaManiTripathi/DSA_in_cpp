#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n;
    cin>>n;
    int temp=0;
    for(int i=1;i<1000;i++){
        if(i&1)temp-=2*i-1;
        else temp+=2*i-1;
        if(temp > n || temp < -n){
            if(i&1)cout<<"Sakurako"<<endl;
            else cout<<"Kosuke"<<endl;
            break;
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