#include <bits/stdc++.h>

#define fi first
#define se second
#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< string > matriz;

/*
12 11 3 11
...........
........3..
.......3.1.
...........
.......2...
.....2.....
.1.1.......
.....2.....
.1.........
...2.......
.1.........
...........
*/
#define coord pair<lli,lli>

const int MAXN = 30;
const ld INF = numeric_limits<lli>::max();
lli w, h, r, s; 

vector< vector< vector<coord> > > alcanzables; // los puntos que cada i, j alcanza
ld mem[MAXN][MAXN][MAXN*MAXN*10];
coord destino,inicio;


bool siAlcanza(lli x1, lli y1, lli x2, lli y2)
{
  return ( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= r*r  );
}

void getAlcanzables(lli I, lli J)
{
  for(int i = 0; i<w; i++)
  {
    for(int j = 0; j<h; j++)
    {
      if( matriz[i][j] != '.' && siAlcanza(I, J, i, j) )
      {
        if(i == I && j == J) continue;
        alcanzables[I][J].push_back({i,j});
      }
    }
  }
}

void sacarAlcanzables()
{
  for(int i = 0; i<w; i++)
  {
    for(int j = 0; j<h; j++)
    {
      if(matriz[i][j] != '.')
        getAlcanzables(i, j);
    }
  }
}

ld distancia(coord a, coord b){
  return sqrt((a.fi-b.fi)*(a.fi-b.fi) + (a.se-b.se)*(a.se-b.se));
}

//coord destino;

ld dp(int i, int j, int st){
    assert(matriz[i][j] != '.');
  if(st > s)
    return INF;
  if(i == destino.fi && j == destino.se)
      return 0;
  if(mem[i][j][st] >= 0)
      return mem[i][j][st];
  ld aux = INF;
  for(auto nxt:alcanzables[i][j]){
    aux = min(aux, distancia({i,j},nxt) + dp(nxt.fi,nxt.se,st + (matriz[nxt.fi][nxt.se] - '0')) );
  }
  return mem[i][j][st] = aux;
}

coord buscarMasAlejado(bool arriba)
{
    if(arriba)
    {
      for(int i = 0; i<w; i++)
        for(int j = 0; j<h; j++)
          if(matriz[i][j] != '.')
            return {i,j};
    }
    else
    {
      for(int i = w-1; i>=0; i--)
        for(int j = 0; j<h; j++)
          if(matriz[i][j] != '.')
            return {i,j};
    }
}

int main()
{
    //fastIO();
    for(int i = 0; i<MAXN; i++)
    {
        for(int j = 0; j<MAXN; j++)
        {
            for(int x = 0; x<MAXN*MAXN*10; x++)
            {
                mem[i][j][x] = -10;
            }
        }
    }
    cin>>w>>h>>r>>s;
    s = min(s, w*h*9);

    alcanzables.assign(w, vector<vector<coord>>(h));

    matriz.resize(w);
    for(int i = 0; i<w; i++)
    {
      cin>>matriz[i];
    }

    destino = buscarMasAlejado(true); // El punto a alcanzar
    coord inicio = buscarMasAlejado(false); // El punto de donde parte

    sacarAlcanzables();
    
    //ld ans = dp(inicio.fi,inicio.se, 0); -> este no da
    ld ans = dp(inicio.fi,inicio.se, matriz[inicio.first][inicio.second] - '0');
    if(ans > 1e10)
    {
        cout <<"impossible";
    }
    else
    {
        cout << fixed << setprecision(15) << ans;
    }
    
    
    return 0;
}