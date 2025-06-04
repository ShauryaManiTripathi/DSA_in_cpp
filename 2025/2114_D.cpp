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
template<typename T> void writln(T x) { cout << x << endl; }
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
    int n;
        cin >> n;
        vector<ll> x(n), y(n);
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i];
        }

        // Prepare sorted copies
        vector<ll> sx = x;
        vector<ll> sy = y;
        sort(sx.begin(), sx.end());
        sort(sy.begin(), sy.end());

        // Find max_x and second_max_x
        ll max_x = sx.back();
        int cnt_max_x = 1;
        int idx = n - 2;
        while (idx >= 0 && sx[idx] == max_x) {
            cnt_max_x++;
            idx--;
        }
        ll second_max_x = (cnt_max_x < n ? sx[n - cnt_max_x - 1] : max_x);

        // Find min_x and second_min_x
        ll min_x = sx.front();
        int cnt_min_x = 1;
        idx = 1;
        while (idx < n && sx[idx] == min_x) {
            cnt_min_x++;
            idx++;
        }
        ll second_min_x = (cnt_min_x < n ? sx[cnt_min_x] : min_x);

        // Find max_y and second_max_y
        ll max_y = sy.back();
        int cnt_max_y = 1;
        idx = n - 2;
        while (idx >= 0 && sy[idx] == max_y) {
            cnt_max_y++;
            idx--;
        }
        ll second_max_y = (cnt_max_y < n ? sy[n - cnt_max_y - 1] : max_y);

        // Find min_y and second_min_y
        ll min_y = sy.front();
        int cnt_min_y = 1;
        idx = 1;
        while (idx < n && sy[idx] == min_y) {
            cnt_min_y++;
            idx++;
        }
        ll second_min_y = (cnt_min_y < n ? sy[cnt_min_y] : min_y);

        // Initial bounding box area
        ll width  = max_x - min_x + 1;
        ll height = max_y - min_y + 1;
        ll min_area = width * height;

        // Try removing each monster
        for (int i = 0; i < n; i++) {
            // X-extents without point i
            ll nx_max = (x[i] == max_x
                         ? (cnt_max_x > 1 ? max_x : second_max_x)
                         : max_x);
            ll nx_min = (x[i] == min_x
                         ? (cnt_min_x > 1 ? min_x : second_min_x)
                         : min_x);

            // Y-extents without point i
            ll ny_max = (y[i] == max_y
                         ? (cnt_max_y > 1 ? max_y : second_max_y)
                         : max_y);
            ll ny_min = (y[i] == min_y
                         ? (cnt_min_y > 1 ? min_y : second_min_y)
                         : min_y);

            ll w = nx_max - nx_min + 1;
            ll h = ny_max - ny_min + 1;
            ll area_rem = w * h;
            ll candidate;

            if (area_rem > (n - 1)) {
                // The removed monster can be placed inside
                candidate = area_rem;
            } else {
                // Must expand one side by 1
                ll opt1 = (w + 1) * h;
                ll opt2 = w * (h + 1);
                candidate = min(opt1, opt2);
            }

            min_area = min(min_area, candidate);
        }

        cout << min_area << "\n";
}












































