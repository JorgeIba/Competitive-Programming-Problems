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

lli n, k; 
string s;

const lli maxN = 1e3 + 20, maxK = 1e3+20;
lli dp[maxN][2*maxK];


bool fun(lli idx, lli diff)
{
    if(idx == n)
    {
        return abs(diff) == k;
    }
    if(abs(diff) == k)
    {
        return false;
    }

    lli &ans = dp[idx][diff+1000];
    if(ans != -1) 
        return ans;


    char curr = s[idx];
    if(curr == 'L')
    {
        return ans = fun(idx+1, diff-1);
    }
    else if(curr == 'D')
    {
        return ans = fun(idx+1, diff);
    }
    else if(curr == 'W')
    {
        return ans = fun(idx+1, diff+1);
    }
    else
    {
        return ans = (fun(idx+1, diff+1) || fun(idx+1, diff-1) || fun(idx+1, diff));
    }
}



void build_ans(lli idx, lli diff, string &ans)
{
    if(idx == n)
        return;
    
    char curr = s[idx];
    if(curr == 'L')
    {
        ans += "L";
        build_ans(idx+1, diff-1, ans);
    }
    else if(curr == 'D')
    {
        ans += "D";
        build_ans(idx+1, diff, ans);
    }
    else if(curr == 'W')
    {
        ans += "W";
        build_ans(idx+1, diff+1, ans);
    }
    else
    {
        if(fun(idx+1, diff+1))
        {
            ans += "W";
            build_ans(idx+1, diff+1, ans);
        }
        else if(fun(idx+1, diff-1))
        {
            ans += "L";
            build_ans(idx+1, diff-1, ans);
        }
        else{
            ans += "D";
            build_ans(idx+1, diff, ans);
        }
    }
}


int main () {
	fastIO();
    cin>>n>>k;
    cin>>s;


    memset(dp, -1, sizeof(dp));

    if(fun(0,0))
    {
        string ans;
        build_ans(0,0,ans);
        cout << ans << endl;
    }
    else{
        cout << "NO" << endl;
    }

	return 0;
}

