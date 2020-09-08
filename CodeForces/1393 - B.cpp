#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli > cont(100010);
    lli squares = 0;
    lli pares = 0;
    vector< lli > nums(n);
    for(auto &x: nums)
    {
        cin>>x;
        cont[x]++;
        if(cont[x] % 2 == 0)
        {
            pares++;
            if(cont[x] % 4 == 0)
            {
                squares++;
            }
        }
    } 
    lli q; cin>>q;
    while(q--)
    {
        lli x;
        char c; cin>>c>>x;
        if(c == '+')
        {
            cont[x]++;
            if(cont[x] % 2 == 0)
            {
                pares++;
                if(cont[x] % 4 == 0)
                {
                    squares++;
                }
            }
        }
        else
        {
            if(cont[x] % 2 == 0)
            {
                pares--;
                if(cont[x] % 4 == 0)
                {
                    squares--;
                }
            }
            cont[x]--;
        }
        if(squares >= 1)
        {
            if(squares>=2)
            {
                cout << "Yes\n";
                continue;
            }
            else if(squares == 1)
            {
                if((pares - 2) >= 2)
                {
                    cout << "Yes\n";
                    continue;
                }
            }
        }
        cout << "No\n";


    }

    
    return 0;
}