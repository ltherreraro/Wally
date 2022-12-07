#include <stdio.h>

#include <windows.h>
#include "main.h"
#include <time.h>
#include <stdbool.h>

typedef struct
{
	int posx;
	int posy;
	char state; // * indicar� obstaculo, ser� vacio
} MapPoint;

direction SimCurrentDirectionMovement = FRONT; // comienza mirando al frente
// just for simulation

int myDelay1 = 10;
int myDelay2 = 10;
int startpointx = 10;
int startpointy = 5;
int anchoWally = 10;
int altoWally = 10;
void display_map();
void fillVoidLine(int line);
void fillFullLine(int width);
void robotPrint(int posxInit, int posyInit, direction dir);
void usReading(USdistances *Measurement);
void moveAheadSimulation();
void moveBackwardsSimulation();
void DebugPrint(char message[64], int valI, float valf);
void DebugPrint2(char message[64], int valI, float valf);
void DebugPrint3(char message[64], int valI, float valf);
void DebugPrint4(char message[64], int valI, float valf);
void printGrid(GridPoint myGrid[100][100]);
void stopSimualtion();
void turnBackSimulation();
void turnLeftSimulation();
void turnRightSimulation();
void delay(int milli_seconds);
void robotCleanH(int posx, int posy);
float check_US_RIGHT();
float check_US_LEFT();
float check_US_UP();
float check_US_DOWN();

