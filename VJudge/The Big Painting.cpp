#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
vector< string > small;
vector< string > big;

void cambiarLados(deque< deque<char> > &curr, lli up, lli down, lli left, lli right, bool flag) // true -> de izq a der, false -> de der a
{
    for(int i = up; i<down; i++)
    {
        if(flag)
        {
            curr[i-up].pop_front();
            curr[i-up].push_back( big[i][right] );
        }
        else
        {
            curr[i-up].pop_back();
            curr[i-up].push_front( big[i][left] );
        }   
    }
}


void cambiarAltura(deque< deque<char> > &curr, lli up, lli down, lli left, lli right)
{
    deque<char> aux;
    for(int j = left; j<right; j++)
    {
        aux.push_back(big[down][j]);
    }
    curr.pop_front();
    curr.push_back(aux);
}


void init(deque< deque<char> > &curr, lli up, lli down, lli right)
{
    for(int i = up; i<down; i++)
    {
        deque<char> aux;
        for(int j = 0; j<right; j++)
        {
            aux.push_front( big[i][j] );
        }
        curr[i] = aux;
    }
}

void solve(lli n1, lli m1, lli n2, lli m2)
{
    //unordered_map< deque< deque<char> > , int> fr;

    small.clear(); small.resize(n1);
    big.clear(); big.resize(n2);

    for(int i = 0; i< n1; i++)
    {
        cin>>small[i];
    }
    for(int i = 0; i < n2; i++)
    {
        cin>>big[i];
    }

    deque< deque<char> > looking(n1);

    for(int i = 0; i<n1; i++)
    {
        deque<char> aux;
        for(int j = 0; j<m1; j++)
        {
            aux.push_front( small[i][j] );
        }
        looking[i] = aux;
    }
    
    deque< deque<char> > curr(n1);
    init(curr, 0, n1, m1);
    //fr[curr] ++;
    lli ans = 0;

    for(int up = 0; up+n1 <= n2; up++)
    {
        if( up != 0)
        {
            if(up % 2 == 0)
            {
                cambiarAltura(curr, up, up+n1-1, 0, m1);
            }
            else
            {
                cambiarAltura(curr, up, up+n1-1, m2-1-m1, m2-1);
            }
            //fr[curr]++;
            if(curr == looking) ans++;
        }
        
        if( up % 2 == 0)
        {
            for(int j = m1; j<m2; j++)
            {
                cambiarLados(curr, up, up+n1, j-m1, j, true);
                if(curr == looking) ans++;
            }
        }
        else
        {
            for(int j = m2-1; j>=m1; j--)
            {
                cambiarLados(curr, up, up+n1, j-m1, j, false);
                if(curr == looking) ans++;
            }
        }        
    }

    cout << ans << endl;


}

int main()
{
    //fastIO();
    lli n1, m1, n2, m2; 
    while(cin>>n1>>m1>>n2>>m2)
    {
        solve(n1,m1,n2,m2);
    }
    return 0;
}