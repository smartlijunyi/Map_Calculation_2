#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define MaxSize 20
#define INFINITY 65535
typedef char VertexType;
typedef struct Graph {
	VertexType ver[MaxSize+1];
	int edg[MaxSize][MaxSize];
}Graph;
void CreateGraph( Graph *g ){
	int i = 0;
	int j = 0;
	int VertexNum;
	VertexType Ver;
 	printf("Please input your vertexs:\n");
	while( '\n' != (Ver=getchar()) )
		g->ver[i++] = Ver;
	g->ver[i] = '\0';
 	VertexNum = strlen(g->ver);
	printf("Please input the adject matrix:\n");
	for( i=0; i<VertexNum; i++ )
		for( j=0; j<VertexNum; j++ )
			scanf("%d", &g->edg[i][j]);
}
void PrintGraph( Graph g ){
	int i, j;
	int VertexNum = strlen(g.ver);
	printf("Vertex:\n");
	for( i=0; i<VertexNum; i++ )
		printf("%c ", g.ver[i]);
	printf("\n");
 	printf("Matrix:\n");
	for( i=0; i<VertexNum; i++ ) {
		for( j=0; j<VertexNum; j++ )
			printf("%d ", g.edg[i][j]);
		printf("\n");
	}
}
int CalVerNum( Graph g ){
	return strlen(g.ver);
}
void SetWeight( Graph *g ){
	for( int i=0; i<CalVerNum(*g); i++ )
		for( int j=0; j<CalVerNum(*g); j++ )
			if( 0 == g->edg[i][j] )
				g->edg[i][j] = INFINITY;
}
void Dijkstra( Graph g ){
	int VertexNum = CalVerNum( g );
	int i,j,k;
	int mini;
	int index = 0;
	int *used = (int *)malloc(sizeof(int)*VertexNum);
	int *distance = (int *)malloc(sizeof(int)*VertexNum);
	int *parent = (int *)malloc(sizeof(int)*VertexNum);
	int *last = (int *)malloc(sizeof(int)*VertexNum);
 	SetWeight( &g );					
 	for( int i=0; i<VertexNum; i++ ) {
		used[i] = 0;
		distance[i] = g.edg[0][i];   
		last[i] = 0;
	}
 	used[0] = 1;
	parent[index++] = 0;
 	for( i=0; i<VertexNum-1; i++ ) {
		j = 0;
		mini = INFINITY;
 		for( int k=0; k<VertexNum; k++ )
			if( (0 == used[k]) && (distance[k] < mini) ) {
				mini = distance[k];
				j = k;			
			}
		used[j] = 1;
 		for( k=0; k<VertexNum; k++ ) 
		if( (0 == used[k]) && (distance[k] > distance[j] + g.edg[j][k]) ){   
				distance[k] = distance[j] + g.edg[j][k];
		}
 		parent[index++] = j;
	}
 	printf("From %c to %c:The Best Way is:\n", g.ver[0], g.ver[VertexNum-1]);
	for( i=0; i<index; i++ )
		printf("%c ", g.ver[parent[i]]);
	printf("\n");
 	printf("The length is: %d\n", mini);
}
int main(void){
	Graph g;
	CreateGraph( &g );
	PrintGraph( g );
 	Dijkstra( g );
	return 0;
}

