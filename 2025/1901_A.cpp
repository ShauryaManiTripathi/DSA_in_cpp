#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════════
// TYPE DEFINITIONS & SHORTCUTS
// ═══════════════════════════════════════════════════════════════════════════════
#define ll long long
#define ld long double
#define ull unsigned long long
#define int128 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define vi vector<int>
#define vl vector<ll>
#define vd vector<double>
#define vii vector<pii>
#define vll vector<pll>
#define vvi vector<vi>
#define vvl vector<vl>
#define vb vector<bool>
#define vs vector<string>
#define vc vector<char>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

// Common operations
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define sum(x) accumulate(all(x), 0LL)
#define minv(x) *min_element(all(x))
#define maxv(x) *max_element(all(x))
#define unique_sort(x) sort(all(x)); x.erase(unique(all(x)), x.end())

// Loops
#define FOR(i, a, b) for(int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for(int i = (a); i >= (b); --i)
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPD(i, n) for(int i = (n) - 1; i >= 0; --i)
#define TRAV(x, v) for(auto& x : v)
#define RTRAV(x, v) for(auto& x : reverse(all(v)))

// Bit operations
#define LSB(x) ((x) & -(x))
#define MSB(x) (63 - __builtin_clzll(x))
#define POPCNT(x) __builtin_popcountll(x)
#define setBit(x, i) (x |= (1LL << i))
#define clearBit(x, i) (x &= ~(1LL << i))
#define toggleBit(x, i) (x ^= (1LL << i))
#define checkBit(x, i) ((x >> i) & 1)
#define isPowerOf2(x) (x && !(x & (x - 1)))

// Math shortcuts
#define ceildiv(a, b) ((a) + (b) - 1) / (b)
#define mod(a, b) ((a % b + b) % b)
#define sqr(x) ((x) * (x))
#define cube(x) ((x) * (x) * (x))

// ═══════════════════════════════════════════════════════════════════════════════
// CONSTANTS & CONFIGURATION
// ═══════════════════════════════════════════════════════════════════════════════
const int MOD = 1e9 + 7;
const int MOD2 = 998244353;
const int MOD3 = 1e9 + 9;
const int INF = 2e9;
const ll LLINF = 9e18;
const double EPS = 1e-9;
const double PI = acos(-1.0);
const int MAXN = 2e5 + 5;
const int MAXLOG = 20;
const int ALPHABET = 26;

// Direction arrays (4-directional, 8-directional)
const int dx4[] = {-1, 1, 0, 0};
const int dy4[] = {0, 0, -1, 1};
const int dx8[] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int dy8[] = {0, 0, -1, 1, -1, 1, -1, 1};
const string DIRS4 = "UDLR";
const string DIRS8 = "UDLRDLDRU";

