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
	const int DIM = 8;

vector<vector<bool>> blocked(DIM, vector<bool>(DIM));
vector<bool> rows_taken(DIM);
// Indicators for diagonals that go from the bottom left to the top right
vector<bool> diag1(DIM * 2 - 1);
// Indicators for diagonals that go from the bottom right to the top left
vector<bool> diag2(DIM * 2 - 1);

int valid_num = 0;

void search_queens(int c = 0) {
	if (c == DIM) {
		// We've filled all rows, increment and return
		valid_num++;
		return;
	}

	for (int r = 0; r < DIM; r++) {
		bool row_open = !rows_taken[r];
		bool diag_open = !diag1[r + c] && !diag2[r - c + DIM - 1];
		if (!blocked[r][c] && row_open && diag_open) {
			// A row and two diagonals have been taken
			rows_taken[r] = diag1[r + c] = diag2[r - c + DIM - 1] = true;
			search_queens(c + 1);
			// And now they aren't anymore
			rows_taken[r] = diag1[r + c] = diag2[r - c + DIM - 1] = false;
		}
	}
}

void solve() {
    for (int r = 0; r < DIM; r++) {
		string row;
		cin >> row;
		for (int c = 0; c < DIM; c++) { blocked[r][c] = row[c] == '*'; }
	}
    search_queens();
    cout<<valid_num<<endl;
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
    freopen("/mnt/back/DSA_in_cpp/input", "r", stdin);
    freopen("/mnt/back/DSA_in_cpp/output", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}