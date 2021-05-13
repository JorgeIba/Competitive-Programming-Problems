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

bool check(string num)
{
    bitset<10> counting;
    for(auto c: num)
    {
        int digit = c - '0';
        if(digit == 0) return false;
        counting[digit] = 1;
    } 
    return counting.count() == 9 && (int)num.length() == 9;
}



int main () {
	//fastIO();
    vector<int> multiplies = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    lli last = -1;
	for(int n = 1; n<=10000; n++)
    {
        string concatProduct;
        for(int num: multiplies)
        {
            concatProduct += to_string(n*num);
            if(concatProduct.length() == 9 && check(concatProduct))
            {
                last = max(last, (lli)stoi(concatProduct));
            }
        }
    }
    cout << last << endl;
    
	return 0;
}