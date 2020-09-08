#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct RollingHash
{
    lli hash=0, mod, p, magic, offset, inverse_p, size = 0; //offset = 'a' 
    RollingHash(lli p, lli mod, lli offset = (int)'b'):p(p), mod(mod), offset(offset) { 
        inverse_p = getInverse(); 
        magic = 1;
    }
    void push(char newAdd)
    {
        hash = (hash*p + newAdd*p)%mod;
        magic = (magic*p)%mod;
        //size++;
    }
    void pop(char oldErase)
    {
        hash = (hash - oldErase*magic)%mod;
        if(hash<0) hash += mod;
        magic = (magic*inverse_p)%mod;
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

int main()
{
    //fastIO();
    string T, s; cin>>T>>s;
    lli n = s.length(), t = T.length();
    RollingHash forT(31, 1e9+7), forS(31, 1e9+7);
    for(auto c: s)
    {
        forS.push(c);
    }
    lli hashLooking = forS.getHash();
    for(int i = 0; i<n; i++)
    {
        forT.push(T[i]);
    }

    vector< lli > ans; ans.reserve(t);
    //lli ans = 0;
    if(forT.getHash() == hashLooking) ans.push_back(0);
    lli l = 0, r = n-1;
    while(r<t)
    {
        forT.pop(T[l]);
        l++;
        r++;
        forT.push(T[r]);
        if(forT.getHash() == hashLooking) ans.push_back(l);
    }
    for(auto x: ans) cout << x << " ";

    

    
    return 0;
}