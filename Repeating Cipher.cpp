#include <iostream>
#include <string>

using namespace std;

int main()
{
	char caracter;
	string cadena;
	int n=0, a=0;
	cin>>n;
	cin.ignore();
	getline(cin, cadena);
	for (int x=0; x<n; x=x+a)
	{
		cout<<cadena[x];
		a=a+1;
	}
	return 0;
}
