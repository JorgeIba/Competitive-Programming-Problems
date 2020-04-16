#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

set<char> alph;
string auxAlph, cadena; 
char arregloCar[250];
set<string> pasado;
vector<string> res;


void cambiandoLetras()
{
    //cout<<"ASD";
    for(int i=0; i<cadena.length(); i++)
    {
        for(auto x: alph)
        {
            //cout<<"ASd";
            if (x != cadena[i])
            {
                string aux = cadena;
                aux[i] = x;
                if (pasado.find(aux) == pasado.end())
                {
                    
                    res.push_back(aux);
                    pasado.insert(aux);
                }
            }
        }
    }
}


void agregandoLetras()
{
    for(int i=0; i<(2*cadena.length() + 1); i+=2)
    {
        for(auto x: alph)
        {
            arregloCar[i]=x;
            string aux="";
            for(int i=0; i<(2*cadena.length()+1); i++)
            {
                if(arregloCar[i]!=' ')
                {
                    aux+=arregloCar[i];
                }
            }
            if( pasado.find(aux) == pasado.end()  )
            {
             
                res.push_back(aux);
                pasado.insert(aux);
            }
            
        }    
        arregloCar[i] = ' ';
    }


}

void eliminandoLetras()
{
    
    for(int i=0; i<cadena.length(); i++)
    {
        string aux=cadena;
        aux[i] = ' ';
        string aux2="";
        for(int i=0; i<cadena.length(); i++)
        {
            if(aux[i]!=' ')
            {
                aux2 +=aux[i];
            }
        }

        if(pasado.find(aux2) == pasado.end())
        {
            res.push_back(aux2);
            pasado.insert(aux2);
        }
        
    }

}



int main()
{
    memset(arregloCar, ' ', sizeof(arregloCar));
    cin>>auxAlph>>cadena;
    int j = 1;
    for(int i=0; i<cadena.length(); i++)
    {
        arregloCar[j]  = cadena[i];
        j+=2;
    }

    /*
    for(int i=0; i<250; i++)
    {
        cout<<arregloCar[i];
    }
    */
    
    for(char car: auxAlph)
    {
        alph.insert(car);
    }

    cambiandoLetras();
    agregandoLetras();
    eliminandoLetras();

    sort(res.begin(), res.end());

    for(auto x: res)
    {
        cout<<x<<endl;
    }


    return 0;
}