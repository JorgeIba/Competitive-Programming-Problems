#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

vector<lli> BIT;

bool compare(pair< lli, pair<lli,lli> > a, pair< lli, pair<lli,lli> > b)
{
    if(a.second.second == b.second.second)
    {
        return a.second.first < b.second.first;
    }
    return a.second.second < b.second.second;
}


void update(lli index, lli value)
{
    while(index<BIT.size())
    {
        BIT[index] += value;
        index += index&(-index);
    }
}

lli sum(lli index)
{
    lli res = 0;
    while(index)
    {
        res += BIT[index];
        index -= index&(-index);
    }
    return res;
}





int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    
    lli q; cin>>q;
    vector< pair< lli, pair<lli,lli> > > queries(q);
    lli index = 0;
    for(auto &x: queries)
    {
        x.first = index++;
        cin>>x.second.first>>x.second.second;
        x.second.first--;
        x.second.second--;
    }
    sort(queries.begin(), queries.end(), compare);


    map<lli,lli> last;
    
    BIT.resize(n+1,0);

    lli j = 0;
    vector< pair<lli,lli> > vecAns(q);
    for(int i=0; i<q; i++)
    {
        pair<lli,lli> query = queries[i].second;
        while(j<=query.second)
        {
            lli num = nums[j];
            if( last.find(num) != last.end())
            {
                update(last[num]+1, -1);
            }
            last[num] = j;
            update(j+1, 1);
            j++;
        }
        lli ans = sum(j) - sum(query.first);
        vecAns[i].first = queries[i].first;
        vecAns[i].second = ans;
    }

    sort(vecAns.begin(), vecAns.end());

    for(auto x: vecAns)
    {
        cout<<x.second<<endl;
    }

    return 0;
}