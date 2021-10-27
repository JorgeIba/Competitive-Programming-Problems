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


vector< vector< lli > > adjList(26);
vector< string > names;

vector<lli> topologicalSort(vector< vector<lli> > &adjList)
{
    int V = SZ(adjList);
    vector<int> in_degree(V, 0);

    for(int i = 0; i<V; i++)
        for(auto v: adjList[i])
            in_degree[v]++;
 
    queue<int> q;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            q.push(i);

    int cnt = 0;
 
    vector<int> top_order;
 
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        top_order.push_back(u);
 
        for(auto v: adjList[u])
        {
            if(--in_degree[v] == 0)
            {
                q.push(v);
            }
        }
        cnt++;
    }
 
    if (cnt != V) {
        return {-1};
    }
 
    vector<lli> ans;
    for(auto u: top_order)
        ans.push_back(u);
    

    return ans;
}
 



int get_diff(string &a, string &b)
{
    int n = SZ(a), m = SZ(b);

    for(int i = 0; i < min(n, m); i++)
    {
        if(a[i] != b[i])
        {
            return i;
        }
    }

    return (n < m ? -1 : -2);
}


int main () {
	//fastIO();
    lli n; cin>>n;  
    names.resize(n);
    for(auto &x: names) cin>>x;

    for(int i = 0; i<n; i++)
    {
        for(int j = i+1; j<n; j++)
        {
            int idx = get_diff(names[i], names[j]);
            if(idx == -1) //una es prefijo de la otra
            {

            }
            else if(idx == -2)
            {
                cout << "Impossible\n";
                return 0;
            }
            else
            {
                char letter_a = names[i][idx], letter_b = names[j][idx]; //letter_a < letter_b
                //cout << letter_a << " " << letter_a - 'a' << " " << letter_b << "  " << letter_b - 'a' << endl;
                adjList[ letter_a - 'a' ].push_back( letter_b - 'a' );
            }
        }
    }

    
    
    auto ans = topologicalSort(adjList);

    if(ans[0] == -1)
    {
        cout << "Impossible\n";
    }
    else
    {
        for(auto x: ans) cout << char(x+'a');
        cout << endl;
    }
	


	return 0;
}

