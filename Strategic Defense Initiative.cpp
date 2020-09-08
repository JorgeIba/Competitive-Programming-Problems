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

int CeilIndex(VLL &nums, VI &tail, lli buscar, int r)
{
	int l=0, res = 0;
	while(l<=r)
	{
		int mid = l + (r-l)/2;
		if ( buscar <= nums[ tail[mid] ]  )
			res = mid, r = mid-1;
		else
			l = mid + 1;
	}
	return res;
}

VLL LIS(VLL &nums)
{
	int n = SZ(nums);
	VI tail(n,0);
	VI prev(n,-1);
	
	int last=0;
	
	for (int i=1; i<n; i++)
	{
		if (nums[i] <= nums[tail[0]])   
			tail[0] = i;
		else if (nums[i] >= nums[tail[last]])
		{
			prev[i] = tail[last];
			tail[++last] = i;
		}
		else
		{
			int index = CeilIndex(nums, tail, nums[i], last);
			prev[i] = tail[index-1];
			tail[index] = i;
		}
	}

	VLL ans;

	for(int i = tail[last]; i!=-1; i = prev[i])
		ans.push_back(nums[i]);

	reverse(all(ans));
	return ans;
}

void funcion1()
{
	VLL nums;
	string TAux;
	while(getline(cin,TAux)and(!TAux.empty()))
	{
			lli x= atoi(TAux.c_str());
			nums.push_back(x);
	}
	VLL ans = LIS(nums);
	cout <<"Max hits: " << SZ(ans) << endl;
	for(auto x: ans) cout << x << endl;
}


int main()
{
	fastIO();
	int t; cin>>t;
	string aux;
	getline(cin, aux);
	getline(cin, aux);
	for(int i=0; i<t; i++)
	{
		funcion1();
		if(i != t-1)
		{
			cout << endl;
		}
	}
	return 0;
}
