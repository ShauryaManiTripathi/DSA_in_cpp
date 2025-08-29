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


// Galaxy Luck, a well-known casino in the entire solar system, introduces a new card game.

// In this game, there is a deck that consists of n
//  cards. Each card has m
//  numbers written on it. Each of the n
//  players receives exactly one card from the deck.

// Then all players play with each other in pairs, and each pair of players plays exactly once. Thus, if there are, for example, four players in total, then six games are played: the first against the second, the first against the third, the first against the fourth, the second against the third, the second against the fourth and the third against the fourth.

// Each of these games determines the winner in some way, but the rules are quite complicated, so we will not describe them here. All that matters is how many chips are paid out to the winner. Let the first player's card have the numbers a1,a2,…,am
// , and the second player's card — b1,b2,…,bm
// . Then the winner of the game gets |a1−b1|+|a2−b2|+⋯+|am−bm|
//  chips from the total pot, where |x|
//  denotes the absolute value of x
// .

// To determine the size of the total pot, it is necessary to calculate the winners' total winnings for all games. Since there can be many cards in a deck and many players, you have been assigned to write a program that does all the necessary calculations.

// Input
// Each test consists of several test cases. The first line contains one integer t
//  (1≤t≤1000
// ) — the number of test cases. The description of the test cases follows.

// The first line of each test case contains two integers n
//  and m
//  (1≤n⋅m≤3⋅105
// ) — the number of cards in the deck and the count of numbers on the one card.

// Each of the following n
//  lines of the test case set contains m
//  integers ci,j
//  (1≤ci,j≤106
// ) — a description of the i
// -th card.

// It is guaranteed that the total n⋅m
//  in all tests does not exceed 3⋅105
// .

// Output
// For each test case, print one number — the total amount of winnings from all games.

// Example
// InputCopy
// 3
// 3 5
// 1 4 2 8 5
// 7 9 2 1 4
// 3 8 5 3 1
// 1 4
// 4 15 1 10
// 4 3
// 1 2 3
// 3 2 1
// 1 2 1
// 4 2 7
// OutputCopy
// 50
// 0
// 31
// Note
// Consider the first test case.

// In the game between the first and second player, the winner receives |1−7|+|4−9|+|2−2|+|8−1|+|5−4|=19
//  chips.

// In the game between the first and third player, the winner receives |1−3|+|4−8|+|2−5|+|8−3|+|5−1|=18
//  in chips.

// In the game between the second and third player, the winner receives |7−3|+|9−8|+|2−5|+|1−3|+|4−1|=13
//  chips.

// The total is 19+18+13=50
//  chips.

void solve() {
    int n,m;
    read(n,m);
    vvi arr(n,vi(m));
    REP(i,n){
        REP(j,m){
            read(arr[i][j]);
        }
    }
    ll pool = 0;
    REP(i,m){
        vl temp;
        REP(j,n){
            temp.push_back(arr[j][i]);
        }
        sort(all(temp));
        ll sum = accumulate(all(temp),0LL);
        REP(k,n){
            sum-=temp[k];
            pool+=llabs(sum - (n-k-1)*temp[k]);
        }
    }
    writln(pool);
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
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }

    return 0;
}