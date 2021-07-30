template<typename T>
struct Segment {
    bool _set_size;
    int siz;
    vector<T> _tree;
    
    Segment():_set_size(false) {}
    Segment(int N):_set_size(true) { setSize(N); }
    void setSize(int N) { 
        _set_size = true;
        for(siz = 1; siz <= N; siz <<= 1); 
        _tree = vector<T>(siz << 1);
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
    void update(int idx, T data) {
        assert(_set_size);
        _tree[idx += siz] = data;
        while(idx >>= 1) _tree[idx] = merge(_tree[idx << 1], _tree[idx << 1 | 1]);
    }
    T query(int l, int r) {
        assert(_set_size);
        T ret = 0;
        for(l += siz, r += siz + 1; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret = merge(ret, _tree[l++]);
            if(r & 1) ret = merge(ret, _tree[--r]);
        }
        return ret;
    }
    T operator[](int idx) const { return _tree[siz + idx]; }
    T merge(T a, T b) { return a + b; } // sample
};
