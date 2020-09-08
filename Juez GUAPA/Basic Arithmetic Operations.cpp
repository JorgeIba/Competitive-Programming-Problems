#include <bits/stdc++.h>

#define lli long long unsigned int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli maxN = 1e4+10, MOD = 999999937;


// Exponenciaciones Binarias
lli binPow(__int128 a, lli e)
{
    __int128 res = 1;
    while(e)
    {
        if(e&1) res = res*a;
        e>>=1;
        a*=a;
    }
    return res;
}

lli binPowMod(__int128 a, lli e, lli mod)
{
    __int128 res = 1;
    a = a%mod;
    while(e)
    {
        if(e&1) res = (res*a)%mod;
        e>>=1;
        a = (a*a)%mod;
    }
    return res;
}


// Pa sacar criba de phi de euler con la criba lineal
lli g(__int128 p, lli e)
{
    return (p-1)*binPow(p, e-1);
}

vector< lli > lp, phi;
void sieveMulFunction(lli n)
{
    lp.resize(n+1), phi.resize(n+1);
    vector<lli> primes, cnt(n+1), pot(n+1);
    phi[1] = 1;
    for(lli i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            phi[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                phi[d] = phi[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                phi[d] = phi[i]*phi[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    
}

// Pa reducir la fraccion
void reduce(lli &a, lli &b)
{
    lli gcd = __gcd(a,b);
    a /= gcd;
    b /= gcd;
    lli cabe = a / b;
    if( a > b) a -= cabe*b;
}

// Pa ver cual tiene la potencia mas alta que divide a b, si 2 o 5
lli counting(lli &b)
{
    lli c5 = 0, c2 = 0;
    while(b%5 == 0)
    {
        c5++; b/=5;
    }
    while(b%2 == 0)
    {
        c2++; b>>=1;
    }
    return max(c5, c2);
}


// Pa obtener factores primos, esto se ocupa para sacar el orden multiplicativo (el tama;o del periodo de una fraccion)
vector< pair<lli,lli> > getFactors(lli b)
{
    vector< pair<lli,lli> > factors;
    while(b>1)
    {
        lli lowest = lp[b];
        if( b % lowest == 0)
        {
            lli veces = 0;
            while(b % lowest == 0)
            {
                veces++;
                b /= lowest;
            }
            factors.push_back({lowest, veces});
        }
    }
    return factors;
}

// Pa obtener el orden multiplicativo
lli multiplicativeOrder(lli x, lli m){
	if(__gcd(x, m) != 1) return 0;
	__int128 order = phi[m];
	auto f = getFactors(order);
	for(auto & factor : f){
		lli p = factor.first;
		lli a = factor.second;
		order /= binPow(p, a);
		lli tmp = binPowMod(x, order, m);
		while(tmp != 1){
			tmp = binPowMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}



// Pa sacar los "n" decimales de una fraccion
void getVectorNo(vector< lli > &inicial, lli maxDiv, lli a, lli b)
{
    while(inicial.size() < maxDiv)
    {
        a *= 10;
        lli flur = a / b;
        inicial.push_back( flur );
        a -= (flur*b);
    }
    for(auto &x: inicial)
        if(!x) x = 7;
}

// Pa sacar el valor al multiplicar los decimales
lli getValues(vector< lli > &values, lli r)
{
    __int128 res = 1;
    for(lli i = 0; i<r; i++)
    {
        res = (res*values[i])%MOD;
    }
    return res;
}

lli solve()
{
    lli a, b, n, aux; cin>>a>>b>>n;
    reduce(a,b);
    aux = b;

    lli maxDiv = counting(aux);
    lli order = multiplicativeOrder(10, aux);
    if(aux == 1) //No periodico
    {
        assert(maxDiv != 0); // Si no es periodico, debe tener al menos una potencia de 2 o 5
        vector< lli > inicial;
        getVectorNo(inicial, maxDiv, a, b);
        if( n <= inicial.size() )
        {
            __int128 res = getValues(inicial, n);
            return res;
        }
        lli diff = n - inicial.size();
        __int128 total = getValues(inicial, maxDiv);
        assert(total < MOD);
        __int128 res = (total*(binPowMod(7, diff, MOD)))%MOD;
        return res;
    }
    else
    {
        if(maxDiv == 0) // Periodico puro
        {
            assert(maxDiv == 0 && order > 0); // Si es periodico no debe tener una potencia de 2 o 5
            vector< lli > ciclo;
            getVectorNo(ciclo, order, a, b); // Se obtienen los "n" decimales, donde "n" es el orden de la fraccion
            if( n <= ciclo.size() )
            {
                __int128 res = getValues(ciclo, n);
                return res;
            }
            lli cabe = n / order;
            __int128 total = getValues(ciclo, order);

            __int128 res = (binPowMod(total, cabe, MOD) * getValues(ciclo, n%order))%MOD;
            return res;
        }
        else //Periodico mixto
        {
            assert(order > 0 && maxDiv > 0); // Si es periodico mixto debe tener alguna potencia de 2 o 5
            vector< lli > todo, noPeridico, Periodico;
            getVectorNo(todo, maxDiv + order, a, b);
            for(int i = 0; i<maxDiv; i++) noPeridico.push_back(todo[i]); // Se obtiene la parte no periodica
            for(int i = maxDiv; i<maxDiv+order; i++) Periodico.push_back(todo[i]); // Se obtiene la parte periodica

            if(n <= maxDiv)
            {
                __int128 res = getValues(noPeridico, n);
                return res;
            }

            __int128 total = getValues(noPeridico, maxDiv);
            n -= maxDiv;

            if(n <= order)
            {
                total = (total * getValues(Periodico, n)) % MOD;
                return total;
            }
            __int128 cabe = n / order, all = getValues(Periodico, order);
            total = (total * binPowMod(all, cabe, MOD) )%MOD;
            total = (total * getValues(Periodico, n%order)) % MOD;
            return total;
        }
    }
}


int main()
{
    //fastIO();
    sieveMulFunction(maxN);

    lli t; cin>>t;
    while(t--) 
    {
        cout << solve();
        if(t > 0)
        {
            cout << endl;
        }
    }

    return 0;
}