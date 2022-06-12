#include<iostream>
#include<vector>
#include<conio.h>
#include<time.h>
#include<synchapi.h>
#include<algorithm>
#include <windows.h>
using namespace std;
namespace consoleforeground //for text colour, colours made using 4 attributes
{
  enum {
    BLACK             = 0,
    DARKBLUE          = FOREGROUND_BLUE,
    DARKGREEN         = FOREGROUND_GREEN,
    DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
    DARKRED           = FOREGROUND_RED,
    DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
    DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
    DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    GRAY              = FOREGROUND_INTENSITY,
    BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
    GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
    CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
    RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
    MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
    YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
    WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
  };
}
namespace consolebackground//for background colour,  colours made using 4 attributes
{
  enum {
    BLACK             = 0,
    DARKBLUE          = BACKGROUND_BLUE,
    DARKGREEN         = BACKGROUND_GREEN,
    DARKCYAN          = BACKGROUND_GREEN | BACKGROUND_BLUE,
    DARKRED           = BACKGROUND_RED,
    DARKMAGENTA       = BACKGROUND_RED | BACKGROUND_BLUE,
    DARKYELLOW        = BACKGROUND_RED | BACKGROUND_GREEN,
    DARKGRAY          = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
    GRAY              = BACKGROUND_INTENSITY,
    BLUE              = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
    GREEN             = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
    CYAN              = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
    RED               = BACKGROUND_INTENSITY | BACKGROUND_RED,
    MAGENTA           = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
    YELLOW            = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
    WHITE             = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
  };
}




vector<int> snake;					//snake vector, to store position of snake in numbers
bool food_eaten=1,colour=1,kids=0,self_hit=1,reverse_snake=0;//for settings
int width=27,lenght=118,food_x=-1,food_y=-2,hsc,time1=20; //hsc- high score


void hidecursor()//to hide the cursor in console window
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;		//can be made TRUE to show if want
   SetConsoleCursorInfo(consoleHandle, &info);
}
void setConsoleColour(unsigned short colour)//function to set colour
{    // this is a function to print space with color
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}
void setcursor(int x, int y)//functiom  to set the position of cursor in console(0 indexing)
{   // we need this function to set cursor and control where snake is
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void print_wall(){	//printing elments that do not change with time on screen
  // printing score and difficulity
	setcursor(0,0);
	setConsoleColour(consoleforeground::DARKYELLOW);
	cout<<"YOUR SCORE:                     ";
	if(time1==20)		cout<<"HIGH";
	else if(time1==50)	cout<<"MEDIUM";
	else if(time1==80)	cout<<"LOW";
	else 				{
		cout<<"Custom: ";
		setConsoleColour(consoleforeground::WHITE);
		cout<<time1<<" ms";
	}
	cout<<"\n";
	//printing walls
	if(colour){
		setConsoleColour(consolebackground::CYAN);
		for(int i=0;i<lenght+2;i++)
		cout<<" ";
		cout<<"\n";
		for(int i=0;i<width;i++){
			for(int j=0;j<lenght+2;j++){
				if(j==0  || j==lenght+1)	setConsoleColour(consolebackground::CYAN);
				else	 					setConsoleColour(consolebackground::BLACK);
				cout<<" ";
			}
			cout<<"\n";
		}
		setConsoleColour(consolebackground::CYAN);
		for(int i=0;i<lenght+2;i++)
		cout<<" ";
	}
}

void move_snake(int move,char direction){//moviing my snake //v-vertical, 1=up,-1=down
	int i,j;
	if(direction=='v'){
		snake.push_back(snake[snake.end()-2-snake.begin()]+move);
		snake.push_back(snake[snake.end()-2-snake.begin()]);
	}
	else{
		snake.push_back(snake[snake.end()-2-snake.begin()]);
		snake.push_back(snake[snake.end()-2-snake.begin()]+move);
	}
	setcursor(snake[1]+1,snake[0]+2);       // printing space behind snake's body black
	if(colour) 				setConsoleColour(consolebackground::BLACK);
	cout<<" ";
	snake.erase(snake.begin());//deleting snake back, vector begin indicates back of snake
	snake.erase(snake.begin());
	
	setcursor(snake.back()+1,snake[snake.end()-snake.begin()-2]+2);//printing snake
	if(colour){//head of snake
		setConsoleColour(consolebackground::WHITE);
		cout<<" ";
	}
	
	setcursor(snake[snake.end()-snake.begin()-3]+1,snake[snake.end()-snake.begin()-4]+2); //body of snake
	if(colour){
		setConsoleColour(consolebackground::RED);
		cout<<" ";
	}
}

void eat_food(){//eating food and generating new food
	food_x=rand()%(width);
	food_y=rand()%(lenght);
	setcursor(food_y+1,food_x+2);
	if(colour){
		setConsoleColour(consolebackground::GREEN);
		cout<<" ";
	}
	snake.insert(snake.begin(),snake[1]);//incresing length of snake if food is eaten
	snake.insert(snake.begin(),snake[1]);
}

int main(){
  
}
