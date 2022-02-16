#include<bits/stdc++.h>


using namespace std ;

int grid[100][100], col[100][100] ;
int n, m ;

void dfs(int i, int j)
{
    col[i][j] = 1 ;

    if(j-1 >=0 && grid[i][j-1] == 1 && col[i][j-1] == 0){
        dfs(i, j-1) ;
    }
    if(j+1 < m && grid[i][j+1] == 1 && col[i][j+1] == 0){
        dfs(i, j+1) ;
    }

    if(i-1>=0 && grid[i-1][j] == 1 && col[i-1][j] == 0){
        dfs(i-1, j) ;
    }
    if(i+1 < n && grid[i+1][j] == 1 && col[i+1][j] == 0){
        dfs(i+1, j) ;
    }

}
int main(){
    int  i, j, sti, stj, endi, endj ;
    scanf("%d %d", &n, &m) ;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            scanf("%d", &grid[i][j]) ;
            col[i][j] = 0 ;
        }
    }

    scanf("%d %d %d %d", &sti, &stj, &endi, &endj) ;
    dfs(sti, stj) ;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ;  j < m  ; j++){
            if(col[endi][endj] == 1){
                 printf("possible\n") ;
                 return 0;
            }

        }

    }

     printf("not possible\n") ;
}
