#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define debug(x) cout << #x << " = " << x << endl

void solve()
{
    int n;
    cin >> n;
    vector<int> maxHeightAtIthHeight(103, 0);
    for (int i = 0; i < n; i++)
    {
        int w, h;
        cin >> w >> h;
        int hcurr = 1;
        while (hcurr <= h)
        {
            maxHeightAtIthHeight[hcurr] = max(maxHeightAtIthHeight[hcurr], w);
            hcurr++;
        }
    }
    int perimeter = 0;

    maxHeightAtIthHeight[0] = 0;
    maxHeightAtIthHeight[101] = 0;
    maxHeightAtIthHeight[102] = 0;

    for (int i = 1; i <= 101; i++)
    {
        if (maxHeightAtIthHeight[i] == 0 && maxHeightAtIthHeight[i + 1] == 0)
        {
            perimeter += abs(maxHeightAtIthHeight[i] - maxHeightAtIthHeight[i - 1]);
            break;
        }
        perimeter += abs(maxHeightAtIthHeight[i] - maxHeightAtIthHeight[i - 1]);
        perimeter += 2;
    }
    cout << perimeter << endl;
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