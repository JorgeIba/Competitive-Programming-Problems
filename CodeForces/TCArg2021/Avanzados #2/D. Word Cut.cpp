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
#define var(x) #x << " = " << x

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

struct RollingHash
{
    lli hash_=0, mod, p, magic, inverse_p, size = 0; 
    deque<char> curr;
    RollingHash(lli p, lli mod): p(p), mod(mod){ 
        inverse_p = getInverse(); 
        magic = 1;
    }
    void push_back(char newAdd)
    {
        hash_ = (hash_*p + newAdd*p)%mod;
        magic = (magic*p)%mod;
        curr.push_back(newAdd);
    }
    char pop_front()
    {
        char oldErase = curr.front();
        hash_ = (hash_ - oldErase*magic)%mod;
        if(hash_<0) hash_ += mod;
        magic = (magic*inverse_p)%mod;
        return oldErase;
    }

    char pop_back()
    {
        char last = curr.back();
        hash_ = (hash_ - curr.back()*p)%mod;
        if(hash_<0) hash_ += mod;
        hash_ = (hash_*inverse_p)%mod;
        magic = (magic*inverse_p)%mod;
        curr.pop_back();
        return last;
    }

    void push_front(char newAdd){
        magic = (magic*p)%mod;
        hash_ = (hash_ + newAdd*magic)%mod;
        curr.push_front(newAdd);
    }

    void shiftRight(){ push_front(pop_back()); }

    void shiftLeft(){ push_back(pop_front()); }

    char getLast(){ return curr.back(); }
    lli getHash(){return hash_;}
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

const lli mod = 1e9 + 7;
int n, m;

vector<lli> dondeIguales(string &s, string &t)
{
    vector<lli> equal(n);
    for(int i = 0; i<n; i++)
    {
        string aux;
        for(int j = 0; j<n; j++)
        {
            aux += s[(i+j)%n];
        }
        if(aux == t)
        {
            equal[i] = 1;
        }
    }
    return equal;
}

int main () {
	fastIO();
	string a, b;
	cin >> a >> b >> m;
	n = SZ(a);
	vlli dp_ant(n);
	lli sum = 1;
	dp_ant[0] = 1;
	forn(j, m){
		vlli dp(n);
		forn(i, n)
			dp[i] = (sum - dp_ant[i] + mod) % mod;
		sum = 0;
		forn(i, n)
			sum = (sum + dp[i]) % mod;
		dp_ant = dp;
	}
	RollingHash rh(31, mod), aux(31, mod);
	forn(i, n){
		aux.push_back(b[i]);
		rh.push_back(a[i]);
	}
    auto v = dondeIguales(a, b);
	lli ans = 0;
    forn(i, n){
        if(v[i])
            ans = (ans + dp_ant[i])%mod;
        /* cout << var(i) << ' ' << var(dp_ant[i]) << endl; */
    }
    cout << ans << endl;
	return 0;
}
