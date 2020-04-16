#include <iostream>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	long int w=0, i=0, p1=0, p2=0, a1=0, a2;
	cin>>w>>i>>p1>>a1>>p2>>a2;
	while (i>0)
	{
			w+=i;
			if (i==a1)
			{
				w-=p1;
			}
			else if (i==a2)
			{
				w-=p2;
			}
			i--;
			if (w<0)
			{
				w=0;
			}
	}
	cout<<w;
	return 0;
}
