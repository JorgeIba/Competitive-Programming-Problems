#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

lli n; 
vector<lli> ST;


bool compare( pair< lli, pair<lli,lli> > a, pair<lli, pair<lli,lli> > b)
{
    if(a.second.second == b.second.second)
    {
        return a.second.first < b.second.first;
    }
    return a.second.second < b.second.second;
}

void update(lli index, lli value)
{
    ST[index += n] += value;
    while(index >> 1)
    {
        ST[index>>1] = ST[index] + ST[index^1];
        index >>= 1;
    }
}

lli query(lli l, lli r)
{
    lli res = 0;
    for(l+=n, r+=n; l<=r; l>>=1, r>>=1)
    {
        if(l&1)
        {
            res += ST[l++];
        }
        if(~r&1)
        {
            res += ST[r--];
        }
    }
    return res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    vector< lli > nums(n);
    map<lli,lli> last;
    ST.resize(2*n+2, 0);
    
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
    }

    lli q; cin>>q;
    vector< pair<lli,  pair<lli,lli> > > queries(q);
    lli index = 0;
    for(auto &x: queries)
    {
        x.first = index++;
        cin>>x.second.first>>x.second.second;
    }
    sort(queries.begin(), queries.end(), compare);

    lli j = 0;
    vector< pair<lli,lli> > vecAns(q);

    for(int i = 0; i<q; i++)
    {
        pair<lli,lli> querie = queries[i].second;
        while(j< querie.second )
        {
            lli num = nums[j];
            if( last.find( num  ) != last.end()  )
            {
                update( last[num], -1  );
            }
            last[num] = j;
            update(j, 1);
            j++;
        }
        vecAns[i].first = queries[i].first;
        vecAns[i].second = query( querie.first - 1, j);
        //cout<<query(j)<<endl;
    }
    sort(vecAns.begin(), vecAns.end());
    for(auto x: vecAns)
    {
        cout<<x.second<<endl;
    }


    return 0;
}
