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

ld dp[301][301][301];
int n;

ld fun(lli a, lli b, lli c)
{
    if(a == 0 && b == 0 && c == 0) return 1;
    
    return (c?fun(a, b+1, c-1)*c/n:0) + (b?fun(a+1, b-1, c)*b/n:0) + (a?fun(a-1, b, c)*a/n:0);
}


int main () {
	//fastIO();
    cin>>n;
    int A = 0, B = 0, C = 0;
    for(int i = 0; i<n; i++)
    {
        int x; cin>>x;
        if(x==1) A++;
        else if(x==2) B++;
        else C++;
    }
    cout << fun(A, B, C) << endl;

    /*
    dp[A][B][C] = 1;

    for(int c = C; c>=0; c--)
    {
        for(int b = B; b>=0; b--)
        {
            for(int a = A; a>=0; a--)
            {
                if(c)
                    dp[a][b+1][c-1] = (ld)(dp[a][b][c]*c)/n;
                if(b)
                    dp[a+1][b-1][c] = (ld)(dp[a][b][c]*b)/n;
                if(a)
                    dp[a-1][b][c] = (ld)(dp[a][b][c]*a)/n;                    
            }
        }
    }
    cout << 1 << endl;
    cout << dp[0][0][0] << endl;
    */

    
	return 0;
}