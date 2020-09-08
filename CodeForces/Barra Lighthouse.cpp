#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

ld eps = 1e-6;
const ld pi = acos(-1);
bool geq(ld a, ld b){return a-b >= -eps;}     //a >= b
bool leq(ld a, ld b){return b-a >= -eps;}     //a <= b
bool ge(ld a, ld b){return a-b > eps;}        //a > b
bool le(ld a, ld b){return b-a > eps;}        //a < b
bool eq(ld a, ld b){return abs(a-b) <= eps;}  //a == b
bool neq(ld a, ld b){return abs(a-b) > eps;}  //a != b

struct Point
{
    ld x, y;
    Point(): x(0), y(0) {}
    Point(ld x, ld y): x(x), y(y) {}

    ld distance()
    {
        return sqrt(x*x + y*y);
    }

    ld ang() const{
		ld a = atan2l(y, x); a += le(a, 0) ? 2*pi : 0; return a;
	}
};

lli n, t, d; 
ld alpha, T;

bool isAtDistance(Point &a)
{
    return leq(a.distance(), d);
}

int main()
{
    //fastIO();
    cin>>n>>t;
    cin>>alpha>>T>>d;
    ld velocity = 2*pi / T;
    alpha = alpha * pi / 180;
    vector< Point > points(n);
    for(int i = 0; i<n; i++)
    {
        cin >> points[i].x >> points[i].y;
    }

    vector< pair<ld,ld> > intervalReach(n); //Time

    for(int i = 0; i<n; i++)
    {
        Point p = points[i];
        intervalReach[i].first = p.ang() / velocity;
        intervalReach[i].second = (p.ang() + alpha) / velocity;
        cerr << intervalReach[i].first << " " << intervalReach[i].second << endl;
    }

    vector< ld > ans(n, 0);
    for(int i = 0; i<n; i++)
    {
        pair<ld,ld> interval = intervalReach[i];
        ld timeInside = interval.second - interval.first;
        ld timeRest = t - interval.first;
        lli howMuch = timeRest / T;
        ans[i] = howMuch * timeInside;
        ld aux = timeRest - howMuch*T;
        if(timeInside < aux)
        {
            ans[i] += timeInside;
        }
        else
        {
            ans[i] += aux;
        }
    }

    
    cout << fixed << setprecision(10);
    for(int i = 0; i<n; i++)
    {
        if( isAtDistance( points[i]  )  )
        {
            cout << ans[i] << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
    

    

    

    return 0;
}