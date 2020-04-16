#include <iostream>
#include <queue>

using namespace std;

	//Protocolo de Funciones
	void principal();
	
int main()
{
	long int t=0;
	cin>>t;
	for (long int q=0; q<t; q++)
	{
		principal();
	}
	return 0;
}

void principal()
{
	long int n=0, num=0, acum=0, suma=0, aux=0;
	priority_queue<int> cola;
	cin>>n;
	for (long int i=0; i<n; i++)
	{
		cin>>num;
		cola.push(num*-1);
	}
	for (long int x=0; x<(n-1); x++)
	{
		aux=cola.top();
		cola.pop();
		suma=aux+cola.top();
		acum=acum+suma;
		cola.pop();
		cola.push(suma);
		
	}
	cout<<acum*-1<<endl;
}
