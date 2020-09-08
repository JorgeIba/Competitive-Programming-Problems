#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
using namespace __gnu_pbds;

typedef tree< pair<int,int> , null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main()
{
    fastIO();
    lli index = 0;
    lli n, m; cin>>n>>m;
    ordered_set T;

    forn(i,0,n)
    {
        lli x; cin>>x; T.insert({x,index++});
    }
    while(m--)
    {
        lli t, x; cin>>t>>x;
        if(t==1)
        {
            lli a = T.order_of_key({x+1, 0});
            T.insert({a+x, index++});
        }
        else if (t==2)
        {
            cout<<T.order_of_key({x+1, 0})<<endl;
        }
        else
        {
            if(x <= 0 || x> T.size()) cout<<"invalid\n";
            else 
            {
                pair<lli,lli> res = *T.find_by_order(x-1);
                cout<<res.first<<endl;
            }
        }
        
    }
    return 0;
}