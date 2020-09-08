#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    string s; cin>>s;
    s += '$';
    lli n = s.length();
    vector<lli> clase(n), index(n);
    {
        //k -> 0
        vector< pair<char, lli> > aux(n);
        for(int i = 0; i<n; i++) aux[i] = {s[i], i};
        sort(all(aux));

        for(int i = 0; i<n; i++) index[i] = aux[i].second;

        clase[index[0]] = 0;

        for(int i = 1; i<n; i++)
        {
            lli ant = clase[index[i-1]];
            clase[ index[i] ] = aux[i].first != aux[i-1].first? ant + 1: ant;
        }
    }
    lli k = 0;
    while( (1<<k) < n)
    {
        vector< pair< pair<lli,lli>, lli > > aux(n);
        for(int i = 0; i<n; i++)
        {
            aux[i] = {{ clase[i], clase[ (i + (1<<k)) % n ]  }, i};
        } 
        
        sort(all(aux));

        for(int i = 0; i<n; i++) index[i] = aux[i].second;

        clase[ index[0]  ] = 0;
        for(int i = 1; i<n; i++)
        {
            clase[ index[i] ] = clase[ index[i-1] ];

            if( aux[i].first != aux[i-1].first  )
            {
                clase[index[i]]++;
            }            
        }
        k++;
    }

    for(int i = 0; i<n; i++) cout<<index[i]<<" ";


    

    return 0;
}