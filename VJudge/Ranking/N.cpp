#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, k; cin>>n>>k;
    vector< pair<lli,lli> > numeros(n);
    for(auto &x: numeros)
    {   
        cin>>x.first>>x.second;

    } 

    sort(numeros.begin(), numeros.end());



    map<lli,lli> frequency;
    map<lli,lli>:: iterator itrFinal;
    map<lli,lli>:: iterator itrInicio;
    
    lli l = 0, r = 0, res = 0;
    bool turno = true; //True -> R, False -> L
    lli aux = 0;
    while(r<n)
    {
        if(turno)
        {
            frequency[ numeros[r].first ]++;
            aux+=numeros[r].second;
        }
         
        itrInicio = frequency.begin();
        itrFinal = frequency.end();
        itrFinal--;
        lli minimo = itrInicio -> first;
        lli maximo = itrFinal -> first;

        lli diff = maximo - minimo;
        if(diff < k)
        {
            res = max(aux, res);
            r++;
            turno = true;
        }
        else
        {
            aux -= numeros[l].second;
            frequency[ numeros[l].first  ]--;
            if(frequency[ numeros[l].first ] <= 0)
            {
                frequency.erase( numeros[l].first  );
            }
            l++;
            turno = false;
        }
        //cout<<"Asd "<<aux<<" "<<diff<<" "<<minimo<<" "<<maximo<<endl;
    }
    cout<<res<<endl;


    return 0;
}