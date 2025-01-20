#include <bits/stdc++.h>
#define ll long long
using namespace std;
const long long INF = 1e18;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<ll> a(n);
        for (auto &x : a)
            cin >> x;
        vector<ll> b(m);
        for (auto &x : b)
            cin >> x;
        vector<ll> pre(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + a[i];
        vector<ll> dp(n + 1, INF);
        dp[0] = 0;
        for (int k = 1; k <= m; k++)
        {
            ll out = b[k - 1];
            for (int i = 0; i < n; i++)
            {
                if (dp[i] == INF)
                    continue;
                ll x = pre[i] + out;
                ll jss = upper_bound(pre.begin(), pre.end(), x) - pre.begin();
                ll j = jss - 1;
                if (j >= i + 1 && j <= n)
                {
                    dp[j] = min(dp[j], dp[i] + (ll)(m - k));
                }
            }
        }
        if (dp[n] == INF)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << dp[n] << endl;
        }
    }

    return 0;
}