#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void solve()
{
	vector< lli > nums(4);
	for(auto &x: nums) cin>>x;
	lli odd = 0, nulo = 0;
	for(int i = 0; i<3; i++)
	{
        lli x = nums[i];
        if(x&1)
        {
            odd++;
        }
        if(x == 0)
		{
            nulo++;
        }        
    }
    if(nums[3]&1) odd++;
    //cout << nulo << endl;
    if(nulo > 0)
    {
        if(odd >= 2)
        {
            cout << "No\n";
        }
        else
        {
            cout << "Yes\n";
        }
    }
    else
    {
        if(odd == 2)
        {
            cout << "No\n";
        }
        else 
        {
            cout <<"Yes\n";
        }
    }

}


int main () {
	//fastIO();
	lli t; cin>>t;
	while(t--) solve();
	
	return 0;
}