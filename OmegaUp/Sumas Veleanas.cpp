#include <bits/stdc++.h>
using namespace std;

int main()
{
	stack<char> pila;
	string entrada;
	long int acumulador=0;
	getline(cin, entrada);
	char letra;
	
	for (int i=0; i<entrada.length(); i++)
	{
		letra=entrada[i];
		if ((letra=='(')or(letra=='{')or(letra=='['))
		{
			pila.push(letra);
		}
		else
		{
			if ((pila.top()=='(')and(letra==')'))
			{
				pila.pop();
			}
			else if ((pila.top()=='[')and(letra==']'))
			{
				pila.pop();
			}
			else if ((pila.top()=='{')and(letra=='}'))
			{
				pila.pop();
			}
			else
			{
				pila.pop();
				acumulador+=1;
			}
		}
	}
	cout<<acumulador;
	
	return 0;
}
