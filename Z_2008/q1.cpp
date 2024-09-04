#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

// void solve() {
//     int a,b;
//     cin>>a>>b;
//     int remaining  =  a-(2*b);
//     if(!remaining)cout<<"YES"<<endl;
//     else if (remaining>0 && !(remaining&1))cout<<"YES"<<endl;
//     else if (remaining<0 && (-remaining)&1)cout<<"NO"<<endl;
//     else if (remaining<0 && (-remaining)%4==0)cout<<"YES"<<endl;
//     else cout<<"NO"<<endl;
// }

void solve(){
    int a,b;
    cin>>a>>b;
    for(int i=0;i<=a;i++){
        for(int j=0;j<=b;j++){
            int result=i*1-(a-i)+j*2-((b-j)*2);
            if(!result){
                cout<<"YES"<<endl;
                return;
            }
        }
    }
    cout<<"NO"<<endl;
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