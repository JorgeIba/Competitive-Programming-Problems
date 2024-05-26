#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


const lli maxN = 55;

//29
void GaussJordanZ2(vector< bitset<maxN> > &equations)
{
	int rows = SZ(equations), cols = maxN;
	for(int i = 0, j = cols-1; (i < rows) && (j >= 0); j--)
	{
		int selected = -1;
		
		for(int k = i; k<rows; k++)
			if(equations[k][j])
				selected = k;
		
		if(selected == -1) continue;
		
		swap(equations[i], equations[selected]);


		for(int k = i; k<rows; k++)
		{
			if(k != i && equations[k][j])
			{
				equations[k] ^= equations[i];

			}
		}
		i++;
	}
}



int main () {
	fastIO();

	lli n; cin>>n;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;


    vector<bitset<maxN>> mat;
    lli totalXor = 0;
	for(auto v: nums) {
        totalXor ^= v;
	}


    vector<lli> new_v(nums);

    for(auto &v: new_v) {
        v &= (~totalXor);
        mat.push_back(bitset<maxN>(v));
    }

    GaussJordanZ2(mat);

	lli ans = 0;
	for(int i = 0; i < n; i++) {
		lli bs = mat[i].to_ullong();
        ans = max(ans, ans ^ bs);
	}


    cout << (totalXor^ans) + ans << endl;
	return 0;
}
 