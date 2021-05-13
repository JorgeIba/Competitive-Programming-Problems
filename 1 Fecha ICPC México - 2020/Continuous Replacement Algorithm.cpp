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

map<string,int> mappeo;
map<int, string> desmappeo;
int cont = 0;


int mapp(const string &s)
{
    if(mappeo.count(s) == 0)
    {
        mappeo[s] = cont;
        desmappeo[cont] = s;
        cont++;
    }
    return mappeo[s];
}


bool compare2(const string &s, const string &t)
{
    int n = s.length();
    int m = t.length();
    if( n == m ) return s < t;
    return n<m;
}


// 7
struct UnionFind {
  int n;
  vector<int> dad, size;
  vector<string> mins;

  UnionFind(int N) : n(N), dad(N), size(N, 1), mins(N) {
    while (N--)
    {
        dad[N] = N;
        mins[N] = desmappeo[N];
    } 
  }
  // 4
  // O(lg*(N))
  int root(int u) {
    if (dad[u] == u) return u;
    return dad[u] = root(dad[u]);
  }
  // 8
  // O(1)
  void join(int u, int v) {
    int Ru = root(u), Rv = root(v);
    if (Ru == Rv) return;
    if (size[Ru] > size[Rv]) swap(Ru, Rv);
    --n;
    dad[Ru] = Rv;
    
    if(compare2(mins[Ru], mins[Rv]))
    {
        mins[Rv] = mins[Ru];
    } 
    else mins[Ru] = mins[Rv];

    
    size[Rv] += size[Ru];
  }
  // 4
  // O(lg*(N))
  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }

    string getMin(int idx)
    {
        return mins[ root(idx) ];
    }


  // 4
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }
};

vector<string> getWords(const string &sentence)
{
    vector<string> ans;
    string aux;
    for (auto x : sentence) 
    {
        if (x == ' ')
        {
            ans.push_back(aux);
            aux = "";
        }
        else {
            aux += x;
        }
    }
    ans.push_back(aux);
    return ans;
}

int main () {
	fastIO();
    int n; cin>>n;
    vector<int> mapping;
    vector< vector<int> > adjList(2*(n+1));
    

    for(int i = 0; i<n; i++)
    {
        string s, t; cin>>s>>t;
        int u = mapp(s);
        int v = mapp(t);
        //cerr << u << " " << v << endl;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
	int how = cont;
    UnionFind U(cont);
    for(int i = 0; i<cont; i++)
    {
        for(auto v: adjList[i])
        {
            //cout << i << endl;
            U.join(i, v);
        }
    }

    cin.ignore();
    string ans;
    string sentence;
    getline(cin,sentence);

    auto words = getWords(sentence);
    int q = SZ(words);
    for(int i = 0; i<q; i++)
    {
        string word = words[i];
        int idx = mapp(word);
        //cerr << idx << " " << how << endl;
        if(idx >= how) ans += word;
        else
        {
            ans += U.getMin( idx );
        }
        if(i != q-1)
        {
            ans += " ";
        }
    }
    cout << ans << endl;
    

    
	return 0;
}