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

unordered_map<string, int> countMoos(const string& s) {
    unordered_map<string, int> moos;
    int n = s.length();
    
    for (int i = 0; i <= n - 3; i++) {
        if (s[i] != s[i+1] && s[i+1] == s[i+2]) {
            string moo = s.substr(i, 3);
            moos[moo]++;
        }
    }
    
    return moos;
}
void solve() {
    int N, F;
    string s;
    read(N, F, s);
    
    map<string, int> mooCount;
    set<string> validMoos;
    
    // Count original moos
    for (int i = 0; i <= N - 3; i++) {
        if (s[i] != s[i+1] && s[i+1] == s[i+2]) {
            string moo = s.substr(i, 3);
            mooCount[moo]++;
        }
    }
    
    // Add moos that already satisfy the frequency requirement
    for (auto& p : mooCount) {
        if (p.second >= F) {
            validMoos.insert(p.first);
        }
    }
    
    // For each position, consider what happens if we change it
    for (int pos = 0; pos < N; pos++) {
        char original = s[pos];
        
        // Remove moos that are affected by changing position 'pos'
        map<string, int> removedMoos;
        for (int i = max(0, pos - 2); i <= min(N - 3, pos); i++) {
            if (s[i] != s[i+1] && s[i+1] == s[i+2]) {
                string moo = s.substr(i, 3);
                removedMoos[moo]++;
            }
        }
        
        for (char newChar = 'a'; newChar <= 'z'; newChar++) {
            if (newChar == original) continue;
            
            // Calculate new moos that would be created
            map<string, int> addedMoos;
            for (int i = max(0, pos - 2); i <= min(N - 3, pos); i++) {
                char c1 = (i == pos) ? newChar : s[i];
                char c2 = (i + 1 == pos) ? newChar : s[i + 1];
                char c3 = (i + 2 == pos) ? newChar : s[i + 2];
                
                if (c1 != c2 && c2 == c3) {
                    string moo = string(1, c1) + c2 + c3;
                    addedMoos[moo]++;
                }
            }
            
            // Calculate net change and check if any moo reaches threshold
            map<string, int> netChange = mooCount;
            
            // Subtract removed moos
            for (auto& p : removedMoos) {
                netChange[p.first] -= p.second;
            }
            
            // Add new moos
            for (auto& p : addedMoos) {
                netChange[p.first] += p.second;
            }
            
            // Check for valid moos
            for (auto& p : netChange) {
                if (p.second >= F) {
                    validMoos.insert(p.first);
                }
            }
        }
    }
    
    cout << validMoos.size() << endl;
    for (const string& moo : validMoos) {
        cout << moo << endl;
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}