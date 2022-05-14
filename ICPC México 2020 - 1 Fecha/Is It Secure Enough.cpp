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

string s; 

bool check1()
{
    for(auto c: s)
    {
        if(islower(c)) return true;
    }
    return false;
}

bool check2()
{
    for(auto c: s)
    {
        if(isupper(c)) return true;
    }
    return false;
}

bool check3()
{
    bool haveNumbers = false;
    int last = -10;
    for(auto c: s)
    {
        if(isdigit(c))
        {
            if(abs ((c - '0') - last) == 1) return false;
            haveNumbers = true;
            last = c - '0';
        }
        else
        {
            last = -10;
        }
    }
    return haveNumbers;
}

bool check4()
{
    for(auto c: s)
    {
        if(c == '.' || c == '#' || c == '$' || c == '%' || c == '/' || c == '(' || c == '&' || c == ')') return true;
    }
    return false;

}

bool check5()
{
    return (int)s.length() >= 10;
}

string solve()
{
    cin>>s;
    int sum = check1() + check2() + check3() + check4() + check5();
    if(sum == 5)
    {
        return "Strong";
    }
    else if(sum == 4)
    {
        return "Good";
    }
    else if(sum == 3)
    {
        return "Weak";
    }
    else
    {
        return "Rejected";
    }
}


int main () {
	fastIO();
    int t; cin>>t;
    for(int i = 1; i<=t; i++)
    {
        cout << "Assertion number #" << i << ": " << solve() << endl;
    }
    
	return 0;
}