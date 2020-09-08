#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

lli n;
lli sumas[1510][1510]; //[filas][columnas]

bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    if( a.second != b.second)
    {
        return a.second <= b.second;
    }
    return a.first <= b.first;

    
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

    map<lli, vector< pair<lli,lli> > > idk;
    
    for(int i=1; i<=n; i++)
    {
        for(int j=i; j<=n; j++)
        {
            sumas[i][j] = sumas[i][j-1] + sumas[0][j];
            idk[ sumas[i][j]  ].push_back(  make_pair(i,j)  );
        }
    }

    /*
    for(auto x: idk)
    {
        if(x.first == 3)
        {
            sort(x.second.begin(), x.second.end(), compare);
            for (auto y : x.second)
            {
                cout<<y.first<<" "<<y.second<<endl;
            }
            
        }
    }
    */


    /*
    for(auto x: idk)
    {
        sort(x.second.begin(), x.second.end());
        cout<<x.first<<endl;
        for(auto y: x.second)
        {
            cout<<y.first<<" "<<y.second<<endl;
        }
        cout<<endl;
    }
    */

    
    vector< pair<lli,lli> > respuesta;  
    for(auto intento: idk)
    {
       lli limDerecha = 0;
       lli contador = 0;
       vector< pair<lli,lli> > aux;
       sort(intento.second.begin(), intento.second.end(), compare);
       for(auto par: intento.second)
       {
           
           if(par == intento.second[0])
           {
                /*
                cout<<intento.first<<endl;
                cout<<par.first<<" "<<par.second<<endl;
                */
                limDerecha = par.second;
                aux.emplace_back(par.first, par.second);
                if(aux.size() > respuesta.size())
                {
                    respuesta = aux;
                }
               
           }
           
            if(par.first > limDerecha)
            {
               
                limDerecha = par.second;
                aux.emplace_back(par.first, par.second);
                if(aux.size() > respuesta.size())
                {
                    respuesta = aux;
                }
               
            }

           
            
        }
   

    }
    cout<<(respuesta.size())<<endl;

    for(auto x: respuesta )
    {
        cout<<x.first<<" "<<x.second<<endl;
    }
    
    

    return 0;
}
