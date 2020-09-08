#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<lli> boys(n);

    for(auto &x: boys)
    {
        cin>>x;
    }

    lli m; cin>>m;
    vector<lli> girls(m);

    for(auto &x: girls)
    {
        cin>>x;
    }

    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    lli up=0, down = 0, res =0;

    while((up < n)or(down < m))
    {
        lli diff = abs( boys[up] - girls[down]  );
        if( diff <= 1  )
        {
            res ++;
            up++;
            down++;
            continue;
        }
        if ( boys[up] > girls[down] )
        {
            down++;
            continue;
        }
        else
        {
            up++;
            continue;
        }

    }
    cout<<res<<endl;
    return 0;
}