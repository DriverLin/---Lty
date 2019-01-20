#include <iostream>
#include<windows.h>
#define true 1
#define false 0 
#define MAXLENGTH 100
typedef struct BoardStruct
{
	char board[MAXLENGTH][MAXLENGTH];
	int length;
	int number;
	int weight[MAXLENGTH][MAXLENGTH];
}Board;

int Condition_1(Board B, int i, int j) {//  \ 判断
	int a, b;
	if (B.board[i][j] == ' ')
		return -1;
	for (a = i, b = j; a>i - B.number; a--, b--) {
		if (B.board[a][b] != B.board[i][j])
			return -1;
	}
	if (B.board[i][j] == '@')
		return 0;
	else
		return 1;
}

int Condition_2(Board B, int i, int j) {//   | 判断
	int a;
	if (B.board[i][j] == ' ')
		return -1;
	for (a = i; a>i - B.number; a--) {
		if (B.board[a][j] != B.board[i][j])
			return -1;
	}
	if (B.board[i][j] == '@')
		return 0;
	else
		return 1;
}
int Condition_3(Board B, int i, int j) {//   / 判断
	int a, b;
	if (B.board[i][j] == ' ')
		return -1;
	for (a = i, b = j; a>i - B.number; a--, b++) {
		if (B.board[a][b] != B.board[i][j])
			return -1;
	}
	if (B.board[i][j] == '@')
		return 0;
	else
		return 1;
}
int Condition_4(Board B, int i, int j) {//  - 判断
	int a;
	if (B.board[i][j] == ' ')
		return -1;
	for (a = j; a<j + B.number; a++) {
		if (B.board[i][a] != B.board[i][j])
			return -1;
	}
	if (B.board[i][j] == '@')
		return 0;
	else
		return 1;
}





int Condition(Board B, int i, int j) {//传入单元位置，判断是否存在连成的棋，返回1玩家赢，0机器赢，-1不存在
	int iFlag = -1;
	iFlag = Condition_1(B, i, j);
	if (iFlag != -1)
		return iFlag;
 
	iFlag = Condition_2(B, i, j);
	if (iFlag != -1)
		return iFlag;

	iFlag = Condition_3(B, i, j);
	if (iFlag != -1)
		return iFlag;

	iFlag = Condition_4(B, i, j);
	if (iFlag != -1)
		return iFlag;

	return -1;
}



int judge(Board B) {//判断棋局是否结束
	int i, j, iflag;
	for (i = 1; i <= B.length; i++) {
		for (j = 1; j <= B.length; j++) {
			iflag = Condition(B, i, j);
			if (iflag == 1) {
				printf("玩家胜利!\n");
				return 1;
			}
			else if (iflag == 0) {
				printf("电脑胜利!\n");
				return 0;
			}
			else;
		}
	}
	for (i = 1; i <= B.length; i++) {
		for (j = 1; j <= B.length; j++) {
			if (B.board[i][j] == ' ')
				return -1;
		}
	}
	printf("平局\n");
	return MAXLENGTH;
}

void PrintfBoard(Board B) {
	int i, j;
	system("cls");
	for (i = 0; i <= B.length; i++)
		printf("%-3d", i);
	printf("\n");
	for (i = 1; i <= B.length; i++) {
		printf("%-3d", i);
		for (j = 1; j <= B.length; j++)
			printf("%-3c", B.board[i][j]);
		printf("\n");
	}
}

int player(Board &B, int i, int j) {
	if (B.board[i][j] != ' ') {
		printf("所选位置不可用");
		return false;//所选位置不可用 返回0
	}
	B.board[i][j] = '*';
	return true;
}

