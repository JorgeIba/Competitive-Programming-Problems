#include <bits/stdc++.h>
#define lli long long int
using namespace std;
vector<lli>dias(100010);
 
int main(){
	lli n,x,y,respuesta,indice=0,indice2=0,numero=0;
	bool si=true;
	cin>>n>>x>>y;
	
	for(lli i  = 0 ; i < n ;i++){
		cin>>dias[i];
	}	
	respuesta=n;
	for(lli i = 0 ; i < n-1 ;i++){
		indice+=1;
		indice2=0;
		if(dias[i]<dias[i+1]){
			respuesta=indice;
			numero=dias[i];
			for (lli j=1;j<=y;j++){
				indice2+=1;
				if(i+j>n-1)
					break;
				if(dias[i+j]<numero){
					
					si=false;
					i+=indice2-1;
					respuesta = indice;
					indice+=indice2-1;
					
					break;
				}
			}
			if(si){
				break;
			}
			si=true;
		}
		
	}
	cout<<respuesta<<endl;	
	return 0;
}
