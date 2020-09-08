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
    lli n, b; cin>>n>>b;
    vector<lli> nums(n);
    for(auto &x: nums)
        cin>>x;
    
    set<lli> digits;
    for(int i = 0; i<b; i++)
    {
        digits.insert(i);
    }

    set<lli> repetido;
    vector<lli> res;
    lli hastaDonde = -1;
    for(int i = 0; i<n; i++)
    {
        //auto itr = upper_bound(all(digits), nums[i]);
        //if(itr != digits.end())
        if(nums[i] < *digits.rbegin())
        {
            hastaDonde = i;
        }
        if(repetido.find(nums[i]) != repetido.end())
        {
            break;
        }
        digits.erase(nums[i]);
        repetido.insert(nums[i]);
    }

    if(hastaDonde == -1)
    {
        vector<lli> aux(n+1);
        for(int i = 0; i<=n; i++)
        {
            aux[i] = i;
        }
        swap(aux[0], aux[1]);
        for(auto x: aux)
        {
            cout<<x<<" ";
        }
        cout<<endl;
        return 0;
    }

    for(int i = 0; i<b; i++)
    {
        digits.insert(i);
    }
    for(int i = 0; i<hastaDonde; i++)
    {
        res.push_back(nums[i]);
        digits.erase(nums[i]);
    }

    //cout<<digits.size()<<endl;

    auto itr = upper_bound(all(digits), nums[hastaDonde]);
    res.push_back(*itr);
    //res[hastaDonde] = *itr;
    digits.erase(*itr);
    itr = digits.begin();
    while(res.size() < n)
    {
        res.push_back(*itr);
        itr++;
    }
    for(auto x: res)
    {
        cout<<x<<" ";
    }

    return 0;
}