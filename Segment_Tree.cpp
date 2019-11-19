#include<iostream>
#include<algorithm>

using namespace std;

template<typename T>
class Segment{
    typedef long long ll;
    T *Tree;
    T siz;
    ll _MAX = (1<<21);

public:
    Segment(){
        Tree = new T[_MAX];
    }
    ~Segment(){
        delete[] Tree;
    }
    
}
