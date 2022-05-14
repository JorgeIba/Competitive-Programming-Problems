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

struct RollingHash{
	    lli hash=0, mod, p, magic, inverse_p, size = 0;
    deque<char> curr;
    RollingHash(lli p, lli mod): p(p), mod(mod){
        inverse_p = getInverse();
        magic = 1;
    }
    void push_back(char newAdd)
    {
        hash = (hash*p + newAdd*p)%mod;
        magic = (magic*p)%mod;
        curr.push_back(newAdd);
    }
    char pop_front()
    {
        char oldErase = curr.front();
        hash = (hash - oldErase*magic)%mod;
        if(hash<0) hash += mod;
        magic = (magic*inverse_p)%mod;
        return oldErase;
    }

    char pop_back()
    {
        char last = curr.back();
        hash = (hash - curr.back()*p)%mod;
        if(hash<0) hash += mod;
        hash = (hash*inverse_p)%mod;
        magic = (magic*inverse_p)%mod;
        curr.pop_back();
        return last;
    }

    void push_front(char newAdd){
        magic = (magic*p)%mod;
        hash = (hash + newAdd*magic)%mod;
        curr.push_front(newAdd);
    }

    void shiftRight(){ push_front(pop_back()); }

    void shiftLeft(){ push_back(pop_front()); }

    char getLast(){ return curr.back(); }
    lli getHash(){return hash;}
    lli getInverse()
    {
        lli b = mod - 2; // If mod is prime, p^(mod-2) = 1 (mod m)
        lli res = 1, aux = p;
        while(b)
        {
            if(b&1) res = (res*aux)%mod;
            b>>=1;
            aux = (aux*aux)%mod;
        }
        return res;
    }
};
const int mxn = 101;
string p[mxn];
int n;
int main(){
	fastIO();
	cin >> n;
	forn(i,n) cin >> p[i];
	set<pii> s;
	forn(i,n){
		RollingHash r1(31,1e9+7);
		RollingHash r2(37,1e8+7);
		for(char c : p[i]){
			r1.push_front(c);
			r2.push_front(c);
		}
		s.insert(pii(r1.getHash(), r2.getHash()));
	}
	forn(i,n){
		RollingHash r1(31,1e9+7);
		RollingHash r2(37,1e8+7);
		for(char c : p[i]){
			r1.push_front(c);
			r2.push_front(c);
		}
		if(s.find(pii(r1.getHash(), r2.getHash())) == s.end())
			continue;
		forn(j,SZ(p[i])){
			r1.shiftRight();
			r2.shiftRight();
			if(s.find(pii(r1.getHash(), r2.getHash())) != s.end())
				s.erase(pii(r1.getHash(), r2.getHash()));
		}
		s.insert(pii(r1.getHash(), r2.getHash()));
	}
	cout << s.size() << '\n';
}

