#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char board[6][7] = {};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int ref_check = 0;
int is_board_full =0;
int chX=1;
int chY=1;
int redindex =0;
int yellowindex = 0;
int colindex =0;
int rowNo =0;
int bak =0;


void print_board()
{
	int i,j;

	printf("\n");
	for(i=0;i<6;i++)
	{
		for(j=0;j<7;j++)
		{
			printf(" %c |", board[i][j]);
		}
		printf("\n");
	}
	printf("\n -------------------------- \n");
	for(i=1;i<8;i++){
		printf(" %d |",i);
	}
	printf("\n -------------------------- \n");
	return;
}

int check_board()
{
	int i,j;

	for(i=0; i<6;i++)
	{
		for(j=0;j<7;j++)\
		{
			if(board[i][j]=='-')
			{
				return(9);
			}
		}
	}
	printf(".....no place for token sir!!!!!!\n");
	return(7);
}

int check_horizontal(){
	int i,j,countR,countY;
	for(i=0;i<6;i++){
		countY=0;
		countR=0;
		for(j=0;j<7;j++){
			if(board[i][j]=='R')
			{
				countY=0;
				countR++;
				if(countR==4){
					printf("\n R wins horizontal...congratulations!!!! \n");
					return(2);
				}
			}else if(board[i][j]=='Y')
			{
				countR=0;
				countY++;
				if(countY==4){
					printf("\n Y wins horizontal...congratulations!!!! \n");
					return(2);
				}
			} else
			{
				countR=0;
				countY=0;
			}
		}
	}
	return(0);
}

int check_diagonal()
{
	int i,j,countR,countY,b;
	b=check_horizontal();
	if(b==2)
		return(2);
	else{
		for(i = 0;i<6;i++){
			countY=0;
			countR=0;
			for(j = 0;j<4;j++){
				if((board[i][j]=='y' &&
					board[i+2][j+2]=='Y' &&
					board[i+3][j+3]=='Y' &&
					board[i+1][j+1]=='Y')
					||
					(board[i-3][j+3]=='Y' &&
						board[i-1][j+1]=='Y' &&
						board[i-2][j+2]=='Y' &&
						board[i][j]=='Y')
					||
					(board[i][j]=='y' &&
						board[i-2][j-2]=='Y' &&
						board[i-3][j-3]=='Y' &&
						board[i-1][j-1]=='Y')
					||
					(board[i+3][j-3]=='Y' &&
						board[i+1][j-1]=='Y' &&
						board[i+2][j-2]=='Y' &&
						board[i][j]=='Y')){
					printf("\n Y wins diagonally...congratulations!!!! \n");
				return (2);
			}else if((board[i][j]=='R' &&
				board[i+2][j+2]=='R' &&
				board[i+3][j+3]=='R' &&
				board[i+1][j+1]=='R')
			||
			(board[i-3][j+3]=='R' &&
				board[i-1][j+1]=='R' &&
				board[i-2][j+2]=='R' &&
				board[i][j]=='R')
			||
			(board[i][j]=='R' &&
				board[i-2][j-2]=='R' &&
				board[i-3][j-3]=='R' &&
				board[i-1][j-1]=='R')
			||
			(board[i+3][j-3]=='R' &&
				board[i+1][j-1]=='R' &&
				board[i+2][j-2]=='R' &&
				board[i][j]=='R')){
				printf("\n R wins diagonally...congratulations!!!! \n");
				return (2);
			}
		}
	}
}
return(0);
}

int check_row(int col)
{
	int i=5;
	int b=0;
	while(i > -1)
	{
		if(board[i][col]=='-')
			return(i);

		i--;
	}
	b = check_board();
	return(b);
}

void *refree(void *arg)
{
	for(;;)
	{
		printf("");
		pthread_mutex_lock(&mutex);  
		while(ref_check == 0){
			pthread_cond_wait(&cond, &mutex);
		}
		printf("\n.....refree replies....\n");
		if(check_board() == 9)
		{
			chY = check_diagonal();
			if(chY==2){
				printf("\n....Winner Found.... \n");
				is_board_full=1;
				ref_check=0;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mutex);
				printf(" \n ....Game Over... \n");
				return(NULL);
			}
			printf("\n.....no win found...go players :)\n");
		}else if(check_board() == 7)
		{
			ref_check=0;
			is_board_full=1;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			printf("....The Game is Over as tie...sorry :) \n");
			return(NULL);
		}
		ref_check=0;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	printf ("ref exited\n");
}

int random_col()
{
	int b;
	time_t t;
	srand(time(&t));
	b = rand()%7;
	if(b<7)
		return(b);

	return(1);
}

void *playerr(void *arg)
{
	for(;;)
	{
		pthread_mutex_lock(&mutex);
		while(ref_check == 1)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		ref_check=1;
		if(is_board_full==1)
		{
			ref_check=0;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			return(NULL);
		}    
		do{
			sleep(1);
			colindex=random_col();
			rowNo=check_row(colindex);
			if(rowNo < 7)
			{
				board[rowNo][colindex]='R';
				bak =1;
			} else if(rowNo == 9){
				bak = 0;
     		}
		}while(bak==0);
		print_board();
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	printf ("Playerx exited\n");
}

void *playery(void *arg)
{
	for(;;)
	{
		pthread_mutex_lock(&mutex);
		while(ref_check == 1)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		ref_check = 1;
		if(is_board_full==1)
		{
			ref_check = 0;
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			return(NULL);
		}
		do{
			sleep(1);
		colindex=random_col();
		rowNo=check_row(colindex);
		if(rowNo < 7){
			board [rowNo][colindex]='Y';
			bak = 1;
		}else if(rowNo==9){
			bak = 0;
		}
		}while(bak == 0);
		print_board();
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	printf ("Playery exited\n");
}

int main(int argc, char *xargv)
{
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			board[i][j] = '-';
		}
	}

	pthread_t ref,pY,pR;

	pthread_create(&ref, NULL, refree, NULL);
	pthread_create(&pR, NULL, playerr, NULL);
	pthread_create(&pY, NULL, playery, NULL);

	pthread_join(ref, NULL);
	pthread_join(pR, NULL);
	pthread_join(pY, NULL);

	exit(0);
}
