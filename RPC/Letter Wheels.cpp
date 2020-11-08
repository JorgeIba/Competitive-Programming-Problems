#include <bits/stdc++.h>

#define lli long long int
#define ld double
#define endl "\n"
#define forn(i, in, fin) for(lli i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;
 
string s, t, u;

struct RollingHash
{
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



int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

lli powerMod(lli a, lli b, lli mod){
	lli res = 1;
	b %= mod-1;
	if(b < 0) b += mod-1;
	while(b){
		if(b & 1) res = (res * a) % mod;
		b >>= 1;
		a = (a * a) % mod;
	}
	return res;
}
 
template<int p, int g, typename T>
void ntt(vector<T> & A, bool inv){ //O(n log n)
	int n = SZ(A);
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}

	vector<lli> wp(n>>1, 1);

	for(int k = 1; k < n; k <<= 1){
		lli wk = powerMod(g, (inv?-1:1) * (p - 1) / (k<<1), p);
		for(int j = 1; j < k; ++j)
			wp[j] = (wp[j - 1] * wk) % p;

		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				lli u = A[i + j], v = (A[i+j+k] * wp[j]) % p;
				A[i+j] = (u + v < p) ? u + v : u + v - p;
				A[i+j+k] = (u - v >= 0) ? u - v: u - v + p;
			}
		}
	}

	if(inv){
		lli inv_n = powerMod(n, p - 2, p);
		for(auto &x: A) x = (x*inv_n)%p;
	}
}
 
template<int p=998244353, int g=3, typename T>
vector<T> multiply(vector<T> A, vector<T> B){ //O(n logn) it uses NTT
	int sz = SZ(A) + SZ(B) - 1;
	int size = nearestPowerTwo(sz);
    
	A.resize(size), B.resize(size);
	ntt<p, g>(A, false); ntt<p, g>(B, false);
	for(int i = 0; i < size; i++)
		A[i] = (lli)A[i] * B[i] % p;
	ntt<p, g>(A, true);

	A.resize(sz);
	return A;
}


char different(char a, char b)
{
    bool isThereA = (a=='A' || b == 'A');
    bool isThereB = (a=='B' || b == 'B');
    bool isThereC = (a=='C' || b == 'C');
    if(!isThereA) return 'A';
    if(!isThereB) return 'B';
    if(!isThereC) return 'C';
    assert(false);
}

//unordered_map< lli, lli > rollingU; // rollingU[hash] = minimum moves
int rollingU[23068676];
const int INF = 1e9;

void getRolling(string &u)
{
    for(int i = 0; i<23068675; i++) rollingU[i] = INF;
    RollingHash R(31, 23068673);
    for(auto c: u)
    {
        R.push_back(c);
    } 

    rollingU[R.getHash()] = 0;
    //cerr << R.getHash() << endl;
    for(int i = 1; i<=(lli)u.length(); i++)
    {
        R.shiftRight();;
        lli hash = R.getHash();
        rollingU[hash] = min(i, rollingU[hash]);
     
    }

    for(int i = 1; i<=(lli)u.length(); i++)
    {
        R.shiftLeft();;
        lli hash = R.getHash();
        rollingU[hash] = min(i, rollingU[hash]);
    }
    
}



lli aux(string s, string t, string u)
{
    string S = s;
    auto aux = s+s;
    s+=aux;
    int n = s.length(), m = t.length();
    vector<int> As(n), At(n,0), Bs(n), Bt(n,0), Cs(n), Ct(n,0);
    for(int i = 0; i<n; i++)
    {
        char si = s[i];
        if(si == 'A') As[i] = 1;
        else if(si == 'B') Bs[i] = 1;
        else Cs[i] = 1;
    }
    for(int i = 0; i<m; i++)
    {
        char ti = t[i];
        if(ti == 'A') Bt[i+m] = Ct[i+m] = 1;
        else if(ti == 'B') At[i+m] = Ct[i+m] = 1;
        else At[i+m] = Bt[i+m] = 1;
    }

    reverse(all(At));
    reverse(all(Bt));
    reverse(all(Ct));

    auto matchsA = multiply(As, At);
    auto matchsB = multiply(Bs, Bt);
    auto matchsC = multiply(Cs, Ct);

    vector<int> possibleIndex;
    for(int i = 0; i<SZ(matchsA); i++)
    {
        if(matchsA[i] + matchsB[i] + matchsC[i] == m)
        {
            //cerr << "Con " << i-n+1 << " shifts en 1er, existen " << matchsA[i] + matchsB[i] + matchsC[i] << " matchs\n";
            possibleIndex.push_back(i-n+1);
        }
    }
    
    getRolling(u);
    int ans = INF;
    for(int i = 0; i<SZ(possibleIndex); i++)
    {
        RollingHash R(31, 23068673);
        string lookingFor(m, 'a');
        int idx = possibleIndex[i];
        if(idx < 0) //muevo el de arriba posiciones para derecha
        {
            //idx = abs(idx);
            for(int j = 0; j<m; j++)
            {
                R.push_back(different(S[(j+idx+m)%m], t[j]));
            }
        }
        else //muevo el de abajo idx para derecha
        {
            idx = abs(idx);
            for(int j = 0; j<m; j++)
            {
                //cout << S[j] << " " << t[(j+idx)%m] << endl;
                R.push_back(different(S[j], t[(j+idx)%m]));
            }
        }
        //cerr << "Moviendo " << idx << " Se obtiene que la cadena a buscar es: " << lookingFor << endl;
        lli hash = R.getHash();
        //cerr << hash << endl;
        int aux = rollingU[hash];
        ans = min(ans, aux + abs(idx));
    }

    
    return ans;
}


int main()
{
    fastIO();
    cin>>s>>t>>u;
    lli ans = min({aux(s, t, u), aux(u, s, t), aux(u, t, s)});
    if(ans == INF) cout << -1 << endl;
    else  cout << ans << endl;
    return 0;
}