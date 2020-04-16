#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n;
    cin>>n;
    vector<lli> columna(n);
    lli total = 0;
    for(int i=0; i<n; i++)
    {
        cin>>columna[i];
        total += columna[i];
    }
    lli deber = 0, aux = 0;
    for(int i=0; i<n; i++)
    {
        if ((columna[i] % 2 == 1)and(deber==0))
        {
            deber ++;
            aux = 0;
            continue;
        }
        else if ((columna[i] % 2 == 1)and(aux % 2==0))
        {
            deber --;
            aux = 0;
        }
        else if ((columna[i] % 2 == 1)and(aux % 2==1))
        {
            deber ++;
            aux = 0;
        }
        if (columna[i] % 2 ==0)
        {
            aux ++;
        }
        
    }
    lli res = total/2 - deber/2 - deber%2;

    return 0;
}