#include <bits/stdc++.h>
#define lli long long int

using namespace std;
vector<lli> numeros;
lli n;
lli dp[2][200010];



lli funcion(lli estado, lli indice, lli anterior, lli acum) //Estado -> 0 si no he eliminado, 1 si elimine
{
    if(indice == n)
    {
        return acum;
    }
    if(dp[estado][indice] != -1)
    {
        return dp[estado][indice];
    }
    if(numeros[indice] <= numeros[anterior])
    {
        if(estado==1)
        {
            return acum;
        }
        lli quitar = funcion(1, indice+1, anterior, acum);
        return dp[estado][indice] = max(acum, quitar);
    }
    else
    {
        if(estado==0)
        {
            lli quitar = funcion(1, indice+1, anterior, acum );
            lli noQuitar = funcion(0, indice+1, indice, acum+1);
            return dp[estado][indice] = max(quitar, noQuitar);
        }
        else
        {
            return dp[estado][indice] = funcion(1, indice+1, indice, acum+1);
        }        
    }
    
    
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    numeros.resize(n);
    memset(dp, -1, sizeof(dp));
    for(auto &x: numeros)
    {
        cin>>x;
    }

    lli best = -1;
    for(int i=1; i<=n; i++)
    {
        best = max(best, funcion(0,i,i-1,1));
    }
    cout<<best<<endl;

    return 0;
}