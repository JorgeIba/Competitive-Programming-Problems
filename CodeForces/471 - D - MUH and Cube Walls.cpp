#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

int main () {
	fastIO();
    lli n, m; cin>>n>>m;
    vector< lli > Pblocks(n), Ppattern(m);
    vector< lli > blocks(n-1), pattern(m-1);
    for(auto &x: Pblocks) cin>>x;
    for(auto &x: Ppattern) cin>>x;
    for(int i = 1; i<n; i++) blocks[i-1] = Pblocks[i] - Pblocks[i-1];
    for(int i = 1; i<m; i++) pattern[i-1] = Ppattern[i] - Ppattern[i-1];

    if(m==1){
        cout << n << endl;
        return 0;
    }
    if(n==1){
        if(m>1) cout << 0 << endl;
        else cout << 1 << endl;
        return 0;
    }

    m--, n--;    


    vector< lli > pi(m);
    pi[0] = 0;
    for(int i = 1; i<m; i++)
    {
        lli j = pi[i-1];
        while(j>0 && pattern[j] != pattern[i]) j = pi[j-1];
        if(pattern[j] == pattern[i]) j++;
        pi[i] = j;
    }

    lli ans = 0;
    lli j = 0;
    for(int i = 0; i<n; i++)
    {
        while(j>0 && blocks[i]!=pattern[j]) j = pi[j-1];
        if(blocks[i] == pattern[j]) j++;
        if(j == m)
        {
            j = pi[j-1];
            ans++;
        } 
    }
    cout << ans << endl;

	return 0;
}