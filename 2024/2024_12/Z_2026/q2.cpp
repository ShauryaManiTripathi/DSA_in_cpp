#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl


bool is_possible(int n, const vector<ll>& a, ll k) {
   vector dp0(n + 1, false);
   vector dp1(n + 1, false);
   dp0[0] = true;
   dp1[0] = false;
   for(int i = 0; i < n; ++i) {
       vector next0(n + 1, false);
       vector next1(n + 1, false);
       if(dp0[i]) {
           if(i + 1 < n && abs(a[i + 1] - a[i]) <= k) {
               next0[i + 2] = true;
           }
           if(k >= 1) {
               next1[i + 1] = true;
           }
       }
       if(dp1[i]) {
           if(i + 1 < n && abs(a[i + 1] - a[i]) <= k) {
               next1[i + 2] = true;
           }
       }
       for(int j = 0; j <= n; ++j) {
           if(next0[j]) dp0[j] = true;
           if(next1[j]) dp1[j] = true;
       }
   }
   return dp0[n] || dp1[n];
}

ll find_minimal_k(int n, const vector<ll>& a) {
   ll left = 0, right = (ll)1e18;
   ll answer = right;
   while(left <= right) {
       ll mid = left + (right - left) / 2;
       if(is_possible(n, a, mid)) {
           answer = mid;
           right = mid - 1;
       } else {
           left = mid + 1;
       }
   }
   return answer;
}

void solve()
{
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a)
        cin >> x;
    cout << find_minimal_k(n, a) << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("/home/shaurya/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/shaurya/Desktop/DSA_in_cpp/output", "w", stdout);
#endif

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i)
    {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}