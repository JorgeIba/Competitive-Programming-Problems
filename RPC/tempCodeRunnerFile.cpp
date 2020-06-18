#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n, k; cin>>n>>k;
    vector<lli> nums(n);
    vector< vector<lli>  > posiciones(k+1);
    for(lli i = 0; i<n; i++)
    {
        cin>>nums[i];
        posiciones[nums[i]].push_back(i);
    }
    
    set<lli> visited;
    stack<lli> ans;
    for(int i = 0; i<n; i++)
    {
        lli num=nums[i];
        if( visited.find(num) != visited.end()) continue;
        if(ans.empty()) 
        {
            ans.push(num); 
            visited.insert(num);
            continue;
        }
        if( num > ans.top() )
        {
            ans.push(num);
            visited.insert(num);
        }
        else
        {
            assert(num != ans.top());
            while(!ans.empty() && ans.top() > num)
            {
                lli last = ans.top();
                auto itr = upper_bound(all( posiciones[last] ), i-1);
                if(itr == posiciones[last].end()) break;
                visited.erase(last);
                ans.pop();
            }
            ans.push(num);
            visited.insert(num);
        }
    }
    vector<lli> res;
    while(!ans.empty())
    {
        res.push_back(ans.top());
        ans.pop();
    }
    reverse(all(res));
    set<lli> check;
    for(int i = 0; i<k; i++)
    {
        cout<<res[i];
        assert( !check.count( res[i] )  );
        check.insert(res[i]);
        if(i!=n-1) cout<<" ";
    }
    cout<<endl;
    

    return 0;
}