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


void factorizar(lli n, bool flag) //Flag arriba = true, abajo = false
{
    while(n != 1)
    {
        lli pot = 0;
        //cout<<n<<" "<<primes[n]<<endl;
        lli aux = primes[n];
        if(aux == 1)
        {
            continue;
        }
        while( n%aux == 0 )
        {
            n/=aux;
            pot++;
        }
        if(flag)
        {
            arriba[ aux  ] += pot;
        }
        else
        {
            abajo[ aux  ] += pot;
        }
        

    }


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
    for(int i=0; i<n; i++)
    {
        lli x;
        cin>>x;
        factorizar(x, true);
    }

    for(int i=0; i<m; i++)
    {
        lli x;
        cin>>x;
        factorizar(x, false);
    }

   
    for(auto x: arriba)
    {
        if(abajo[x.first] > 0)
        {
            lli minimo = min(arriba[x.first], abajo[x.first]);
            arriba[x.first] -=minimo;
            abajo[x.first] -=minimo;
        }
    }


    vector<lli> resArriba;
    vector<lli> resAbajo;

    for(auto x: arriba)
    {
        if(x.second > 0) 
        {
            while(x.second>0)
            {
                resArriba.push_back( x.first  );
                x.second--;
            }
            
        }
    }
    
    for(auto x: abajo)
    {
        while(x.second>0)
            {
                resAbajo.push_back( x.first  );
                x.second--;
            }
    }
    
    if(resArriba.size() == 0)
    {
        resArriba.push_back(1);
    }

    if(resAbajo.size() == 0)
    {
        resAbajo.push_back(1);
    }

    cout<<resArriba.size()<<" "<<resAbajo.size()<<endl;
    for(auto x: resArriba)
    {
        cout<<x<<" ";
    }
    cout<<endl;

    for(auto x: resAbajo)
    {
        cout<<x<<" ";
    }

    return 0;
}