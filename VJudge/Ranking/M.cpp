#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<lli> numeros(n);
    for(auto &x: numeros) cin>>x;
    lli l = 0, r = 1, res = -1;
    map<lli,lli> frequency;
    map<lli,lli>:: iterator itrFinal;
    map<lli,lli>:: iterator itrInicio;
    lli left = numeros[l];
    lli right = numeros[r];
    frequency[left]++;
    frequency[right]++;


    while(r<n)
    {
        itrFinal = frequency.end();
        itrFinal--;

        itrInicio = frequency.begin();

        lli maximo = itrFinal->first;
        lli minimo = itrInicio->first;        
        lli diff = abs( maximo - minimo);
        if(diff<=1)
        {
            if((r-l+1)>res)
            {
                res = r-l+1;
            }
            r++;
            lli right = numeros[r];
            frequency[right]++;
        }
        else
        {
            lli left = numeros[l];
            frequency[left]--;
            if(frequency[left] <= 0)
            {
                frequency.erase(left);
            }
            l++;
        }
    
    }
    cout<<res<<endl;


    return 0;
}