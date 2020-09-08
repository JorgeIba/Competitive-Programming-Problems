#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    lli value;
    Node *l = NULL, *r = NULL; // l-> 0, r -> 1
//    Node(lli digit): digit(digit){}
};

void insert(lli num, Node *root)
{
    Node *aux = root;
    for(lli i = 32; i>=0; i--)
    {
        //cerr << num << " " << ((1LL<<i))<< endl;
        if(num & (1LL<<i)) // pa la derecha
        {
            //cerr << "Si\n";
            if(aux->r == NULL)
            {
                aux->r = new Node();
            }
            aux = aux->r;
        }
        else // pa la izquierda
        {

            //cerr << "No\n";
            if(aux->l == NULL)
            {
                aux->l = new Node();
            }
            aux = aux->l;
        }
    }
    aux->value = num;
}

lli query(lli sum, Node *root)
{
    Node *aux = root;
    lli mask = 0;
    for(lli i = 32; i>=0; i--)
    {
        if(sum&(1LL<<i)) // Voy a buscar un cero
        {
            if(aux->l != NULL)
            {
                aux = aux->l;
            }
            else
            {
                if(aux->r == NULL) cout << i << endl;
                //assert(aux->r != NULL);
                //mask = mask | (1LL<<i);
                aux = aux->r;
            }
        }
        else // Voy a buscar un uno
        {
            if(aux->r != NULL)
            {
                //mask = mask | (1LL<<i);
                aux = aux->r;
            }
            else
            {
                if(aux->l == NULL) cout << i << endl;
                //assert(aux->l != NULL);
                aux = aux->l;
            }
        }
    }
    return aux->value ^ sum;
}


void solve()
{
    lli n; cin>>n;
    vector< lli > nums(n+1);
    for(int i = 1; i<=n; i++) cin>>nums[i];
    vector< lli > sumXOR(n+1);
    for(int i = 1; i<=n; i++)
    {
        sumXOR[i] = sumXOR[i-1] ^ nums[i];
    }
    lli maximum = -1;
    Node *root = new Node();

    for(int i = 0; i<=n; i++) insert(sumXOR[i], root);

    for(int i = 0; i<=n; i++)
    {
        //cout << i << " ";
        lli q = query(sumXOR[i], root);
        //cout << q << endl;
        maximum = max(maximum, q);
    }
    cout << maximum << " ";

}


int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}