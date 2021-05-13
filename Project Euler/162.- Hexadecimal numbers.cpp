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

const int n = 16;

lli dp[20][2][2][2][2];

lli fun(int idx, bool prefixZero, bool flagOne, bool flagZero, bool flagA)
{
    if(idx == n)
    {
        return flagOne && flagZero && flagA;
    }

    lli &ans = dp[idx][prefixZero][flagOne][flagZero][flagA];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=15; d++)
    {
        if(prefixZero && d == 0)
        {
            ans += fun(idx+1, true, flagOne , false, flagA);
        }
        else
        {
            ans += fun(idx+1, false, flagOne | (d == 1), flagZero | (d == 0), flagA | (d == 10));
        }
    }
    return ans;
}

char castHex(int num)
{
    if(num <= 9) return num + '0';
    else if(num == 10) return 'A';
    else if(num == 11) return 'B';
    else if(num == 12) return 'C';
    else if(num == 13) return 'D';
    else if(num == 14) return 'E';
    else return 'F';
}

string convertHex(lli num)
{
    string ans;
    while(num)
    {
        ans += castHex( num % 16 );
        num /= 16;
    }
    reverse(all(ans));
    return ans;
}


int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));

    lli ans = fun(0, true, false, false, false);
    cerr << ans << endl;
    cout << convertHex(ans) << endl;


	return 0;
}