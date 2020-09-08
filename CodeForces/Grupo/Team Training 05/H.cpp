#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

struct RollingHash
{
    int hash=0, mod, p, magic, inverse_p, size = 0; 
    RollingHash(lli p, lli mod): p(p), mod(mod){ 
        inverse_p = getInverse(); 
        magic = 1;
    }
    void push(char newAdd)
    {
        hash = (hash*p + newAdd*p);
        magic = (magic*p);
        //size++;
    }
    void pop(char oldErase)
    {
        hash = (hash - oldErase*magic);
        //if(hash<0) hash += mod;
        magic = (magic*inverse_p);
    }
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


int main () {
	fastIO();
    ifstream cin("hash.in");
	ofstream cout("hash.out");
    lli k; cin>>k;

    string res(k, 'y');
    //vector< string > ans;
    cout << res << endl;
    for(int i = 0; i<k-1; i++)
    {
        //string aux = res;
        res[i] = 'z';
        res[i+1] = 'Z';
        cout << res << endl;
        res[i] = 'y';
        res[i+1] = 'y';
        //ans.push_back(res);
    }

    /*
    cout << SZ(ans) << endl;
    for(auto x: ans)
    {
        RollingHash H(31, 100);
        for(int i = 0; i<SZ(x); i++)
        {
            H.push(x[i]);
        }
        //cout << H.getHash() << endl;
    }   
   for(auto x: ans) cout << x << endl;
   */
    

	return 0;
}