#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define fore(i, x, n) for (int i = x; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


struct UnionFind {
	int n,comp;
	vector<int> uf,si,c;
	UnionFind(int n=0):n(n),comp(n),uf(n),si(n,1){
		fore(i,0,n)uf[i]=i;}
	int find(int x){return x==uf[x]?x:find(uf[x]);}
	bool join(int x, int y){
		if((x=find(x))==(y=find(y)))return false;
		if(si[x]<si[y])swap(x,y);
		si[x]+=si[y];uf[y]=x;comp--;c.push_back(y);
		return true;
	}
	int snap(){return c.size();}
	void rollback(int snap){
		while(c.size()>snap){
			int x=c.back();c.pop_back();
			si[uf[x]]-=si[x];uf[x]=x;comp++;
		}
	}
};

vector<lli> ans;

enum {ADD,DEL,QUERY};
struct Query {int type,x,y;};
struct DynCon {
	vector<Query> q;
	UnionFind dsu;
	vector<int> mt;
	map<pair<int,int>,int> last;
	DynCon(int n):dsu(n){}
	void add(int x, int y){
		if(x>y)swap(x,y);
		q.push_back((Query){ADD,x,y});mt.push_back(-1);last[{x,y}]=q.size()-1;
	}
	void remove(int x, int y){
		if(x>y)swap(x,y);
		q.push_back((Query){DEL,x,y});
		int pr=last[{x,y}];mt[pr]=q.size()-1;mt.push_back(pr);
	}
	void query(){q.push_back((Query){QUERY,-1,-1});mt.push_back(-1);}
	void process(){ // answers all queries in order
		if(!q.size())return;
		fore(i,0,q.size())if(q[i].type==ADD&&mt[i]<0)mt[i]=q.size();
		go(0,q.size());
	}
	void go(int s, int e){
		if(s+1==e){
			if(q[s].type==QUERY) // answer query using DSU
                ans.push_back(dsu.comp-1);
			return;
		}
		int k=dsu.snap(),m=(s+e)/2;
		for(int i=e-1;i>=m;--i)if(mt[i]>=0&&mt[i]<s)dsu.join(q[i].x,q[i].y);
		go(s,m);dsu.rollback(k);
		for(int i=m-1;i>=s;--i)if(mt[i]>=e)dsu.join(q[i].x,q[i].y);
		go(m,e);dsu.rollback(k);
	}
};


int main () {
	//fastIO();

    ifstream cin("connect.in");
	ofstream cout("connect.out");


	lli n, k; cin>>n>>k;
	
    DynCon *DC = new DynCon(n+1);

    while(k--) {
        char t; cin>>t;
        if(t == '?') {
            DC->query();
        } else if(t == '+') {
            int u, v; cin>>u>>v;

            DC->add(u, v);
        } else {
            int u, v; cin>>u>>v;
            DC->remove(u, v);
        }
    }

    DC->process();
    for(auto x: ans) cout << x << endl;

	return 0;
}

 