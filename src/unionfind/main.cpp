#include<bits/stdc++.h>

using namespace std;

struct UF {
    bool _set_size;
    vector<int> _uf, _subsize;
    UF():_set_size(false) { }
    UF(int N):_set_size(true) { setSize(N); }
    void setSize(int N) {
        _set_size = true;
        _uf = vector<int>(N, -1);
        _subsize = vector<int>(N, 1);
    }
    int find(int x) {
        assert(_set_size);
        if(_uf[x] < 0) return x;
        return _uf[x] = find(_uf[x]);
    }
    bool merge(int a, int b) {
        assert(_set_size);
        a = find(a); b = find(b);
        if(a == b) return false;
        _uf[b] = a;
        _subsize[a] += _subsize[b];
        return true;
    }
    int operator[](int idx) { return find(idx); }
    int getSize(int x) { return _subsize[x]; }
};

UF uf;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N; cin >> N;
    uf.setSize(N);
    vector<tuple<int, int, int>> V;
    for(int i = 1; i < N; i++) {
        int a, b, c; cin >> a >> b >> c;
        V.emplace_back(-c, --a, --b);
    }
    sort(V.begin(), V.end());
    long long ans = 0;
    for(auto [c, a, b] : V) {
        ans += 1LL * -c * uf.getSize(uf[a]) * uf.getSize(uf[b]);
        uf.merge(a, b);
    }
    cout << ans;

    return 0;
}
