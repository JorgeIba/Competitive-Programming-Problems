#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, a,b,k; cin>>n>>a>>b>>k;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    vector<lli> values;
    lli contador = 0;
    for(auto x: nums)
    {
        lli total = a+b;
        if(x%total == 0)
        {
            x = total;
        }
        else
        {
            x = x%total;
        }
        x-= a;
        //cout<<x<<" ";
        if(x <= 0)
        {
            contador++;
        }
        else
        {
            values.push_back(x);
        }
    }

    sort(values.begin(), values.end());

    for(auto x: values)
    {
        lli necesito = 0;
        if(x%a == 0)
        {
            necesito = x/a;
        }
        else
        {
            necesito = x/a + 1;
        }
        
        if(necesito <= k)
        {
            contador++;
            k-=necesito;
        }
        else
        {
            break;
        }
        
    }

    cout<<contador<<endl;

    return 0;
}