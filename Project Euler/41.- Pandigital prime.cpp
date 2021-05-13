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

vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			if(i * i <= n)
				for(int j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


lli largest = -1;

vector<int> availables = {0, 1, 1, 1, 1, 1, 1, 1};

void fun(int idx, string num)
{
    if(idx == 7)
    {
        //cout << num << endl;
        if(isPrime[stoi(num)])
        {
            largest = max(largest, (lli)stoi(num));
        }
        return;
    }
    for(int i = 1; i<=7; i++)
    {
        if(availables[i])
        {
            availables[i] = 0;
            string aux = num; aux+= to_string(i);
            fun(idx+1, aux);
            availables[i] = 1;
        }
    }
}


int main () {
	//fastIO();
    primesSieve(1e8);
    cerr << 1 << endl;
    fun(0, "");
    cout << largest << endl;

    
	return 0;
}