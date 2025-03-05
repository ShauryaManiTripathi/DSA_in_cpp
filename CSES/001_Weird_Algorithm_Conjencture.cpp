// Learnings
// ! Always watch out for overflows
// ! dont be cunt


// ._____. ._____. ._____. ._____. ._____. ._____. ._____. ._____.
// | ._. | | ._. | | ._. | | ._. | | ._. | | ._. | | ._. | | ._. |
// | !_| |_|_|_! | | !_| |_|_|_! | | !_| |_|_|_! | | !_| |_|_|_! |
// !___| |_______! !___| |_______! !___| |_______! !___| |_______!
// .___|_|_| |_________|_|_| |___. .___|_|_| |_________|_|_| |___.
// | ._____| |_____________| |_. | | ._____| |_____________| |_. |
// | !_! | | |         | | ! !_! | | !_! | | |         | | ! !_! |
// !_____! | |         | | !_____! !_____! | |         | | !_____!
// ._____. | |     .___| |___.     ._______|_|___.     | | ._____.
// | ._. | | |     | ._| |_. |     | ._________. |     | | | ._. |
// | !_| |_|_|_____| |_|_|_| |_____|_|_____| |_|_|_____| |_|_|_! |
// !___| |_________| |_____| |_____________| |_________| |_______!
// .___|_|_| |___. | !_| |_|_|_____| |_____|_|_! | .___|_|_| |___.
// | ._____| |_. | !___| |_________| |___________! | ._____| |_. |
// | !_! | | !_! | .___|_|_| |___. | | .___| |___. | !_! | | !_! |
// !_____! !_____! | ._____| |_. | | | | ._| |_. | !_____! !_____!
// ._____. ._____. | !_| |_! | | | | !_| |_|_|_! | ._____. ._____.
// | ._. | | ._. | !___| |___! | | !___| |_______| | ._. | | ._. |
// | !_| |_|_|_! | .___|_|_____| |_____|_|_| |___. | !_| |_|_|_! |
// !___| |_______! | ._________| |_________| |_. | !___| |_______!
// .___|_|_| |_____|_|_| |_____|_|_____| |_|_|_| |_____|_|_| |___.
// | ._____| |_________| |_____________| |_____| |_________| |_. |
// | !_! | | |     | !_|_|_____! |     | !_| |_! |     | | ! !_! |
// !_____! | |     !_____________!     !___| |___!     | | !_____!
// ._____. | |         | | ._____. ._____. | |         | | ._____.
// | ._. | | |         | | | ._. | | ._. | | |         | | | ._. |
// | !_| |_|_|_________| |_|_|_! | | !_| |_|_|_________| |_|_|_! |
// !___| |_____________| |_______! !___| |_____________| |_______!
// .___|_|_| |___. .___|_|_| |___. .___|_|_| |___. .___|_|_| |___.
// | ._____| |_. | | ._____| |_. | | ._____| |_. | | ._____| |_. |
// | !_! | | !_! | | !_! | | !_! | | !_! | | !_! | | !_! | | !_! |
// !_____! !_____! !_____! !_____! !_____! !_____! !_____! !_____!


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
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPD(i, n) for(int i = (n) - 1; i >= 0; --i)

// Constants
const int MOD = 1e9 + 7;
const int INF = INT_MAX;
const ll LLINF = LLONG_MAX;
const double EPS = 1e-9;

// Debug
#define debug(x) cout << #x << " = " << x << endl
#define debugv(v) cout << #v << " = "; for (auto &x : v) cout << x << " "; cout << endl
#define debugvv(vv) cout << #vv << ":\n"; for (auto &v : vv) { for (auto &x : v) cout << x << " "; cout << endl; }

// I/O
#define endl '\n'
template<typename T> void read(T &x) { cin >> x; }
template<typename T1, typename T2> void read(pair<T1, T2> &p) { read(p.F); read(p.S); }
template<typename T> void read(vector<T> &v) { for (auto &x : v) read(x); }
template<typename T> void write(T x) { cout << x << " "; }
template<typename T> void writeln(T x) { cout << x << endl; }
template<typename T1, typename T2> void write(pair<T1, T2> &p) { write(p.F); write(p.S); }
template<typename T> void write(vector<T> &v) { for (auto &x : v) write(x); cout << endl; }
template<typename... Args>void read(Args&... args) {(read(args), ...);}
template<typename... Args>void write(Args... args) {(write(args), ...);}

// Custom hash for unordered_map
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void solve() {
    ll n;
    read(n);
    while(n!=1){
        write(n);
        if(n&1){
            n=3*n+1;
        }
        else{
            n/=2;
        }
    }
    writeln(1);
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("/run/media/fullname/back/DSA_in_cpp/input", "r", stdin);
    freopen("/run/media/fullname/back/DSA_in_cpp/output", "w", stdout);
#endif

    int t = 1;
    //cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}
