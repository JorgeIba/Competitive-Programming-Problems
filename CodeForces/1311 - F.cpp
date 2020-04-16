#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;
vector< pair<lli,lli>  > nums;
map<lli,lli> mappeo;
vector<lli> BITCont;
vector<lli> BITVal;


bool compare(pair<lli,lli> a, pair<lli,lli> b)
{
    if(a.second == b.second)
    {
        return a.first < b.first;
    }
    return a.second < b.second;

}

void mappear()
{
    sort(nums.begin(), nums.end(), compare);
    lli contador = 1;
    for(auto x: nums)
    {
        if(mappeo.find(x.second) == mappeo.end())
        {
            mappeo[x.second] = contador++;
        }
    }
    for(auto &x: nums)
    {
        x.second = mappeo[x.second];
    }
}


void update(lli index, lli value)
{
    while(index < BITCont.size())
    {
        BITCont[index] ++;
        BITVal[index] += value;
        index += index&(-index);
    }
}


lli queryCant(lli index)
{
    lli res = 0;
    while(index)
    {
        res += BITCont[index];
        index -= index&(-index);
    }
    return res;
}

lli querySum(lli index)
{
    lli res = 0;
    while(index)
    {
        res += BITVal[index];
        index -= index&(-index);
    }
    return res;
}



lli query(lli index, lli value)
{
    lli cant = queryCant(index);
    
    lli sum = querySum(index);
    return cant*value - sum;
}


int main()
{  
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    nums.resize(n);
    BITCont.resize(200010);
    BITVal.resize(200010);
    for(auto &x: nums)
    {
        cin>>x.first;
    }
    for(auto &x: nums)
    {
        cin>>x.second;
    }
    mappear();
    sort(nums.begin(), nums.end());    
    lli res = 0;
    for(auto x: nums)
    {
        res += query(x.second, x.first);
        update(x.second, x.first);
    }
    cout<<res<<endl;
    


    return 0;
}