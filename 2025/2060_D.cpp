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
    int sorted=true;
    for(int i=0;i<n-1;i++){
        if(a[i]>a[i+1]){
            sorted=false;
            break;
        }
    }

    if(sorted){
        cout<<"YES"<<endl;
    }
    else{
        for(int i=0;i<n-1;i++){
            //substract min of i+1, and i from both
            int temp=min(a[i],a[i+1]);
            a[i+1]-=temp;
            a[i]-=temp;
        }
        sorted=true;
        for(int i=0;i<n-1;i++){
            if(a[i]>a[i+1]){
                sorted=false;
                break;
            }
        }
        if(sorted){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
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