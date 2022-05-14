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


lli query(lli x){
    cout << "+ " << x << endl;
    cout.flush();
    lli res; cin>>res;
    return res;
}


int main () {
	//fastIO();
    lli n; cin>>n;

    vector<lli> nums(n+1);

    for(int i = 1; i<n; i++) nums[i] = i;

    lli l = 1, r = n-1, last = 0, ans = -1;
    
    while(r-l >= 1){
        lli mid = (l+r)/2 + 1;

        lli next = last+1;
        lli diff = next*n - nums[mid];

        lli rest = query(diff);

        if(rest == next)
        {
            ans = mid;
            l = mid;
            last = next;
        }
        else {
            r = mid-1;
        }

        for(int i = 1; i<n; i++) nums[i] += diff;
    }
    if(ans == -1) ans = 1;
    cout << "! " << nums[ans] << endl;

	return 0;
}

