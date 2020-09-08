#include <bits/stdc++.h>
#define lli long long int

using namespace std;


vector< vector<int> > binarios;

void getSetBitsFromOneToN(lli N, lli index, bool flag)
{ 
    lli two = 2,ans = 0; 
    lli n = N;
    int aux = 0; 
    lli j  = 0;
    while(n){ 
        aux = 0;
        aux =  (N/two)*(two>>1);   
        if((N&(two-1)) > (two>>1)-1) 
        {
            aux += (N&(two-1)) - (two>>1)+1;
        }
        two <<= 1; 
        n >>= 1; 
        //aux regresa cuantos bit encendidos hay en una fila
        if(flag)
        {
            binarios[index][j++] += aux;
        }
        else
        {
            binarios[index][j++] -= aux;
        }
        
    } 
} 

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;

    binarios.assign(n, vector<int>(60,0) );



    for(int i = 0; i<n; i++)
    {
        lli x, m; cin>>x>>m;
        getSetBitsFromOneToN(x+m-1, i,  true);
        getSetBitsFromOneToN(x-1,i, false);
        for(auto &x: binarios[i])
        {
            x = x&1;
        }
    }

    for(int i = 0; i<60; i++)
    {
        lli aux = 0;
        for(int j = 0; j<n; j++)
        {
            aux += binarios[j][i];
        }
        if(aux&1)
        {
            //cout<<aux<<" ";
            cout<<"tolik\n";
            return 0;
        }
    }
    cout<<"bolik\n";

    return 0;
}