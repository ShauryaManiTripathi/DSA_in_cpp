#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool isDivisible(string& num_str, ll div) {
    ll remainder = 0;
    for(char digit : num_str) {
        remainder = (remainder * 10 + (digit - '0')) % div;
    }
    return remainder == 0;
}
string solve(int n) {
    if(n == 1) return "-1";
    string num(n, '3'); 
    num[n-1] = '6';
    while(true) {
        if(isDivisible(num, 66)) {
            return num;
        }
        int i = n-2;
        while(i >= 0 && num[i] == '6') {
            num[i] = '3';
            i--;
        }
        if(i < 0) return "-1";
        num[i] = '6';
    }
    
    return "-1";
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/home/shaurya/Desktop/DSA_in_cpp/input", "r", stdin);
    freopen("/home/shaurya/Desktop/DSA_in_cpp/output", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        cout << solve(n) << "\n";
    }
    return 0;
}