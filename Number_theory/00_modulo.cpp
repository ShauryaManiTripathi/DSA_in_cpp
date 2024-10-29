#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin>>n;
    int M=47;
    long long factorial=1;
    for (int i = 2; i <= n; i++)factorial=(factorial*i)%M;
    cout<<factorial<<endl;
    return 0;
}

// 1. Large Prime Number: 1e10+7 is a large prime number, which helps in reducing the chances of collisions in hashing algorithms and ensures a uniform distribution of hash values.
// 2. Prevents Overflow: Using a large modulus like 1e10+7 helps in preventing overflow in arithmetic operations, especially in competitive programming where large numbers are common.
// 3. Mathematical Properties: Prime numbers have desirable properties in modular arithmetic, such as ensuring that every non-zero element has a multiplicative inverse, which is crucial for algorithms involving division in modular arithmetic.
// 4. very close to int_max
// int modInverse(int a, int m) {
//     int m0 = m, t, q;
//     int x0 = 0, x1 = 1;
//     if (m == 1) return 0;
//     while (a > 1) {
//         q = a / m;
//         t = m;
//         m = a % m, a = t;
//         t = x0;
//         x0 = x1 - q * x0;
//         x1 = t;
//     }
//     if (x1 < 0) x1 += m0;
//     return x1;
// }

