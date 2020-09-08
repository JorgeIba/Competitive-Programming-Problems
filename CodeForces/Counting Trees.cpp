#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
vector< lli > ST, nums;
const lli INF = 1e18;
lli n;

const lli MOD = 1e9 + 7;
const lli maxN = 1e6;

vector< lli > catalan(maxN), factorial(2*maxN+100), inverseFact(2*maxN + 100);


//12
void build() //ST size == 2*n
{
    for(int i = n; i<2*n; i++)
    {
        ST[i] = nums[i-n];
    }
    for(int i = n-1; i>0; i--)
    {
        ST[i] = min( ST[i<<1] , ST[i<<1|1] ) ;
    }
}
//11
lli query(lli l, lli r) //lli could be just an integer
{
    lli MAX1 = INF;
    lli MAX2 = INF;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1) MAX1 = min(MAX1, ST[l++]);   
        if(~r&1) MAX2 = min(ST[r--],MAX2);
    }
    return min(MAX1, MAX2);
}

lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    a = (a)%mod;
    while(b)
    {
        if(b&1) res = (res*a)%mod;
        b>>=1;
        a = (a*a)%mod;
    }
    return res;
}

void prep(lli n)
{
    factorial[0] = inverseFact[0] = 1;
    catalan[0] = 1;
    for(int i = 1; i<=2*maxN; i++)
    {
        factorial[i] = (factorial[i-1] * i)%MOD;
        inverseFact[i] = binPow(factorial[i], MOD-2, MOD);
    }
    for(int i = 1; i<=maxN; i++)
    {
        catalan[i] = (((factorial[2*i] * inverseFact[i+1])%MOD)*inverseFact[i])%MOD;
    }
}

vector< vector< lli > > posiciones;

/*
    2 3 1 2 2 1 1 3 2 3
*/

lli solve(lli L, lli R)
{
    //assert(R > 0);
    if(L>=R) return 1LL;
    lli minimo = query(L, R);
    lli index = lower_bound(all(posiciones[minimo]), L) - posiciones[minimo].begin();
    vector< lli > where;
    while(index < posiciones[minimo].size() && posiciones[minimo][index] <= R)
    {
        where.push_back(posiciones[minimo][index++]);
    }
    assert((int)where.size() <= n && (int)where.size() > 0);
    lli res = catalan[(int)where.size()], lAux = L;
    for(auto idx: where)
    {
        res = (res * solve(lAux, idx-1))%MOD;
        lAux = idx+1;
    }
    res = (res*solve(lAux, R))%MOD;
    return res;
}

int main()
{
    fastIO();
    cin>>n;
    prep(n);
    posiciones.resize(maxN + 10);
    ST.resize(2*(n+1), INF);
    nums.resize(n);
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
        posiciones[nums[i]].push_back(i);
    }
    build();
    
    cout << solve(0, n-1) << endl;

    return 0;
}