int rows = 80;
int columns = 80;
MapPoint FullMap[80][80];
COORD c = {0, 0};
// int robotPosX = 20, robotPosy = 70;
int robotPosX = 30, robotPosy = 60;
void setxy(int x, int y)
{
	c.X = x;
	c.Y = y; // Set X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void mapping()
{
	display_map();
	robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
	ShowConsoleCursor(false);
}

void display_map()
{

	int i, j;
	// Equivalencias array y pos    ->>FILA=Y, COLUMNA=X
	//[0][0] = (y,x) 10,5

	// render fila 0,columna j (top)
	setxy(startpointx, startpointy);
	for (j = 0; j < columns; j++)
	{
		FullMap[0][j].posx = startpointx;
		FullMap[0][j].posy = startpointy + j;
		FullMap[0][j].state = '*';
		printf("%c", FullMap[0][j].state);
	}

	// render fila 400,columna j (bottom)
	setxy(startpointx, startpointy + rows);
	for (j = 0; j <= columns; j++)
	{
		FullMap[rows - 1][j].posx = columns + startpointx;
		FullMap[rows - 1][j].posy = startpointy + j;
		FullMap[rows - 1][j].state = '*';
		printf("%c", FullMap[rows - 1][j].state);
	}

	// fill the rest, fila i, columna j

	for (i = 1; i < rows - 1; i++)
	{
		fillVoidLine(i);
	}

	int WidthObstacle = 5;
	int posxInit = 30;
	int posyInit = 30;

	// Render trash
	setxy(startpointx + posxInit, startpointy + posyInit);
	for (j = posyInit; j <= posyInit + WidthObstacle; j++)
	{
		FullMap[posyInit][j].posx = columns + startpointx;
		FullMap[posyInit][j].posy = startpointy + j;
		FullMap[posyInit][j].state = '*';
		printf("%c", FullMap[posyInit][j].state);
	}
	setxy(startpointx + posxInit, startpointy + posyInit + 1);
	for (j = posyInit; j <= posyInit + WidthObstacle; j++)
	{
		FullMap[posyInit][j].posx = columns + startpointx;
		FullMap[posyInit][j].posy = startpointy + j;
		FullMap[posyInit][j].state = '*';
		printf("%c", FullMap[posyInit][j].state);
	}
	setxy(startpointx + posxInit, startpointy + posyInit + 2);
	for (j = posyInit; j <= posyInit + WidthObstacle; j++)
	{
		FullMap[posyInit + 1][j].posx = columns + startpointx;
		FullMap[posyInit + 1][j].posy = startpointy + j;
		FullMap[posyInit + 1][j].state = '*';
		printf("%c", FullMap[posyInit + 1][j].state);
	}
	setxy(startpointx + posxInit, startpointy + posyInit + 3);
	for (j = posyInit; j <= posyInit + WidthObstacle; j++)
	{
		FullMap[posyInit + 2][j].posx = columns + startpointx;
		FullMap[posyInit + 2][j].posy = startpointy + j;
		FullMap[posyInit + 2][j].state = '*';
		printf("%c", FullMap[posyInit + 2][j].state);
	}
	setxy(startpointx + posxInit, startpointy + posyInit + 4);
	for (j = posyInit; j <= posyInit + WidthObstacle; j++)
	{
		FullMap[posyInit + 3][j].posx = columns + startpointx;
		FullMap[posyInit + 3][j].posy = startpointy + j;
		FullMap[posyInit + 3][j].state = '*';
		printf("%c", FullMap[posyInit + 3][j].state);
	}
	printf("\n");
}
void fillVoidLine(int line)
{
	int j;
	// llenando los bordes
	setxy(startpointx, startpointy + line);
	FullMap[line][0].posx = startpointx;
	FullMap[line][0].posy = line;
	FullMap[line][0].state = '*';
	printf("%c", FullMap[line][0].state);

	setxy(columns + startpointx, startpointy + line);
	FullMap[line][columns - 1].posx = columns + startpointx;
	FullMap[line][columns - 1].posy = line;
	FullMap[line][columns - 1].state = '*';
	printf("%c", FullMap[line][columns - 1].state);

	for (j = 1; j < columns - 1; j++)
	{
		setxy(startpointx + j, startpointy + line);
		FullMap[line][j].posx = startpointx + j;
		FullMap[line][j].posy = line;
		FullMap[line][j].state = ' ';
		printf("%c", FullMap[line][j].state);
	}
}
void fillFullLine(int width)
{
	int j;
	// llenando los bordes

	for (j = 30; j < 50 - 1; j++)
	{
		setxy(startpointx + j, startpointy + 30);
		FullMap[4][j].posx = startpointx + j;
		FullMap[4][j].posy = 30;
		FullMap[4][j].state = '*';
		printf("%c", FullMap[4][j].state);
	}
}

void robotPrint(int posxInit, int posyInit, direction dir)
{
	if (dir == RIGHT)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 2);
		printf("|   Yo    %c|\n", 26);
		setxy(posxInit, posyInit + 3);
		printf("|   Soy   %c|\n", 26);
		setxy(posxInit, posyInit + 4);
		printf("|   Wally %c|\n", 26);
		setxy(posxInit, posyInit + 5);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 6);
		printf("|  Virtual%c|\n", 26);
		setxy(posxInit, posyInit + 7);
		printf("|    xD   %c|\n", 26);
		setxy(posxInit, posyInit + 8);
		printf("|         %c|\n", 26);
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == LEFT)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 2);
		printf("|%c  Yo     |\n", 27);
		setxy(posxInit, posyInit + 3);
		printf("|%c  Soy    |\n", 27);
		setxy(posxInit, posyInit + 4);
		printf("|%c  Wally  |\n", 27);
		setxy(posxInit, posyInit + 5);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 6);
		printf("|%c Virtual |\n", 27);
		setxy(posxInit, posyInit + 7);
		printf("|%c   xD    |\n", 27);
		setxy(posxInit, posyInit + 8);
		printf("|%c         |\n", 27);
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == FRONT)
	{
		setxy(posxInit, posyInit);
		printf("-%c%c%c%c%c%c%c%c%c-\n", 24, 24, 24, 24, 24, 24, 24, 24, 24);
		setxy(posxInit, posyInit + 1);
		printf("|          |\n");
		setxy(posxInit, posyInit + 2);
		printf("|   Yo     |\n");
		setxy(posxInit, posyInit + 3);
		printf("|   Soy    |\n");
		setxy(posxInit, posyInit + 4);
		printf("|   Wally  |\n");
		setxy(posxInit, posyInit + 5);
		printf("|          |\n");
		setxy(posxInit, posyInit + 6);
		printf("|  Virtual |\n");
		setxy(posxInit, posyInit + 7);
		printf("|    xD    |\n");
		setxy(posxInit, posyInit + 8);
		printf("|          |\n");
		setxy(posxInit, posyInit + 9);
		printf("------------\n");
	}
	else if (dir == BACK)
	{
		setxy(posxInit, posyInit);
		printf("------------\n");
		setxy(posxInit, posyInit + 1);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 2);
		printf("|%c  Yo     |\n");
		setxy(posxInit, posyInit + 3);
		printf("|%c  Soy    |\n");
		setxy(posxInit, posyInit + 4);
		printf("|%c  Wally  |\n");
		setxy(posxInit, posyInit + 5);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 6);
		printf("|%c Virtual |\n");
		setxy(posxInit, posyInit + 7);
		printf("|%c   xD    |\n");
		setxy(posxInit, posyInit + 8);
		printf("|%c         |\n");
		setxy(posxInit, posyInit + 9);
		printf("-%c%c%c%c%c%c%c%c%c-\n", 25, 25, 25, 25, 25, 25, 25, 25, 25);
	}
}
void robotCleanH(int posxc, int posyc)
{
	setxy(posxc, posyc);
	printf(" ");
	setxy(posxc, posyc + 1);
	printf(" ");
	setxy(posxc, posyc + 2);
	printf(" ");
	setxy(posxc, posyc + 3);
	printf(" ");
	setxy(posxc, posyc + 4);
	printf(" ");
	setxy(posxc, posyc + 5);
	printf(" ");
	setxy(posxc, posyc + 6);
	printf(" ");
	setxy(posxc, posyc + 7);
	printf(" ");
	setxy(posxc, posyc + 8);
	printf(" ");
	setxy(posxc, posyc + 9);
	printf(" ");
}
void DebugPrint(char message[64], int valI, float valf)
{
	setxy(0, 0);
	printf("\n");
	printf(message);
	printf(" --: %d, : %f \n", valI, valf);
}
void DebugPrint2(char message[64], int valI, float valf)
{
	setxy(0, 1);
	printf("\n");
	printf(message);
	printf(" %d, %f \n", valI, valf);
}
void DebugPrint3(char message[64], int valI, float valf)
{
	setxy(0, 2);
	printf("\n");
	printf(message);
	printf(": %d, : %f \n", valI, valf);
}
void DebugPrint4(char message[64], int valI, float valf)
{
	setxy(0, 3);
	printf("\n");
	printf(message);
	printf(": %d : %f \n", valI, valf);
}

