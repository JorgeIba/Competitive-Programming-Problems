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



const lli maxN = 5e5+1;
const lli sz = 2*maxN+10;

// 7
struct UnionFind {
  int n;
  vector<lli> dad, size;
  vector<vector<lli>> values;
  vector<int> value_saves;

  UnionFind(int N): n(sz), dad(sz), size(sz, 1), values(sz), value_saves(sz) {
    for(int i = 1; i <= maxN; i++)
    {
        value_saves[i] = i;
    } 
    for(int i = 1; i<sz; i++) dad[i] = i;
  }
  // 4
  // O(lg*(N))
  int root(int u) {
    if (dad[u] == u) return u;
    return dad[u] = root(dad[u]);
  }
  // 8
  // O(1)
  void join(int u, int v, int value) {
    int Ru = root(u), Rv = root(v);
    if (Ru == Rv) return;
    // if (size[Ru] > size[Rv]) swap(Ru, Rv);
    --n, dad[Ru] = Rv;
    value_saves[Rv] = value;
    size[Rv] += size[Ru];
  }
  // 4
  // O(lg*(N))
  bool areConnected(int u, int v) {
    return root(u) == root(v);
  }
  // 4
  int getSize(int u) { return size[root(u)]; }

  int numberOfSets() { return n; }

    int getValuesSaves(int u) { return value_saves[root(u)]; }

    void insert_element(lli u, lli value) {
        values[u].push_back(value);
    }

};


void print(int count_first, UnionFind *UF)
{
    vector<lli> ans(count_first);
    for(int i = 1; i < (int)UF->value_saves.size(); i++)
    {
        lli value = UF->getValuesSaves(i);
        // cout << i << " with value " << UF->getValuesSaves(i) << ":\n";
        for(auto x: UF->values[i])
        {
            ans[x-1] = value;
            // cout << x << " ";
        }
        // cout << endl;
    }
    
    for(auto x: ans)
    {
        assert(1 <= x && x <= 5e5);
        cout << x << " ";
    } 
    cout << endl;
}


int main () {
	fastIO();
	
    lli q; cin>>q;

	UnionFind *UF = new UnionFind(q+1);


    map<lli,lli> num_to_idx;

    for(int i = 1; i<=maxN; i++) {
        num_to_idx[i] = i;
    }



    int idx_array = 1, last_group = q+1, count_first = 0;
    for(int i = 0; i < q; i++)
    {
        lli t; cin>>t;
        if(t == 1)
        {
            lli x; cin>>x; //insert x at the end
            assert(1 <= x && x <= 5e5);
            lli idx = num_to_idx[x];
            UF->insert_element(idx, idx_array++);

            count_first++;
        }
        else {
            lli x, y; cin>>x>>y; // change x for y

            assert(1 <= x && x <= 5e5);
            assert(1 <= y && y <= 5e5);
            
            if(x == y) continue;
            if(!num_to_idx.count(x) || UF->value_saves[num_to_idx[x]] != x) continue;



            lli idx_x = num_to_idx[x];
            lli idx_y = num_to_idx[y];

            UF->join(idx_x, idx_y, y);

            UF->value_saves[last_group] = x;
            num_to_idx[x] = last_group++;
            
        }     
    }


    print(count_first, UF);



	return 0;
}

