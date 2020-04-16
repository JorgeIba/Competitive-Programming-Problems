#include <iostream>
#include <string>
#include <stack>
using namespace std;
	int ChecarPila(char , stack <char>&, char,stack <int>&, int );
	int Buscar(stack <int>);

int main()
{
	ios::sync_with_stdio(false);
	string S;
	int tamano, posicion;
	getline(cin, S);
	stack <char> pila;
	stack <int> Sposicion;
	char comparar;
	tamano=S.length();
	for (int i=0; i<tamano; i++)
	{ 
		posicion=i+1;
		if ((S[i]=='(') or (S[i]==')') )
		{
			comparar='(';
			if (ChecarPila(S[i], pila, comparar, Sposicion, posicion)==1)
			{
				cout<<i+1;
				return 0;
			}
		}
		else if ((S[i]=='[') or (S[i]==']'))
		{
			comparar='[';
			if (ChecarPila(S[i], pila, comparar, Sposicion, posicion)==1)
			{
				cout<<i+1;
				return 0;
			}
		}
		
		else if ((S[i]=='{') or (S[i]=='}'))
		{
			comparar='{';
			if (ChecarPila(S[i], pila, comparar, Sposicion, posicion)==1)
			{
				cout<<i+1;
				return 0;
			}
		}
		
	}
	if(pila.empty())
	{
		cout<<"Success";
	}
	else 
	{
	cout<<Buscar(Sposicion);
	}
	return 0;
}

int ChecarPila(char elemento, stack <char> &pila, char comparar, stack <int> &Sposicion, int posicion)
{
	if ((elemento=='(') or (elemento=='[') or (elemento=='{'))
	{
		pila.push(elemento);
		Sposicion.push(posicion);
	}
	else if ((elemento==')') or (elemento==']') or (elemento=='}'))
	{
		if (pila.empty())
		{
			return 1;
		}
		if (comparar==pila.top())
		{
			Sposicion.pop();
			pila.pop();
		}
		else
		{
			return 1;
		}
	}
	if (pila.empty())
	{
		return 0;
	}
}
int Buscar(stack <int> Sposicion)
{
	int aux;
	while (!Sposicion.empty())
	{
		aux=Sposicion.top();
		Sposicion.pop();
	}
	return aux;
}
