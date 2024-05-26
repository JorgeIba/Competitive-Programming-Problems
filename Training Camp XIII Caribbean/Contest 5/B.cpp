#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef struct item *pitem;
struct item {
	int pr,cnt,val;
  
	pitem l,r;
    pitem f;
	item(int val): pr(rand()),cnt(1),val(val), l(0), r(0), f(0) {}
};
 
const lli INF = 1e9;
 
int cnt(pitem t){return t?t->cnt:0;}
void upd_cnt(pitem t){
	if(t){
		t->cnt=cnt(t->l)+cnt(t->r)+1;
	}
}
 
void merge(pitem& t, pitem l, pitem r){
	push(l);push(r);
	if(!l||!r)t=(l?l:r);
	else if(l->pr>r->pr)merge(l->r,l->r,r),l->r->f=t=l;
	else merge(r->l,l,r->l),r->l->f=t=r;
	upd_cnt(t);
}
 
void split(pitem t, pitem& l, pitem& r, int sz){
	if(!t){l=r=0;return;}
	push(t);
	if(sz<=cnt(t->l)){
		split(t->l,l,t->l,sz);r=t;
		if(l)l->f=0;
		if(t->l)t->l->f=t;
	}
	else {
		split(t->r,t->r,r,sz-1-cnt(t->l));l=t;
		if(r)r->f=0;
		if(t->r)t->r->f=t;
	}
	upd_cnt(t);
}
void push_all(pitem t){
	if(t->f)push_all(t->f);
	push(t);
}
pitem root(pitem t, int& pos){
	push_all(t);
	pos=cnt(t->l);
	while(t->f){
		pitem f=t->f;
		if(t==f->r) pos += cnt(f->l)+1;
		t = f;
	}
	return t;
}



int main () {
	fastIO();
	
    int n, q; cin>>n>>q;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;
    for(auto &x: nums) x--;


    vector< pitem > nodes(n);
    for(int i = 0; i < n; i++) {
        auto num = nums[i];
        nodes[i] = new item(i+1);
    }


    vector<bool> visited(n);
    vector< vector<int> > cycles;
    for(int i = 0; i < n; i++){
        if(visited[i]) continue;

        int curr = i, start = i;
        vector<int> cycle;
        do{
            cycle.push_back(curr);
            visited[curr] = true;   
            curr = nums[curr];
        }while(curr != start);

        cycles.push_back(cycle);
    } 


    for(auto &v: cycles) {
        for(int i = 0; i < SZ(v)-1; i++) {
            int curr = v[i];
            int next = v[i+1];
            

            int pos_;
            auto parent_curr = root(nodes[curr], pos_);
            auto parent_next = root(nodes[next], pos_);
            merge(parent_curr, parent_curr, parent_next);
        }
    }
    

    auto get_val = [&](pitem root, int kth) {
        pitem left, middle, right;

        kth++;

        split(root, left, right, kth);
        split(left, left, middle, kth-1);
        
        int val = middle->val;

        merge(root, left, middle);
        merge(root, root, right);

        return val;
    };



    while(q--){
        int t; cin>>t;

        if(t == 2) {
            int x, k; cin>>x>>k; x--;
            int pos; 
            auto parent = root(nodes[x], pos);

            int sz = cnt(parent);
            int to_print = (pos + k) % sz;

            cout << get_val(parent, to_print) << endl;
        } else {
            int x, y; cin>>x>>y; x--, y--;

            int pos_x;
            auto father_x = root(nodes[x], pos_x);

            int pos_y;
            auto father_y = root(nodes[y], pos_y);
            

            if(father_x != father_y) {


                pitem left_x, right_x;
                pitem left_y, right_y;

                split(father_x, left_x, right_x, pos_x+1);
                split(father_y, left_y, right_y, pos_y+1);


                merge(father_x, left_x, right_y);
                merge(father_x, father_x, left_y);
                merge(father_x, father_x, right_x);

            } else {

                if(pos_x > pos_y) swap(pos_x, pos_y);

                pitem left, middle, right;
                split(father_x, middle, right, pos_y+1);
                split(middle, left, middle, pos_x + 1);

                merge(father_x, left, right);

            }
        }
    }


	return 0;
}

