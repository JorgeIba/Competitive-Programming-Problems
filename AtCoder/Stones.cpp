#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;


int main()
{
    fastIO();
    lli n, k; cin>>n>>k;
    vector<lli> poss(n);
    vector<lli> NIM(k+1);
    for(auto &x: poss)
    {
        cin>>x;
    }

    for(int i = 1; i<=k; i++)
    {
        set<int> check;
        lli j = 0;
        while(j < n  &&  (i - poss[j] >= 0))
        {
            if(NIM[i-poss[j]] == 0)   
            {
                NIM[i] = 1;
                break;
            }
            j++;
        }
        NIM[i] = NIM[i]==1?1:0;
    }
    
    if(NIM[k] == 0) cout<<"Second\n";
    else cout<<"First\n";

    return 0;
}