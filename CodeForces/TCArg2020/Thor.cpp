#include<bits/stdc++.h>
#define forn(i,n) for(int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i<= n; i++)
#define __ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define fi first
#define se second
#define pb push_back
#define all(u) u.begin(),u.end()
#define lli long long int
#define ld long double
 
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<vi> vvi;
vi queries;
int n, q, unread = 0, act = 0, opc, x;
int app[400050];
int indx[400050];
map<int,bool> m;
int main(){__
	memset(indx,-1,sizeof(indx));
    memset(app, 0, sizeof(app));
	cin >> n >> q;
	forn(i,q){
		cin >> opc >> x;
		if(opc == 1){
			queries.pb(x);
			unread++;
			app[x]++;
		}
		else if(opc == 2){
			unread -= app[x];
			app[x] = 0;
			indx[x] = queries.size();
		}
		else{
			x--;
			for(;act <= x; act++){
				if(app[queries[act]] && indx[queries[act]] <= act) {
					app[queries[act]]--;
					unread--;
					indx[queries[act]] = act;
				}
			}
		}
		cout << unread << '\n';
	}
	return 0;
}