/* 
* 求从指定源点出发到各个顶点的最短路径。
* 
* 假设：图中结点名均为单个互不相同的字母，权值均>0。
* 
* 输入：
*   第一行：结点数量n，弧数量e，源点
*   后续e行：<结点，结点，权值>
* 
* 输出：
*   按结点的升序输出到达各个结点的最短路径长度
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef struct VNode {
	char  data;   // 顶点信息
	int weight;   // 这条边的权
	struct VNode *next;  // 指向下一个顶点的指针
} VNode;

typedef struct ALGraph {
	VNode  vertices[30];//顶点列表
	int      vexnum, arcnum; //顶点数，边数
} ALGraph;

int dist[30],prior[30],vis[30];

void Creategraph(ALGraph &G, int a, char b, int weight) {
	VNode *q;
	q = (VNode *)malloc(sizeof(VNode));
	q->data = b;
	q->weight = weight;
	q->next = G.vertices[a].next;
	G.vertices[a].next = q;
}

void Dijkstra(ALGraph G, int i) {
	vis[i] = 1;
	VNode *p;
	int j,min=INF,minarc,flag=0;
//	printf("next->%c\n",i+'a');
//	printf("--p=%d--\n",p=G.vertices[i].next);
	for (p=G.vertices[i].next; p!=NULL; p=p->next) {
		j = p->data-'a';
		if (vis[j] == 0) {
			prior[j] = prior[i] + p->weight;
//		printf("--%c:%d--\n",'a'+j,prior[j]);
			if (prior[j] < dist[j]) dist[j] = prior[j];
			else prior[j] = dist[j];
			if (p->weight < min) {
				min = p->weight;
				flag = 1;
			}
			minarc = p->data - 'a';
		}
	}
	if (flag) {
		Dijkstra(G,minarc);
	} else return;
}

void print(ALGraph G) {
	VNode *p;
	for (int i=0; i<G.vexnum; i++) {
		p = G.vertices[i].next;
		printf("%c",G.vertices[i].data);
		while(p != NULL) {
			printf(" <%c,%d>",p->data,p->weight);
			p = p->next;
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
//	freopen("num.txt","r",stdin);
	ALGraph G;
	VNode *p;
	char head,h,t;
	int a,b,weight,start;
	scanf("%d,%d,%c",&G.vexnum,&G.arcnum,&head);
	for (int i=0; i<G.vexnum; i++) {
		G.vertices[i].data = 'a' + i;
		G.vertices[i].weight = 0;
		G.vertices[i].next = NULL;
	}
	getchar();
	for (int i=0; i<G.arcnum; i++) {
		scanf("<%c,%c,%d>",&h,&t,&weight);
		getchar();
//		printf("h=%c\n",h);
		Creategraph(G,h-'a',t,weight);
//		Creategraph(G,t-'a',h,weight);
	}
//	print(G);
	memset(dist,INF,sizeof(dist));
	start = head - 'a';
//	putchar(head);
	dist[start] = 0;
	for (p=G.vertices[start].next; p!=NULL; p=p->next){
		int next = p->data - 'a';
		dist[next] = p->weight;
	}
	for (p=G.vertices[start].next; p!=NULL; p=p->next) {
		int next = p->data - 'a';
		prior[next] = p->weight;
//		printf("next->%c\n",p->data);
		memset(vis,0,sizeof(vis));
		vis[start] = 1;
		Dijkstra(G,p->data-'a');
	}
	for(int i=0; i<G.vexnum; i++) {
//		if (dist[i] == INF) printf("%c:0\n",i+'a');
		printf("%c:%d\n",i+'a',dist[i]);
	}
	return 0;
}