#include <stdio.h>
int main(){
	int n;
	scanf("%d",&n);
	
	int a[n][n];
	int row=0,line=0,turn,pace=n-1,temp=1,r;

	for(turn=1;turn<=2*n-1;turn++){
		switch(turn%4){
			case 1:{
				for(r=pace;r>=0;r--){
					a[row][line]=temp;
					temp++;
					line++;
				}
				line--;
				row++;
				if(row>0) pace--;
				break;
			}
			case 2:{
				for(r=pace;r>=0;r--){
					a[row][line]=temp;
					temp++;
					row++;
				}
				row--;
				line--;
				break;
			}
			case 3:{
				for(r=pace;r>=0;r--){
					a[row][line]=temp;
					temp++;
					line--;
				}
				line++;
				row--;
				pace--;
				break;
			}
			case 0:{
				for(r=pace;r>=0;r--){
					a[row][line]=temp;
					temp++;
					row--;
				}
				row++;
				line++;
				break;
			}
		}
	}
	
	for(row=0;row<=n-1;row++){
		for(line=0;line<=n-1;line++)
			printf("%3d",a[row][line]);
		printf("\n");
	}
}
