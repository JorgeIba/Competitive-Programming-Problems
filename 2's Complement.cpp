#include <bits/stdc++.h>
using namespace std;

unsigned int Contar(unsigned int i)
{
    int contador=0;
    while(i)
    {
        contador++;
        i&=(i-1);
    }
    return contador;
}
void Principal()
{
    long int inferior=0, mayor=0;
    int contadorMayor=0;
    cin>>inferior>>mayor;
    
    if ((inferior<=0)&&(mayor>=0))
    {
    	if (abs(inferior)<=mayor)
    	{
	    	for (unsigned int i=abs(inferior); i>=0; i-- )
	    	{
	    		if (i<mayor)
	    		{
	    			if (i%2!=0)
	    			{
	    				contadorMayor+=33;
					}
				}
			}
		}
		unsigned int nuevoInferior=mayor - abs(inferior);
		for (unsigned int q=nuevoInferior; q<=mayor; q++)
		{
			if ()
		}
    	
		
    }
    
    else if ((inferior<0)&&(mayor<0))
    {
        unsigned int complemento=0;
            for (unsigned int i=abs(inferior); i>=abs(mayor); i--)
            {
                complemento=(~i)+1;
                contadorMayor+=(Contar(complemento));
            }
    }
    
    
    else
    {
            for (unsigned int x=inferior; x<=mayor; x++ )
            {
                contadorMayor+=Contar(x);
            }    
    }
    
    cout<<contadorMayor<<endl;
}

int main()
{
    int casos=0;
    cin>>casos;
    for (int x=0; x<casos; x++)
    {
        Principal();
    }
    return 0;
}

