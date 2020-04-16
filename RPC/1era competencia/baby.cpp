#include<bits/stdc++.h>

using namespace std;

int main(){
	int n;
	int indice=0;
	int aux=1;
	int numero;
	vector<string>cadenas(10000);
	vector<int>numeros(10000,-1);
	string entrada;
	bool correcto=false;
	bool flag=false;
	cin>>n;
	
	
	for(int i = 0 ; i < n ; i++){
		cin>>cadenas[i];
	}
	
	for (int i = 0; i <n; i++)
	{
		if (cadenas[i]=="mumble")
		{
			flag=true;
		}
		else
		{
			flag=false;
			break;
		}
	}
	if (flag)
	{
		cout<<"make sense\n";
		return 0;
	}
	
	
	if(n==1){
		cout<<"makes sense";
		exit(-1);
	}
		
	for(int i = 0 ; i < n ; i++){
		if(cadenas[i]!="mumble"){
			numeros[i]=atoi(cadenas[i].c_str());
		}
		else{
			if(i!=0 && numeros[i-1]!=-1)
				numeros[i]=numeros[i-1]+1;
		}
	}
	
	if(numeros[0]==-1){
		while(numeros[indice]==-1){
			indice++;
		}
		
		while(indice>0){
			numeros[indice-1]=numeros[indice]-1;
			indice--;
		}
	}
	
	for(int i = 0 ; i < n-1 ; i++){
		if(numeros[i]+1==numeros[i+1]){
			correcto=true;
		}
		else{
			correcto=false;
			break;
		}
	}
	
	if(numeros[0]<0){
		correcto=false;
	}
	
	if(correcto){
		cout<<"makes sense";
	}
	else{
		cout<<"something is fishy";
	}
	
}
