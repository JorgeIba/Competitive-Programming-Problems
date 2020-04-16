#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<lli> potencias(31);
    for(int i=1; i<=30; i++)
    {
        potencias[i] = pow(2,i);
    }
    lli n; cin>>n;

    map<lli, lli> check;
    vector<lli> numeros(n);
    lli resul = 0;

    for(int i=0; i<n; i++)
    {
        cin>>numeros[i];
        lli aux = numeros[i];
        check[aux]++;
    }

    for(lli num: numeros)
    {
        for(auto x: potencias)
        {
            lli res = x - num;
            if(res <= 0)
            {
                continue;
            }
            if( res == num  )
            {
                if(check[res] > 1)
                {
                    resul+= (check[res] - 1);
                }
            }
            else
            {
                if(check[res] > 0)
                {
                    resul+= (check[res]);
                }
            }
        }
        check[num]--;
    }
    cout<<resul<<endl;

    
    return 0;
}