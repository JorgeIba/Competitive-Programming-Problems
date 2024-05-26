#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;


template<typename T>
struct flowEdge{
	int dest;
	T flow, capacity, cost;
	flowEdge *res;

	flowEdge(): dest(0), flow(0), capacity(0), cost(0), res(NULL){}
	flowEdge(int dest, T flow, T capacity, T cost = 0): dest(dest), flow(flow), capacity(capacity), cost(cost), res(NULL){}

	void addFlow(T flow){
		this->flow += flow;
		this->res->flow -= flow;
	}
};

template<typename T>
struct flowGraph{
	T inf = numeric_limits<T>::max();
    int V;
	vector<vector<flowEdge<T>*>> adjList;
	vector<int> dist, pos;
	
	flowGraph(int V): V(V), adjList(V), dist(V), pos(V){}
	~flowGraph(){
		for(int i = 0; i < V; ++i)
			for(int j = 0; j < adjList[i].size(); ++j)
				delete adjList[i][j];
	}
	void addEdge(int u, int v, T capacity, T cost = 0){
		flowEdge<T> *uv = new flowEdge<T>(v, 0, capacity, cost);
		flowEdge<T> *vu = new flowEdge<T>(u, capacity, capacity, -cost);
		uv->res = vu;
		vu->res = uv;
		adjList[u].push_back(uv);
		adjList[v].push_back(vu);
	}

	//Maximun Flow using Dinic Algorithm O(EV^2)
	T blockingFlow(int u, int t, T flow){
		if(u == t) return flow;
		for(int &i = pos[u]; i < (int)adjList[u].size(); ++i){
			flowEdge<T> *v = adjList[u][i];
			if(v->capacity > v->flow && dist[u] + 1 == dist[v->dest]){
				T fv = blockingFlow(v->dest, t, min(flow, v->capacity - v->flow));
				if(fv > 0){
					v->addFlow(fv);
					return fv;
				}
			}
		}
		return 0;
	}
	T dinic(int s, int t){
		T maxFlow = 0;
		dist[t] = 0;
		while(dist[t] != -1){
			fill(dist.begin(), dist.end(), -1);
			queue<int> Q;
			Q.push(s);
			dist[s] = 0;
			while(!Q.empty()){
				int u = Q.front(); Q.pop();
				for(flowEdge<T> *v : adjList[u]){
					if(dist[v->dest] == -1 && v->flow != v->capacity){
						dist[v->dest] = dist[u] + 1;
						Q.push(v->dest);
					}
				}
			}
			if(dist[t] != -1){
				T f;
				fill(pos.begin(), pos.end(), 0);
				while((f = blockingFlow(s, t, inf)))
					maxFlow += f;
			}
		}
		return maxFlow;
	}


};

#define point pair<lli,lli>


const int AVA = 1;
const int MARK = 2;
const int DEV = 3;

void main_(){
    int n, m; cin>>n>>m;
    vector< vector<int> > mat(n+1, vector<int>(m+1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char t; cin>>t;
            if(t == 'H') {
                mat[i][j] = AVA;
            } else if(t == 'A') {
                mat[i][j] = MARK;
            } else {
                mat[i][j] = DEV; 
            }
        }
    }

    for(int i = 0; i <= m; i++) mat[n][i] = MARK;
    for(int i = 0; i <= n; i++) mat[i][m] = MARK;


    // for(int i = 0; i <= n; i++) {
    //     for(int j = 0; j <= m; j++) {
    //         cout << mat[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    int N = n+1, M = m+1;

    flowGraph<lli> *FG = new flowGraph<lli>(N*M + 5);

    int s = N*M + 2;
    int t = N*M + 3;

    auto get_idx = [&](lli i, lli j) {
        return i*(M) + j;
    };

    
    vector< vector<point> > closest_down(n, vector<point>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == AVA) {
                for(int k = i; k < N; k++) {
                    if(mat[k][j] == MARK) {
                        closest_down[i][j] = {k, j};
                        break;
                    }
                } 
            }
        }
    }


    for(int i = 0; i < n; i++) {
        for(int j = 0; j < M; j++) {
            if(mat[i][j] == MARK) {
                for(int k = j-1; k >= 0; k--) {
                    if(mat[i][k] == MARK) break;
                    else if(mat[i][k] == AVA){
                        auto p = closest_down[i][k];
                        FG->addEdge(get_idx(i, j), get_idx(p.first, p.second), 1);
                    }
                }
            }
        } 
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(mat[i][j] == MARK) {
                FG->addEdge(s, get_idx(i, j), 1);
                FG->addEdge(get_idx(i, j), t, 1);
            }
        }
    }

    
    for(int i = 0; i < m; i++) FG->addEdge(get_idx(n, i), t, 1);
    for(int i = 0; i < n; i++) FG->addEdge(s, get_idx(i, m), 1);
        
    lli ans = FG->dinic(s, t);

    cout << ans << endl;
}


int main () {
	fastIO();
	
	int t = 1; 
    cin>>t;
	while(t--) 
		main_();


	return 0;
}

