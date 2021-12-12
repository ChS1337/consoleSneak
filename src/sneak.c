/*
 ============================================================================
 Name        : sneak.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int getRandomNumber(int min, int max);
void moves();
void renderSize(int xMax,int yMax);

int main(){
	//int coords[2] = { 0 , 0};
	int getchval = 0;
	int size = 1;
	int coordsSneak[2][500];
	int lastcoordsSneak[2][500];
	int matrixSize[4] = { 0, 19, 29, 1};
	int apple[2] = { 0, 0};
	apple[0] = getRandomNumber(matrixSize[0], matrixSize[2]);
	apple[1] = getRandomNumber(matrixSize[3], matrixSize[1]);
	memset(coordsSneak, 0, sizeof(coordsSneak));
	coordsSneak [0][0] = 0;
	coordsSneak [1][0] = 10;
	//   72
	//75 80 77
	int move[4] = { 75, 72, 77, 80};
	char matrix[30][20];

	int facing = 2;
	int moveCount = 0;

	int isDead = 0;

	renderSize(31,20);

	while(1){
		if(_kbhit()){
			getchval = getch();
			if(move[0] == getchval){
				if(facing != 2){
//					if(facing != 0){
//						coordsSneak[0][0]--;
//						moveCount = 0;
//					}
					facing = 0;
				}
			}
			if(move[1] == getchval){
				if(facing != 3){
//					if(facing != 1){
//						coordsSneak[1][0]++;
//						moveCount = 0;
//					}
					facing = 1;
				}
			}
			if(move[2] == getchval){
				if(facing != 0){
//					if(facing != 2){
//						coordsSneak[0][0]++;
//						moveCount = 0;
//					}
					facing = 2;
				}
			}
			if(move[3] == getchval){
				if(facing != 1){
//					if(facing != 3){
//						coordsSneak[1][0]--;
//						moveCount = 0;
//					}
					facing = 3;
				}
			}
		}
		for(int i = 0;i < size;i++){
			lastcoordsSneak[0][i] = coordsSneak[0][i];
			lastcoordsSneak[1][i] = coordsSneak[1][i];
		}
		moves();
		memset(matrix, 0, sizeof(matrix));

		switch(facing){//autoMove
		case 0:
			if(moveCount >= 3){
				if(coordsSneak[0][0] > matrixSize[0])
					coordsSneak[0][0]--;
				else
					isDead = 1;
				moveCount = 0;
			}else moveCount++;
			break;
		case 1:
			if(moveCount >= 5){
				if(coordsSneak[1][0] < matrixSize[1])
				coordsSneak[1][0]++;
				else
									isDead = 1;
				moveCount = 0;
			}else moveCount++;
			break;
		case 2:
			if(moveCount >= 3){
				if(coordsSneak[0][0] < matrixSize[2])
					coordsSneak[0][0]++;
				else
					isDead = 1;
				moveCount = 0;
			}else moveCount++;
			break;
		case 3:
			if(moveCount >= 5){
				if(coordsSneak[1][0] > matrixSize[3])
					coordsSneak[1][0]--;
				else
					isDead = 1;
				moveCount = 0;
			}else moveCount++;
			break;
		default: break;
		}

		for(int i = 5;i < size;i++)
			if(coordsSneak[0][i] == coordsSneak[0][0] && coordsSneak[1][i] == coordsSneak[1][0]){
				isDead = 1;
			}

		if(size > 1)
			for(int i = 1; i < size;i++){ //render sneak other element
				coordsSneak[0][i] = lastcoordsSneak[0][i-1];
				coordsSneak[1][i] = lastcoordsSneak[1][i-1];
				matrix[coordsSneak[0][i]][coordsSneak[1][i]] = 'o';
			}

		//if(matrix[coordsSneak[0][0]][coordsSneak[1][0]] == 'o') isDead = 1;


		matrix[coordsSneak[0][0]][coordsSneak[1][0]] = '*'; //render sneak head


		if(coordsSneak[0][0] == apple[0]
									  && coordsSneak[1][0] == apple[1]){ //check Eat
			while(1){
				int x = getRandomNumber(matrixSize[0], matrixSize[2]);
				int y = getRandomNumber(matrixSize[3], matrixSize[1]);
				if(matrix[x][y] == 0){
					apple[0] = getRandomNumber(matrixSize[0], matrixSize[2]);
					apple[1] = getRandomNumber(matrixSize[3], matrixSize[1]);
					break;
				}
			}
			size+= 4;

		}
		matrix[apple[0]][apple[1]] = 'a';

		if(isDead){
			printf("Game over.");
			getch();
			exit(1);
		}

		for(int y = matrixSize[1];y > matrixSize[0];y--){ //Render matrix
			for(int x = 0;x <= matrixSize[2];x++){
				printf("%c",matrix[x][y]);
			}
			printf("\n");
		}



		//printf("sneakX=%i sneakY=%i Facing=%i Size=%i appleX=%i applyY=%i\n",coordsSneak[0][0], coordsSneak[1][0],facing,size,apple[0],apple[1]);
		//printf("sneakX=%i sneakY=%i sneakX2=%i sneakY2=%i\n",coordsSneak[0][0], coordsSneak[1][0],coordsSneak[0][1], coordsSneak[1][1]);

		//printf("%i\n",getch());
	}

	return 0;
}

int getRandomNumber(int min, int max)
{
  srand(time(NULL));

  int num = min + rand() % (max - min + 1);

  return num;
}

void moves(){
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { 0, 0 };
	SetConsoleCursorPosition(h,c);
}

void renderSize(int xMax,int yMax){
	int countH = 0;
	int countV = 0;
	for(int y = 0;y < yMax;y++){
		for(int x = 0;x < xMax;x++){
			int trigget = 1;
			if(y == yMax - 1){
				if(x == xMax-1)
					printf("%c",188);
				else
					printf("%c",205);
				countH++;
				if(countH == 4)
					countH = 0;
				trigget = 0;
			}
			else
			if(x == xMax-1){
				printf("%c",186);
				countV++;
				trigget = 0;
			}
			if(trigget == 1)
				printf(" ");
			if(countV == 4)
				countV = 0;

		}
		countH = 0;
		printf("\n");
	}
}


