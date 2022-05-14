#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,n) for(int i = a; i <= n; i++)
#define all(v) v.begin(), v.end()
#define se second
#define fi first
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
 
using namespace std; 

typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

int main(){
	fastIO();

  lli n; cin>>n;
  vector<lli> nums(n);
  for(auto &x: nums) cin>>x;


  lli best = 0;
  for(int d = 1; d<360; d++)
  {   
        vector<lli> new_nums;
        for(auto x: nums) new_nums.push_back((x+d)%360);

        set<lli> contains;
        for(auto x: nums) contains.insert(x);


        set<lli> prohibidos;
        lli parejas = 0;
        for(auto x: new_nums)
        {
            lli old = (x-d+360) % 360;
            lli new_x = x;

            if(prohibidos.count(new_x)) continue;

            if(contains.count(new_x))
            {
                contains.erase(old);
                contains.erase(new_x);
  
                prohibidos.insert( (new_x + d) % 360 );
                parejas++;
            }

        }

    best = max(best, parejas);
  }
  cout << best << endl;

	return 0;
  }
