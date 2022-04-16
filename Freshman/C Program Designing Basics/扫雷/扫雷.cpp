#include <stdio.h>
int main(){
	int row,line,i,j,k;
	
	for(i=1;1;i++){
		scanf("%d%d",&row,&line);
		if(row==0&&line==0) return 0;
		
		char map[row+2][line+2],hint[row][line],s;
		
		for(j=0;j<row+2;j++){		//初始化地图数组 
			for(k=0;k<line+2;k++){
				map[j][k]='.';
			}
		}
		
		for(j=1;j<row+1;j++){		//获取地图
			for(k=1;k<line+1;k++){
				scanf("%c",map[j][k]);
			}
		}
		
		for(j=1;j<row+1;j++){		//数字图形界面
			for(k=1;k<line+1;k++){
				if(map[k][j]=='*'){
					hint[j-1][k-1]='*';
					continue;
				}
				s='0';
				if(map[j-1][k-1]=='*') s++;
				if(map[j-1][k]=='*') s++;
				if(map[j-1][k+1]=='*') s++;
				if(map[j][k-1]=='*') s++;
				if(map[j][k+1]=='*') s++;
				if(map[j+1][k-1]=='*') s++;
				if(map[j+1][k]=='*') s++;
				if(map[j+1][k+1]=='*') s++;
				hint[j-1][k-1]=s;
			}
		}
		
		printf("Field #%d:\n",i);
		for(j=0;j<row;j++){
			for(k=0;k<line;k++){
				printf("%c",hint[j][k]);
			}
			printf("\n");
		}
	}
}
