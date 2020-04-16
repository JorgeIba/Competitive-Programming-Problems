#include <bits/stdc++.h>
#define lli long long int
#define ld long double
using namespace std;

void funcion(int p, int q, int r, int s, int t, int u)
{
	ld x=0.5;
	ld fx, fpx, sec;
	int dirty;
	for (int i=0; i<40; i++)
	{
		sec=1/(cos(x));
		fx=p*(exp(-x)) + (q*sin(x)) + (r*cos(x)) + (s*tan(x)) + (t*(x*x)) + u;
		fpx= (-p*(exp(-x))) + (q*(cos(x))) - (r*sin(x)) + s*(sec*sec) + (2*x*t);
		x= x - (fx/fpx);
	}
	if ((x>=-0.0001)and(x<=1.000009))
	{
		
		if (( p*(exp(-x)) + (q*sin(x)) + (r*cos(x)) + (s*tan(x)) + (t*(x*x)) + u <=0.0009   )and(( p*(exp(-x)) + (q*sin(x)) + (r*cos(x)) + (s*tan(x)) + (t*(x*x)) + u >=-0.0009 )))
		{
			cout<<fixed<<setprecision(4)<<abs(x)<<endl;	
		}
		else
		{
			cout<<"No solution\n";
		}
		
	}
	else
	{
		cout<<"No solution\n";
	}
	return;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	ifstream fichero;
	fichero.open("in.txt", ios::in);
	lli p,q,r,s,t,u;
	while (cin>>p>>q>>r>>s>>t>>u)
	{
		
		funcion(p,q,r,s,t,u);
	}
	return 0;
}

