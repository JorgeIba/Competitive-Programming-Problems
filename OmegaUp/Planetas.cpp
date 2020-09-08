#include <bits/stdc++.h>
#define ld long double
using namespace std;



int n;
priority_queue<int> solucion;

void funcion(int indiceI, int indiceSig, vector<int> pos)
{
    ld auxl=pos[indiceI], auxr=pos[indiceSig];
    //cout<<auxl<<" "<<auxr<<endl;
    ld m, M;
        for (int j=0; j<40; j++)
            {

                m=auxl + (auxr - auxl)/2;
                ld sumaM=0, sumam=0;
                //cout<<m<<endl;
                for(int i=indiceI; i>=0; i--)
                {
                        sumam+= (ld) 1/  (ld)(abs(pos[i] - m)) ;
                }
                for(int i=indiceSig; i<n; i++)
                {
                        sumaM+= (ld) 1/ (ld) (abs(pos[i] - m)) ;
                }
                
//                if (sumam==sumaM)
//                {
//                    M=m;
//                }
                if (sumam > sumaM)
                {
                    auxl=m;
                }
                else if (sumam < sumaM)
                {
                    auxr=m;
                }
            }
            cout<<fixed<<setprecision(3)<<m<<" ";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    cin>>n;
    vector<int> pos(n);
    for (int i=0; i<n; i++)
    {
        cin>>pos[i];
    }
	sort(pos.begin(), pos.end());
	cout<<n-1<<endl;
    for (int i=0; i<n-1; i++)
    {
        funcion(i, i+1, pos);
    }
    return 0;
}
