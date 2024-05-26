#include <bits/stdc++.h>
 
using namespace std;

const int MAXN = 1000 + 10;

char mat[MAXN][MAXN];
bool visited[MAXN][MAXN];

int n, m;

// Función para saber si una coordenada (x,y) es válida o se sale de la matriz
bool isInside(int x, int y){
    bool is_x_valid = (0 <= x && x < n);
    bool is_y_valid = (0 <= y && y < m);
    return is_x_valid && is_y_valid;
}

void dfs(int x, int y){

    // Marco como visitado a todos los nodos que pueda llegar
    visited[x][y] = true;

    // Puedo a la derecha?
    if(isInside(x, y+1) && mat[x][y+1] == '.' && !visited[x][y+1]) {
        dfs(x, y+1);
    }

    // Puedo a la izquierda?
    if(isInside(x, y-1) && mat[x][y-1] == '.' && !visited[x][y-1]) {
        dfs(x, y-1);
    }

    // Puedo arriba?
    if(isInside(x-1, y) && mat[x-1][y] == '.' && !visited[x-1][y]){
        dfs(x-1, y);
    }

    // Puedo abajo?
    if(isInside(x+1, y) && mat[x+1][y] == '.' && !visited[x+1][y]){
        dfs(x+1, y);
    }
}

int main () {


    cin>>n>>m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin>>mat[i][j];
        }
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(mat[i][j] == '#' || visited[i][j]) continue;

            ans++;
            // Es una nueva componente conexa
            dfs(i, j);
        }
    }

    cout << ans << endl;




	return 0;
}

