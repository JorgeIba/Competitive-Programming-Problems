#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;



int main () {
	//fastIO();

    int w, h, n; cin>>w>>h>>n;

    multiset<int> Ws, Hs;
    Ws.insert(w);
    Hs.insert(h);

    set<int> lines_w, lines_h;
    lines_w.insert(0);
    lines_w.insert(w);

    lines_h.insert(0);
    lines_h.insert(h);


    auto insert_w = [&](int line) -> void {
        lines_w.insert(line);
        auto itr = lines_w.find(line);
        int line_prev = *(--itr);
        int line_next  = *(++(++itr));

        Ws.erase(Ws.find(line_next - line_prev));
        
        Ws.insert(line - line_prev);
        Ws.insert(line_next - line);
    };

    auto insert_h = [&](int line) -> void {
        lines_h.insert(line);
        auto itr = lines_h.find(line);
        int line_prev = *(--itr);
        int line_next  = *(++(++itr));
    
        itr = Hs.find(line_next - line_prev);
        assert(itr != Hs.end());
        Hs.erase( itr );
        
        lines_h.insert(line);
        Hs.insert(line - line_prev);
        Hs.insert(line_next - line);
    };


    auto get_ans = [&]() -> lli {
        auto gr_w = *Ws.rbegin();
        auto gr_h = *Hs.rbegin();
        return 1LL * gr_w * gr_h;
    };


    while(n--){
        char t;
        int line;
        cin>>t>>line;
        if(t == 'H') {
            insert_h(line);
        } else {
            insert_w(line);
        }

        cout << get_ans() << endl;
    }










	return 0;
}