void moveAheadSimulation()
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		if (FullMap[robotPosy - startpointy - 1][robotPosX - startpointx].state == ' ') // Restricting upside
		{
			robotPrint(robotPosX, robotPosy--, SimCurrentDirectionMovement);
			setxy(robotPosX, robotPosy + 10);
			printf("             ");
			delay(myDelay1);
		}
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		if (FullMap[robotPosy - startpointy + altoWally][robotPosX - startpointx].state == ' ')
		{
			robotPrint(robotPosX, robotPosy++, SimCurrentDirectionMovement);
			setxy(robotPosX, robotPosy - 1);
			printf("             ");
			delay(myDelay1);
		}
		else
		{
			DebugPrint4("obstaculo back", FullMap[robotPosy - startpointy + altoWally][robotPosX - startpointx].state, 0);
		}
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx - 1].state == ' ')
		{ // as long as the next pos isnt filled (' '), allow movement.
			robotPrint(robotPosX--, robotPosy, SimCurrentDirectionMovement);
			robotCleanH(robotPosX + 12, robotPosy);
			delay(myDelay1);
		}
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx + 2 + anchoWally].state == ' ') // Restrict bat on right side wall
		{
			robotPrint(robotPosX++, robotPosy, SimCurrentDirectionMovement);
			robotCleanH(robotPosX - 1, robotPosy);
			delay(myDelay1);
		}
	}
}

void moveBackwardsSimulation()
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		if (FullMap[robotPosy - startpointy - 1][robotPosX - startpointx].state == ' ') // Restricting upside
		{
			robotPrint(robotPosX, robotPosy++, SimCurrentDirectionMovement);
			setxy(robotPosX, robotPosy + 10);
			printf("             ");
			delay(myDelay1);
		}
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		if (FullMap[robotPosy - startpointy + altoWally][robotPosX - startpointx].state == ' ')
		{
			robotPrint(robotPosX, robotPosy--, SimCurrentDirectionMovement);
			setxy(robotPosX, robotPosy - 1);
			printf("             ");
			delay(myDelay1);
		}
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx - 1].state == ' ')
		{ // as long as the next pos isnt filled (' '), allow movement.
			robotPrint(robotPosX++, robotPosy, SimCurrentDirectionMovement);
			robotCleanH(robotPosX + 12, robotPosy);
			delay(myDelay1);
		}
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		if (FullMap[robotPosy - startpointy][robotPosX - startpointx + 2 + anchoWally].state == ' ') // Restrict bat on right side wall
		{
			robotPrint(robotPosX--, robotPosy, SimCurrentDirectionMovement);
			robotCleanH(robotPosX - 1, robotPosy);
			delay(myDelay1);
		}
	}
}

stopSimualtion()
{
	robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
}

void turnBackSimulation()
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		SimCurrentDirectionMovement = BACK;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		SimCurrentDirectionMovement = FRONT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		SimCurrentDirectionMovement = LEFT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		SimCurrentDirectionMovement = RIGHT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
}
void turnLeftSimulation()
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		SimCurrentDirectionMovement = LEFT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		SimCurrentDirectionMovement = RIGHT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		SimCurrentDirectionMovement = BACK;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		SimCurrentDirectionMovement = FRONT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
}
void turnRightSimulation()
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		DebugPrint("Giroderecha", 0, 0);
		SimCurrentDirectionMovement = RIGHT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		SimCurrentDirectionMovement = LEFT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		SimCurrentDirectionMovement = FRONT;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		SimCurrentDirectionMovement = BACK;
		robotPrint(robotPosX, robotPosy, SimCurrentDirectionMovement);
		delay(myDelay2);
	}
}

