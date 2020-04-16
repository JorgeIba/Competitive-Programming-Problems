#include <iostream>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	int a=0, b=1, c=0, contador=0, inferior, superior;
	cin>>inferior>>superior;
	for (c;c<superior;)
	{
		if (c>inferior)
		{
			contador++;
		}
		c=a+b;
		a=b;
		b=c;
	}
	cout<<contador;
	return 0;
}

