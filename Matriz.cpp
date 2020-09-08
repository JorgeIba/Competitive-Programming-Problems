#include <bits/stdc++.h>
#define lli long long int

using namespace std;

typedef vector< vector<int> > matriz;


matriz multi(matriz A, matriz B)
{
	lli rowsA = A.size();
	lli columA = A[0].size();
	lli columB = B[0].size();
	matriz C;
	C.assign(rowsA, vector<int> (columB,0));
	for(int i=0; i<rowsA; i++)
	{
		for(int j=0; j<columB; j++)
		{
			for(int k=0; k<columA; k++)
			{
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}
	
	return C;
}


matriz BinPow(matriz A, lli b)
{
	matriz res;
	res.assign(2, vector<int> (2,0));
	res[0][0]=1;
	res[1][1]=1;
	while(b)
	{
		if (b&1)
		{
			res = multi(res,A);
		}
		b/=2;
		A = multi(A,A);
	}
	return res;
}


lli fibo(lli n)
{
	if((n==0)or(n==1))
	{
		return 1;
	}
	matriz fib;
	fib.assign(2, vector<int> (1,0));
	fib[0][0] = 1;
	fib[1][0] = 1;
	matriz aux;
	aux.assign(2, vector<int>(2,0));
	aux[0][0] = 1;
	aux[0][1] = 1;
	aux[1][0] = 1;
	aux[1][1] = 0;
	matriz exxpo = BinPow(aux, n-2);
	matriz resultado = multi(exxpo, fib);
	
	return resultado[0][0];
	
}


int main()
{
	lli n;
	cin>>n;
	lli i=2;
	while(true)
	{
		
		lli res = fibo(i);
		if(res>=n)
		{
			return 0;
		}
		cout<<res<<" ";
		i++;
		
	}
	
	
	
	
	
	return 0;
}
