#include <bits/stdc++.h>
#define lli long long int

using namespace std;

const lli MAX = 1000000000LL;
const lli MIN = -MAX;

vector< pair<lli,lli> > orden;
lli n;
vector< pair<lli,lli> > aros;


bool check(lli x, lli y, lli indice)
{
    lli dist = (x-aros[indice].first)*(x-aros[indice].first) + y*y;
    //cout<<dist<<endl;
    if(  dist <= aros[indice].second*aros[indice].second  )
    {
        return true;
    }
    return false;
}


lli Binaria(lli num)
{
    lli l = 0, r = n+1 , res = MIN;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( orden[mid].first <= num )
        {   
            res = mid;
            l = mid + 1;
        } 
        else
        {
            r = mid - 1;
        }
    }
    return res;
}

int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    cin>>n;
    orden.resize(n+2);
    aros.resize(n+2); //Primero -> (-1000000, 1) - 0. Ultimo -> (10000000, 1)  - n+1
    aros[0].first = orden[0].first = MIN;
    aros[0].second = 1 ;
    aros[n+1].first = orden[n+1].first = MAX;
    aros[n+1].second = 1;
    orden[0].second = 0;
    orden[n+1].second = n+1;
    vector<lli> res(n+2, -1);

    for(int i = 0; i< n; i++)
    {
        cin>>aros[i+1].first>>aros[i+1].second;
        orden[i+1].first = aros[i+1].first;
        orden[i+1].second = i+1;
    }
    sort(orden.begin(), orden.end());

    for(auto x: orden)
    {
        //cout<<x.first<<" ";
    }
    /*
    while(true)
    {
        lli x; cin>>x;
        cout<<Binaria(x)<<endl;
    }
    */

    lli m; cin>>m;
    lli cont = 0;
    for(int i = 0; i < m; i++)
    {
        lli x,y; cin>>x>>y;
        lli ind = Binaria(x);
        lli indiceIzq =  orden[ ind  ].second;
        lli indiceDer = orden[ ind+1  ].second ;


        //cout<<indiceIzq<<" -> "<<aros[indiceIzq].first<<" "<<aros[indiceIzq].second<<endl;
        //cout<<indiceDer<<" <- "<<aros[indiceDer].first<<" "<<aros[indiceDer].second<<endl;



        if( check(x,y,indiceIzq)  )
        {
            if(res[indiceIzq] == -1)
            {
                res[indiceIzq] = i+1;
                cont++;
            }
        }
        if( check(x,y,indiceDer)  )
        {
            if(res[indiceDer] == -1)
            {
                res[indiceDer] = i+1;
                cont++;
            }
        }
    }
    
    cout<<cont<<endl;
    for(int i = 1; i<=n; i++)
    {
        cout<<res[i]<<" ";
    }
    
    
    

    return 0;
}
