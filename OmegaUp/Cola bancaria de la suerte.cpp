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
typedef tuple<int,int,string> LLS;

int first(const LLS &a) { return get<0>(a); }
int second(const LLS &a) { return get<1>(a); }
string third(const LLS &a) { return get<2>(a); }


class Compare{
    public:
    bool operator()(const LLS &a, const LLS &b)
    {
        return (first(a) < first(b)) || (first(a) == first(b) && second(a) > second(b));
    }
};

vector< priority_queue<LLS, vector<LLS>, Compare> > best_letter(26); //{priority, time}
vector<lli> current_lazy(26);
lli t = 0;

void insert_custom(const string &name, const int &priority)
{
    char first = name[0];
    best_letter[first-'A'].push({priority - current_lazy[first-'A'], t++, name});
}

void add_custom(const char &first,const int &adding)
{
    current_lazy[first-'A'] += adding;
}

const lli INF = 1e9;
string get_top()
{
    LLS better = {-INF, INF, "null"};
    for(int i = 'A'; i<='Z'; i++)
    {
        if(best_letter[i-'A'].empty()) continue;

        LLS current = best_letter[i-'A'].top();
        get<0>(current) += current_lazy[i-'A'];

        better = max({better, current}, Compare());
    }

    char first = (third(better))[0];
    best_letter[first-'A'].pop();

    return third(better);
}



int main () {
	fastIO();
    
    int q; cin>>q;
    
    while(q--)
    {
        char t; cin>>t;
        if(t == 'C')
        {
            string name; cin>>name;
            int priority; cin>>priority;
            insert_custom(name, priority);
        }
        else if(t == 'S')
        {
            char first; cin>>first;
            int adding; cin>>adding;
            add_custom(first, adding);
        }
        else
        {
            cout << get_top() << endl; 
        }
    }

    
	return 0;
}