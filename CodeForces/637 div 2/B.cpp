#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void solve()
{
    lli n, k; cin>>n>>k;
    vector<lli> nums(n);
    vector<bool> peak(n, false);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli best = 0, res = 0;
    for(int i = 1; i<k-1; i++)
    {
        if((nums[i] > nums[i-1]) && (nums[i] > nums[i+1]))
        {
            peak[i] = true;
            best++;
        }
    }
    lli contador = best, index = 1;
    for(int i = k-1, l = 1; i < n-1; l++, i++ )
    {
        if(peak[l] == true)
        {
            contador--;
        }
        if( nums[i] > nums[i-1] && nums[i] > nums[i+1] )
        {
            contador++;
            peak[i] = true;
        }
        if( contador > best)
        {
            best = contador;
            index = l+1;
        }
    }
    cout<<(lli)(best+1)<<" "<<(lli)(index)<<endl;

}


int main()
{
    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
    lli t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}