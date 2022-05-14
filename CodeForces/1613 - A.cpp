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


void solve()
{
    lli num1, x1, num2, x2; 
    cin>>num1>>x1;
    cin>>num2>>x2;

    string s_num1 = to_string(num1);
    string s_num2 = to_string(num2);

    while(SZ(s_num1) < SZ(s_num2) && x1 > 0)
    {
        s_num1.push_back('0');
        x1--;
    }

    while(SZ(s_num1) > SZ(s_num2) && x2 > 0)
    {
        s_num2.push_back('0');
        x2--;
    }

    if(SZ(s_num1) + x1 > SZ(s_num2) + x2)
    {
        cout << ">" << endl;
    }
    else if(SZ(s_num1) + x1 < SZ(s_num2) + x2)
    {
        cout << "<" << endl;
    }
    else {
        //same size
        if(s_num1 < s_num2)
        {
            cout << "<" << endl;
        }
        else if(s_num1 > s_num2)
        {
            cout << ">" << endl;
        }
        else cout << "=" << endl;
    }
    
}



int main () {
	fastIO();
    int t; cin>>t;

    while(t--) solve();


	return 0;
}

