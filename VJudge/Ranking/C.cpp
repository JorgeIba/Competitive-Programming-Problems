#include <bits/stdc++.h>
#include <windows.h>
#define lli long long int

using namespace std;

vector< pair<lli,lli> > dishes;
set< pair<lli,lli> > check;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, m; cin>>n>>m;
    dishes.resize(n);
    for(int i=0; i<n; i++)
    {
        cin>>dishes[i].first;
    }
    for(int i=0; i<n; i++)
    {
        cin>>dishes[i].second;
    }

    for(int i=0; i<n; i++)
    {
        check.insert(  make_pair( dishes[i].second, i  )   );
    }

    //ver();

    for(int i=0; i<m; i++)
    {
        lli tipo, cantidad; cin>>tipo>>cantidad;
        lli ganado = 0;
        tipo--;
        if( dishes[tipo].first >= cantidad  )
        {
            dishes[tipo].first -= cantidad;
            ganado += cantidad*dishes[tipo].second;
            
            if(dishes[tipo].first == 0)
            {
                pair<lli, lli> aux = make_pair( dishes[tipo].second, tipo );
                check.erase(aux);
            }
            //ver();
        }
        else
        {
            lli resto = dishes[tipo].first;
            dishes[tipo].first = 0;
            pair<lli, lli> aux = make_pair( dishes[tipo].second, tipo );
            check.erase(aux);
            ganado += dishes[tipo].second*resto;
            cantidad -= resto;

            while( (cantidad > 0) and  (check.size() > 0))
            {
                auto itr = check.begin();
                lli auxTipo = itr->second;
                if(cantidad <= dishes[auxTipo].first)
                {
                    dishes[auxTipo].first -= cantidad;
                    ganado += cantidad*dishes[auxTipo].second;
                    if(dishes[tipo].first == 0)
                    {
                        pair<lli, lli> aux = make_pair( dishes[tipo].second, tipo );
                        check.erase(aux);
                    }
                    cantidad = 0;
                }
                else
                {
                    lli resto = dishes[auxTipo].first;
                    dishes[auxTipo].first = 0;
                    pair<lli, lli> aux = make_pair( dishes[auxTipo].second, auxTipo );
                    check.erase(aux);
                    ganado += dishes[auxTipo].second*resto;
                    cantidad -= resto;

                }
            }
            if( (check.size() == 0) and (cantidad > 0))
            {
                cout<<0<<endl;
                continue;
            }     

        }
        cout<<ganado<<endl;

    }

    return 0;
}