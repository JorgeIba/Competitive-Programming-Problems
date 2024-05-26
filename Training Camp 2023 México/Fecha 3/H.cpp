#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


struct Node{
    lli dishes=0, people=0;

    bool flagLazy = false;
    int lazy = 0;

    lli l, r;

    Node(){}
    Node(lli dishes, lli people, int l, int r): dishes(dishes), people(people), l(l), r(r) {}

    // Combine 2 nodes
    Node operator+(const Node &b) {
        Node res(0, 0, l, b.r);
        res.dishes = b.dishes + (dishes - min(dishes, b.people));
        res.people = people + (b.people - min(dishes, b.people));

        return res;
    }

    // Update range
    void updateNode(int type, int value) {
        if(type == 0) {
            dishes += value;
        } else {
            people += value;
        }

        int match = min(dishes, people);

        dishes -= match;
        people -= match;
    }
};

// T Lo que le vas a pasar
template<typename T>
struct SegmentTree {
    vector<Node> ST;
    int N;

    SegmentTree(int n, const vector<T> &values): N(n){
        ST.resize(4*N);
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value, int idx){
        if(value > 0) {
            ST[curr] = Node(value, 0, idx, idx);
        } else {
            ST[curr] = Node(0, -value, idx, idx);
        }
    }

    // UPDATE
    void update(int curr, int l, int r, int ql, int qr, int type, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            ST[curr].updateNode(type, value);
            return;
        }

        // pushToChildren(curr);

        int mid = l + (r-l)/2;
        update(2*curr, l, mid, ql, qr, type, value);
        update(2*curr+1, mid+1, r, ql, qr, type, value);

        ST[curr] = ST[2*curr] + ST[2*curr+1];
    }
    void update(int ql, int qr, int type, T value){
        update(1, 1, N, ql, qr, type, value);
    }
    
    // QUERY
    Node query(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return Node();
        else if(ql <= l && r <= qr) return ST[curr];
        else {
            // pushToChildren(curr);
            int mid = l + (r-l) / 2;
            return query(2*curr, l, mid, ql, qr) + query(2*curr+1, mid+1, r, ql, qr);
        }
    }
    Node query(int ql, int qr){
        return query(1, 1, N, ql, qr);
    }

    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1], l);
        } else {
            int mid = l + (r-l)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            ST[curr] = ST[2*curr] + ST[2*curr+1];
        }
    }
};


const int maxN = 1e6;


int main () {
	// fastIO();
	
    int n, m; cin>>n>>m;
    vector< int > dishes(n), people(m);

    for(auto &x: dishes) cin>>x;
    for(auto &x: people) cin>>x;

    vector< int > values(maxN+10);
    for(auto dish: dishes) values[dish-1]++;
    for(auto person: people) values[person-1]--;


    SegmentTree<int> *ST = new SegmentTree<int>(maxN+10, values);

    auto solve = [&]() {
        if(!ST->ST[1].dishes) return -1;

        int l = 1, r = maxN, ans = -1; 
        while(l <= r) {
            int mid = (l+r) / 2;
            if( ST->query(mid, maxN).dishes > 0 ) {
                ans = mid;
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        return ans;
    };


    int q; cin>>q;
    while(q--){
        int t; cin>>t;
        if( t == 1 ){
            int i, x; cin>>i>>x;
            int val_before = dishes[i-1];

            ST->update(val_before, val_before, 0, -1);
            ST->update(x, x, 0, 1);

            dishes[i-1] = x;
        } else {

            int i, x; cin>>i>>x;
            int val_before = people[i-1];

            ST->update(val_before, val_before, 1, -1);
            ST->update(x, x, 1, 1);

            people[i-1] = x;
        }
        cout << solve() << endl;
    }
    

	return 0;
}

