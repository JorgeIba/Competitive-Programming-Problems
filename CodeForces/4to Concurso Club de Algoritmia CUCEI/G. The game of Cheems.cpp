#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

vector<int> suff;
vector<int> lcp;
void count_sort(vector<int>& p, const vector<int>& c){
	int n = c.size();
	vector<int> p_new(n), cnt(n+1);
	for(int x : c) cnt[x+1]++;
	for(int i = 1; i < n; i++) cnt[i] += cnt[i-1];
	for(int x : p) p_new[cnt[c[x]]++] = x;
	p.swap(p_new);
}
void suffixArray(string t){
	t += "$"; //Alphabetically less that all characters
	int n = SZ(t);
	suff.assign(n,0);
	lcp.assign(n,0);
	vector<int> c(n);
	vector<pair<char,int>> a(n);
	for(int i = 0; i < n; i++) a[i] = {t[i], i};
	sort(a.begin(), a.end());
	for(int i = 0; i < n; i++) suff[i] = a[i].se;
	c[suff[0]] = 0;
	for(int i = 1; i < n; i++){
		if(a[i].fi == a[i-1].fi) c[suff[i]] = c[suff[i-1]];
		else c[suff[i]] = c[suff[i-1]]+1;
	}
	int k = 0;
	while((1<<k) < n){
		for(int i = 0; i < n; i++) suff[i] = (suff[i]-(1<<k)+n)%n;
		count_sort(suff,c);
		vector<int> c_new(n);
		c_new[suff[0]] = 0;
		for(int i = 1; i < n; i++){
			pair<int,int> prev = {c[suff[i-1]], c[(suff[i-1]+(1<<k))%n]};
			pair<int,int> now = {c[suff[i]], c[(suff[i]+(1<<k))%n]};
			if(now == prev) c_new[suff[i]] = c_new[suff[i-1]];
			else c_new[suff[i]] = c_new[suff[i-1]]+1;
		}
		c.swap(c_new);
		k++;
	}
	k = 0;
	for(int i = 0; i < n-1; i++){
		int pi = c[i];
		int j = suff[(pi-1+n)%n];
		while((i+k) < n && (j+k) < n && t[i+k] == t[j+k]) k++;
		lcp[pi] = k;
		k = max(k-1, 0);
	}
	//for(int x : lcp) cout << x << ' '; cout << '\n';
}
void print(string t){
	int n = t.size();
	for(int x : suff) cout << t.substr(x, n-x);
}
const int mod = 1e9+7;
lli binpow(lli a, lli b){
	lli ans = 1;
	while(b){
		if(b&1) ans = (ans*a)%mod;
		a = (a*a)%mod;
		b >>= 1;
	}
	return ans;
}
lli get_sum(lli n, lli rep, lli k){
	//cout <<"N: " <<  n << ' '  << "rep: " << rep << '\n';
	return (n*binpow(rep,k))%mod;
}
lli calc(int k){
	stack<pii> s;
	lli ans = 0;
	lcp.pb(0);
	for(int i = 0; i < SZ(lcp); i++){
		if(s.size()){
			//cout << "TOPE: " << s.top().fi << ' ' << s.top().se << '\n';
		}
		if(lcp[i] == 0){
			if(s.empty()) continue;
			else{
				while(!s.empty()){
					pii aux = s.top();
					s.pop();
					if(!s.empty()){
						ans = (ans+get_sum(aux.fi - s.top().fi, aux.se, k))%mod;
						pii aux2 = s.top(); s.pop();
						aux2.se += aux.se-1;
						s.push(aux2);
					}
					else{
						ans = (ans + get_sum(aux.fi, aux.se, k))%mod;
					}
				}
			}
		}
		else{
			if(s.empty()) {
				s.push({lcp[i],2});
			}
			else{
				if(s.top().fi == lcp[i]){
					pii aux = s.top();s.pop();
					aux.se++;
					s.push(aux);
				}
				else if(s.top().fi < lcp[i]){
					//cout << lcp[i] << '\n';
					s.push({lcp[i], 2});
				}
				else{
					pii aux;
					bool done = 1;
					while(s.top().fi >= lcp[i]){
						aux = s.top(); s.pop();
						if(s.empty()){
							s.push({lcp[i], aux.se});
							done = 1;
							break;
						}
						else{
							pii aux2 = s.top(); s.pop();
							aux2.se += aux.se - 1;
							ans = (ans + get_sum(aux.fi - aux2.fi, aux.se,k))%mod;
							s.push(aux2);
						}
					}
					if(done){
						aux = s.top(); s.pop(); aux.se++;
						s.push(aux);
					}
					else{
						s.push({lcp[i], 2});
					}
				}
			}
		}
	}
	return ans;
}

lli just_one(int k, int n){
	lli ans = 0;
	forr(i,1,SZ(suff)-1){
		ans = (ans+(n-suff[i]-max(lcp[i], lcp[i+1])))%mod;
		if(ans < 0) ans += mod;
	}
	return ans;
}

int main(){
	fastIO();
	string s;
	int n, k;
	cin >> n >> k;
	cin >> s;
	suffixArray(s);
	lli ans = (calc(k)+ just_one(k,n))%mod;
	cout << ans << '\n';
	return 0;
}