// Knight moves
const int dxK[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dyK[] = {-1, 1, -2, 2, -2, 2, -1, 1};

// ═══════════════════════════════════════════════════════════════════════════════
// DEBUG & I/O UTILITIES
// ═══════════════════════════════════════════════════════════════════════════════
#define endl '\n'
#ifndef ONLINE_JUDGE
#define debug(x) cout << #x << " = " << x << endl
#define debugv(v) cout << #v << " = "; for(auto x : v) cout << x << " "; cout << endl
#define debugp(p) cout << #p << " = (" << p.fi << ", " << p.se << ")" << endl
#define debugvv(vv) cout << #vv << ":\n"; for(auto v : vv) { for(auto x : v) cout << x << " "; cout << endl; }
#define debugm(m) cout << #m << ":\n"; for(auto [k,v] : m) cout << k << " -> " << v << "\n";
#define TIMER auto start = chrono::high_resolution_clock::now();
#define TIME_TAKEN auto end = chrono::high_resolution_clock::now(); cout << "Time: " << chrono::duration<double>(end - start).count() << "s\n";
#else
#define debug(x)
#define debugv(v)
#define debugp(p)
#define debugvv(vv)
#define debugm(m)
#define TIMER
#define TIME_TAKEN
#endif

template<typename T> void read(T &x) { cin >> x; }
template<typename T1, typename T2> void read(pair<T1, T2> &p) { read(p.fi); read(p.se); }
template<typename T> void read(vector<T> &v) { for(auto &x : v) read(x); }
template<typename... Args> void read(Args&... args) { (read(args), ...); }

template<typename T> void write(T x) { cout << x << " "; }
template<typename T> void writeln(T x) { cout << x << endl; }
template<typename T1, typename T2> void write(pair<T1, T2> p) { write(p.fi); write(p.se); }
template<typename T> void write(vector<T> v) { for(auto x : v) write(x); cout << endl; }
template<typename... Args> void write(Args... args) { (write(args), ...); }

// Fast I/O for competitive programming
void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// ═══════════════════════════════════════════════════════════════════════════════
// PRIME SIEVE & COMBINATORICS
// ═══════════════════════════════════════════════════════════════════════════════

vector<bool> is_prime;
vector<int> primes, spf; // smallest prime factor
vector<ll> fact, inv_fact;

// Fast modular exponentiation (Binary Exponentiation)
ll power(ll base, ll exp, ll mod = MOD) {
    ll res = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Modular inverse
ll modinv(ll a, ll mod = MOD) { return power(a, mod - 2, mod); }

void sieve(int n = MAXN) {
    is_prime.assign(n, true);
    spf.assign(n, 0);
    is_prime[0] = is_prime[1] = false;
    
    for(int i = 2; i < n; i++) {
        if(is_prime[i]) {
            primes.pb(i);
            spf[i] = i;
            for(ll j = (ll)i * i; j < n; j += i) {
                if(is_prime[j]) {
                    is_prime[j] = false;
                    if(spf[j] == 0) spf[j] = i;
                }
            }
        } else if(spf[i] == 0) {
            for(int p : primes) {
                if(p * p > i) break;
                if(i % p == 0) {
                    spf[i] = p;
                    break;
                }
            }
        }
    }
}

void precompute_factorials(int n = MAXN) {
    fact.assign(n, 1);
    inv_fact.assign(n, 1);
    
    for(int i = 1; i < n; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }
    
    inv_fact[n-1] = modinv(fact[n-1]);
    for(int i = n-2; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
    }
}

ll C(int n, int r) {
    if(r > n || r < 0) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n-r] % MOD;
}

ll P(int n, int r) {
    if(r > n || r < 0) return 0;
    return fact[n] * inv_fact[n-r] % MOD;
}

// ═══════════════════════════════════════════════════════════════════════════════
// NUMBER THEORY TOOLKIT
// ═══════════════════════════════════════════════════════════════════════════════

// Basic functions
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Extended Euclidean Algorithm
ll exgcd(ll a, ll b, ll& x, ll& y) {
    if(!b) { x = 1, y = 0; return a; }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// Euler's totient function
ll phi(ll n) {
    ll result = n;
    for(ll i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0) n /= i;
            result -= result / i;
        }
    }
    if(n > 1) result -= result / n;
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════════
// ADVANCED DATA STRUCTURES
// ═══════════════════════════════════════════════════════════════════════════════

// Segment Tree with Lazy Propagation
template<typename T>
struct SegTree {
    int n;
    vector<T> tree, lazy;
    T neutral;
    function<T(T, T)> combine;
    function<T(T, T, int)> apply_lazy;
    
    SegTree(vector<T>& arr, T _neutral, function<T(T, T)> _combine, function<T(T, T, int)> _apply_lazy = nullptr) 
        : n(arr.size()), neutral(_neutral), combine(_combine), apply_lazy(_apply_lazy) {
        tree.resize(4 * n, neutral);
        lazy.resize(4 * n, neutral);
        build(arr, 1, 0, n - 1);
    }
    
    void build(vector<T>& arr, int v, int tl, int tr) {
        if(tl == tr) tree[v] = arr[tl];
        else {
            int tm = (tl + tr) / 2;
            build(arr, 2*v, tl, tm);
            build(arr, 2*v+1, tm+1, tr);
            tree[v] = combine(tree[2*v], tree[2*v+1]);
        }
    }
    
    void push(int v, int tl, int tr) {
        if(lazy[v] != neutral && apply_lazy) {
            tree[v] = apply_lazy(tree[v], lazy[v], tr - tl + 1);
            if(tl != tr) {
                lazy[2*v] = combine(lazy[2*v], lazy[v]);
                lazy[2*v+1] = combine(lazy[2*v+1], lazy[v]);
            }
            lazy[v] = neutral;
        }
    }
    
    T query(int l, int r) { return query(1, 0, n-1, l, r); }
    T query(int v, int tl, int tr, int l, int r) {
        if(l > r) return neutral;
        if(l == tl && r == tr) {
            push(v, tl, tr);
            return tree[v];
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return combine(query(2*v, tl, tm, l, min(r, tm)),
                      query(2*v+1, tm+1, tr, max(l, tm+1), r));
    }
    
    void update(int l, int r, T val) { update(1, 0, n-1, l, r, val); }
    void update(int v, int tl, int tr, int l, int r, T val) {
        if(l > r) return;
        if(l == tl && r == tr) {
            if(apply_lazy) lazy[v] = combine(lazy[v], val);
            else tree[v] = val;
            push(v, tl, tr);
            return;
        }
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(2*v, tl, tm, l, min(r, tm), val);
        update(2*v+1, tm+1, tr, max(l, tm+1), r, val);
        push(2*v, tl, tm); push(2*v+1, tm+1, tr);
        tree[v] = combine(tree[2*v], tree[2*v+1]);
    }
};

// Fenwick Tree (Binary Indexed Tree)
template<typename T>
struct FenwickTree {
    vector<T> tree;
    int n;
    
    FenwickTree(int _n) : n(_n), tree(_n + 1, 0) {}
    FenwickTree(vector<T>& arr) : n(arr.size()), tree(n + 1, 0) {
        for(int i = 0; i < n; i++) update(i, arr[i]);
    }
    
    void update(int i, T delta) {
        for(++i; i <= n; i += i & -i) tree[i] += delta;
    }
    
    T query(int i) {
        T sum = 0;
        for(++i; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
    
    T range_query(int l, int r) {
        return query(r) - (l > 0 ? query(l - 1) : 0);
    }
};

// Union-Find (DSU) with full functionality
struct DSU {
    vi parent, rank, size;
    int components;
    
    DSU(int n) : parent(n), rank(n, 0), size(n, 1), components(n) {
        iota(all(parent), 0);
    }
    
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        if(rank[x] == rank[y]) rank[x]++;
        components--;
        return true;
    }
    
    bool connected(int x, int y) { return find(x) == find(y); }
    int get_size(int x) { return size[find(x)]; }
    int get_components() { return components; }
};

// Trie for strings
struct Trie {
    struct Node {
        array<Node*, ALPHABET> children;
        bool is_end;
        int count;
        Node() : is_end(false), count(0) { children.fill(nullptr); }
    };
    
    Node* root;
    Trie() : root(new Node()) {}
    
    void insert(const string& word) {
        Node* curr = root;
        for(char c : word) {
            int idx = c - 'a';
            if(!curr->children[idx]) curr->children[idx] = new Node();
            curr = curr->children[idx];
            curr->count++;
        }
        curr->is_end = true;
    }
    
    bool search(const string& word) {
        Node* curr = root;
        for(char c : word) {
            int idx = c - 'a';
            if(!curr->children[idx]) return false;
            curr = curr->children[idx];
        }
        return curr->is_end;
    }
    
    bool starts_with(const string& prefix) {
        Node* curr = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if(!curr->children[idx]) return false;
            curr = curr->children[idx];
        }
        return true;
    }
    
    int count_words_with_prefix(const string& prefix) {
        Node* curr = root;
        for(char c : prefix) {
            int idx = c - 'a';
            if(!curr->children[idx]) return 0;
            curr = curr->children[idx];
        }
        return curr->count;
    }
};

// ═══════════════════════════════════════════════════════════════════════════════
// GRAPH ALGORITHMS
// ═══════════════════════════════════════════════════════════════════════════════

// Graph class for maximum modularity
struct Graph {
    int n;
    vector<vi> adj;
    vector<vector<pii>> wadj;
    
    Graph(int _n) : n(_n), adj(_n), wadj(_n) {}
    
    void add_edge(int u, int v, bool directed = false) {
        adj[u].pb(v);
        if(!directed) adj[v].pb(u);
    }
    
    void add_weighted_edge(int u, int v, int w, bool directed = false) {
        wadj[u].pb({v, w});
        if(!directed) wadj[v].pb({u, w});
    }
    
    // BFS with distance tracking
    vi bfs(int start) {
        vi dist(n, INF);
        queue<int> q;
        dist[start] = 0;
        q.push(start);
        
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(int u : adj[v]) {
                if(dist[u] == INF) {
                    dist[u] = dist[v] + 1;
                    q.push(u);
                }
            }
        }
        return dist;
    }
    
    // Dijkstra with path tracking
    pair<vl, vi> dijkstra(int start) {
        vl dist(n, LLINF);
        vi parent(n, -1);
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        
        dist[start] = 0;
        pq.push({0, start});
        
        while(!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if(d > dist[v]) continue;
            
            for(auto [u, w] : wadj[v]) {
                if(dist[v] + w < dist[u]) {
                    dist[u] = dist[v] + w;
                    parent[u] = v;
                    pq.push({dist[u], u});
                }
            }
        }
        return {dist, parent};
    }
    
    // Get path from parent array
    vi get_path(int target, const vi& parent) {
        vi path;
        for(int v = target; v != -1; v = parent[v]) path.pb(v);
        reverse(all(path));
        return path;
    }
    
    // Topological sort
    vi topological_sort() {
        vi indegree(n, 0);
        for(int i = 0; i < n; i++) {
            for(int j : adj[i]) indegree[j]++;
        }
        
        queue<int> q;
        for(int i = 0; i < n; i++) {
            if(indegree[i] == 0) q.push(i);
        }
        
        vi result;
        while(!q.empty()) {
            int v = q.front(); q.pop();
            result.pb(v);
            
            for(int u : adj[v]) {
                indegree[u]--;
                if(indegree[u] == 0) q.push(u);
            }
        }
        return result.size() == n ? result : vi(); // empty if cycle
    }
    
    // Find bridges in graph
    vector<pii> find_bridges() {
        vi tin(n, -1), low(n, -1);
        vb visited(n, false);
        vector<pii> bridges;
        int timer = 0;
        
        function<void(int, int)> bridge_dfs = [&](int v, int p) {
            visited[v] = true;
            tin[v] = low[v] = timer++;
            
            for(int u : adj[v]) {
                if(u == p) continue;
                if(visited[u]) {
                    low[v] = min(low[v], tin[u]);
                } else {
                    bridge_dfs(u, v);
                    low[v] = min(low[v], low[u]);
                    if(low[u] > tin[v]) {
                        bridges.pb({min(v, u), max(v, u)});
                    }
                }
            }
        };
        
        for(int i = 0; i < n; i++) {
            if(!visited[i]) bridge_dfs(i, -1);
        }
        
        return bridges;
    }
    
    // Strongly Connected Components
    vector<vi> find_sccs() {
        vi tin(n, -1), low(n, -1);
        vb on_stack(n, false);
        stack<int> st;
        vector<vi> sccs;
        int timer = 0;
        
        function<void(int)> tarjan = [&](int v) {
            tin[v] = low[v] = timer++;
            st.push(v);
            on_stack[v] = true;
            
            for(int u : adj[v]) {
                if(tin[u] == -1) {
                    tarjan(u);
                    low[v] = min(low[v], low[u]);
                } else if(on_stack[u]) {
                    low[v] = min(low[v], tin[u]);
                }
            }
            
            if(low[v] == tin[v]) {
                vi scc;
                int u;
                do {
                    u = st.top(); st.pop();
                    on_stack[u] = false;
                    scc.pb(u);
                } while(u != v);
                sccs.pb(scc);
            }
        };
        
        for(int i = 0; i < n; i++) {
            if(tin[i] == -1) tarjan(i);
        }
        
        return sccs;
    }
};

// ═══════════════════════════════════════════════════════════════════════════════
// STRING ALGORITHMS
// ═══════════════════════════════════════════════════════════════════════════════

// KMP Algorithm
vi compute_lps(const string& pattern) {
    int m = pattern.length();
    vi lps(m, 0);
    int len = 0, i = 1;
    
    while(i < m) {
        if(pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        } else if(len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}

vi kmp_search(const string& text, const string& pattern) {
    vi lps = compute_lps(pattern);
    vi matches;
    int n = text.length(), m = pattern.length();
    int i = 0, j = 0;
    
    while(i < n) {
        if(text[i] == pattern[j]) i++, j++;
        if(j == m) {
            matches.pb(i - j);
            j = lps[j - 1];
        } else if(i < n && text[i] != pattern[j]) {
            if(j) j = lps[j - 1];
            else i++;
        }
    }
    return matches;
}

// Rolling Hash
struct RollingHash {
    static const ll BASE = 31;
    static const ll MOD1 = 1e9 + 7;
    static const ll MOD2 = 1e9 + 9;
    
    string s;
    int n;
    vector<pll> hash, pow_base;
    
    RollingHash(const string& _s) : s(_s), n(_s.length()) {
        hash.resize(n + 1, {0, 0});
        pow_base.resize(n + 1, {1, 1});
        
        for(int i = 0; i < n; i++) {
            hash[i + 1] = {
                (hash[i].fi * BASE + (s[i] - 'a' + 1)) % MOD1,
                (hash[i].se * BASE + (s[i] - 'a' + 1)) % MOD2
            };
            pow_base[i + 1] = {
                (pow_base[i].fi * BASE) % MOD1,
                (pow_base[i].se * BASE) % MOD2
            };
        }
    }
    
    pll get_hash(int l, int r) {
        ll h1 = (hash[r + 1].fi - hash[l].fi * pow_base[r - l + 1].fi % MOD1 + MOD1) % MOD1;
        ll h2 = (hash[r + 1].se - hash[l].se * pow_base[r - l + 1].se % MOD2 + MOD2) % MOD2;
        return {h1, h2};
    }
};

// ═══════════════════════════════════════════════════════════════════════════════
// UTILITIES
// ═══════════════════════════════════════════════════════════════════════════════

// Binary search utilities
template<typename T, typename F>
T binary_search_first_true(T lo, T hi, F check) {
    while(lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

template<typename T, typename F>
T binary_search_last_true(T lo, T hi, F check) {
    while(lo < hi) {
        T mid = lo + (hi - lo + 1) / 2;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// Random number generator
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll random_ll(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
int random_int(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }

// Custom hash for unordered containers
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

// ═══════════════════════════════════════════════════════════════════════════════
// SOLUTION
// ═══════════════════════════════════════════════════════════════════════════════

void solve() {
    int n,x;
    read(n, x);
    vi a(n);
    read(a);
    int init= a[0]-0;
    int final = 2*(x - a[n-1]);
    int max_diff = 0;
    for(int i = 1; i < n; i++) {
        max_diff = max(max_diff, a[i] - a[i-1]);
    }
    writeln(max(max(init,final), max_diff));
    
}













































// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣾⡟⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠘⢷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⣠⣴⣿⣛⣭⣥⣤⣤⣤⣄⠀⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⢀⣴⣶⣦⣀⣾⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠁⠘⠉⠉⠉⠉⠉⢻⣿⣷⣦⡀⠀⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⢸⣿⠟⠙⣿⣟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢓⣠⣤⣤⣤⣀⣀⡀⠈⠻⣿⣷⣄⠀⠉⢠⣶⠀⣀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣿⡿⢠⣾⡗⠛⠀⠀⠀⠀⠀⠀⠀⠀⠚⠃⠀⠀⣠⣾⣿⣿⡿⠛⠛⠛⠛⢿⣿⣷⣦⣌⣻⣿⣷⣤⣾⡿⢠⣿⣄⠀⠀⠰⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣿⣣⣄⣽⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣿⣿⣿⣿⣿⣶⢻⣿⣿⣿⣷⣿⣿⣿⣿⣿⡿⣿⣿⠋⢀⣾⣿⡟⠛⠿⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣿⣿⣿⣿⠋⡇⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠟⠿⣿⡏⢿⡀⠻⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠉⠁⢀⣾⣿⣿⣿⣶⣶⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⣿⠟⢻⣿⡺⠇⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠑⠀⠀⠀⠀⠀⣦⣬⣿⣿⣿⣿⣿⣿⣿⣿⠿⠃⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⢸⡇⠈⠛⢃⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠉⣉⣿⣿⣿⣿⠟⠛⠉⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠈⢿⣴⠶⢿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⣮⣿⣇⣠⡄⢶⣶⣿⡿⠿⠿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠈⢻⣶⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠙⣿⡟⣷⠟⠛⢻⠟⠀⢀⣠⡖⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣧⣸⣶⣿⣿⡟⠀⢸⠇⠀⢀⣾⣿⢁⠄⠀⠀⠀⠀⠀⠀⠀⠀⡿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⣾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⠃⠀⠄⠀⠀⢸⣿⣿⡏⠀⠀⠀⠠⠄⠀⠀⠀⠘⢷⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠟⠡⠞⠀⠀⠀⠀⠀⠙⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⣀⣼⣿⢹⣿⡿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠙⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠀⠀⠀⠀⣠⠀⠀⠀⠀⠀⢹⣷⣀⣴⣶⡶⣶⣦⠀⢀⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⠏⠀⠀⢀⡾⠋⠀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣄⣼⣿⣴⣿⣿⡿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⢀⣼⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⡟⠀⠀⠠⠟⠁⠀⠀⠀⠀⠀⠀⠀⢀⣠⣼⣿⡯⣽⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⢀⣾⠋⠀⠀⠀⠄⠀⠀⠀⠀⠀⢠⡾⠟⠁⠀⠀⠀⠀⠀⠀⠀⣠⣾⡦⠶⠀⠿⠟⡛⠿⠗⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⢀⡾⠃⠀⠀⠀⠀⠀⠀⠀⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⣀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡟⠁⠀⠀⢩⡝⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣄⠀⠀⠀⠀⢰⣿⣟⠀⠀⠀⠀⣸⣿⣦⣤⣶⣿⣿⣿⣿⣿⣿⣿⣿⡛⢿⣶⣤⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣷⣄⠀⠀⠈⠙⣿⣷⠀⠀⠾⠛⠉⠉⠙⠛⠛⠛⠛⠛⠋⢡⡾⣿⣷⣸⡆⠈⠙⠿⣶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀
// ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⡄⠈⢳⣆⠀⠀⠀⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣶⣶⣿⣿⡏⣿⡀⠀⠀⠈⠛⠿⣦⣀⡀⠀⠀⠀⠀⠀
// ⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣷⣼⣿⡇⠀⠀⢿⣷⣄⠀⠀⣟⣀⣀⠀⠀⠀⠀⠀⣀⣀⠀⠀⠀⠉⣿⣿⣿⡇⢹⣷⣆⠀⠀⠀⠀⠈⠉⠛⢿⣶⣦⣤⣀
// ⡙⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣷⣤⠀⣶⣿⣿⣿⣶⣯⣍⣁⣀⠀⠀⠀⢰⣿⣿⡇⠀⠀⠀⠸⣿⣿⡿⠀⢻⣿⣧⠀⠀⠀⠀⢀⣀⠀⠀⢠⡍⠀
 
 
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
    fast_io();

#ifndef ONLINE_JUDGE
    freopen("/run/media/fullname/back/DSA_in_cpp/input", "r", stdin);
    freopen("/run/media/fullname/back/DSA_in_cpp/output", "w", stdout);
#endif

    // Uncomment these if needed:
    // sieve();                    // For prime-related problems
    // precompute_factorials();    // For combinatorics problems
    
    TIMER // Start timing (only in debug mode)
    
    int t = 1;
    cin >> t;  // Uncomment for multiple test cases
    while(t--) {
        solve();
    }
    
    TIME_TAKEN // Print execution time (only in debug mode)

    return 0;
}