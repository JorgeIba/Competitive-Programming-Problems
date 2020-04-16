#include <bits/stdc++.h>
#define lli long long int

using namespace std;
string cadena;
vector< set<lli> > indices(30);

void change()
{
    lli ind; cin>>ind;
    char cambiar; cin>>cambiar;
    ind--;
    lli aux = cadena[ind] - 97;
    indices[aux].erase(ind);
    lli numero = cambiar-97;
    indices[numero].insert(ind);
    cadena[ind] = cambiar;
    //checar();
}


void distinct()
{
    //checar();
    lli l, r, contador = 0; cin>>l>>r;
    l--; r--;
    for(int i=0; i<30; i++)
    {
        //cout<<i<<" ";
        auto itr = indices[i].lower_bound(l);
        if( (itr != indices[i].end()) and( *itr <=r) )
        {
            //cout<<(char(i+97))<<" "<<*itr<<endl;
            contador++;
        }
    }

    cout<<contador<<endl;


}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>cadena;
    for(int i=0; i<cadena.length(); i++)
    {
        lli aux = cadena[i] - 97; //a = 97
        indices[aux].insert(i);
    }
    
    lli q; cin>>q;
    while(q--)
    {
        lli opcion; cin>>opcion;
        if(opcion==1)
        {
            change();
        }
        else
        {
            distinct();
        }
        
    }
 
    
    return 0;
}