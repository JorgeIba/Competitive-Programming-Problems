#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


vector< pair<lli,lli> > indicesRes;
lli mayor = 0;
lli n; 
lli sumas[1510][1510]; //[filas][columnas]

lli busquedaBinaria(lli numeroBuscar, lli i, lli j)
{
    lli l = j, r = n;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(  sumas[i][mid] == numeroBuscar   )
        {
            return mid;
        }
        else if (  sumas[i][mid] < numeroBuscar   )
        {
            l = mid+1;
        }
        else
        {
            r = mid-1;
        }
    }
    return -1;
}



vector< pair<lli,lli> > buscar(lli numeroBuscar, lli i, lli j)
{
    vector< pair<lli, lli> > aux;
    lli ifixed = j+1, jfixed = j+1;
    while( ifixed <= n  )
    {
        lli pos = busquedaBinaria( numeroBuscar, ifixed, jfixed  );
        if(  pos != -1 )
        {
            aux.push_back( make_pair(  ifixed, pos   )  );
            ifixed = pos+1;
            jfixed = pos+1;
        }
        else
        {
            ifixed++;
            jfixed++;
        }
    }
    return aux;
}




int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin>>n;

    memset(sumas, 0, sizeof(sumas));

    for(int i=1; i<=n; i++)
    {
        cin>>sumas[0][i];
    }
    for(int i=1; i<=n; i++)
    {
        sumas[i][i] = sumas[0][i];
    }
    for(int i=1; i<=n; i++)
    {
        for(int j=i; j<=n; j++)
        {
            sumas[i][j] = sumas[i][j-1] + sumas[0][j];
        }
    }

    /*
    while(true)
    {
        lli numeroBuscar, i, j;
        cin>>numeroBuscar>>i>>j;
        cout<<busquedaBinaria(numeroBuscar, i,j)<<endl;
    }
   vector< pair<lli,lli> > aux = buscar(3, 1, 1);

   for(auto x: aux)
   {
       cout<<x.first<<" "<<x.second<<endl;
   }
    for(int i=0; i<=n; i++)
    {
        for(int j=0; j<=n; j++)
        {
            cout<<sumas[i][j]<<" ";
        }
        cout<<endl;
    }
    */
    vector< pair<lli, lli> > res;
    lli q=0;
    for(int i=1; i<=n; i++)
    {
        for(int j=i; j<=n; j++)
        {
            
            //cout<<sumas[i][j]<<" "<<i<<endl;
            
            vector< pair<lli,lli> > aux;
            lli porBuscar = sumas[i][j];
            
            aux = buscar( porBuscar, i, j );

            aux.push_back( make_pair(i, j)  );

            if(aux.size() > res.size())
            {
                res = aux;
            }
            
        }
        cout<<i<<endl;
        
    }

    cout<<(res.size())<<endl<<q;
    for(auto x: res)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }



    return 0;
}