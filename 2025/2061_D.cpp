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
template<typename T1, typename T2> void write(pair<T1, T2> &p) { write(p.F); write(p.S); }
template<typename T> void write(vector<T> &v) { for (auto &x : v) write(x); cout << endl; }

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

bool canForm(int target, vector<int>& numbers) {
    auto it = find(numbers.begin(), numbers.end(), target);
    if (it != numbers.end()) {
        return true;
    }
    
    sort(numbers.begin(), numbers.end());
    for (int i = 0; i < numbers.size() - 1; i++) {
        for (int j = i + 1; j < numbers.size(); j++) {
            if (abs(numbers[i] - numbers[j]) <= 1) {
                int newNum = numbers[i] + numbers[j];
                if (newNum == target) {
                    return true;
                }
                if (newNum < target) {
                    vector<int> newNumbers;
                    for (int k = 0; k < numbers.size(); k++) {
                        if (k != i && k != j) {
                            newNumbers.push_back(numbers[k]);
                        }
                    }
                    newNumbers.push_back(newNum);
                    if (canForm(target, newNumbers)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), b(m);
    long long sum_a = 0, sum_b = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum_a += a[i];
    }
    
    for (int i = 0; i < m; i++) {
        cin >> b[i];
        sum_b += b[i];
    }
    if (sum_a != sum_b) {
        cout << "No\n";
        return;
    }
    
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    vector<int> currentNumbers = a;
    for (int target : b) {
        if (!canForm(target, currentNumbers)) {
            cout << "No\n";
            return;
        }
        auto it = find(currentNumbers.begin(), currentNumbers.end(), target);
        if (it != currentNumbers.end()) {
            currentNumbers.erase(it);
        } else {
            bool found = false;
            for (int i = 0; i < currentNumbers.size() - 1 && !found; i++) {
                for (int j = i + 1; j < currentNumbers.size(); j++) {
                    if (abs(currentNumbers[i] - currentNumbers[j]) <= 1) {
                        int sum_val = currentNumbers[i] + currentNumbers[j];
                        if (sum_val == target) {
                            currentNumbers.erase(currentNumbers.begin() + j);
                            currentNumbers.erase(currentNumbers.begin() + i);
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    cout << "Yes\n";
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