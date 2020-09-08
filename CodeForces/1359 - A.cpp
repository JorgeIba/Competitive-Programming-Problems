#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
    lli n, m, k; cin>>n>>m>>k;
    lli get = n/k;
    lli maximo = min(get, m);
    m-= maximo;
    if(m==0)
    {
        cout<<maximo<<endl;
    }
    else
    {
        lli toca = m/(k-1);
        if(m%(k-1) != 0) toca++;
        //cout<<maximo<<" "<<toca<<endl;
        cout<< (maximo - toca) << endl;
    }
    
        

}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}