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
    for(auto &x: numeros)
    {
        cin>>x;
    }
    lli k; cin>>k;

    deque< pair<lli,lli>  > cola;

    for(int i=0; i<k; i++)
    {
        lli numero = numeros[i];
        if(cola.empty())
        {
            cola.push_front({numero,i});
            continue;
        }

        if(numero >= cola.front().first)
        {
            while(!cola.empty())
            {
                cola.pop_front();
            }
            cola.push_front({numero,i});
        }

        else
        {
            while((cola.size() > 1) and (numero >= cola.back().first)  )
            {
                cola.pop_back();
            }
            cola.push_back({numero,i});
        }
        
    }

    cout<<cola[0].first<<" ";

    lli l = 0, r = k-1;
    while(r < n-1)
    {
        if( cola[0].second == l  )
        {
            cola.pop_front();
        }
        l++;
        r++;
        lli numero = numeros[r];
        if(cola.empty())
        {
            cola.push_front({numero,r});
        }

        if(numero >= cola[0].first)
        {
            while(!cola.empty())
            {
                cola.pop_front();
            }
            cola.push_front({numero, r});
        }

        else
        {
            while(cola.size() > 1 and (numero>= cola.back().first))
            {
                cola.pop_back();
            }
            cola.push_back({numero,r});
        }
        

        cout<<cola[0].first<<" ";

    }
    return 0;
}
