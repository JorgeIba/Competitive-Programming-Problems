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
    lli n, m; cin>>n>>m;
    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;
    lli mitad = n/2;
    lli mitad2 = n - mitad;
    vector<lli> a(1<<mitad);
    for(int i = 0; i<(1<<mitad); i++)
    {
        lli tmp = 0;
        for(int j = 0; j<mitad; j++)
        {
            if(i & (1<<j))
            {
                tmp = (tmp + nums[j])%m;
            }
        }
        a[i] = tmp;
    }

    vector<lli> b(1<<mitad2);
    for(int i = 0; i<(1<<mitad2); i++)
    {
        lli tmp = 0;
        for(int j = 0; j<mitad2; j++)
        {
            if(i & (1<<j))
            {
                tmp = (tmp + nums[n-j-1])%m;
            }
        }
        b[i] = tmp;
    }

    sort(all(b));
    lli best = -1;

    for(auto mask: a)
    {
        lli l=0, r = b.size()-1, looking = m-mask-1;
        while(l<=r)
        {
            lli mid = l + (r-l)/2;
            best=max(best, (mask+b[mid])%m );
            if(b[mid] == looking) break;
            else if(b[mid] < looking) l = mid + 1;
            else r = mid - 1;
        }
    }
    cout<<best<<endl;


    return 0;
}