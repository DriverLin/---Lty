#include <iostream>
#include <time.h>
#define true 1
#define false 0 
#define MAXLENGTH 100
#define coefficient 0.9 	//参数 决定了AI优先关注玩家不赢还是自己赢
using namespace std;

int weight_1(Board B ,int i ,int j , int kind){ 
	char yes,no;
	int a,b,count,comprehensiveweight=0;
	int weight;
	if(kind==1){
		yes='*';
		no='@';
	}
	else{
		yes='@';
		no='*';
	}
	
	for(a=i-(B.number-1);a<=i;a++){//每次循环 开始位置从+1 
		b=a;//b开始 检验b到b+B.number之内
		weight=1;
		for(count=1;count<=B.number;count++){//
			
			if(B.board[b][j]==' '){
				weight*=10;
			}
			else if(B.board[b][j]==yes){
				weight*=100;
			}
			else if(B.board[b][j]==no){
				weight=0;
				break;//此时，已经不可能构成连成，weight=0且停止
			}
			else{
				weight=0;
				break;//同上
			}
			b++;
		}//从可能构成连成的边缘开始找，直到下标i；每次返回一个权值 最后返回权值之和，最大的将会影响总权值 
		comprehensiveweight+=weight;
	}
	return comprehensiveweight;
}

int weight_2(Board B ,int i ,int j , int kind){
	char yes,no;
	int a,b,count,comprehensiveweight=0;
	int weight;
	if(kind==1){
		yes='*';
		no='@';
	}
	else{
		yes='@';
		no='*';
	}
	
	for(a=j-(B.number-1);a<=i;a++){
		b=a;
		weight=1;
		for(count=1;count<=B.number;count++){
			if(B.board[i][b]==' '){
				weight*=10;
			}
			else if(B.board[i][b]==yes){
				weight*=100;
			}
			else if(B.board[i][b]==no){
				weight=0;
				break;
			}
			else{
				weight=0;
				break;
			}
			b++;
		}
		comprehensiveweight+=weight;
	}
	return comprehensiveweight;
}

int weight_3(Board B ,int i ,int j , int kind){ 
	char yes,no;
	int a,b,a_t,b_t,count,comprehensiveweight=0;
	int weight;
	if(kind==1){
		yes='*';
		no='@';
	}
	else{
		yes='@';
		no='*';
	}
	
	for(a=i-(B.number-1),b=j-(B.number-1);a<=i;a++,b++){
		b_t=b;
		a_t=a;
		weight=1;
		for(count=1;count<=B.number;count++){
			
			if(B.board[a_t][b_t]==' '){
				weight*=10;
			}
			else if(B.board[a_t][b_t]==yes){
				weight*=100;
			}
			else if(B.board[a_t][b_t]==no){
				weight=0;
				break;
			}
			else{
				weight=0;
				break;
			}
			b_t++;
			a_t++;
		}
		comprehensiveweight+=weight;
	}
	return comprehensiveweight;
}

int weight_4(Board B ,int i ,int j , int kind){ 
	char yes,no;
	int a,b,a_t,b_t,count,comprehensiveweight=0;
	int weight;
	if(kind==1){
		yes='*';
		no='@';
	}
	else{
		yes='@';
		no='*';
	}
	for(a=i-(B.number-1),b=j+(B.number-1);a<=i;a++,b--){
		b_t=b;
		a_t=a;
		weight=1;
		for(count=1;count<=B.number;count++){
			if(B.board[a_t][b_t]==' '){
				weight*=10;
			}
			else if(B.board[a_t][b_t]==yes){
				weight*=100;
			}
			else if(B.board[a_t][b_t]==no){
				weight=0;
				break;
			}
			else{
				weight=0;
				break;
			}
			b_t--;
			a_t++;
		}
		comprehensiveweight+=weight;
	}
	return comprehensiveweight;
}

int win_weight(Board B ,int i ,int j , int kind){//计算当前位置的权值 kind设定为1代表计算玩家 *；0计算AI @ 。
	char yes,no;
	int comprehensiveweight=0;
	if(kind==1){
		yes='*';
		no='@';
	}
	else{
		yes='@';
		no='*';
	}
	comprehensiveweight+=weight_1(B,i,j,kind);
	comprehensiveweight+=weight_2(B,i,j,kind);
	comprehensiveweight+=weight_3(B,i,j,kind);
	comprehensiveweight+=weight_4(B,i,j,kind);
	return comprehensiveweight;
}

void updateweight(Board &B){
	int i ,j ;
	for(i =1 ; i <= B.length ; i++){
		for(j =1 ; j <= B.length ; j++){
			if(B.board[i][j]!=' '){
				B.weight[i][j]=0;
			}
			else
				B.weight[i][j]=win_weight(B, i, j , 0)+coefficient*win_weight(B, i, j , 1);//位置的最终权值为 AI赢权值+参数*玩家赢权值
			//printf("%-5d",B.weight[i][j]);
		}
		//printf("\n\n");
	}
}

void AI(Board &B) {
	int i, j, maxweight=0, a=0, b=0;
	updateweight(B);//更新权值
	for(i =1 ; i <= B.length ; i++){
		for(j =1 ; j <= B.length ; j++){
			if(B.weight[i][j]>maxweight){
				maxweight=B.weight[i][j];
				a=i;
				b=j;
			}
			if( B.weight[i][j]==maxweight && rand()%2==1 ){
				maxweight=B.weight[i][j];
				a=i;
				b=j;
			}
		}
	}
	B.board[a][b]='@';//AI会选择下在权值最大的位置 有相同则是最前 后来添加了随机性
}


void AI_2(Board &B) {
	int i, j, maxweight=0, a=0, b=0;
	updateweight(B);//更新权值
	for(i =1 ; i <= B.length ; i++){
		for(j =1 ; j <= B.length ; j++){
			if(B.weight[i][j]>maxweight){
				maxweight=B.weight[i][j];
				a=i;
				b=j;
			}
		}
	}
	B.board[a][b]='*';//AI会选择下在权值最大的位置
}