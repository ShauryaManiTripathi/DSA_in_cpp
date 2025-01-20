#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

int compare(pair<int,int> a,pair<int,int> b){
    // int countA=0;
    // int countB=0;
    // if(a.first<=b.first)countA++;
    // if(a.second<=b.second)countA++;
    // if(a.first<=b.second)countA++;
    // if(a.second<=b.first)countA++;
    // if(b.first<=a.first)countB++;
    // if(b.second<=a.second)countB++;
    // if(b.first<=a.second)countB++;
    // if(b.second<=a.first)countB++;
    // return countA>countB;
    return a.first+a.second<b.first+b.second;
}
void solve() {
    int n;
    cin>>n;
    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; i++)
    {
        cin>>a[i].first;
        cin>>a[i].second;
    }
    sort(a.begin(),a.end(),compare);
    for (int i = 0; i < n; i++)
    {
        if(i!=n-1)
        cout<<a[i].first<<" "<<a[i].second<<" ";
        else
        cout<<a[i].first<<" "<<a[i].second;
    }
    cout<<endl;
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