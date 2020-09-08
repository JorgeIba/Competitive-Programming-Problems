#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli CanLetras, CanPermitidas; cin>>CanLetras>>CanPermitidas;
    set<char> permitidas;
    string car;
    cin>>car;
    for(int i=0; i<CanPermitidas; i++)
    {
        char aux;
        cin>>aux;
        permitidas.insert(aux);
    }
    lli anterior = 0;
    lli total = 0;
    for(int i=0; i<CanLetras; i++)
    {
        char aux = car[i];
        if( permitidas.find(aux) != permitidas.end())
        {
            total++;
            total+=anterior;
            anterior++;
        }
        else
        {
            anterior = 0;
        }
    }
    cout<<total<<endl;



    return 0;
}