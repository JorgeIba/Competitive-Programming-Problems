#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string cadena;
    cin>>cadena;
    int tam = cadena.length();
    int res[tam];
    lli l = 0, r = tam-1;
    
    for(int i=0; i<tam; i++)
    {
        if(cadena[i] == 'l')
            res[r--] = (i+1);
        else
            res[l++] = (i+1);
    }
    for(auto x: res)
    {
        cout<<x<<"\n";
    }
    return 0;
}