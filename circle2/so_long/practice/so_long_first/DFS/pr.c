

#include <stdio.h>

int n, cnt = 0;
int arr[11][11];
int visit[200];

void DFS(int depth)
{
	visit[depth] = 1; cnt++;
	//printf("visit[%d] : %d\n", depth, visit[depth]);
	for (int i = 1; i <= n; i++)
	{
		if (arr[depth][i] == 1 && visit[i] == 0)
		{
			printf("DFS IN i : %d\n", i);
			DFS(i);

			//printf("DFS OUT i : %d\n", i);
		}
	}
}

int main()
{
	n = 7;
	arr[1][3] = 1;
	arr[3][1] = 1;
	arr[3][5] = 1;
	arr[5][3] = 1;
	arr[5][7] = 1;
	arr[7][5] = 1;
	arr[1][2] = 1;
	arr[2][1] = 1;
	arr[2][4] = 1;
	arr[4][2] = 1;
	arr[4][8] = 1;
	arr[8][4] = 1;
	printf("DFS IN i : %d\n", 1);
	DFS(1);
}





#include <stdio.h>
 
int graph[11][11];    // 인접행렬로 구현한 그래프 
int visited[11];        // 방문 여부 체크 
 
void DFS(int cur, int n){
    int i;
    visited[cur] = 1;    // 현재 노드 방문 체크 
    for(i=1; i<=n; i++){    // 모든 인접한 노드 체크 
        if(graph[cur][i] == 1 && visited[i] == 0){    // 인접하고 방문하지 않은 노드라면 
            printf("DFS IN : %d\n", i);
            DFS(i, n);
			printf("DFS OUT : %d\n", i);
        }
    }
}
 
int main()
{
    int start = 1;
    graph[1][3] = 1; graph[3][5] = 1; graph[5][7] = 1; 
    graph[3][1] = 1; graph[5][3] = 1; graph[7][5] = 1; 
     
    graph[1][2] = 1; graph[2][4] = 1; graph[4][8] = 1;
    graph[2][1] = 1; graph[4][2] = 1; graph[8][4] = 1;
    
    //printf("%d ",start);
    DFS(start,10); 
    
    return 0;
}