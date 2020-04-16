#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli primes[10000100];
map<lli,lli> arriba;
map<lli,lli> abajo;



void lowestPrimes()
{
    for(int i=1; i<=10000000; i++)
    {
        if (i&1)
        {
            primes[i] = i;
        }
        else
        {
            primes[i] = 2;
        }
        
    }
    for(lli i = 3; i * i <=10000000; i+=2)
    {
        if(primes[i] == i)
        {
            for(lli j = i*i; j<= 10000000; j+=2*i)
            {
                if(primes[j] == j)
                {
                    primes[j] = i;
                }
            }
        }
    }

}

lli binPow(lli numero, lli potencia)
{
    lli res = 1;
    while(potencia)
    {
        if(potencia&1)
        {
            res = res*numero;
        }
        potencia>>=1;
        numero*=numero;
    }

    return res;
}


pair<lli,lli> factorizar(lli &n) //Flag arriba = true, abajo = false
{
   
    lli pot = 0;
    //cout<<n<<" "<<primes[n]<<endl;
    lli aux = primes[n];

    while( n%aux == 0 )
    {
        n/=aux;
        pot++;
    }
    return {aux,pot};
    /*
    if(flag)
    {

        arriba[ aux  ] += pot;
    }
    else
    {
        abajo[ aux  ] += pot;
    }
    */
    


}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lowestPrimes();
    lli n, m; cin>>n>>m;
    arriba.clear();
    abajo.clear();
    vector<lli> resArriba(n);
    vector<lli> resAbajo(m);
    for(int i=0; i<n; i++)
    {
        lli x; cin>>x;
        resArriba[i] = x;
        while(x > 1)
        {
            pair<lli,lli> aux = factorizar(x);
            arriba[aux.first]  += aux.second;
        }
        
    }

    for(int i=0; i<m; i++)
    {
        lli x; cin>>x;
        resAbajo[i] = x;
        while(x > 1)
        {
            pair<lli,lli> aux = factorizar(x);
            abajo[aux.first]  += aux.second;
        }
    }

    cout<<n<<" "<<m<<endl;
    map<lli,lli> gcd;
    for(auto x: arriba)
    {
        if( abajo[x.first] > 0  )
        {
            gcd[x.first] = min(x.second, abajo[x.first]);
        }
    }
    map<lli,lli> gcdAux = gcd;
    for(int i=0; i<n; i++)
    {
        lli x = resArriba[i];
        lli res = 1;
        while(x>1)
        {
            pair<lli,lli> aux = factorizar(x);    
            if( gcdAux[ aux.first  ] > 0  )
            {
                lli mini = min(gcdAux[aux.first], aux.second);
                gcdAux[ aux.first ] -= mini;
                aux.second -= mini;
            }
            res *= binPow(aux.first, aux.second);
        }
        cout<<res<<" ";
    }
    cout<<endl;
    map<lli,lli> gcdAux2 = gcd;

    for(int i=0; i<m; i++)
    {
        lli x = resAbajo[i];
        lli res = 1;
        while(x>1)
            {
                pair<lli,lli> aux = factorizar(x);    
                if( gcdAux2[ aux.first  ] > 0  )
                {
                    lli mini = min(gcdAux2[aux.first], aux.second);
                    gcdAux2[ aux.first ] -= mini;
                    aux.second -= mini;
                }
                res *= binPow(aux.first, aux.second);
            }
            cout<<res<<" ";
    }
    
    return 0;
}