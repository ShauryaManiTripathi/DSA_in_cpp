#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int n,k;
    cin>>n>>k;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    ll clicks=0;
    sort(a,a+n);
    ll delta=0;
    for(int i=0;i<n;i++){
        ll minitrNoFail=a[i]-delta;
        ll maxGotNoFail=minitrNoFail*(n-i);
        if(maxGotNoFail<=k){
            k-=maxGotNoFail;
            clicks+=maxGotNoFail;
            delta+=a[i]-delta;
        }
        else{
            clicks+=k;
            break;
        }
        //failing
        if(k>0){
            for(int j=i+1;j<n;j++){
                if(a[j]!=a[i]){
                    int fails=j-i;
                    clicks+=fails;
                    i=j-1;
                    break;
                }
            }
        }
        else{
            break;
        }
    }
    cout<<clicks<<endl;
        
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