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
