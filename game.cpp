
//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
#include<cstdlib>
#include<ctime>
#include<fstream>
using namespace std;


 

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;

enum DIRECTIONS 
{   UP = 0, 
    DOWN = 1, 
    LEFT = 2,
    RIGHT = 3
};
enum OC_DIRECTIONS
{    oUP=0,
     oDOWN=1,
     oLEFT=2,
     oRIGHT=3		
};

enum TRACKS 
{    FIRST = 0,
     SECOND = 1,
     THIRD = 2
};

	int points2;
	
	float x = 470; 
	float y = 50;

	float oppx = 470; 
	float oppy = 150;

	float carx1 = 310; 
	float cary1 = 50;
	int myCarDirection = LEFT;
	int oppCarDirection = oRIGHT;
	int oppCarDirection1 = oRIGHT;
	
	int giftbox[64][3];
	int arrx[64]={510,570,630,690,750,750,750,750,750,750,750,750,750,750,690,630,570,510,310,250,190,130,70,70,70,70,70,70,70,70,70,70,130,190,250,310,520,580,640,640,640,640,640,640,580,520,300,240,180,180,180,180,180,180,240,300,500,550,550,500,325,275,275,325};
	int arry[64]={50,50,50,50,50,120,180,240,300,455,515,575,635,715,715,715,715,715,715,715,715,715,715,645,585,525,465,300,240,180,120,50,50,50,50,50,150,150,150,210,270,490,550,610,610,610,610,610,610,550,490,270,210,150,150,150,255,300,480,525,525,480,300,255};
	bool tf[64]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	int trackConstant = 100;
	int trackNumber = FIRST;

	int OP_trackNumber = FIRST;
	int OP_trackNumber1 = SECOND;	
	int points=0;// point variable
	int state=0;// changing menus and levels variable
	int life=3;// life variable
	int OCran;// opponent car random variable
	
	int col=-10; // for changing colours
	int change=0;
	int oppspeed=1;
	int selct=0;

	void NisarCar()
	{
		// Drawing  car
		if (myCarDirection == LEFT){
			carx1--;
			cout<<carx1<<" "<<cary1<<endl;
			if (carx1 < 50 + ( trackConstant * trackNumber) )
				myCarDirection = UP;
		}
	
	
		if (myCarDirection == UP){
			cary1++;
			cout<<carx1<<" "<<cary1<<endl;
			if (cary1 > 690 - ( trackConstant * trackNumber) )
				myCarDirection = RIGHT;
		}
	
		if (myCarDirection == RIGHT){
			carx1++;
			cout<<carx1<<" "<<cary1<<endl;
			if (carx1 > 730 - ( trackConstant * trackNumber) )
				myCarDirection = DOWN;
		}
	
		if (myCarDirection == DOWN){
			cary1--;
			cout<<carx1<<" "<<cary1<<endl;
			if (cary1 < 51 + ( trackConstant * trackNumber) )
				myCarDirection = LEFT;
		}
		
		float width1 = 15; 
		float height1 = 10;
		float* color1 = colors[BROWN]; 
		float radius1 =5.0;
		DrawRoundRect( carx1,cary1,width1,height1,color1,radius1 ); // bottom left tyre
		DrawRoundRect( carx1+width1*3,cary1,width1,height1,color1,radius1 ); // bottom right tyre
		DrawRoundRect( carx1+width1*3,cary1+height1*4,width1,height1,color1,radius1 ); // top right tyre
		DrawRoundRect( carx1,cary1+height1*4,width1,height1,color1,radius1 ); // top left tyre
		DrawRoundRect( carx1, cary1+height1*2, width1, height1, color1, radius1/2 ); // body left rect
		DrawRoundRect( carx1+width1, cary1+height1, width1*2, height1*3, color1, radius1/2 ); // body center rect
		DrawRoundRect( carx1+width1*3, cary1+height1*2, width1, height1, color1, radius1/2 ); // body right rect  
	
	}

	void AICAR(){
	// Drawing opponent car
	

 
		if (oppCarDirection == oRIGHT){
			x+=oppspeed;
			if (x > 730 - ( trackConstant * OP_trackNumber) )
			oppCarDirection = oUP;
		}


		if (oppCarDirection == oUP){
			y+=oppspeed;
			if (y > 690 - ( trackConstant * OP_trackNumber) )
				oppCarDirection = oLEFT;
		}

		if (oppCarDirection == oLEFT){
			x-=oppspeed;
			if (x < 50 + ( trackConstant * OP_trackNumber) )
				oppCarDirection = oDOWN;
		}

		if (oppCarDirection == oDOWN){
			y-=oppspeed;
			if (y < 51 + ( trackConstant * OP_trackNumber) )
				oppCarDirection = oRIGHT;
		}

	
		float width = 15; 
		float height = 10;
		float* color = colors[BLUE_VIOLET]; 
		float radius = 5.0;
		DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
		DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
		DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
		DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
		DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
		DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
		DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect

	}
	
	void AICAR1(){
	// Drawing opponent car
	

 
		if (oppCarDirection1 == oRIGHT){
			oppx+=oppspeed;
			if (oppx > 730 - ( trackConstant * OP_trackNumber1) )
			oppCarDirection1 = oUP;
		}


		if (oppCarDirection1 == oUP){
			oppy+=oppspeed;
			if (oppy > 690 - ( trackConstant * OP_trackNumber1) )
				oppCarDirection1 = oLEFT;
		}

		if (oppCarDirection1 == oLEFT){
			oppx-=oppspeed;
			if (oppx < 50 + ( trackConstant * OP_trackNumber1) )
				oppCarDirection1 = oDOWN;
		}

		if (oppCarDirection1 == oDOWN){
			oppy-=oppspeed;
			if (oppy < 51 + ( trackConstant * OP_trackNumber1) )
				oppCarDirection1 = oRIGHT;
		}

	
		float width = 15; 
		float height = 10;
		float* color = colors[BLUE_VIOLET]; 
		float radius = 5.0;
		DrawRoundRect(oppx,oppy,width,height,color,radius); // bottom left tyre
		DrawRoundRect(oppx+width*3,oppy,width,height,color,radius); // bottom right tyre
		DrawRoundRect(oppx+width*3,oppy+height*4,width,height,color,radius); // top right tyre
		DrawRoundRect(oppx,oppy+height*4,width,height,color,radius); // top left tyre
		DrawRoundRect(oppx, oppy+height*2, width, height, color, radius/2); // body left rect
		DrawRoundRect(oppx+width, oppy+height, width*2, height*3, color, radius/2); // body center rect
		DrawRoundRect(oppx+width*3, oppy+height*2, width, height, color, radius/2); // body right rect

	}

	void GiftBox()
	{
		for(int i=0; i<64; i++ ){   //printing GIFTBOXES
		
			if(tf[i]==1)
				DrawSquare( arrx[i] , arry[i] ,20,colors[GREEN]); 
		}

	
		//GIFT BOX PICKING
	
		//arena1 line1 pick
		for(int i=0; i<64 ; i++){
			
			if( ( carx1>=arrx[i]-40 and carx1<=arrx[i]+40 ) and  
			    ( cary1>=arry[i]-40 and cary1<=arry[i]+40 ) ){

				if ( tf[i]==1 ){
					points+=2;		
					tf[i]=0;	
				}	
			}	
		}		
	}

	void GameArena()
	{
		//block arena	
		int gap_turn3 = 0;
		int sx3 = 340;
		int sy3 = 310;
		int swidth3 = 160/2 - gap_turn3/2; // half width
		int sheight3 = 5;
		float *scolor3 = colors[BROWN];
		DrawRectangle(sx3, sy3, swidth3, sheight3, scolor3); // bottom left
		DrawRectangle(sx3 + swidth3 + gap_turn3, sy3, swidth3, sheight3, scolor3); // bottom right
		DrawRectangle(sx3+swidth3*2+gap_turn3, sy3+sheight3, sheight3*2, swidth3, scolor3); // right down
		DrawRectangle(sx3+swidth3*2+gap_turn3, sy3+sheight3+swidth3+gap_turn3, sheight3*2, swidth3, scolor3); // right up
		DrawRectangle(sx3 + swidth3 + gap_turn3, sy3+160, swidth3, sheight3, scolor3); // top left
		DrawRectangle(sx3, sy3+160, swidth3, sheight3, scolor3); // top right
		DrawRectangle(sx3-sheight3*2, sy3+sheight3+swidth3+gap_turn3, sheight3*2, swidth3, scolor3); // left up
		DrawRectangle(sx3-sheight3*2, sy3+sheight3, sheight3*2, swidth3, scolor3); // left down
		
		//Third arena	
		int gap_turn2 = 100;
		int sx2 = 240;
		int sy2 = 210;
		int swidth2 = 360/2 - gap_turn2/2; // half width
		int sheight2 = 5;
		float *scolor2 = colors[BROWN];
		DrawRectangle(sx2, sy2, swidth2, sheight2, scolor2); // bottom left
		DrawRectangle(sx2 + swidth2 + gap_turn2, sy2, swidth2, sheight2, scolor2); // bottom right
		DrawRectangle(sx2+swidth2*2+gap_turn2, sy2+sheight2, sheight2*2, swidth2, scolor2); // right down
		DrawRectangle(sx2+swidth2*2+gap_turn2, sy2+sheight2+swidth2+gap_turn2, sheight2*2, swidth2, scolor2); // right up
		DrawRectangle(sx2 + swidth2 + gap_turn2, sy2+360, swidth2, sheight2, scolor2); // top left
		DrawRectangle(sx2, sy2+360, swidth2, sheight2, scolor2); // top right
		DrawRectangle(sx2-sheight2*2, sy2+sheight2+swidth2+gap_turn2, sheight2*2, swidth2, scolor2); // left up
		DrawRectangle(sx2-sheight2*2, sy2+sheight2, sheight2*2, swidth2, scolor2); // left down
	
		//second arena
		int gap_turn1 = 100;
		int sx1 = 140;
		int sy1 = 110;
		int swidth1 = 560/2 - gap_turn1/2; // half width
		int sheight1 = 5;
		float *scolor1 = colors[BROWN];
		DrawRectangle(sx1, sy1, swidth1, sheight1, scolor1); // bottom left
		DrawRectangle(sx1 + swidth1 + gap_turn1, sy1, swidth1, sheight1, scolor1); // bottom right
		DrawRectangle(sx1+swidth1*2+gap_turn1, sy1+sheight1, sheight1*2, swidth1, scolor1); // right down
		DrawRectangle(sx1+swidth1*2+gap_turn1, sy1+sheight1+swidth1+gap_turn1, sheight1*2, swidth1, scolor1); // right up
		DrawRectangle(sx1 + swidth1 + gap_turn1, sy1+560, swidth1, sheight1, scolor1); // top left
		DrawRectangle(sx1, sy1+560, swidth1, sheight1, scolor1); // top right
		DrawRectangle(sx1-sheight1*2, sy1+sheight1+swidth1+gap_turn1, sheight1*2, swidth1, scolor1); // left up
		DrawRectangle(sx1-sheight1*2, sy1+sheight1, sheight1*2, swidth1, scolor1); // left down
		
		// Drawing Arena
		int gap_turn = 100;
		int sx = 40;
		int sy = 10;
		int swidth = 760/2 - gap_turn/2; // half width
		int sheight = 10;
		float *scolor = colors[BROWN];
		DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
		DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
		DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
		DrawRectangle(sx + swidth + gap_turn, sy+760, swidth, sheight, scolor); // top left
		DrawRectangle(sx, sy+760, swidth, sheight, scolor); // top right
		DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
		DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
		
		
	}

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	// calling some functions from util.cpp file to help students
	
    		

	
	if(state==1)
	{
		oppspeed=1;
	
		GameArena();  // arena function
		GiftBox();// giftbox function
		AICAR();//opponent car function
		NisarCar();//Users car
		

		//Square at 250,250 position
		//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
		//Display Score
		DrawString( 50, 800, "Score=", colors[MISTY_ROSE]);
		string points1=to_string(points);
		DrawString( 130, 800, points1, colors[MISTY_ROSE]);
		//DrawString3( 70, 800, points, colors[GOLD]);
		DrawString( 380,800, "LEVEL 1", colors[GOLD]);
		string life1=to_string(life);
		DrawString( 650, 800,"life=", colors[SILVER]);
		DrawString( 700, 800,life1, colors[SILVER]);
		//Triangle at 300, 450 position
		//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		//Circle at 50, 670 position
		//DrawCircle(50,670,10,colors[RED]);
		//Line from 550,50 to 550,480 with width 10
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	

		
	
		
	
		if ( ( carx1>=x-15 and carx1<=x+15  ) and (cary1>=y-10 and cary1<=y+10 ) ) // car collision theory
		{		
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;
				OP_trackNumber=FIRST;
				
				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				trackNumber=FIRST;
				points2=points;
	


				life--;
				points=0;
		}

		ofstream fout;
		fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
		{
			fout << points2<< endl;
		}																																			
		fout.close();


		if(life==0){
	
			system("canberra-gtk-play -f lose.wav");
			state=7;
		}


		srand(time(NULL));  //opponent car directions
  				
				if ( x == 415 and oppCarDirection == LEFT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y+=100;
						else
							y+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						y-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
			
				if ( x == 415 and oppCarDirection == RIGHT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y-=100;
						else
							y-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							y+=100;
						else 						
							y+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
		if ( points > 384 )
			state=4;	
		else if ( points> 256 )
			state=3;
		else if ( points> 128)
			state=2;
		
	
		else if ( points==128 )
		{
			for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
			x = 470;
		        y = 50;
			oppCarDirection = oRIGHT;
			OP_trackNumber=FIRST;				
			carx1 = 310; 
			cary1 = 50;
			myCarDirection = LEFT;
			trackNumber=FIRST;
			state=2;
		}

		

	
	}

	if(state==2)
	{

		oppspeed=1;

		GameArena();  // arena function
		GiftBox();// giftbox function
		AICAR();//opponent car function
		NisarCar();//Users car

					

		//Square at 250,250 position
		//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
		//Display Score
		DrawString( 50, 800, "Score=", colors[MISTY_ROSE]);
		string points1=to_string(points);
		DrawString( 130, 800, points1, colors[MISTY_ROSE]);
		//DrawString3( 70, 800, points, colors[GOLD]);
		DrawString( 380,800, "LEVEL 2", colors[GOLD]);
		string life1=to_string(life);
		DrawString( 650, 800,"life=", colors[SILVER]);
		DrawString( 700, 800,life1, colors[SILVER]);
		//Triangle at 300, 450 position
		//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		//Circle at 50, 670 position
		//DrawCircle(50,670,10,colors[RED]);
		//Line from 550,50 to 550,480 with width 10
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	

		
	
		
	
		if ( ( carx1>=x-15 and carx1<=x+15  ) and (cary1>=y-10 and cary1<=y+10 ) ) // car collision theory
		{		
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;
				OP_trackNumber=FIRST;
				
				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				trackNumber=FIRST;
				points2=points;
	


				life--;
				points=128;
		}

		ofstream fout;
		fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
		{
			fout << points2<< endl;
		}																																			
		fout.close();


		if(life==0){
	
			system("canberra-gtk-play -f lose.wav");
			state=7;
		}


		srand(time(NULL));  // random turning
				
  				
				if ( x == 415 and oppCarDirection == LEFT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y+=100;
						else
							y+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						y-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
			
				if ( x == 415 and oppCarDirection == RIGHT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y-=100;
						else
							y-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							y+=100;
						else 						
							y+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
			
				if ( y == 370 and oppCarDirection == UP ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x+=100;
						else
							x+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						x-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
				if ( y == 370 and oppCarDirection == DOWN ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x-=100;
						else
							x-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							x+=100;
						else 						
							x+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
	

		if ( points==256 )
		{
			for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
			x = 470;
		        y = 50;
			oppCarDirection = oRIGHT;
			OP_trackNumber=FIRST;				
			carx1 = 310; 
			cary1 = 50;
			myCarDirection = LEFT;
			trackNumber=FIRST;
			state=3;
		}

	
	}
	
	if(state==3)
	{

			
		oppspeed=2;

		GameArena();  // arena function
		GiftBox();// giftbox function
		AICAR();//opponent car function
		NisarCar();//Users car

					

		//Square at 250,250 position
		//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
		//Display Score
		DrawString( 50, 800, "Score=", colors[MISTY_ROSE]);
		string points1=to_string(points);
		DrawString( 130, 800, points1, colors[MISTY_ROSE]);
		//DrawString3( 70, 800, points, colors[GOLD]);
		DrawString( 380,800, "LEVEL 3", colors[GOLD]);
		string life1=to_string(life);
		DrawString( 650, 800,"life=", colors[SILVER]);
		DrawString( 700, 800,life1, colors[SILVER]);
		//Triangle at 300, 450 position
		//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		//Circle at 50, 670 position
		//DrawCircle(50,670,10,colors[RED]);
		//Line from 550,50 to 550,480 with width 10
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	

		
	
		
	
		if ( ( carx1>=x-15 and carx1<=x+15  ) and (cary1>=y-10 and cary1<=y+10 ) ) // car collision theory
		{		
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;
				OP_trackNumber=FIRST;
				
				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				trackNumber=FIRST;
				points2=points;
	


				life--;
				points=256;
		}

		ofstream fout;
		fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
		{
			fout << points2<< endl;
		}																																			
		fout.close();


		if(life==0){
	
			system("canberra-gtk-play -f lose.wav");
			state=7;
		}


		srand(time(NULL));  // random turning
				
  				
				if ( x == 416 and oppCarDirection == LEFT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y+=100;
						else
							y+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						y-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
			
				if ( x == 416	 and oppCarDirection == RIGHT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y-=100;
						else
							y-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							y+=100;
						else 						
							y+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
			
				if ( y == 370 and oppCarDirection == UP ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x+=100;
						else
							x+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						x-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
				if ( y == 370 and oppCarDirection == DOWN ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x-=100;
						else
							x-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							x+=100;
						else 						
							x+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
	

		if ( points==384 )
		{
			for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
			x = 470;
		        y = 50;
			oppCarDirection = oRIGHT;
			OP_trackNumber=FIRST;				
			carx1 = 310; 
			cary1 = 50;
			myCarDirection = LEFT;
			trackNumber=FIRST;
			state=4;
		}

	
	}

	if(state==4)
	{

			
		oppspeed=1;

		GameArena();  // arena function
		GiftBox();// giftbox function
		AICAR();//opponent car function
		AICAR1(); //opponent car 2 function
		NisarCar();//Users car

					

		//Square at 250,250 position
		//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
		//Display Score
		DrawString( 50, 800, "Score=", colors[MISTY_ROSE]);
		string points1=to_string(points);
		DrawString( 130, 800, points1, colors[MISTY_ROSE]);
		//DrawString3( 70, 800, points, colors[GOLD]);
		DrawString( 380,800, "LEVEL 3", colors[GOLD]);
		string life1=to_string(life);
		DrawString( 650, 800,"life=", colors[SILVER]);
		DrawString( 700, 800,life1, colors[SILVER]);
		//Triangle at 300, 450 position
		//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
		//Circle at 50, 670 position
		//DrawCircle(50,670,10,colors[RED]);
		//Line from 550,50 to 550,480 with width 10
		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
		//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	

		
	
		
	
		if ( ( carx1>=x-15 and carx1<=x+15  ) and (cary1>=y-10 and cary1<=y+10 ) ) // car collision theory
		{		
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;
				OP_trackNumber=FIRST;
				oppx = 470;
			        oppy = 150;
				oppCarDirection1 = oRIGHT;
				OP_trackNumber=SECOND;
				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				trackNumber=FIRST;
				points2=points;
	


				life--;
				points=384;
		}
		if ( ( carx1>=oppx-15 and carx1<=oppx+15  ) and (cary1>=oppy-10 and cary1<=oppy+10 ) ) // car collision theory
		{		
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;
				OP_trackNumber=FIRST;
				oppx = 470;
			        oppy = 150;
				oppCarDirection1 = oRIGHT;
				OP_trackNumber1=SECOND;
				
				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				trackNumber=FIRST;
				points2=points;
	


				life--;
				points=384;
		}

		ofstream fout;
		fout.open ("high score.txt"); //this function takes the name of the file that you are writing to
		{
			fout << points2<< endl;
		}																																			
		fout.close();


		if(life==0){
	
			system("canberra-gtk-play -f lose.wav");
			state=7;
		}


		srand(time(NULL));  // random turning
				
  				
				if ( x == 416 and oppCarDirection == LEFT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y+=100;
						else
							y+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						y-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
			
				if ( x == 416	 and oppCarDirection == RIGHT ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							y-=100;
						else
							y-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							y+=100;
						else 						
							y+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
			
				if ( y == 370 and oppCarDirection == UP ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x+=100;
						else
							x+=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber)
						x-=(100*(OCran-OP_trackNumber));
					OP_trackNumber=OCran;					
				}
				
				if ( y == 370 and oppCarDirection == DOWN ){
					OCran= trackNumber ;
					if (OCran < OP_trackNumber){
						if (OCran + OP_trackNumber ==3)
							x-=100;
						else
							x-=(100*((OCran+OP_trackNumber)));
					}

					else if (OCran > OP_trackNumber){
						if (OCran + OP_trackNumber == 3 ) 
							x+=100;
						else 						
							x+=(100*(OCran-OP_trackNumber));

					}
					OP_trackNumber=OCran;				
				}
	

		if ( points==512 )
		{
			state=10;
		}

	
	}

	else if (state==0)
	{
		 
        	DrawString( 318, 573, "D", colors[WHITE]);
	  	DrawString( 320, 576, "D", colors[col+30]);
	        
		DrawString( 338, 568, "O", colors[WHITE]);
		DrawString( 340, 571, "O", colors[col+30]); 

        	DrawString( 358, 573, "D", colors[WHITE]);
		DrawString( 360, 576, "D", colors[col+30]); 

        	DrawString( 378, 568, "G", colors[WHITE]);
		DrawString( 380, 571, "G", colors[col+30]);  

        	DrawString( 398, 573, "E", colors[WHITE]); 
		DrawString( 400, 576, "E", colors[col+30]); 

        	DrawString( 428, 568, "E", colors[WHITE]);    
		DrawString( 430, 571, "E", colors[col+30]);

        	DrawString( 448, 573, "M", colors[WHITE]);                                             	 
	        DrawString( 450, 576, "M", colors[col+30]);
		
		if (change==0)
		{
			col++;
			if (col==5)
				change=1;
		}
		else if (change==1)
		{
			col--;
			if (col==-5)
				change=0;
		}
	 	DrawString( 328, 513, "Start a new game", colors[WHITE]); 
			 			 		 			 	      	    			 
	 	DrawString( 328, 473, "See High-Scores", colors[WHITE]); 
        
         	DrawString( 328, 433, "Help", colors[WHITE]); 	
	 	
         	DrawString( 328, 313, "Press ESC key to exit", colors[col]);	


		                                 	 
	 

	}
	else if( state==5 )
	{
		DrawString( 328, 513, "Press 1 key to Start a new game", colors[GOLD]); 
			 			 		 			 	      	    			 
	 	DrawString( 328, 473, "Press 2 key to see High-Scores", colors[GOLD]); 
        
         	DrawString( 328, 433, "Press 3 to see Instructions", colors[GOLD]); 	
	 	
         	DrawString( 328, 393, "Press ESC key to exit", colors[GOLD]);

		DrawString( 328, 353, "Press R key to resume", colors[GOLD]);
	}
	else if ( state==6 )
	{
	     DrawString( 340, 810, "HELP MENU", colors[GOLD]);
	     DrawString( 342, 812, "HELP MENU", colors[col+20]);
		if (change==0)
		{
			col++;
			if (col==5)
				change=1;
		}
		else if (change==1)
		{
			col--;
			if (col==-5)
				change=0;
		}	
		
		DrawString( 10, 770, "INSTRUCTIONS: ", colors[FIREBRICK]);

			DrawString( 200, 740, "Objective of the game is to collect all the giftboxes while ", colors[WHITE]);
			DrawString( 200, 715, "dodging the opponent car. Once you collect all giftboxes  ", colors[WHITE]);
			DrawString( 200, 690, "you will proceed to the next level until you win the game. ", colors[WHITE]);
		
		DrawString( 10, 620, "CONTROLS: ", colors[FIREBRICK]);
			DrawString( 200, 590, "Use arrow keys to turn the car around the corners.", colors[WHITE]);
			DrawString( 200, 565, "1.UP arrow key for going up.", colors[WHITE]);
			DrawString( 200, 540, "2.DOWN arrow key for going down.", colors[WHITE]);
			DrawString( 200, 515, "3.LEFT arrow key for going left.", colors[WHITE]);
			DrawString( 200, 490, "2.RIGHT arrow key for going right.", colors[WHITE]);

			DrawString( 200, 440, "ESC key for exiting to main menu.", colors[WHITE]);
			DrawString( 200, 415, "P key to pause the game.", colors[WHITE]);
			DrawString( 200, 390, "R key to resume the game.", colors[WHITE]);

	}

	else if( state==7 )
	{
		DrawString( 340, 480, "GAME OVER", colors[FIREBRICK]);
		DrawString( 344, 484, "GAME OVER", colors[col+20]);
		
		if (change==0)
		{
			col++;
			if (col==5)
				change=1;
		}
		else if (change==1)
		{
			col--;
			if (col==-5)
				change=0;
		}
	}
	else if ( state==8 )
	{
		DrawString( 340, 480, "SCORE BOARD", colors[FIREBRICK]);
		string score="";
		ifstream fin ("high score.txt"); //name of the file it is supposed to read
		if (fin.is_open())
		{
			while ( getline (fin, score) ) 
			{
			  	cout << score << '\n';
		  		DrawString( 370, 450, score , colors[FIREBRICK]);
		 
		  
			}
		}
		fin.close();
	}
	else if ( state==10)
	{
		DrawString( 340, 480, "YOU WON!!!", colors[GOLD]);
	     DrawString( 342, 484, "YOU WON!!!", colors[col+20]);
		if (change==0)
		{
			col++;
			if (col==5)
				change=1;
		}
		else if (change==1)
		{
			col--;
			if (col==-5)
				change=0;
		}	
	}


	glutPostRedisplay();

	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

	

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...



		if (cary1 > 350 and cary1 < 390 and (carx1>606 and carx1<806) ){
			carx1-=100;
			trackNumber++;
		}
		if (cary1 > 350 and cary1 < 390 and (carx1<335 and carx1>135) ){
			carx1-=100;
			trackNumber--;
		}
	
	


	}
	else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {


		if (cary1 > 380 and cary1 < 520 and (carx1>505 and carx1<705) ){			
			carx1+=100;
			trackNumber--;
		}
		if (cary1 > 350 and cary1 < 390 and (carx1>35 and carx1<235) ){
			carx1+=100;
			trackNumber++;
		}
	
	


	}
	else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {


		if (carx1 > 375 and carx1 < 415 and (cary1>10 and cary1<185) ){
			cary1+=100;
			trackNumber++;
		}
		if (carx1 > 375 and carx1 < 415 and (cary1<650 and cary1>450) ){
			cary1+=100;
			trackNumber--;
		}



	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {


		if (carx1 > 395 and carx1 < 415 and (cary1<800 and cary1>550)  ){
			cary1-=100;
			trackNumber++;
		}
		if (carx1 > 395 and carx1 < 415 and (cary1>135 and cary1<265) ){
			cary1-=100;
			trackNumber--;
		}


	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		if (state==0 || state==5 )
			exit(1); // exit the program when escape key is pressed.
		if (state==1 || state==2 || state==3 || state==4 || state==6 || state==7 || state==8 || state==10 )
			state=0;
	}

	if (key == 'p' || key == 'P')  // for pausing
	{
		if( state==1 || state==2 || state==3 || state==4 )
			state=5;
			

	}

	if (key == 'r' || key == 'R')  // for resuming
	{
		if( state==5 )
			state=1;
			

	}
	if (key == '1')  // for new game
	{
		if( state==5 ){
			for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				life=3;
				points=0;
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;

				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				state=1;
			}

	}
	if (key == '2')  // for Highscores
	{
		if( state==5 )
			state=8;
			

	}
	if (key == '3')  // for Help
	{
		if( state==5 )
			state=6;
			

	}
	
	
	if (key == 32){		//ASCII for 'SPACE'
		if(myCarDirection==LEFT)
			carx1-=2;
		if(myCarDirection==UP)
			cary1+=2;
		if(myCarDirection==RIGHT)
			carx1+=2;
		if(myCarDirection==DOWN)
			cary1-=2;		

	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
		if (state==0)
		{
			if ( (x>=328 and x<=500) and ( y<=328 and y>=298 ) ) {
				
				for(int i=0; i<64 ; i++)
				{
					tf[i]=1;
				}
				life=3;
				points=0;
				x = 470;
			        y = 50;
				oppCarDirection = oRIGHT;

				carx1 = 310; 
				cary1 = 50;
				myCarDirection = LEFT;
				state=1;
			}	
			if ( (x>=328 and x<=400) and ( y<=410 and y>=388 ) )
				state=6;

			if ( (x>=328 and x<=500) and ( y<=370 and y>=350 ) )
				state=8;
		}
		
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
				cout << GLUT_DOWN << " " << GLUT_UP << endl;
				

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	
	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 840, height = 840; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("D O D G E___E M"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	
	
	
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);
	
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	
 	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
