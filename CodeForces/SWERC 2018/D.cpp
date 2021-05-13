#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std;
 
typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 100005;

struct event{
	int y,type;
	event(int y, int type): y(y), type(type){}
	bool operator<(const event& e){
		return y < e.y;
	}
};

lli sum;
int X,Y,n,y_ceros;
int cols[MAXN][2];
set<int> s_y,s_x;
set<pii> s;
vector<event> events;

lli solve(){
	int cnt_up,cnt_down;
	cnt_down = s_x.size();
	cnt_up = 0;
	int j = 0;
	lli ans = 1e18;
	forn(i,Y){
//		cout << "[y]: " << i << " sum: " << sum << endl;
		ans = min(ans,X-1 + 2*sum);
		while(j < events.size() && events[j].y == i){
			if(events[j].type)
				cnt_up++;
			else
				cnt_down--;
			j++;
		}
//		cout << "cnt_up: " << cnt_up << endl;
//		cout << "cnt_down: " << cnt_down << endl;
		sum += cnt_up;
		sum -= cnt_down;
	}
	return ans;
}

int main () {
	fastIO();
	cin >> X >> Y >> n;
	forn(i,MAXN){
		cols[i][0] = 1e9;
		cols[i][1] = -1;
	}
	forn(i,n){
		pii p;
		cin >> p.fi >> p.se;
		if(p.se == 0) y_ceros++;
		s_y.insert(p.se);
		s_x.insert(p.fi);
		cols[p.fi][0] = min(cols[p.fi][0],p.se);
		cols[p.fi][1] = max(cols[p.fi][1],p.se);
	}
	for(auto i:s_x){
//		cout << "[x] = " << i << " min_y: " << cols[i][0] << " max_y: " << cols[i][1] << endl;
		events.pb(event(cols[i][0],1));
		events.pb(event(cols[i][1],0));
		sum += cols[i][1];
	}
	sort(all(events));
	cout << solve() << endl;
	return 0;
}
