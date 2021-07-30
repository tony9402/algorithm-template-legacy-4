#include<bits/stdc++.h>

using namespace std;

const long long W = 3;
const long long MOD = 998244353;

template<typename T>
T power(T a, T b) {
    T ret = 1;
    while(b) {
        if(b & 1) ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return ret;
}

void _NTT(vector<long long> &V, bool inv = false) {
    int N = (int)V.size();
    vector<long long> root(N >> 1);
    for(int i = 1, j = 0; i < N; i++) {
        int bit = (N >> 1);
        for(; j >= bit; bit >>= 1) j &= ~bit; 
        j |= bit;
        if(i < j) swap(V[i], V[j]);
    }
    long long angle = power(W, (MOD - 1) / N);
    if(inv) angle = power(angle, MOD - 2);
    root[0] = 1;
    for(int i = 1; i * 2 < N; i++) root[i] = root[i - 1] * angle % MOD;
    for(int i = 2; i <= N; i <<= 1) {
        long long step = N / i;
        for(int j = 0; j < N; j += i) {
            for(int k = 0; k * 2 < i; k++) {
                long long u = V[j | k];
                long long v = V[j | k | i >> 1] * root[step * k] % MOD;
                V[j | k] = (u + v) % MOD;
                V[j | k | i >> 1] = (u - v) % MOD;
                if(V[j | k | i >> 1] < 0) V[j | k | i >> 1] += MOD;
            }
        }
    }
    if(inv) {
        long long t = power(1LL * N, MOD - 2);
        for(int i = 0; i < N; i++) V[i] = (V[i] * t) % MOD;
    }
}

vector<long long> multiply(const vector<long long> &vec1, const vector<long long> &vec2) { 
    vector<long long> A(vec1.begin(), vec1.end());
    vector<long long> B(vec2.begin(), vec2.end());
    int L = (int)vec1.size(), R = (int)vec2.size(), N;
    for(N = 2; N < L + R; N <<= 1);
    A.resize(N); B.resize(N);
    _NTT(A); _NTT(B);
    for(int i = 0; i < N; i++) A[i] = A[i] * B[i] % MOD;
    _NTT(A, true);
    return A;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    string a, b; cin >> a >> b;
    vector<long long> A, B, result;
    A.reserve(a.size()); B.reserve(b.size());
    for(int i = (int)a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for(int i = (int)b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');
    result = multiply(A, B);
    result.push_back(0);
    for(int i = 0; i < (int)result.size(); i++) {
        if(result[i] < 0) {
            int b = (-result[i] + 9) / 10;
            result[i + 1] -= b;
            result[i] += b * 10;
        }
        else {
            result[i + 1] += result[i] / 10;
            result[i] %= 10;
        }
    }
    while(result.size() > 1 && result.back() == 0) result.pop_back();
    string s;
    for(int i = (int)result.size() - 1; i >= 0; i--) s += result[i] + '0';
    cout << s;

    return 0;
}
