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

void initialise_snake(){//making my starting snake
	snake.clear();
	for(int i=0;i<2;i++){//loop to initialse snake,
		snake.push_back(0);//x cordinate
		snake.push_back(i);//y cordinate
	}   // pushing starting x and y coordinates into snake vector
}

void hidecursor()//to hide the cursor in console window
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;		//can be made TRUE to show if want
   SetConsoleCursorInfo(consoleHandle, &info);
}
void setConsoleColour(unsigned short colour) //function to set colour
{    // this is a function to print space with color
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}
void setcursor(int x, int y)//functiom  to set the position of cursor in console(0 indexing)
{   // we need this function to set cursor and control where should be screen be colored
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
	if(time1>=20 && time1<50)	cout<<"HIGH";
	else if(time1>=50 && time1<80)	cout<<"MEDIUM";
	else if(time1>=80)	cout<<"LOW";
	cout<<"\n";
	//printing wall
	setConsoleColour(consolebackground::CYAN);
	for(int i=0;i<lenght+2;i++)
	cout<<" ";
	cout<<"\n";
	for(int i=0;i<width;i++){
		for(int j=0;j<lenght+2;j++){
			if(j==0  || j==lenght+1)	setConsoleColour(consolebackground::CYAN);
			else	 			setConsoleColour(consolebackground::BLACK);
			cout<<" ";
		}
		cout<<"\n";
	}
	setConsoleColour(consolebackground::CYAN);
	for(int i=0;i<lenght+2;i++)
	cout<<" ";
}

void print_highscore(){//printing high score(changes with time
	int i,j;
	setcursor(11,0);
	setConsoleColour(consoleforeground::WHITE);
	cout<<snake.size()/2-3<<"  ";//-3 because the initial size of snake is 3
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
	setConsoleColour(consolebackground::BLACK);
	cout<<" ";
	snake.erase(snake.begin());//deleting snake back, vector begin indicates back of snake
	snake.erase(snake.begin());
	
	setcursor(snake.back()+1,snake[snake.end()-snake.begin()-2]+2);//printing snake
	//head of snake
	setConsoleColour(consolebackground::WHITE);
	cout<<" ";
	
	setcursor(snake[snake.end()-snake.begin()-3]+1,snake[snake.end()-snake.begin()-4]+2); //body of snake
	setConsoleColour(consolebackground::RED);
	cout<<" ";
}

void eat_food(){//eating food and generating new food
	food_x=rand()%(width);
	food_y=rand()%(lenght);
	setcursor(food_y+1,food_x+2);
	setConsoleColour(consolebackground::GREEN);
	cout<<" ";
	snake.insert(snake.begin(),snake[1]);//incresing length of snake if food is eaten
	snake.insert(snake.begin(),snake[1]);
}

bool check_interbody_death(){//to check if snake died by touching its own body or not
	int x,y,i;
	bool j=0;
	x=snake[snake.end()-snake.begin()-2];//x cordinate of snake mouth
	y=snake.back();						 //y cordinate of snake mouth
	for(i=0;i<snake.size()-2;i=i+2){	 //checking with body array
		if(x==snake[i] && y==snake[i+1]){
			j=1;
			break;
		}
	}
	return j;
}

void pause_menu(){// to print pause menu	
		setcursor(1,(width-5)/2+2);
		setConsoleColour(consolebackground::WHITE);
		for(int i=0;i<lenght;i++) 						cout<<" ";
		setcursor(1,(width-5)/2+3);
		for(int i=0;i<(lenght-11)/2;i++) 				cout<<" ";
		cout<<"GAME PAUSED";
		for(int i=0;i<lenght-11-(lenght-11)/2;i++)		cout<<" ";
		setcursor(1,(width-5)/2+4);
		for(int i=0;i<lenght;i++) 						cout<<" ";
		setcursor(1,(width-5)/2+5);
		for(int i=0;i<(lenght-21)/2;i++) 				cout<<" ";
		cout<<"PRESS 'P' TO CONTINUE";
		for(int i=0;i<lenght-21-(lenght-21)/2;i++) 		cout<<" ";
		setcursor(1,(width-5)/2+6);
		for(int i=0;i<lenght;i++) 						cout<<" ";
}

