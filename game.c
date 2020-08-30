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

/* Append: 남대영 */
#define NULL_OBJECT -1

#define FOOD 3 // 음식 
#define CHARACTOR 2 //캐릭터 
#define WALL 1 // 벽 
#define NONE 0 // Null Game-Object

struct Food // 음식의 위치를 랜덤으로 생성하는 좌표 x,y 생성 
{
   int x, y;
};

void GotoXY(int x, int y, char* s);
void Title(void); //게임 시작화면 
void Reset(void); //게임을 초기화 
void DrawMap(void); // 게임판 테두리를 그림 
void Move(void); //뱀머리를 이동 
void Pause(void); //일시정지 
void GameOver(void); //게임 오버를 확인 
void GenerateFoodOfRandomLoc(void); // 음식 생성 
void Status(void); // 개발자용 status표시

/*
Append: 남대영 
*/
void GameLoop(); //게임 루프 함수 
void VisibleCursor();
void SnakeMoveDirectionHandle(); //뱀 머리 이동관련 
void InitializeMap(); //맵 초기화 

/*
	Game Variables
*/
char * snake = "＠"; // 뱀
int key = 0;
int posX = 25;
int posY = 12;
int direction = NULL_OBJECT; //현재 뱀의 이동방향
struct Food food = {
	.x = NULL_OBJECT,
	.y = NULL_OBJECT	
};

int map[MAP_HEIGHT][MAP_WIDTH];
 
int main(void)
{
	VisibleCursor(); //커서를 없애줍니다.
	GameLoop();
	
	return 0;
}

////////////////////////////////////// Utility Functions /////////////////////////////////////////////////////////////
/*
x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입
*/
void GotoXY(int x, int y, char* s)
{   
   COORD pos = { 2 * x,y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
   printf("%s", s);
}

/*
	커서를 없앱니다. 
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
	direction = RIGHT; //오른쪽 방향으로 이동하게 기본설정 
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
	//키보드가 눌렸을때 
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
		이전 위치를 지우고 새롭게 깔아줍니다.
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

void DrawMap(void) // 맵 가로 32, 세로 21
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
    				GotoXY(x, y, "■");
    				break;
    			case FOOD:
    				GotoXY(x, y, "♪");
    				break;
    			case CHARACTOR:
    				GotoXY(x, y, "＠"); 
    				break;
			}
		}
	}
}

/*
음식생성
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
   	  함수는 한가지 일만 하는게 좋습니다.
	  그려주는 부분은 DrawMap이 하도록 하게 해주세요. 
   */
//   if (rd.x >5 && rd.y>5)
//   {
//      GotoXY(rd.x, rd.y, "♬");
//   }   
}
