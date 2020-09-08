#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main () {
	fastIO();
	lli n; cin>>n;
    vector< lli > nums(n);
    for(auto &x: nums) cin>>x;
    lli last = 0;
    for(lli col = 63; col>=0; col--)
    {
        lli temptative = -1;
        for(lli row = last; row < n ; row++)
        {
            if(nums[row] & (1LL<<col))
                temptative = row;
        }
        if(temptative == -1) continue;
        else swap(nums[last], nums[temptative]);

        for(lli row = 0; row<n; row++)
            if(nums[row] & (1LL<<col) && row != last)
                nums[row] = nums[row] ^ nums[last];
        last++;
    }

    lli sumaXor = 0;
    for(auto v: nums)
    {
        sumaXor ^= v;
    }
    cout << sumaXor << endl;
    
    /*
    for(auto v: nums)
    {
        bitset<5> aux = v;
        cout << aux.to_string() << endl;
    }
    */
    

	return 0;
}