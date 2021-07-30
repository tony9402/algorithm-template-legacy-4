#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct SegmentLazy {
    bool _set_size;
    vector<T> _tree, _lazy;
    int siz;

    SegmentLazy():_set_size(false) { }
    SegmentLazy(int N):_set_size(true) { setSize(N); }
    void setSize(int N) { 
        _set_size=true;
        for(siz=1;siz<=N;siz<<=1); 
        _tree = _lazy = vector<T>(siz << 1);
    }
    void setItem(int idx, T data) { 
        assert(_set_size);
        _tree[idx + siz] = data;
    }
    void build() { 
        assert(_set_size);
        int idx = siz;
        while(--idx) _tree[idx] = merge(_tree[idx << 1], _tree[idx << 1 | 1]);
    }
    void propagate(int l, int r, int idx) {
        if(_lazy[idx]) {
            _tree[idx] = merge(_tree[idx], _lazy[idx] * (r - l + 1));
            if(l != r) {
                _lazy[idx << 1] = merge(_lazy[idx << 1], _lazy[idx]);
                _lazy[idx << 1 | 1] = merge(_lazy[idx << 1 | 1], _lazy[idx]);
            }
            _lazy[idx] = 0;
        }
    }
    void update(int l, int r, int s, int e, int idx, T data) {
        if(s <= l && r <= e) {
            _lazy[idx] = merge(_lazy[idx], data);
            propagate(l, r, idx);
            return;
        }
        propagate(l, r, idx);
        if(e <  l || r <  s) return;
        int m = (l + r) / 2;
        update(l, m, s, e, idx << 1, data);
        update(m + 1, r, s, e, idx << 1 | 1, data);
        _tree[idx] = merge(_tree[idx << 1], _tree[idx << 1 | 1]);
    }
    void update(int s, int e, T data) { 
        assert(_set_size);
        update(0, siz - 1, s, e, 1, data); 
    }
    T query(int l, int r, int s, int e, int idx) {
        propagate(l, r, idx);
        if(s <= l && r <= e) return _tree[idx];
        if(e <  l || r <  s) return T(0);
        int m = (l + r) / 2;
        return merge(query(l, m, s, e, idx << 1), query(m + 1, r, s, e, idx << 1 | 1));
    }
    T query(int s, int e) { 
        assert(_set_size);
        return query(0, siz - 1, s, e, 1); 
    }
    T merge(T a, T b) { return a + b; }
};

SegmentLazy<long long> tree;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K; cin >> N >> M >> K;
    M += K;
    tree.setSize(N);
    for(int i = 0; i < N; i++) {
        int x; cin >> x;
        tree.setItem(i, x);
    }
    tree.build();
    while(M --) {
        int type; cin >> type;
        int a, b, c;
        if(type == 1) {
            cin >> a >> b >> c;
            tree.update(--a, --b, c);
        }
        else {
            cin >> a >> b;
            cout << tree.query(--a, --b) << '\n';
        }
    }

    return 0;
}
