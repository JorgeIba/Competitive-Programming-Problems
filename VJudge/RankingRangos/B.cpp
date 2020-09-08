#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

unordered_map<lli,lli> mappeo;
vector<lli> BIT;


void update(lli index, lli value)
{
    while(index < BIT.size())
    {
        BIT[index] += value;
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




void comprimir(vector<lli> &nums, int flag)
{
    vector<lli> aux = nums;
    if(flag == 1)
    {
        sort(aux.rbegin(), aux.rend());
    }
    else
    {
        sort(aux.begin(), aux.end());
    }
    
    lli contador = 2;
    for(auto x: aux)
    {
        if(mappeo.find(x) == mappeo.end())
        {
            mappeo[x] = contador;
            x = contador++;
        }
    }
    for(auto &x: nums)
    {
        x = mappeo[x];
    }
}




int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, p; cin>>n>>p;
    vector<lli> numeros(n);
    BIT.resize(n+1,0);
    for(auto &num: numeros)
    {
        cin>>num;
    }
    vector<lli> vecAux = numeros;
    comprimir(numeros, 0); //0-> ascendente, 1-> descendente
    vector<lli> arreglo(n,0);
    lli paux = 0, i = n-1;

    while(paux<p)
    {
        update(numeros[i], 1);
        i--;
        paux++;
    }
    lli r = n - 1;
    for(int j = i; j>=0; j--)
    {
        lli numerosR = numeros[r];
        lli numerosL = numeros[j];
        update(numerosL, 1);
        update(numerosR, -1);
        arreglo[j] = query(numerosL-1);
        r--;
    }

    BIT.clear();
    BIT.resize(n+1,0);
    mappeo.clear();

    comprimir(vecAux, 1); //0-> ascendente, 1-> descendente

    lli l = 0, res = 0, index = -1, aux=0;
    for(int i = 0; i<p; i++)
    {
        lli num = vecAux[i];
        update(num, 1);
        aux += query(num-1);
        if(aux > res)
        {
            res = aux;
            index = l;
        }
    }

    for(int i=p; i<n; i++)
    {
        lli numL = vecAux[l];
        lli numR = vecAux[i];
        update(numL, -1);
        update(numR, 1);
        aux -= arreglo[l];
        aux += query(numR-1);
        l++;
        if(aux > res)
        {
            res = aux;
            index = l;
        }
        
    }
    cout<<(index+1)<<" "<<res<<endl;
 
    

    return 0;
}