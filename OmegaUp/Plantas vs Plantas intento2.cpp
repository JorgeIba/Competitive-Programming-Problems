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

const int maxN = 1e6 + 10;

int main () {
	fastIO();
	lli n; cin>>n;
	vector<lli> plants(n), howMany(maxN);
	for(auto &plant: plants) cin>>plant;

	stack<lli> increase;
	lli maximum_time = 0;
	for(int i = n-1; i>=0; i--)
	{
		lli cont = 0;
		while(!increase.empty() && plants[i] > increase.top())
		{
			if(cont < howMany[increase.top()])
			{
				cont = howMany[increase.top()];
			}
			else cont++;
			increase.pop();
		}
		//empty or top bigger
		howMany[plants[i]] = cont;
		increase.push(plants[i]);
		maximum_time = max(maximum_time, cont);
	}
	cout << maximum_time << endl;

    
	return 0;
}