// ⠀⠀⠀⠀⠀⠀⠀⠀⠐⢀⡀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣯⡌⠳⣆⣲⡲⣤⠠⣀⣠⣄⠴⢐⣶⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠁⢄⠀⠀⠀⠀⠀⢸⣿⣿⣿⣟⣫⣽⠼⠏⡹⣧⡡⣡⣠⣴⢿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⣰⣿⣿⣿⣿⣿⣯⣤⢚⠤⣀⣈⡿⣆⢫⢻⠯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠀⡀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣦⣭⣶⣣⣇⠘⠆⣫⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣲⣟⢰⣽⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡤
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⠟⣱⡿⣿⣿⣿⣿⣃⢻⣿⣿⣸⣟⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⡿⣿⣿⡿⣿⡿⢶⠿⣿⡟⣏⣤⣼⣿⣿⣿⡿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠊⢀⠐⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⣿⣿⣿⣿⣿⣷⣀⠀⠀⠀⠈⠀⠛⢃⣾⣿⣿⣿⢏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠎⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⢰⣿⣿⣿⣿⣿⣟⠀⠀⠀⠀⠀⠀⠐⣲⣿⣿⣿⡟⢂⠠⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⣼⣿⣿⣿⣿⣿⣿⡇⣀⠀⠉⢀⣠⣼⣿⣿⣤⣤⡈⣤⢠⡈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⣿⣿⣿⣿⣿⣿⣿⣿⡿⣶⣷⣾⡿⣿⣿⣿⣿⣿⣛⠛⠋⠁⠠⡀⢁⡀⢀⠀⠀⣀⠔⢡⠀⡄⡜⡄⠀
// ⢆⠒⠤⢒⠰⢂⠴⢀⠆⡐⠞⣇⢩⣿⢿⣿⣿⣿⣿⣿⡙⣤⡐⢀⡶⠤⠸⣿⣿⣿⣿⣿⡟⣖⠤⣦⢶⣳⡝⣳⢆⠈⠀⠈⠐⠈⠐⠘⠐⠀
// ⠀⠈⡀⠄⠁⡀⠂⠀⡀⠘⢆⣹⣿⣾⣿⣿⣿⣿⡿⠣⣝⢀⡈⠉⠀⢀⠠⢹⡌⢿⠛⠙⣷⣿⣷⡝⢿⣷⡿⣵⡻⣍⠁⠆⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⢼⣿⣿⣿⣿⡿⡟⠀⠀⠀⠀⠠⡠⠈⠀⠀⠀⠱⡈⠱⡄⠀⢻⣿⡿⣺⡍⠛⠀⠈⠁⠀⢠⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⠟⡼⠁⠤⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠙⢷⣬⣿⣥⣿⣿⣿⣶⣦⣤⣀⠸⢆⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⠋⡘⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡰⠛⡱⠄⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡠⡀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⡟⢡⡾⢧⠀⠀⠀⠀⠀⠀⠀⡆⠀⠀⠀⣰⠁⠀⠀⠘⢣⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣴⡀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢿⣿⢰⣿⠁⠛⣆⠀⠀⠀⠀⠀⠀⣇⠀⠀⣼⣷⣦⣴⣦⣶⣼⡄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⠄⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⣸⣿⣿⣿⣷⣦⣘⣦⣄⠀⠀⠀⠃⡏⣄⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⡛⠿⢿⣿⣿⣿⣿⡟⠀⠀⠀
// ⣶⣴⣶⣴⣠⣤⣤⣤⣤⣧⣧⣿⣿⣿⣿⣿⣿⣿⣿⠷⣲⠟⢈⠏⠉⢯⣝⣛⠛⠛⢟⣻⢿⣿⣿⢿⡼⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⣿⣿⣿⣿⣿⠉⠉⠻⣩⣿⣿⣿⣿⣿⣿⣯⡵⠒⠁⠀⠈⠁⠀⠀⠈⠉⠋⠛⠉⡁⣾⡿⠛⢿⡛⢿⡻⠻⣿⣟⠛⢻⣿⣿⣟⣿⣶⠦
// ⠀⠀⣿⣿⣿⣿⢿⠀⠀⠀⢼⣿⣿⣿⣿⣿⣿⣎⠀⠀⠄⠀⠀⠈⠀⠀⠀⠀⠀⡀⠊⢰⡟⡄⢒⠋⠈⡜⠁⠀⠘⠋⠀⠨⣿⣿⣿⣿⣯⠀
// ⠀⠀⣿⣿⣿⣿⢸⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⡿⠃⠄⠂⠀⠀⠀⠀⠀⠀⠀⠔⠀⠀⠀⠂⠈⠁⠀⠁⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⠀
// ⠀⠀⣿⣿⣾⣿⢺⠀⠀⢰⣿⣿⣿⣿⣿⣿⡟⠁⠌⠀⠄⠁⡀⠀⠀⠀⠔⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⢸⠀
// ⠀⠀⣿⣿⣽⣿⠭⠀⢀⣨⣿⣿⣿⣿⣿⠏⠀⡐⠀⠈⠄⠂⡠⠔⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⢸⠀
// ⠀⠀⣿⣯⣿⣾⢇⢰⣿⣿⣿⣿⣿⣿⢿⡀⠀⠀⠀⠁⢀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⡀⠀⠀⠀⠀⠀⠀⢸⣿⡿⣿⡟⠈⠀
// ⠀⠀⣿⣷⢿⣻⡌⠈⣿⣿⣿⣿⣿⣿⣌⢧⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡜⣄⠀⠀⠀⠀⠀⠀⢸⣿⡿⣿⣇⠀⠀
// ⢀⣀⣿⣯⣿⡿⠷⠀⣨⣿⣿⣿⣿⠃⠈⠛⠷⢦⣀⠀⡀⠀⠀⠀⠁⠀⡀⠄⠀⠀⠀⠀⣀⡤⠚⢉⣿⢷⡀⠀⠀⠀⠀⢸⣿⢿⣟⣯⠀⠀
// ⣏⣉⣏⡉⡁⠀⡉⠀⣸⣿⣿⣿⡟⠀⠀⠀⢀⠀⠉⢻⣤⣄⣀⠀⠀⠀⠀⠀⣀⣠⣼⠛⠉⠀⠀⢸⡜⣿⣿⣀⠀⠀⠀⢸⣿⡟⣿⡏⡇⠀
// ⣿⣿⣻⣿⠿⢛⣉⣴⣠⣼⣿⣽⠇⠠⠁⠀⠂⠙⠲⢄⡙⢿⣿⣿⣿⣿⣿⣿⣿⢟⠡⠐⠀⠈⠀⣶⣿⣿⣿⠃⠀⠀⠀⢸⣿⣟⣿⣯⡇⠀
// ⠉⠘⣷⣿⣿⣿⠟⠿⢿⡯⢟⣿⠂⠁⠠⠈⠀⣀⠀⠀⠉⠺⢿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⢹⢛⢻⣰⠀⠈⠁⠉⣹⣿⡿⠟⠓⠁⠀
// ⠀⠀⣿⢷⣻⣯⠃⠀⠀⠀⠀⢘⠀⠐⠀⠀⠁⠀⠈⠐⢄⠀⠂⢹⡛⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⢸⡈⣼⣿⣶⣦⣶⣿⣯⣧⣤⣄⣀⣄⣀
// ⠀⠀⣿⣻⢯⣟⠂⠀⠀⠀⠀⠸⠀⠈⠀⠀⠀⠀⠀⠀⠀⠁⠈⠈⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠀⣿⣽⣾⣟⣾⣽⣳⣿⢿⣿⣿⡿⣿
// ⠀⠀⣯⣟⣯⢿⡀⠀⠀⠀⠀⠀⢆⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⣰⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠻⠈⠉⠉⠙⢻⣯⣿⢯⡷⠿⠻
// ⠀⠀⣷⢫⣞⣟⡆⠀⠀⠀⠀⠀⠘⠄⠀⠠⠀⠀⠀⠀⠀⠀⠐⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⢸⡷⣯⢿⡇⠀⠀
// ⠀⠀⣏⢿⡼⡾⠇⠂⠀⠀⠀⠀⠀⠨⠀⠠⠀⡀⠀⠀⠀⡰⠱⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡐⠀⠀⠀⠀⠀⠀⠀⢸⡻⢽⣯⡟⠀⠀
// ⠀⠀⠬⠇⠻⠱⠉⠀⠀⠀⠀⠀⠀⠀⠱⡀⠐⢀⠀⠂⢄⠰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⡰⣷⣈⣷⠃⠀⠀
// ⡴⣐⢶⢲⠶⣍⠧⡠⠄⠤⡀⠀⠀⠀⠀⢥⠈⠄⡨⢐⡈⡎⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠐⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠾⠿⠱⠶⠀⠀

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("/run/media/fullname/back/DSA_in_cpp/input", "r", stdin);
    freopen("/run/media/fullname/back/DSA_in_cpp/output", "w", stdout);
#endif

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}