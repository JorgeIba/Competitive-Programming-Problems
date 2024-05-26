#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;


// example that supports range reverse and addition updates, and range sum query
// (commented parts are specific to this  problem)
typedef struct item *pitem;
struct item {
	int pr,cnt,val;

    int maxi;

	pitem l,r;
    pitem f;
	item(int val): pr(rand()),cnt(1),val(val), maxi(val), l(0), r(0), f(0) {}
};

void push(pitem it){
	if(it){
		/*if(it->rev){
			swap(it->l,it->r);
			if(it->l)it->l->rev^=true;
			if(it->r)it->r->rev^=true;
			it->rev=false;
		}
		it->val+=it->add;it->sum+=it->cnt*it->add;
		if(it->l)it->l->add+=it->add;
		if(it->r)it->r->add+=it->add;
		it->add=0;*/
	}
}

const lli INF = 1e9;

int cnt(pitem t){return t?t->cnt:0;}
int maxi(pitem t){return t?push(t),t->maxi:-INF;}
void upd_cnt(pitem t){
	if(t){
		t->cnt=cnt(t->l)+cnt(t->r)+1;
        
		t->maxi= max({t->val, maxi(t->l), maxi(t->r)});
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
pitem root(pitem t, int& pos){ // get root and position for node t
	push_all(t);
	pos=cnt(t->l);
	while(t->f){
		pitem f=t->f;
		if(t==f->r) pos += cnt(f->l)+1;
		t = f;
	}
	return t;
}
void output(pitem t){ // useful for debugging
	if(!t)return;
	push(t);
	output(t->l);printf(" %d",t->val);output(t->r);
}
// use merge and split for range updates and queries

struct Query{
    int t, a, b;
    Query() {}
    Query(int t, int a): t(t), a(a) {}
    Query(int t, int a, int b): t(t), a(a), b(b) {}
};


int main () {
	//fastIO();
	
    int n, m, q; cin>>n>>m>>q;

    vector< vector<int> > values(n+1);

    vector< Query > queries(q);
    for(int i = 0; i < q; i++) {
        int t; cin>>t;
        if(t == 1) {
            int a, b; cin>>a>>b;
            queries[i] = Query(t, a, b);

            values[a].push_back(b);
            values[a].push_back(b+1);

            values[a+1].push_back(b);
            values[a+1].push_back(b+1);
        } else {
            int a; cin>>a;
            queries[i] = Query(t, a);
        }
    }

    for(int i = 1; i <= n; i++) {
        values[i].push_back(1);
        values[i].push_back(m+1);
    }

    for(int i = 1; i <= n; i++){
        sort(all(values[i]));
        values[i].erase(unique(all(values[i])), values[i].end());
    }

    vector< map<int,int> > original_to_map(n+1);

    for(int i = 1; i <= n; i++){
        for(int j = 0; j < SZ(values[i]); j++){
            int num = values[i][j];
            original_to_map[i][num] = j;
        }
    }

    
    vector< vector< pitem > > treap_arrays(n+1);

    for(int i = 1; i <= n; i++){
        int m = SZ(values[i]);
        pitem p_all = NULL;
        for(int j = 0; j < m; j++) {
            int pos = 0;
            pitem treap_val = new item(   j != m-1 ? 0 : i );
            merge( p_all, p_all, treap_val);
            treap_arrays[i].push_back( treap_val );
        }
    }


    for(int i = 0; i < q; i++){
        auto [t, a, b] = queries[i];
        if(t == 2){
            int pos = 0;
            pitem root_a = root(treap_arrays[a][0], pos);
            cout << root_a->maxi << endl;
        } else {
            // Split (a, b) y (a, b+1), 
            // Split (a+1, b) y (a+1, b+1)
            // Merge (a, b) with (a+1, b+1)
            // Merge(a+1, b) with (a, b+1)

            int q_ab = original_to_map[a][b];
            int q_a1b = original_to_map[a+1][b];


            int pos_ab = 0;
            int pos_a1b = 0;
            pitem parent_qab = root(treap_arrays[a][q_ab], pos_ab);
            pitem parent_qa1b = root(treap_arrays[a+1][q_a1b], pos_a1b);


            pitem left_a, right_a, left_a1, right_a1;
            split(parent_qab, left_a, right_a, pos_ab + 1);
            split(parent_qa1b, left_a1, right_a1, pos_a1b + 1);

            merge(parent_qab, left_a, right_a1);
            merge(parent_qa1b, left_a1, right_a);
        }
    }


	return 0;
}

