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

lli f(lli n)
{
    return (n*(3*n - 1)) / 2;
}

bool isSquare(lli num)
{
    lli l = 1, r = num/2, ans = -1;
    while(l<=r)
    {
        lli mid = l + (r-l)/2;
        if(mid*mid <= num)
        {
            ans = mid; l = mid+1;
        }
        else r = mid-1;
    }
    return ans*ans == num;
}


bool check(lli n)
{
    if(n < 1) return false;
    if(isSquare(1 + 24*n))
    {
        lli root = sqrt(1 + 24*n);
        if ((1 + root )%6 == 0)
        {
            if(n == 12929540 || n == 16412642)
            {
                cout << (1 + root) / 6 << endl;
            }
            return true;
        } 
    }
    return false;
}

int main () {
	//fastIO();
    const int maxLooking = 1e4;
	for(int k = 1; ;k++)
    {
        for(int q = k+1; q<maxLooking; q++)
        {
            lli fq = f(q), fk = f(k);
            if((fq - fk) % 2 == 0)
            {
                lli fn = (fq - fk) / 2;
                lli fx = fk + fn;
                if(check(fn) && check(fx))
                {
                    cout << fn << " " << fx << " " << fk << " " << fq << endl;
                    return 0;
                }
            }
        }
    }    
	return 0;
}