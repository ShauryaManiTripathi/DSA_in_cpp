#include <bits/stdc++.h>
using namespace std;

// Type definitions
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vii vector<pii>
#define vll vector<pll>
#define vvi vector<vi>
#define vvl vector<vl>
#define vb vector<bool>
#define pb push_back
#define eb emplace_back
#define mp make_pair

// Shortcuts for common operations
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define F first
#define S second

// Loops
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPD(i, n) for (int i = (n) - 1; i >= 0; --i)

// Constants
const int MOD = 1e9 + 7;
const int INF = INT_MAX;
const ll LLINF = LLONG_MAX;
const double EPS = 1e-9;

// Debug
#define debug(x) cout << #x << " = " << x << endl
#define debugv(v)         \
    cout << #v << " = ";  \
    for (auto &x : v)     \
        cout << x << " "; \
    cout << endl
#define debugvv(vv)           \
    cout << #vv << ":\n";     \
    for (auto &v : vv)        \
    {                         \
        for (auto &x : v)     \
            cout << x << " "; \
        cout << endl;         \
    }

// I/O
#define endl '\n'
template <typename T>
void read(T &x) { cin >> x; }
template <typename T1, typename T2>
void read(pair<T1, T2> &p)
{
    read(p.F);
    read(p.S);
}
template <typename T>
void read(vector<T> &v)
{
    for (auto &x : v)
        read(x);
}
template <typename T>
void write(T x) { cout << x << " "; }
template <typename T1, typename T2>
void write(pair<T1, T2> &p)
{
    write(p.F);
    write(p.S);
}
template <typename T>
void write(vector<T> &v)
{
    for (auto &x : v)
        write(x);
    cout << endl;
}

// Custom hash for unordered_map
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve()
{
    int n;
    read(n);
    vi a(n);
    read(a);
    int top, bottom, sides;
    bool top_set = false, bottom_set = false, sides_set = false;
    map<int, int> freq;
    REP(i, n)
    {
        freq[a[i]]++;
    }
    
    // select two numbers from the array which are same , they will serve as sides
    for (auto x : freq)
    {
        if (x.S >= 2)
        {
            sides = x.F;
            sides_set = true;
        }
    }
    freq[sides] -= 2;
    if (freq[sides] == 0)
    {
        freq.erase(sides);
    }

    // Find consecutive or same numbers for top and bottom with smallest difference
    int min_diff = INT_MAX;
    for(auto it = freq.begin(); it != freq.end(); ++it) {
        // Case 1: Same number if frequency > 1
        if(it->S > 1) {
            top = it->F;
            bottom = it->F;
            if(min_diff > 0) {
                min_diff = 0;
                top_set = bottom_set = true;
            }
        }
        
        // Case 2: Consecutive numbers
        auto next = it;
        next++;
        if(next != freq.end()) {
            int curr_diff = next->F - it->F;
            if(curr_diff < min_diff) {
                min_diff = curr_diff;
                top = it->F;
                bottom = next->F;
                top_set = bottom_set = true;
            }
        }
    }
    if (top_set && bottom_set && sides_set)
    {
        if ((bottom < top + sides + sides))
        {
            cout << top << " " << bottom << " " << sides << " " << sides << endl;
        }
        else
        {
            cout << "-1" << endl;
        }
    }
    else
        cout << "-1" << endl;
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