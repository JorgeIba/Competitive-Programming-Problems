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

	//Max Flow Min Cost
	pair<T, T> maxFlowMinCost(int s, int t){
		vector<bool> inQueue(V);
		vector<T> distance(V), cap(V);
		vector<flowEdge<T>*> parent(V);
		T maxFlow = 0, minCost = 0;
		while(true){
			fill(distance.begin(), distance.end(), inf);
			fill(parent.begin(), parent.end(), nullptr);
			fill(cap.begin(), cap.end(), 0);
			distance[s] = 0;
			cap[s] = inf;
			queue<int> Q;
			Q.push(s);
			while(!Q.empty()){
				int u = Q.front(); Q.pop(); inQueue[u] = 0;
				for(flowEdge<T> *v : adjList[u]){
					if(v->capacity > v->flow && distance[v->dest] > distance[u] + v->cost){
						distance[v->dest] = distance[u] + v->cost;
						parent[v->dest] = v;
						cap[v->dest] = min(cap[u], v->capacity - v->flow);
						if(!inQueue[v->dest]){
							Q.push(v->dest);
							inQueue[v->dest] = true;
						}
					}
				}
			}
			if(!parent[t]) break;
			maxFlow += cap[t];
			minCost += cap[t] * distance[t];
			for(int u = t; u != s; u = parent[u]->res->dest)
				parent[u]->addFlow(cap[t]);
		}
		return {maxFlow, minCost};
	}
};


int main () {
	//fastIO();

    string want; cin>>want;
    lli n; cin>>n;

    vector<string> words(n);
    vector<lli> cap(n);
    for(int i = 0; i < n; i++) {
        cin>>words[i];
        cin>>cap[i];
    }


    
    const lli ALPH = 26;
    vector<lli> fr_want(ALPH);
    for(auto c: want) fr_want[c-'a']++;

    
    flowGraph<lli> *FG = new flowGraph<lli>(ALPH + n + 2);

    lli s = ALPH+n;
    lli t = ALPH+n+1;

    for(int i = 0; i < ALPH; i++) {
        FG->addEdge(s, i, fr_want[i], 0);
    }

    
    for(int i = 0; i < n; i++) {
        auto word = words[i];
        vector<lli> fr_word(ALPH);
        for(auto c: word) fr_word[c-'a']++;

        for(int j = 0; j < ALPH; j++) {
            if(fr_word[j]){
                FG->addEdge(j, ALPH+i, fr_word[j], i+1);
            }
        }
    }

    

    for(int i = 0; i < n; i++) {
        FG->addEdge(ALPH+i, t, cap[i], 0);
    }


    auto ans = FG->maxFlowMinCost(s, t);
    // cout << ans.first << " " << ans.second << endl;

    if(ans.first == SZ(want)) {
        cout << ans.second << endl;
    } else {
        cout << -1 << endl;
    }

    /*
    for(int i = 0; i < ALPH + n + 2; i++){
        cout << i << " ";
        if(i < ALPH) cout << i+'a';
        cout << ": ";
        for(auto E: FG->adjList[i]) {
            cout << " va pa: " << E->dest << " con cap: " << E->capacity << " y costo: " << E->cost << "  ";
        }
        cout << endl;
    }
    */


	return 0;
}

