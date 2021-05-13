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


int main () {
	fastIO();
    lli n; 
    while(cin>>n)
    {
        priority_queue< tuple<lli, lli, string> > pq;
        for(int i = 0; i<n; i++)
        {
            lli t, time, prio;
            string name;
            cin>>t>>time;
            if(t == 1)
            {
                cin>>prio>>name;
                pq.push({-prio, -time, name});
            }
            else
            {
                tuple<lli, lli, string> ans = pq.top();
                pq.pop();
                lli arrive = -get<1>(ans);
                cout << arrive << " " << time << " " << (time - arrive) << " " << get<2>(ans) << endl;
            }
        }
    }
    
	return 0;
}