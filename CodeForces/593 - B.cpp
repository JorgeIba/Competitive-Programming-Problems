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

struct Line{
    lli m, b;
    Line() {}
    Line(lli m, lli b): m(m), b(b) {}
    lli eval(lli x){ return m*x + b; }
};

lli n, x1, x2; 

bool compare(Line A, Line B)
{
    return A.eval(x1) < B.eval(x1) || (A.eval(x1) == B.eval(x1) && A.eval(x2) < B.eval(x2));
}

int main () {
	//fastIO();
    cin>>n>>x1>>x2;

    vector<Line> lines(n);
    for(int i = 0; i<n; i++)
    {
        cin>>lines[i].m>>lines[i].b;
    }

    sort(all(lines), compare);

    lli last_x1 = lines[0].eval(x1), last_x2 = lines[0].eval(x2);
    bool ans = false;
    for(int i = 0; i<n; i++)
    {
        lli evaluation_x1 = lines[i].eval(x1);
        lli evaluation_x2 = lines[i].eval(x2);

        //cout << evaluation_x1 << " " << evaluation_x2 << endl;

        if(last_x1 < evaluation_x1 && last_x2 > evaluation_x2) ans = true;
        
        last_x1 = evaluation_x1;
        if(evaluation_x2 > last_x2) last_x2 = evaluation_x2;
    }

    cout << (ans? "YES" : "NO") << endl;
    
	return 0;
}