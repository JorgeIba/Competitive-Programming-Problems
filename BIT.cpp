#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> BIT;
vector<lli> numeros;


void build(lli index, lli num)
{
    while(index < BIT.size())
    {
        BIT[index] += num;
        index += index&(-index);
    }
}

void update(lli index, lli num)
{
    num = num - BIT[index];
    while(index < BIT.size())
    {
        BIT[index] += num;
        index += index&(-index);
    }

}


lli sum(lli index)
{
    lli res = 0;
    while(index)
    {
        res+=BIT[index];
        index -= index&(-index);
    }
    return res;
}



int main()
{
    cout<<"Cuantos elementos?\n";
    lli n; cin>>n;
    numeros.resize(n);
    BIT.resize(n+1);
    for(auto &num: numeros)
    {
        cin>>num;
    }
    for(int i=0; i<n; i++)
    {
        build(i+1, numeros[i] );
    }
    cout<<"Cuantas queries?\n";
    lli queries; cin>>queries;
    while(queries--)
    {
        cout<<"0:Change()\t1:Sum()\n";
        lli type, index; cin>>type;
        switch(type)
        {
            case 0:
                cout<<"Ingresa el index y el valor:\n";
                lli value; cin>>index>>value;
                update(index, value);        
            break;

            case 1:
                cout<<"Ingresa el index\n";
                cin>>index;
                cout<< sum(index) << endl;
            break;
        }
    }


    return 0;
}