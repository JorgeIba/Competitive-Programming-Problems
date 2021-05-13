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

const int numDigits = 100;

lli dp1[105][2][11];

lli fun1(lli index, bool prefixZero, int lastDigit) //Decreasing
{
    if(index == numDigits) return 1;

    lli &ans = dp1[index][prefixZero][lastDigit];
    if(ans != -1) return ans;
    ans = 0;

    for(int d = 0; d<=lastDigit; d++)
    {
        if(d == 0 && prefixZero)
            ans += fun1(index+1, true, 9);
        else
            ans+= fun1(index+1, false, d);
    }
    return ans;
}

lli dp2[105][10];

lli fun2(lli index, int lastDigit) //Increasing
{
    if(index == numDigits) return 1;

    lli &ans = dp2[index][lastDigit];
    if(ans != -1) return ans;
    ans = 0;
    for(int d = lastDigit; d<=9; d++)
    {
        ans += fun2(index+1, d);
    }
    return ans;
}



int main () {
	//fastIO();
    memset(dp1, -1, sizeof(dp1));
    lli howManyDecreasing = fun1(0, true, 9);

    memset(dp2, -1, sizeof(dp2));
    lli howManyIncreasing = fun2(0, 0);

    cout << howManyDecreasing + howManyIncreasing - 9*numDigits - 2 << endl;

	return 0;
}