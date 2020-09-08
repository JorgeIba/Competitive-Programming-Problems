#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
 
using namespace std;
 
vector<lli> numeros;
vector<lli> renumeros;
vector<lli> BIT;
map< lli, lli> mappeo;
map<lli,lli> values;
 
 
void update(lli index, lli num)
{
    while(index < BIT.size())
    {
        BIT[index] += num;
        index += index&(-index);
    }
}
 
lli query(lli index)
{   
    lli res = 0;
    while(index)
    {
        res += BIT[index];
        index -= index&(-index);
    }
    return res;
}
 
 
void solve()
{
    lli n; cin>>n;
    numeros.clear();
    numeros.resize(n,0);
    renumeros.clear();
    renumeros.resize(n,0);
    mappeo.clear();
    values.clear();
    lli res =0, contador = 1;
 
    for(int i=0; i<numeros.size(); i++)
    {
        cin>>numeros[i];
        renumeros[i] = numeros[i];
    }
 
    sort(numeros.begin(), numeros.end());
 
    for(int i =0; i<numeros.size(); i++)
    {
        lli x = numeros[i];
        if(mappeo.find(x) == mappeo.end())
        {
            mappeo[x] = contador;
            contador++;
        }
    }
 
    for(int i=0; i<renumeros.size(); i++)
    {
        lli aux = renumeros[i];
        lli re = mappeo[aux];
        values[re] = aux;
        renumeros[i] = re;
 
    }
 	BIT.clear();
    BIT.resize(mappeo.size() + 1,0);
    res = 0;
    for(auto x: renumeros)
    {
        update(x , values[x] );
        res += query(x-1);
    }    
 
    cout<<res<<endl;
}
 
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
} 