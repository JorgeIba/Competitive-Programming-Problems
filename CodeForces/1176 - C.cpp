#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;

lli arreglo[6];

int mappeo(lli n)
{
    switch(n)
    {
        case 4:
            return 0;
            break;
        case 8:
            return 1;
            break;
        case 15:
            return 2;
            break;
        case 16:
            return 3;
            break;
        case 23:
            return 4;
            break;
        case 42:
            return 5;
            break;
        
        default:
            return -1;
            break;
    }
}


bool check(lli n)
{
    lli aux = mappeo(n);
    if(aux == -1)
    {
        return false;
    }
    arreglo[aux]++;
    for(int i=aux; i<6; i++)
    {
        if(arreglo[aux] > arreglo[i])
        {
            arreglo[aux]--;
            return false;
        }
    }
    return true;
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(arreglo, 0, sizeof(arreglo));
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    lli contador = 0;
    for(int i=n-1; i>=0; i--)
    {
        lli num = nums[i];
        if(!check(num))
        {
            contador++;
        }
    }
    //cout<<contador<<endl;
    lli minimo = 1000000000000LL;

    for(int i=0; i<6; i++)
    {
        minimo = min(minimo, arreglo[i]);
    }
    for(int i=0; i<6; i++)
    {
        contador += (arreglo[i]-minimo);
    }
    cout<<contador<<endl;

    return 0;
}