#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n; cin>>n;
    vector<lli> nums(n);
    bool arreglo[n+5][2];
    memset(arreglo, false, sizeof(arreglo));
    for(auto &x: nums)
    {
        cin>>x;
    }

    for(int i = 0; i<n; i++)
    {
        if(nums[i] == 0)
        {
            arreglo[i+1][0] = true;
        }
        else
        {
            arreglo[ nums[i] ][1] = true;
        }
    }

    vector< pair<lli,lli> > acomodo;

    for(int i = 1; i<=n; i++)
    {
        if(arreglo[i][0])
        {
            acomodo.push_back({i, -1});
        }
        //cout<<arreglo[i][0]<<" "<<arreglo[i][1]<<endl;
    }

    lli j = 0;
    for(int i = 1; i<=n; i++)
    {
        if(!arreglo[i][1])
        {
            acomodo[j++].second = i;
        }
    }

    for(int i = 1; i< acomodo.size(); i++)
    {
        if(acomodo[i].first == acomodo[i].second)
        {
            lli aux = acomodo[i].second;
            acomodo[i].second = acomodo[i-1].second;
            acomodo[i-1].second = aux;
        }
    }
    
    if(acomodo[0].first == acomodo[0].second)
    {
        lli saize = acomodo.size();
        lli aux = acomodo[0].second;
        acomodo[0].second = acomodo[ saize-1  ].second;
        acomodo[saize-1].second = aux;
    }


    for(auto x: acomodo)
    {
        nums[x.first-1] = x.second;
        //cout<<x.first<<" "<<x.second<<endl;
    }

    for(auto x: nums)
    {
        cout<<x<<" ";
    }

    return 0;
}