void usReading(USdistances *Measurement)
{
	if (SimCurrentDirectionMovement == FRONT)
	{
		Measurement->USfront = check_US_UP();
		Measurement->USback = check_US_DOWN();
		Measurement->USleft = check_US_LEFT();
		Measurement->USright = check_US_RIGHT();
	}
	else if (SimCurrentDirectionMovement == BACK)
	{
		Measurement->USfront = check_US_DOWN();
		Measurement->USback = check_US_UP();
		Measurement->USleft = check_US_RIGHT();
		Measurement->USright = check_US_LEFT();
	}
	else if (SimCurrentDirectionMovement == LEFT)
	{
		Measurement->USfront = check_US_LEFT();
		Measurement->USback = check_US_RIGHT();
		Measurement->USleft = check_US_DOWN();
		Measurement->USright = check_US_UP();
	}
	else if (SimCurrentDirectionMovement == RIGHT)
	{
		Measurement->USfront = check_US_RIGHT();
		Measurement->USback = check_US_LEFT();
		Measurement->USleft = check_US_UP();
		Measurement->USright = check_US_DOWN();
	}
}

float check_US_RIGHT()
{
	int distance = 0;
	while (1)
	{ // FullMap[altoWally / 2][robotPosX - startpointx + anchoWally + distance]

		if (FullMap[robotPosy - startpointy][robotPosX - startpointx + anchoWally + distance + 2].state == ' ')
		{
			distance++; // aumentar distancia en cada punto sin obstaculos
		}
		else
		{
			break;
		}
	}

	return distance;
}
float check_US_LEFT()
{
	int distance = 0;
	while (1)
	{ // FullMap[altoWally / 2][robotPosX - startpointx + anchoWally + distance]

		if (FullMap[robotPosy - startpointy][robotPosX - startpointx - distance - 1].state == ' ')
		{
			distance++; // aumentar distancia en cada punto sin obstaculos
		}
		else
		{
			break;
		}
	}

	return distance;
}
float check_US_UP()
{
	int distance = 0;
	while (1)
	{ // FullMap[altoWally / 2][robotPosX - startpointx + anchoWally + distance]

		if (FullMap[robotPosy - startpointy - distance - 1][robotPosX - startpointx].state == ' ')
		{
			distance++; // aumentar distancia en cada punto sin obstaculos
		}
		else
		{
			break;
		}
	}

	return distance;
}
float check_US_DOWN()
{
	int distance = 0;
	while (1)
	{ // FullMap[altoWally / 2][robotPosX - startpointx + anchoWally + distance]
		if (FullMap[robotPosy - startpointy + altoWally + distance][robotPosX - startpointx].state == ' ')
		{
			distance++; // aumentar distancia en cada punto sin obstaculos
		}
		else
		{
			DebugPrint4("obstaculo back", FullMap[robotPosy - startpointy + altoWally][robotPosX - startpointx].state, 0);
			// DebugPrint4("DownMeasure", distance, 0);
			break;
		}
	}

	return distance;
}

void delay(int milli_seconds)
{

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void printGrid(GridPoint myGrid[100][100])
{
	// DebugPrint2("entre aqui0->", myToken, myGrid[0][0].obstacle);
	int a, b;
	setxy(0, columns + 8);
	printf("\n");
	printf("Mapeo en la memoria del robot");
	printf("\n");

	for (a = 0; a < 100; a++)
	{
		// DebugPrint3("entre aqui", 0, myGrid[0][0].obstacle);

		for (b = 0; b < 100; b++)
		{

			if (myGrid[b][a].obstacle)
			{ // graficar la fila primero
				setxy(b, columns + 11 + a);
				printf("*");
			}
			else
			{
				setxy(b, columns + 11 + a);
				printf(" ");
			}
		}
		printf("\n");
	}
}
/* void printGrid(GridPoint* myGrid[100][100],direction myToken)
{

	int a,b;
	setxy(0, columns + 10);
	printf("\n");
	printf("Mapeo en la memoria del robot");
	printf("\n");
	if(myToken==LEFT){
		for (a=0;a<100;a++){
			for(b=0;b<100;b++){
				if(myGrid[b][a]->obstacle)//graficar la fila primero
					printf("*");
				else
					printf(" ");
			}
			printf("\n");
		}
	}
}

*/
