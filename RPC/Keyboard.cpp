#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

map< char, set<lli> > neig;

lli solve()
{
    string a, b; cin>>a>>b;
    lli n = a.length(), t = b.length();
    if(n != t) return 3;

    bool flag = true;
    for(int i = 0; i<n; i++)
    {
        if(a[i] != b[i])
        {
            flag = false;
            break;
        }
    }
    if(flag) return 1;
    bool similar = true;
    for(int i = 0; i<n; i++)
    {
        if( a[i] == b[i]  ) continue;
        else if( neig[a[i]].find(b[i]) == neig[a[i]].end() )
        {
            similar = false;
            break;
        }        
    }
    if(similar) return 2;
    else return 3;
    
}

void prec()
{
    char ady[3][9];
    char aux = 'a';
    for(int i = 0; i<2; i++)
    {
        for(int j = 0; j<9; j++)
        {
            ady[i][j] = aux++;
        }
    }
    for(int j = 0; j<8; j++)
    {
        ady[2][j] = aux++;
    }

    for(int i = 0; i<9; i++)
    {
        for(int j = 0; j < (i==2? 8: 9); j++)
        {
            if(i>0) neig[ ady[i][j]  ].insert(ady[i-1][j]);
            if(i<2) neig[ ady[i][j] ].insert(ady[i+1][j]);
            if(j>0) neig[ ady[i][j] ].insert(ady[i][j-1]);
            if(j<8) neig[ ady[i][j] ].insert(ady[i][j+1]);
            if( i < 2 &&  j < 8) neig[ ady[i][j] ].insert(ady[i+1][j+1]);
            if( i < 2 && j > 0) neig[ ady[i][j] ].insert(ady[i+1][j-1]);
            if( i > 0 && j < 8 ) neig[ ady[i][j] ].insert(ady[i-1][j+1]);
            if( i > 0 && j > 0) neig[ ady[i][j] ].insert(ady[i-1][j-1]);
        }
    }

}


int main()
{
    //fastIO();
    prec();
    lli t; cin>>t;
    while(t--) cout << solve() << endl;
    
    return 0;
}