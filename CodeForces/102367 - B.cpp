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


VLL get_divisors(lli n)
{
    VLL divisors;
    for(lli i = 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            divisors.push_back(i);
            if(i*i != n) divisors.push_back(n/i);
        }
    }
    return divisors;
}


lli is_square(lli n)
{
    lli l = 1, r = 1e9;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if( mid * mid == n)
            return mid;
        else if(mid * mid < n)
            l = mid+1;
        else
            r = mid-1;
    }
    return -1;
}

int main () {
	//fastIO();
    lli k; cin>>k;

    set<lli> ans;

    auto divisors = get_divisors(k);

    for(auto d: divisors)
    {
        lli dk = k / d;
        if( (d+dk) % 2 != 0 ) continue;
        lli m = (d+dk)/2;
        lli n = d - m;
        if(n > 0)
            ans.insert(n*n);

        n = (d+dk)/2;
        m = d-n;
        if(m > 0)
            ans.insert(-n*n);
    }

    for(lli i = 1; i <= 1e5; i++)
    {
        lli n2 = i*i;
        if(n2 >= k) continue;

        lli sq = is_square(k - n2);
        if(sq != -1)
            ans.insert(-n2);
    }

    cout << SZ(ans) << endl;
    
    if(SZ(ans))
    {
        for(auto a: ans)
        {
            cout << a << " ";
        }
    }

	return 0;
}

