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

const lli maxN = 1e6+10;
const lli MOD = 188888881; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r)
{
    if(n<0 || r < 0 || r>n) return 0;
    return fact[n] * invFact[n-r] % MOD * invFact[r] % MOD;
}


int main () {
	//fastIO();
    prec();
    lli n; cin>>n;
    string s;
    cin.ignore();

    map< string, pair<lli,lli> > orders;

    bool isOrdering = false;

    while(getline(cin, s))
    {
        istringstream auxS(s);
        string word;
        vector< string > words;
        while(auxS >> word)
        {
            words.push_back(word);
        }
        
        if(SZ(words) == 1)
        {
            if(words[0] != "Restaurant")
                isOrdering = true;
            else
                isOrdering = false;
        } 
        else
        {
            lli howMany = stoi(words[0]);
            string dish;
            for(auto c: words[1]) dish.push_back(tolower(c));
            
            if(isOrdering)
            {
                orders[dish].first += howMany;
            }
            else
            {
                orders[dish].second = howMany;
            }
        }
    }


    vector<lli> max_amount;

    for(auto x: orders)
    {
        n -= x.second.first;
        max_amount.push_back(x.second.second - x.second.first);
    }

    if(n < 0)
    {
        cout << 0 << endl;
        return 0;
    }
    for(auto x: max_amount)
    {
        if(x<0)
        {
            cout << 0 << endl;
            return 0;
        }
    }

    lli N = SZ(max_amount);

    lli up = n + N - 1;

    lli ans = 0;
    for(lli mask = 0; mask<(1<<N); mask++)
    {
        lli taken = 0;
        for(int j = 0; j<N; j++)
        {
            if(mask & (1<<j))
            {
                taken += (max_amount[j] + 1);
            }
        }

        lli howMany = nCr(up - taken, N-1);
        if(__builtin_popcount(mask) & 1)
        {
            ans = (ans - howMany)%MOD;
            if(ans < 0) ans += MOD;
        }
        else
        {
            ans = (ans + howMany)%MOD;
        }
    }

    //cin.ignore();
    cout << ans << endl;

    

    
	return 0;
}