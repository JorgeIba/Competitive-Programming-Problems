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

lli query1(lli idx)
{
    cout << "? " << idx << endl;
    cout.flush();
    lli num; cin>>num;
    return num;
}

bool query2(lli x)
{
    cout << "> " << x << endl;
    cout.flush();
    bool is_there; cin>>is_there;
    return is_there;
}

lli n, leftt = 60; 

lli find_number()
{
    lli l = 0, r = 1e9, ans = -1;
    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(!query2(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else
        {
            l  = mid+1;
        }
        leftt--;
    }
    return ans;
}

int main () {
	fastIO();
    cin>>n;

    lli x_n = find_number();

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, n);

    lli gcd = 0;
    for(int i = 1; i<=leftt; i++)
    {
        gcd = __gcd(gcd, x_n - query1(dis(gen)));
    }
    lli x_i = x_n - (n-1)*gcd;
    cout << "! " << x_i << " " << gcd << endl;

    
	return 0;
}