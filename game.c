#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

/* Append: ���뿵 */
#define NULL_OBJECT -1

#define FOOD 3 // ���� 
#define CHARACTOR 2 //ĳ���� 
#define WALL 1 // �� 
#define NONE 0 // Null Game-Object

struct Food // ������ ��ġ�� �������� �����ϴ� ��ǥ x,y ���� 
{
   int x, y;
};

void GotoXY(int x, int y, char* s);
void Title(void); //���� ����ȭ�� 
void Reset(void); //������ �ʱ�ȭ 
void DrawMap(void); // ������ �׵θ��� �׸� 
void Move(void); //��Ӹ��� �̵� 
void Pause(void); //�Ͻ����� 
void GameOver(void); //���� ������ Ȯ�� 
void GenerateFoodOfRandomLoc(void); // ���� ���� 
void Status(void); // �����ڿ� statusǥ��

/*
Append: ���뿵 
*/
void GameLoop(); //���� ���� �Լ� 
void VisibleCursor();
void SnakeMoveDirectionHandle(); //�� �Ӹ� �̵����� 
void InitializeMap(); //�� �ʱ�ȭ 

/*
	Game Variables
*/
char * snake = "��"; // ��
int key = 0;
int posX = 25;
int posY = 12;
int direction = NULL_OBJECT; //���� ���� �̵�����
struct Food food = {
	.x = NULL_OBJECT,
	.y = NULL_OBJECT	
};

int map[MAP_HEIGHT][MAP_WIDTH];
 
int main(void)
{
	VisibleCursor(); //Ŀ���� �����ݴϴ�.
	GameLoop();
	
	return 0;
}

////////////////////////////////////// Utility Functions /////////////////////////////////////////////////////////////
/*
x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����
*/
void GotoXY(int x, int y, char* s)
{   
   COORD pos = { 2 * x,y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
   printf("%s", s);
}

/*
	Ŀ���� ���۴ϴ�. 
*/
void VisibleCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GameLoop()
{
	direction = RIGHT; //������ �������� �̵��ϰ� �⺻���� 
	InitializeMap();
	map[MAP_HEIGHT/2][MAP_WIDTH/2] = CHARACTOR;
	posY = MAP_HEIGHT/2;
	posX = MAP_WIDTH/2;

	while(1)
	{
		GenerateFoodOfRandomLoc();
		Move();
		DrawMap();
		
		Sleep(50);
	}
}

void SnakeMoveDirectionHandle()
{
	int i;
	//Ű���尡 �������� 
	for(i = 0; i < 5; i++)
	{
		if(_kbhit())
		{
			int keyCode = _getch();
			
			if(keyCode == UP || keyCode == DOWN || keyCode == LEFT || keyCode == RIGHT)
			{
				direction = keyCode;
			}
		}	
	} 
}

void Move()
{
	SnakeMoveDirectionHandle();
	int tmpX = posX;
	int tmpY = posY;
	
	switch(direction)
	{
		case UP:
			--posY;
			break;
		case DOWN:
			++posY;
			break;
		case LEFT:
			--posX;
			break;
		case RIGHT:
			++posX;
			break;
	}
	
	/*
		���� ��ġ�� ����� ���Ӱ� ����ݴϴ�.
	*/
	map[tmpY][tmpX] = NONE; 
	map[posY][posX] = CHARACTOR;
}

void InitializeMap()
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (i != 0 && j != 0 && j != MAP_WIDTH - 1 && i != MAP_HEIGHT - 1)
				map[i][j] = NONE;
			else
				map[i][j] = WALL;
		}
	}
}

void DrawMap(void) // �� ���� 32, ���� 21
{
	system("cls");
    int x, y;
	    
    for(y = 0; y < MAP_HEIGHT; y++)
    {
    	for(x = 0; x < MAP_WIDTH; x++)
    	{
    		switch(map[y][x])
    		{
    			case WALL:
    				GotoXY(x, y, "��");
    				break;
    			case FOOD:
    				GotoXY(x, y, "��");
    				break;
    			case CHARACTOR:
    				GotoXY(x, y, "��"); 
    				break;
			}
		}
	}
}

/*
���Ļ���
*/
void GenerateFoodOfRandomLoc(void)
{
 	if(food.x == NULL_OBJECT && food.y == NULL_OBJECT)
 	{
 		food.x = (rand() % MAP_WIDTH-1) + 1;
		food.y = (rand() % MAP_HEIGHT-1) + 1;
		
		map[food.y][food.x] = FOOD;
	}
 	
   /*
   	  �Լ��� �Ѱ��� �ϸ� �ϴ°� �����ϴ�.
	  �׷��ִ� �κ��� DrawMap�� �ϵ��� �ϰ� ���ּ���. 
   */
//   if (rd.x >5 && rd.y>5)
//   {
//      GotoXY(rd.x, rd.y, "��");
//   }   
}
