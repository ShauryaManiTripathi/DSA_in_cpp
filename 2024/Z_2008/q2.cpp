#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve() {
    int a;
    cin>>a;
    string s;
    cin>>s;
    double sqside=sqrt(a);
    if((static_cast<int>(sqside))==sqside){
        int n=static_cast<int>(sqside);
        for(int i=0;i<n;i++){
            string temp=s.substr(i*n,n);
            if(i==0 || i==n-1){
                for(int j=0;j<n;j++){
                    if(temp[j]=='0'){
                        cout<<"No"<<endl;
                        return;
                    }
                }
            }
            else{
                for(int j=0;j<n;j++){
                    if(j==0 || j==n-1){
                        if(temp[j]=='0'){
                            cout<<"No"<<endl;
                            return;
                        }
                    }
                    else{
                        if(temp[j]=='1'){
                            cout<<"No"<<endl;
                            return;
                        }
                    }
                }
            }
        }
        cout<<"Yes"<<endl;
    }
    else cout<<"No"<<endl;

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