void welcome_to(){//printing welcome screen
	system("cls");//clearing screen
	setConsoleColour(consoleforeground::BLUE);
	int a;
	bool t=1;
	cout<<"\n\n\n\n\n\n\n\n\n                                       WELCOME TO MY SNAKE GAME\n\n";
	/* cout<<"                         Press S to open settings, any other key to  continue\n";*/
	cout<<"                              During game, press 'p' to pause the game\n";
	cout<<"                               During game, press 'C' to end the game";
	a=getch();
}

int print_final_message(){//printing final message screen
	setConsoleColour(consoleforeground::BLACK);
	system("cls");
	setConsoleColour(consoleforeground::MAGENTA);
	int a=snake.size()/2-3,k;
	if(a>hsc)
	hsc=a;
	cout<<"\n\n\n\n\n               GAME OVER\n";
	cout<<"               YOUR SCORE: "<<snake.size()/2-3<<endl;
	cout<<"               HIGH SCORE EVER: "<<hsc;
	cout<<endl<<endl<<endl;
	cout<<"               PRESS ANY KEY TO RESTART\n";
	cout<<"               esc to EXIT\n\n\n\n\n\n";
	setConsoleColour(consoleforeground::DARKYELLOW);
	a=getch();
	return a;
}

void remove_pause(){// to remove th eprinted pausee menu
	setcursor(1,(width-5)/2+2);
	setConsoleColour(consolebackground::BLACK);
	for(int i=0;i<5;i++){
		setcursor(1,(width-1)/2+i);
		for(int j=0;j<lenght;j++)					cout<<" ";
	}
	setcursor(food_y+1,food_x+2); //printing food again, if food is below pause menu, then it would have become blank
	setConsoleColour(consolebackground::GREEN);
	cout<<" ";
}


int main(){
  cin.tie(NULL);//to gain mannual flush control
	cout.tie(NULL);//to gain mannual flush control
	srand(time(0));//to generate random numbers, diiferent every time
	hidecursor();
	welcome_to();  // welcome screen
	restart_game://goto statement, came from last
		food_eaten=1;
		system("cls");//to clean the screen 
		print_wall();
		initialise_snake();
		eat_food();
		int i1=80,i2=80;   //key press
		while(i1!=99){
			if(kbhit()){//if a key press is detected
				i1=getch();//take the buffer of keyboard
				if(i1==72 && (i2!=80 || reverse_snake))				i2=i1,move_snake(-1,'v');
				else if(i1==80 && (i2!=72 || reverse_snake))			i2=i1,move_snake(1,'v');
				else if(i1==75 && (i2!=77 || reverse_snake))			i2=i1,move_snake(-1,'h');
				else if(i1==77 && (i2!=75 || reverse_snake))			i2=i1,move_snake(1,'h');
				else if(i1==112){//112- p    // if "p" key is pressed
					pause_menu();  // run pause menu
					while(1){//to not remove pause menu untill p is pressed again
						i1=getch();
						if(i1==112)
						break;
					}
					remove_pause();       //to clear the screen
				}
				else 	goto congo;//if other than arrow key are pressed
			}
			else{	//if no key is pressed
				congo:
				if(i2==72 )		move_snake(-1,'v');
				else if(i2==80)	        move_snake(1,'v');
				else if(i2==75)		move_snake(-1,'h');
				else if(i2==77)		move_snake(1,'h');
			}
			if(check_interbody_death() && !reverse_snake && self_hit)	break;//body collision
			if(snake.back()>lenght-1 || snake.back()<0 || snake[snake.end()-snake.begin()-2]<0 || snake[snake.end()-snake.begin()-2]>width-1)     break;//wall collision
			if(food_y==snake.back() && food_x==snake[snake.end()-2-snake.begin()])	   eat_food();
			print_highscore();
			Sleep(time1);   //for defficulty
		}
		int result;//keypress at last screen
		print_final:
			result=print_final_message();   // print final screen
			if(result!=27)  //if any key is pressed other than esc
				goto restart_game;
}
