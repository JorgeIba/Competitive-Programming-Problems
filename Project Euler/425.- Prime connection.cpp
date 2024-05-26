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


//20
vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


const lli maxN = 1e7;
vector<lli> getTransitions(lli n) {

    string str_n = to_string(n);
    int sz = str_n.length();

    vector<lli> transitions;
    for(lli i = 1; i <= 9; i++) {
        string tran = to_string(i) + str_n;
        lli v = stoll(tran);

        if(v <= maxN && isPrime[v]) {
            transitions.push_back(v);
        }
    }

    for(int pos = 0; pos < sz; pos++) {
        for(int d = 0; d <= 9; d++) {
            if(d == 0 && pos == 0) continue;

            string tran = str_n;
            tran[pos] = d + '0';

            if(tran == str_n) continue;

            lli v = stoll(tran);

            if(v <= maxN && isPrime[v])
            {
                transitions.push_back(v);
            }
                
        }
    }

    return transitions;
}




int main () {
	fastIO();

    time_t begin_t = clock();

    primesSieve(maxN+1);


    vector<vector<lli>> adjList(maxN+1);
    for(auto p: primes) {
        adjList[p] = getTransitions(p);
    }
    
    
    vector<lli> starts = {2};

    const lli INF = 1e18;
    vector<lli> dist(maxN+1, INF);

    queue<lli> q;
    
    q.push(2);
    dist[2] = 0;

    while(!q.empty()) {
        auto u = q.front(); q.pop();

        for(auto v: adjList[u]) {
            lli max_way = max(dist[u], u);
            if(max_way < dist[v]) {
                dist[v] = max_way;
                q.push(v);
            }
        }
    }

    lli ans = 0;
    for(int i = 2; i <= maxN; i++) {    
        ans += i*(isPrime[i] && dist[i] >= i);
    }
    cout << ans << endl;
    

    cout << (ld)(clock() - begin_t) / CLOCKS_PER_SEC << endl;

	return 0;
}




