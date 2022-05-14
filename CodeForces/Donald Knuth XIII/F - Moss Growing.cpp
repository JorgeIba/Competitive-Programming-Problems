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
#define point pair<lli,lli>


typedef __int128 i128;

struct rectangle
{
	lli xl, yl, xh, yh;
    rectangle() {}
    rectangle(lli xl, lli yl, lli xh, lli yh): xl(xl), yl(yl), xh(xh), yh(yh) {}
};

i128 rectangle_area(vector<rectangle> &rs)
{
	vector<lli> ys; // coordinate compression
	for (auto r : rs)
	{
		ys.push_back(r.yl);
		ys.push_back(r.yh);
	}
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	int n = ys.size(); // measure tree
	vector<lli> C(8 * n), A(8 * n);
	function<void(int, int, int, int, int, int)> aux =
			[&](int a, int b, int c, int l, int r, int k)
			{
				if ((a = max(a,l)) >= (b = min(b,r))) return;
				if (a == l && b == r) C[k] += c;
				else
				{
					aux(a, b, c, l, (l+r)/2, 2*k+1);
					aux(a, b, c, (l+r)/2, r, 2*k+2);
				}
				if (C[k]) A[k] = ys[r] - ys[l];
				else A[k] = A[2*k+1] + A[2*k+2];
			};

	struct event
	{
		lli x, l, h, c;
	};
	// plane sweep
	vector<event> es;
	for (auto r : rs)
	{
		int l = lower_bound(ys.begin(), ys.end(), r.yl) - ys.begin();
		int h = lower_bound(ys.begin(), ys.end(), r.yh) - ys.begin();
		es.push_back({ r.xl, l, h, +1 });
		es.push_back({ r.xh, l, h, -1 });
	}
	sort(es.begin(), es.end(), [](event a, event b)
			{return a.x != b.x ? a.x < b.x : a.c > b.c;});
	i128 area = 0, prev = 0;
	for (auto &e : es)
	{
		area += (e.x - prev) * A[0];
		prev = e.x;
		aux(e.l, e.h, e.c, 0, n, 0);
	}
	return area;
}


vector< point > points;
lli n, m; 


bool check(lli t)
{
    vector< rectangle > rectangles;
    for(int i = 0; i < m; i++)
    {
        point p = points[i];
        lli x1 = max( p.first - t, 1LL);
        lli y1 = max( p.second - t, 1LL);
        lli x2 = min(p.first + t, n) + 1;
        lli y2 = min(p.second + t, n) + 1;
        
        rectangles.push_back(rectangle(x1, y1, x2, y2));
    }

    i128 ans = rectangle_area(rectangles);

    return ans % n == 0 && ans/n == n ;
}




int main () {
	//fastIO();

    cin>>n>>m;

    points.resize(m);
    for(auto &x: points) cin>>x.first>>x.second;


    
    lli l = 0, r = 1e18;
    lli ans = -1;


    while(l <= r)
    {
        lli mid = l + (r-l)/2;
        if(check(mid))
        {
            ans = mid;
            r = mid-1;
        }
        else
        {
            l = mid+1;
        }
    }

    cout << ans << endl;
    
    

	return 0;
}

