#include "iGraphics.h"
#include <stdlib.h>

int recX,recY,col1,col2,down=0,bpawnselect = 10,wpawnselect = 10,wrookselect = 10,brookselect = 10,wbishopselect = 10,bbishopselect = 10;
int m,br,bg,bb,cursor,ent_name=0,Xcursor1,Xcursor2,showname1=0,showname2=0,watch_main,watch1,watch2;
int clickNewGame,prompt=0,whitemove_done = 0,blackmove_done = 0;
char player1[30],player2[30],wht[7],blk[7];
int rowY[9] = {0,80,160,240,320,400,480,560,640};
int colX[9] = {20,100,180,260,340,420,500,580,660};
int startX,startY,endX,endY,click1,wknightselect = 10,bknightselect = 10,wkingselect = 10,bkingselect = 10,wqueenselect = 10,bqueenselect=10;
int whity[7] = {100,260,420,580,740,900,1060},s1,min1,h1,s2,h2,min2;
int play1 = 1,play2 = 0,count_valid = 0,wpawnx,wpawny,wknightx,wknighty,wbishopx,wbishopy,wrookx,wrooky,wqueenx=3,wqueeny=0,wkingx=4,wkingy=0;
int board[8][8]={0},bpawnx,bpawny,brookx,brooky,bknightx,bknighty,bbishopx,bbishopy,bqueenx,bqueeny,bkingx,bkingy;
int wPawn_alive[8]={1,1,1,1,1,1,1,1},wGameover,bGameover;
int bPawn_alive[8]={1,1,1,1,1,1,1,1};
int wRook_alive[2] = {1,1};
int bRook_alive[2] = {1,1};
int wBishop_alive[2] = {1,1};
int bBishop_alive[2] = {1,1};
int wKnight_alive[2] = {1,1};
int bKnight_alive[2] = {1,1},passX,passY,bCheckmate,wCheckmate,wleftrook,wrightrook,bleftrook,brightrook,wkingmove,bkingmove;
int wKing_alive = 1,bKing_alive = 1,wQueen_alive=1,bQueen_alive=1,kill,wpromo,bckgrnd=1,dev=0,tool=0,countWcheck,countBcheck;
int inix,iniy,enx,eny,h,min,s,blackCheck = 0,whiteCheck=0,_invAlert,showAlert,t,tango;
char hour[5],minute[5],sec[5],hour1[5],minute1[5],sec1[5],hour2[5],minute2[5],sec2[5];
FILE *fp;

struct chess
{
	int x;
	int y;
} white_pawn[8],black_pawn[8],white_rook[2],black_rook[2],white_bishop[2],black_bishop[2],white_knight[2],black_knight[2],white_king[1],black_king[1],white_queen[1],black_queen[1];

void prebck()				//pre background
{
	if(bckgrnd)
	{
		iShowBMP(0,0,"newbck.bmp");
		if(dev)
		{
			iShowBMP(35,100,"developer.bmp");
		}
		if(tool)
		{
			iShowBMP(35,100,"tools.bmp");
		}
	}
}

void drawbackgrnd()
{
	iSetColor(100,150,150);
	iFilledRectangle(0,0,1320,680);
}

void drawBoard()
{
	double x[4]={660,665,665,660};
	double y[4]={0,0,645,640};
	double p[4]={20,20,15,15};
	double q[4]={0,640,645,0};
	double a[4]={20,660,665,15};
	double b[4]={640,640,645,645};
	int f=0,i,j;
	for(m=0;m<8;m++)
	{
		if(f==0)
		{
			for(i=0,j=1; i<8,j<8; i+=2,j+=2)
			{	
				iSetColor(0,0,0);
				iFilledRectangle(recX+(80*m),recY+(80*i),80,80);
				iSetColor(255,255,255);
				iFilledRectangle(recX+(80*m),recY+(80*j),80,80);
			}
			f = 1;
		}
		else
		{
			for(i=0,j=1; i<8,j<8; i+=2,j+=2)
			{	
				iSetColor(255,255,255);
				iFilledRectangle(recX+(80*m),recY+(80*i),80,80);
				iSetColor(0,0,0);
				iFilledRectangle(recX+(80*m),recY+(80*j),80,80);
			}
			f = 0;
		}
	}
	iSetColor(71,71,71);
	iFilledPolygon(x,y,4);
	iFilledPolygon(p,q,4);
	iFilledPolygon(a,b,4);
	iSetColor(128,0,0);
	iPolygon(x,y,4);
	iPolygon(p,q,4);
	iPolygon(a,b,4);
}

void boxPlayer1()
{
	int x=680;
	int y = 440;
	double p[5]={1320,1180,1200,1320,1320};
	double q[5]={357,357,327,327,357};
	iSetColor(41,36,33);
	iFilledRectangle(677,357,643,165);
	iFilledRectangle(677,519,244,53);
	iSetColor(90,90,90);
	iFilledPolygon(p,q,5);
	iFilledRectangle(680,520,240,50);
	iSetColor(255,255,255);
	iText(700,530,"PLAYER 1:",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,0);
	iPolygon(p,q,5);
	iFilledRectangle(680,360,640,160);
	iText(1205,333,"I  Surrender",GLUT_BITMAP_HELVETICA_18);
	if(showname1)
	{
		iSetColor(255,255,255);
		iText(830,530,player1,GLUT_BITMAP_HELVETICA_18);
		ent_name = 1;
		showname1 = 1;
	}
	if(play1)
	{
		iSetColor(0,238,0);
		iText(700,530,"PLAYER 1:",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(830,530,player1,GLUT_BITMAP_HELVETICA_18);
	}
	for(int i=0; i<8; i++)			//uploading dead black pawns on the side bar
	{
		if(bPawn_alive[i]==0)
		{
			iShowBMP(x,y,"pawnblack_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 360;
			}
		}
	}
	for(int j=0; j<2; j++)			//uploading dead black rooks on the side bar
	{
		if(bRook_alive[j]==0)
		{
			iShowBMP(x,y,"rookblack_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 360;
			}
		}
		if(bKnight_alive[j]==0)			//uploading dead black knights on the side bar
		{
			iShowBMP(x,y,"knightblack_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 360;
			}
		}
		if(bBishop_alive[j]==0)			//dead black bishop
		{
			iShowBMP(x,y,"bishopblack_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 360;
			}	
		}
	}
	if(bQueen_alive==0)					//dead black queen
	{
		iShowBMP(x,y,"queenblack_blk_bckgrnd.bmp");
		x+=80;
		if(x==1320)
		{
			x = 680;
			y = 360;
		}	
	}
	if(bKing_alive==0)					//dead black king
	{
		iShowBMP(x,y,"kingblack_blk_bckgrnd.bmp");
		x+=80;
		if(x==1320)
		{
			x = 680;
			y = 360;
		}	
	}
}

void boxPlayer2()
{
	int x = 680;
	int y = 170;
	double p[5]={1320,1180,1200,1320,1320};
	double q[5]={87,87,57,57,87};
	iSetColor(41,36,33);
	iFilledRectangle(677,247,244,55);
	iFilledRectangle(677,87,643,165);
	iSetColor(90,90,90);
	iFilledPolygon(p,q,5);
	iFilledRectangle(680,250,240,50);
	iSetColor(255,255,255);
	iText(700,260,"PLAYER 2:",GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(0,0,0);
	iPolygon(p,q,5);
	iFilledRectangle(680,90,640,160);
	iText(1205,65,"I  Surrender",GLUT_BITMAP_HELVETICA_18);
	if(showname2)
	{
		iSetColor(255,255,255);
		iText(830,260,player2,GLUT_BITMAP_HELVETICA_18);
		ent_name = 1;
		prompt = 1;
		showname2 = 1;
	}
	if(play2)
	{
		iSetColor(0,238,0);
		iText(700,260,"PLAYER 2:",GLUT_BITMAP_TIMES_ROMAN_24);	
		iText(830,260,player2,GLUT_BITMAP_HELVETICA_18);
	}
	for(int i=0; i<8; i++)				//uploading dead white pawns on the side bar
	{
		if(wPawn_alive[i]==0)
		{
			iShowBMP(x,y,"pawnwhite_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 90;
			}
		}
	}
	for(int j=0; j<2; j++)
	{
		if(wRook_alive[j]==0)			//uploading dead white rooks on the side bar
		{
			iShowBMP(x,y,"rookwhite_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 90;
			}
		}
		if(wKnight_alive[j]==0)				//uploading dead white knights on the side bar
		{
			iShowBMP(x,y,"knightwhite_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 90;
			}
		}
		if(wBishop_alive[j]==0)				//dead white bishop
		{
			iShowBMP(x,y,"bishopwhite_blk_bckgrnd.bmp");
			x+=80;
			if(x==1320)
			{
				x = 680;
				y = 90;
			}
		}
	}
	if(wQueen_alive==0)						//dead white queen
	{
		iShowBMP(x,y,"queenwhite_blk_bckgrnd.bmp");
		x+=80;
		if(x==1320)
		{
			x = 680;
			y = 90;
		}
	}
	if(wKing_alive==0)						//dead white king
	{
		iShowBMP(x,y,"kingwhite_blk_bckgrnd.bmp");
		x+=80;
		if(x==1320)
		{
			x = 680;
			y = 90;
		}
	}
}

void showmove()			//shows moving positions
{
	iSetColor(39,64,139);
	iFilledRectangle(949,524,122,47);
	iFilledRectangle(949,254,122,47);
	iSetColor(0,8,10);
	iFilledRectangle(950,525,120,45);
	iFilledRectangle(950,255,122,45);
	iSetColor(255,255,255);
	iText(975,535,wht,GLUT_BITMAP_HELVETICA_18);
	iText(975,265,blk,GLUT_BITMAP_HELVETICA_18);
}

void drawCommand()		//top menu functions
{
	iSetColor(199,199,199);
	iFilledRectangle(0,660,200,20);
	iFilledRectangle(200,660,105,20);
	iFilledRectangle(305,660,105,20);
	iSetColor(0,0,0);
	iRectangle(0,660,200,20);
	iRectangle(200,660,105,20);
	iRectangle(305,660,105,20);
	iFilledRectangle(95,660,1,20);
	iSetColor(0,0,0);
	iText(5,665,"New Game F1");
	iText(100,665,"Save Game F2");
	iText(205,665,"Load Game F3");
	iText(310,665,"Quit Game F4");
}

void drawPrompt()		//box for entering player name
{
	iSetColor(99,99,99);
	iFilledRectangle(400,400,400,50);
	iSetColor(255,255,255);
	iFilledRectangle(410,410,380,30);
	if(!ent_name)
	{
		iSetColor(0,0,0);
		iText(412,414,"Player 1:",GLUT_BITMAP_HELVETICA_18);
		iSetColor(br,bg,bb);
		iFilledRectangle(Xcursor1,414,2,15);
		iSetColor(0,0,0);
		iText(490,414,player1,GLUT_BITMAP_HELVETICA_18);
	}
	else
	{
		iSetColor(0,0,0);
		iText(412,414,"Player 2:",GLUT_BITMAP_HELVETICA_18);
		iSetColor(br,bg,bb);
		iFilledRectangle(Xcursor2,414,2,15);
		iSetColor(0,0,0);
		iText(490,414,player2,GLUT_BITMAP_HELVETICA_18);
	}
}

void endGame()				//ending game
{
	if(wKing_alive==0 && (play1 || play2))
	{
		wGameover=1;	
	}
	if(bKing_alive==0 && (play1 ||play2))
	{
		bGameover=1;	
	}
}



void check_whiteCheckMate()					//checkmate for black
{
	int posx,posy,x,y,flag=0,g,f,enemy=0;
	int row[8]={-1,-1,-1,0,1,1,1,0};
	int col[8]={-1,0,1,1,1,0,-1,-1};
	for(int i=1; i<9; i++)
	{		
		if(white_king[0].x == colX[i-1]) posx = i-1;
		if(white_king[0].y == rowY[i-1]) posy = i-1;				
	}
	for(i=0; i<8; i++)//loop for 8 positions around the king
	{
		wCheckmate=0;
		g=row[i]+posx;
		f=col[i]+posy;
		if(g>=0 && g<8 && f>=0 && f<8 && board[f][g]!=1) 
		{
			if(f-2==bknighty && g-1==bknightx) /*********checking knight*********/
			{
				flag=1;
				wCheckmate=1;
			}
			if(f-1==bknighty && g-2==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f+1==bknighty && g-2==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f+2==bknighty && g-1==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f-2==bknighty && g+1==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f-1==bknighty && g+2==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f+1==bknighty && g+2==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}
			if(f+2==bknighty && g+1==bknightx) 
			{
				flag=1;
				wCheckmate=1;
			}									/*********checking knight*********/
			x = g;
			y = f;
			while(board[y+1][x]!=1)		//checking a row
			{
				++y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)			//checking queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==brooky && x==brookx)				//checking rook
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==bkingy && x==bkingx)			//checking king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x]!=1)		//checking row
			{
				--y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==brooky && x==brookx)		//checking for rook
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bkingy && x==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(y<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y][x-1]!=1)			//checking column
			{
				--x;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==brooky && x==brookx)		//checking for rook
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bkingy && x==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y][x+1]!=1)			//checking column
			{
				++x;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==brooky && x==brookx)		//checking for rook
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bkingy && x==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y+1][x+1]!=1)		//checking diagonal
			{
				++x;
				++y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==bbishopy && x==bbishopx)	//checking for bishop
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==bpawny && g+1==bpawnx)		//checking for pawn
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==bkingy && g+1==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x>7 || y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y+1][x-1]!=1)		//checking diagonal
			{
				--x;
				++y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==bbishopy && x==bbishopx)	//checking for bishop
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==bpawny && g-1==bpawnx)		//checking for pawn
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==bkingy && g-1==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x<0 || y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x-1]!=1)		//checking diagonal
			{
				--x;
				--y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==bbishopy && x==bbishopx)	//checking for bishop
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bpawny && g-1==bpawnx)		//checking for pawn
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bkingy && g-1==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}
					else break;
			}
				if(x<0 || y<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x+1]!=1)		//checking diagonal
			{
				++x;
				--y;
				if(board[y][x]==1) break;
				if(board[y][x]==2 && !flag)
				{
					if(y==bqueeny && x==bqueenx)	//checking for queen
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(y==bbishopy && x==bbishopx)	//checking for bishop
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bpawny && g+1==bpawnx)		//checking for pawn
					{
						wCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==bkingy && g+1==bkingx)		//checking for king
					{
						wCheckmate=1;
						flag=1;
						break;	
					}	
					else break;
				}
				if(x>7 || y<0 || flag) break;
			}
			if(wCheckmate) enemy++;
			else 
			{
				enemy=0;
				break;
			}
		}
	}
	if(!enemy) wCheckmate=0;
}

void check_blackCheckMate()					//checkmate for black
{
	int posx,posy,x,y,flag=0,g,f,enemy=0;
	int row[8]={-1,-1,-1,0,1,1,1,0};
	int col[8]={-1,0,1,1,1,0,-1,-1};
	for(int i=1; i<9; i++)
	{		
		if(black_king[0].x == colX[i-1]) posx = i-1;
		if(black_king[0].y == rowY[i-1]) posy = i-1;				
	}
	for(i=0; i<8; i++)//loop for 8 positions around the king
	{
		bCheckmate=0;
		g=row[i]+posx;
		f=col[i]+posy;
		if(g>=0 && g<8 && f>=0 && f<8 && board[f][g]!=2) 
		{
			if(f-2==wknighty && g-1==wknightx) /*********checking knight*********/
			{
				flag=1;
				bCheckmate=1;
			}
			if(f-1==wknighty && g-2==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f+1==wknighty && g-2==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f+2==wknighty && g-1==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f-2==wknighty && g+1==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f-1==wknighty && g+2==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f+1==wknighty && g+2==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}
			if(f+2==wknighty && g+1==wknightx) 
			{
				flag=1;
				bCheckmate=1;
			}									/*********checking knight*********/
			x = g;
			y = f;
			while(board[y+1][x]!=2)		//checking a row
			{
				++y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)			//checking queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wrooky && x==wrookx)				//checking rook
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==wkingy && x==wkingx)			//checking king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x]!=2)		//checking row
			{
				--y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wrooky && x==wrookx)		//checking for rook
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wkingy && x==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(y<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y][x-1]!=2)			//checking column
			{
				--x;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wrooky && x==wrookx)		//checking for rook
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wkingy && x==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y][x+1]!=2)			//checking column
			{
				++x;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wrooky && x==wrookx)		//checking for rook
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wkingy && x==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y+1][x+1]!=2)		//checking diagonal
			{
				++x;
				++y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wbishopy && x==wbishopx)	//checking for bishop
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==wpawny && g+1==wpawnx)		//checking for pawn
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==wkingy && g+1==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x>7 || y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y+1][x-1]!=2)		//checking diagonal
			{
				--x;
				++y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wbishopy && x==wbishopx)	//checking for bishop
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==wpawny && g-1==wpawnx)		//checking for pawn
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f+1==wkingy && g-1==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
				}
				if(x<0 || y>7 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x-1]!=2)		//checking diagonal
			{
				--x;
				--y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wbishopy && x==wbishopx)	//checking for bishop
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wpawny && g-1==wpawnx)		//checking for pawn
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wkingy && g-1==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}
					else break;
			}
				if(x<0 || y<0 || flag) break;
			}
			x = g;
			y = f;
			while(board[y-1][x+1]!=2)		//checking diagonal
			{
				++x;
				--y;
				if(board[y][x]==2) break;
				if(board[y][x]==1 && !flag)
				{
					if(y==wqueeny && x==wqueenx)	//checking for queen
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(y==wbishopy && x==wbishopx)	//checking for bishop
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wpawny && g+1==wpawnx)		//checking for pawn
					{
						bCheckmate=1;
						flag=1;
						break;
					}
					else if(f-1==wkingy && g+1==wkingx)		//checking for king
					{
						bCheckmate=1;
						flag=1;
						break;	
					}	
					else break;
				}
				if(x>7 || y<0 || flag) break;
			}
			if(bCheckmate) enemy++;
			else 
			{
				enemy=0;
				break;
			}
		}
	}
	if(!enemy) bCheckmate=0;
}

void check_black()					//check for black
{
	int posx,posy,x,y,flag=0;
	blackCheck=0;
	for(int i=1; i<9; i++)
	{		
		if(black_king[0].x == colX[i-1]) posx = i-1;
		if(black_king[0].y == rowY[i-1]) posy = i-1;				
	}
	if(posy-2==wknighty && posx-1==wknightx) /*********checking knight*********/
	{
		flag=1;
		blackCheck=1;
	}
	if(posy-1==wknighty && posx-2==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy+1==wknighty && posx-2==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy+2==wknighty && posx-1==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy-2==wknighty && posx+1==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy-1==wknighty && posx+2==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy+1==wknighty && posx+2==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}
	if(posy+2==wknighty && posx+1==wknightx) 
	{
		flag=1;
		blackCheck=1;
	}									/*********checking knight*********/
	x = posx;
	y = posy;
	while(board[y+1][x]!=2)		//checking a row
	{
		++y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)			//checking queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wrooky && x==wrookx)				//checking rook
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==wkingy && x==wkingx)			//checking king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x]!=2)		//checking row
	{
		--y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wrooky && x==wrookx)		//checking for rook
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wkingy && x==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(y<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y][x-1]!=2)			//checking column
	{
		--x;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wrooky && x==wrookx)		//checking for rook
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wkingy && x==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y][x+1]!=2)			//checking column
	{
		++x;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wrooky && x==wrookx)		//checking for rook
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wkingy && x==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y+1][x+1]!=2)		//checking diagonal
	{
		++x;
		++y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wbishopy && x==wbishopx)	//checking for bishop
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==wpawny && posx+1==wpawnx)		//checking for pawn
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==wkingy && posx+1==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x>7 || y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y+1][x-1]!=2)		//checking diagonal
	{
		--x;
		++y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wbishopy && x==wbishopx)	//checking for bishop
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==wpawny && posx-1==wpawnx)		//checking for pawn
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==wkingy && posx-1==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x-1]!=2)		//checking diagonal
	{
		--x;
		--y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wbishopy && x==wbishopx)	//checking for bishop
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wpawny && posx-1==wpawnx)		//checking for pawn
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wkingy && posx-1==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || y<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x+1]!=2)		//checking diagonal
	{
		++x;
		--y;
		if(board[y][x]==2) break;
		if(board[y][x]==1 && !flag)
		{
			if(y==wqueeny && x==wqueenx)	//checking for queen
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(y==wbishopy && x==wbishopx)	//checking for bishop
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wpawny && posx+1==wpawnx)		//checking for pawn
			{
				blackCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==wkingy && posx+1==wkingx)		//checking for king
			{
				blackCheck=1;
				flag=1;
				break;	
			}	
			else break;
		}
		if(x>7 || y<0 || flag) break;
	}
}

void check_white()					//checkmate for white
{
	int posx,posy,x,y,flag=0;
	whiteCheck=0;
	for(int i=1; i<9; i++)
	{		
		if(white_king[0].x == colX[i-1]) posx = i-1;
		if(white_king[0].y == rowY[i-1]) posy = i-1;				
	}
	if(posy-2==bknighty && posx-1==bknightx) /*********checking knight*********/
	{
		flag=1;
		whiteCheck=1;   
	}
	if(posy-1==bknighty && posx-2==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy+1==bknighty && posx-2==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy+2==bknighty && posx-1==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy-2==bknighty && posx+1==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy-1==bknighty && posx+2==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy+1==bknighty && posx+2==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}
	if(posy+2==bknighty && posx+1==bknightx) 
	{
		flag=1;
		whiteCheck=1;
	}							/*********checking knight*********/
	x = posx;
	y = posy;
	while(board[y+1][x]!=1)		//checking a row
	{
		++y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)			//checking queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==brooky && x==brookx)				//checking rook
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==bkingy && x==bkingx)			//checking king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x]!=1)		//checking row
	{
		--y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==brooky && x==brookx)		//checking for rook
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bkingy && x==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(y<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y][x-1]!=1)			//checking column
	{
		--x;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==brooky && x==brookx)		//checking for rook
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bkingy && x==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y][x+1]!=1)			//checking column
	{
		++x;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==brooky && x==brookx)		//checking for rook
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bkingy && x==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y+1][x+1]!=1)		//checking diagonal
	{
		++x;
		++y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==bbishopy && x==bbishopx)	//checking for bishop
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==bpawny && posx+1==bpawnx)		//checking for pawn
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==bkingy && posx+1==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x>7 || y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y+1][x-1]!=1)		//checking diagonal
	{
		--x;
		++y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==bbishopy && x==bbishopx)	//checking for bishop
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==bpawny && posx-1==bpawnx)		//checking for pawn
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy+1==bkingy && posx-1==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || y>7 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x-1]!=1)		//checking diagonal
	{
		--x;
		--y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==bbishopy && x==bbishopx)	//checking for bishop
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bpawny && posx-1==bpawnx)		//checking for pawn
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bkingy && posx-1==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x<0 || y<0 || flag) break;
	}
	x = posx;
	y = posy;
	while(board[y-1][x+1]!=1)		//checking diagonal
	{
		++x;
		--y;
		if(board[y][x]==2 && !flag)
		{
			if(y==bqueeny && x==bqueenx)	//checking for queen
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(y==bbishopy && x==bbishopx)	//checking for bishop
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bpawny && posx+1==bpawnx)		//checking for pawn
			{
				whiteCheck=1;
				flag=1;
				break;
			}
			else if(posy-1==bkingy && posx+1==bkingx)		//checking for king
			{
				whiteCheck=1;
				flag=1;
				break;	
			}
			else break;
		}
		if(x>7 || y<0 || flag) break;
	}
	printf("%d white king %d %d %d %d\n",whiteCheck,posy,posx,bpawny,bpawnx);
}

void white_attack(int x,int y)			//white attack
{
	for(int p=0; p<8; p++)
	{
		if(black_pawn[p].x == x && black_pawn[p].y == y)    //if the attack on a black pawn
		{
			bPawn_alive[p] = 0;
			printf("p=%d\n",p);
			kill=1;
			return;
		}
	}
	for(int q=0; q<2; q++)
	{
		if(black_rook[q].x == x && black_rook[q].y == y)    //if the attack on a black rook
		{
			bRook_alive[q] = 0;
			kill=1;
			return;
		}
		if(black_knight[q].x==x && black_knight[q].y==y)		//if the attack on a black knight
		{
			bKnight_alive[q] = 0;
			kill=1;
			return;
		}
		if(black_bishop[q].x==x && black_bishop[q].y==y)		//if the attack on black bishop
		{
			bBishop_alive[q]=0;
			kill=1;
			return;
		}
	}
	if(black_queen[0].x==x && black_queen[0].y==y)				//if the attack on black queen
	{
		bQueen_alive=0;
		kill=1;
		return;
	}
	if(black_king[0].x==x && black_king[0].y==y)				//if the attack on black king
	{
		bKing_alive = 0;
		kill=1;
		return;
	}	
}

void black_attack(int x,int y)				//black attack
{
	for(int p=0; p<8; p++)
	{
		if(white_pawn[p].x==x && white_pawn[p].y==y)		//if the attack on a white pawn
		{
			wPawn_alive[p] = 0;
			kill=1;
			return;
		}
	}
	for(int q=0; q<2; q++)
	{
		if(white_rook[q].x == x && white_rook[q].y == y)       //if the attack on a white rook
		{
			wRook_alive[q] = 0;
			kill=1;
			return;
		}
		if(white_knight[q].x == x && white_knight[q].y == y)		//if the attack on a white knight
		{
			wKnight_alive[q] = 0;
			kill=1;
			return;
		}
		if(white_bishop[q].x==x && white_bishop[q].y==y)			//if attack on white bishop
		{
			wBishop_alive[q] = 0;
			kill=1;
			return;
		}
	}
	if(white_queen[0].x==x && white_queen[0].y==y)				//if the attack on white queen
	{
		wQueen_alive=0;
		kill=1;
		return;
	}
	if(white_king[0].x==x && white_king[0].y==y)				//if the attack on the white king
	{
		wKing_alive = 0;
		kill=1;
		return;
	}
}

int checkValidity(int x, int y)					//getting endX and endY as parameter
{
	if(play1)								//player1
	{
		if(wpawnselect<8)						//check vaLIDITY for white pawns
		{
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wpawnselect = 10;
				_invAlert=0;
				return 0;
			}
			if(y < startY) return 0;
			for(int i=0; i<8; i++)
			{
				if(white_pawn[i].x == x && white_pawn[i].y == y)
				{
					startX = endX;
					startY = endY;
					wpawnselect = 10;
					return 0;
				}
			}
			if(startX==x)
			{
				if(startY==80 && y<=240) 
				{
					if(board[eny][enx]==2) return 0; 
					return 1;
				}

				else if(startY==80 && y>240) return 0;

				else if(y==startY+80) 
				{
					if(board[eny][enx]==2) return 0; 
					else return 1;
				}
				else return 0;
			}
			else
			{
				if((x == startX+80 || x==startX-80) && y==startY+80)
				{
					if(board[eny][enx]==2) //successful attack on black by a white pawn
					{
						white_attack(x,y);
						return 1;
					}								
					else return 0;
				}
				else return 0;
			}
		}//end pawn

		if(wrookselect<2)				//check validity for white rook
		{	
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wrookselect = 10;
				_invAlert=0;
				return 0;
			}
			if(x == startX)
			{
				if(eny>iniy)		//forward
				{
					for(int p=iniy+1; p<=eny; p++)			//checking intermediate white
					{
						if(board[p][enx]==1) return 0;
					}
					for(int q=iniy+1; q<eny; q++)			//checking intermediate black
					{
						if(board[q][enx]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white rook
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;
				}
				else				//reverse
				{
					for(int p=iniy-1; p>=eny; p--)				//checking intermediate white		
					{
						if(board[p][enx]==1) return 0;
					}
					for(int q=iniy-1; q>eny; q--)			//checking intermediate black
					{
						if(board[q][enx]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white rook
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;
				}
			}
			else if(y == startY)
			{
				if(enx > inix)		//forward
				{
					for(int p=inix+1; p<=enx; p++)				//checking intermediate white
					{
						if(board[eny][p] == 1) return 0;	
					}
					for(int q=inix+1; q<enx; q++)			//checking intermediate black
					{
						if(board[eny][q]==2) return 0;
					}
					if(board[eny][enx]==2)					//successful attack on black by a white rook
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
				else			//reverse
				{
					for(int p=inix-1; p>=enx; p--)				//checking intermediate white		
					{
						if(board[eny][p]==1) return 0;
					}
					for(int q=inix-1; q>enx; q--)			//checking intermediate black
					{
						if(board[eny][q]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white rook
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;	
				}
			}
			else return 0;
		}//end rook

		if(wknightselect<2)					//check validity for white knight 
		{
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wknightselect = 10;
				_invAlert=0;
				return 0;
			}
			if(eny == iniy-2 && enx==inix-1)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)					//successful attack on black
					{
						white_attack(x,y);
						return 1;	
					}
					return 1;
				}
			}
			else if(eny==iniy-1 && enx==inix-2)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+1 && enx==inix-2)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+2 && enx==inix-1)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+2 && enx==inix+1)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;	
				}
			}
			else if(eny==iniy+1 && enx==inix+2)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy-1 && enx==inix+2)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy-2 && enx==inix+1)
			{
				if(board[eny][enx]==1) return 0;			//checking white
				else
				{
					if(board[eny][enx]==2)			//successful attack on a black
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else return 0;
		}//end knight

		if(wbishopselect<2)						//validity for white bishop
		{
			int pox,poy,toy,tox;
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wbishopselect = 10;
				_invAlert=0;
				return 0;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				++pox;
				printf("%d%d\n",poy,pox);
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						++tox;
						if(board[toy][tox]==1) return 0;			//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;				//normal move
				}
				if(poy>7 || pox>7) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						--tox;
						if(board[toy][tox]==1) return 0;				//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;				//normal move
				}
				if(poy<0 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						--tox;
						if(board[toy][tox]==1) return 0;				//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;
				}
				if(poy>7 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						++tox;
						if(board[toy][tox]==1) return 0;			//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;
				}
				if(poy<0 || pox>7) break;
			}
			return 0;				//invalid move
		}//end bishop

		if(wqueenselect<1)
		{
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wqueenselect = 10;
				_invAlert=0;
				return 0;
			}
			int pox,poy,toy,tox;
			if(x == startX)
			{
				if(eny>iniy)		//forward
				{
					for(int p=iniy+1; p<=eny; p++)			//checking intermediate white
					{
						if(board[p][enx]==1) return 0;
					}
					for(int q=iniy+1; q<eny; q++)			//checking intermediate black
					{
						if(board[q][enx]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white queen
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;
				}
				else				//reverse
				{
					for(int p=iniy-1; p>=eny; p--)				//checking intermediate white		
					{
						if(board[p][enx]==1) return 0;
					}
					for(int q=iniy-1; q>eny; q--)			//checking intermediate black
					{
						if(board[q][enx]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white queen
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;
				}
			}
			else if(y == startY)
			{
				if(enx > inix)		//forward
				{
					for(int p=inix+1; p<=enx; p++)				//checking intermediate white
					{
						if(board[eny][p] == 1) return 0;	
					}
					for(int q=inix+1; q<enx; q++)			//checking intermediate black
					{
						if(board[eny][q]==2) return 0;
					}
					if(board[eny][enx]==2)					//successful attack on black by a white queen
					{
						white_attack(x,y);
						return 1;
					}
					return 1;
				}
				else			//reverse
				{
					for(int p=inix-1; p>=enx; p--)				//checking intermediate white		
					{
						if(board[eny][p]==1) return 0;
					}
					for(int q=inix-1; q>enx; q--)			//checking intermediate black
					{
						if(board[eny][q]==2) return 0;
					}
					if(board[eny][enx]==2)			//successful attack on black by a white queen
					{
						white_attack(x,y);
						return 1;		
					}
					return 1;	
				}
			}
			/***********************function of bishop in queen***********************/
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				++pox;
				printf("%d%d\n",poy,pox);
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						++tox;
						if(board[toy][tox]==1) return 0;			//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;				//normal move
				}
				if(poy>7 || pox>7) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						--tox;
						if(board[toy][tox]==1) return 0;				//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;				//normal move
				}
				if(poy<0 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						--tox;
						if(board[toy][tox]==1) return 0;				//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;
				}
				if(poy>7 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						++tox;
						if(board[toy][tox]==1) return 0;			//intermediate white
						if(board[toy][tox]==2)				//attack on black
						{
							kill=0;
							white_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate black
						}
					}
					return 1;
				}
				if(poy<0 || pox>7) break;
			}
			return 0;				//invalid move		
		}//end queen

		if(wkingselect<1)
		{
			int a,b;
			int row[8]={-1,-1,-1,0,1,1,1,0};
			int col[8]={-1,0,1,1,1,0,-1,-1};
			if(board[eny][enx]==1)				//selecting another object
			{
				startX = endX;
				startY = endY;
				iniy=eny;
				inix=enx;
				wkingselect = 10;
				_invAlert=0;
				return 0;
			}
			for(int i=0; i<8; i++)
			{
				a = iniy+row[i];
				b = inix+col[i];
				if(a==eny && b==enx && board[eny][enx]==2)			//successful attack on black
				{
					white_attack(x,y);
					return 1;	
				}
				else if(a==eny && b==enx && board[eny][enx]==1) return 0;
				else if(a==eny && b==enx && board[eny][enx]==0) return 1;
			}
			return 0;
		}//end

	}
	if(play2)						//player2
	{
		if(bpawnselect<8)					//check validity for black pawns
		{
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				bpawnselect=10;
				_invAlert=0;
				return 0;
			}
			if(y > startY) return 0;
			for(int j=0; j<8; j++)
			{
				if(black_pawn[j].x == x && black_pawn[j].y == y) 
				{
					bpawnselect= 10;
					startX = endX;
					startY = endY;
					return 0;
				}
			}
			if(startX==x)
			{
				if(startY==480 && y>=320)
				{
					if(board[eny][enx]==1) return 0; 
					else return 1;	
				}

				else if(startY==480 && y<320) return 0;

				else if(y==startY-80)
				{
					if(board[eny][enx]==1) return 0; 
					else return 1;
				}
				else return 0;
			}
			else
			{
				if((x==startX-80 || x==startX+80) && y==startY-80)
				{
					if(board[eny][enx]==1)		//successful attack on a white by a black pawn
					{
						black_attack(x,y);
						return 1;
					}
					else return 0;
				}
				else return 0;
			}
		}//end pawn
		if(brookselect<2)				//check validity for black rook
		{	
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				brookselect=10;
				_invAlert=0;
				return 0;
			}
			if(x == startX)
			{
				if(eny>iniy)		//forward
				{
					for(int p=iniy+1; p<=eny; p++)			//checking intermediate black
					{
						if(board[p][enx]==2) return 0;
					}
					for(int q=iniy+1; q<eny; q++)			//checking intermediate white
					{
						if(board[q][enx]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a white rook
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;
				}
				else				//reverse
				{
					for(int p=iniy-1; p>=eny; p--)				//checking intermediate black		
					{
						if(board[p][enx]==2) return 0;
					}
					for(int q=iniy-1; q>eny; q--)			//checking intermediate white
					{
						if(board[q][enx]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a black rook
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;
				}
			}
			else if(y == startY)
			{
				if(enx > inix)		//forward
				{
					for(int p=inix+1; p<=enx; p++)				//checking intermediate black
					{
						if(board[eny][p] == 2) return 0;	
					}
					for(int q=inix+1; q<enx; q++)			//checking intermediate white
					{
						if(board[eny][q]==1) return 0;
					}
					if(board[eny][enx]==1)					//successful attack on white by a black rook
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
				else			//reverse
				{
					for(int p=inix-1; p>=enx; p--)				//checking intermediate black		
					{
						if(board[eny][p]==2) return 0;
					}
					for(int q=inix-1; q>enx; q--)			//checking intermediate white
					{
						if(board[eny][q]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a black rook
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;	
				}
			}
			else return 0;
		}//end rook

		if(bknightselect<2)					//check validity for black knight 
		{
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				bknightselect=10;
				_invAlert=0;
				return 0;
			}
			if(eny == iniy-2 && enx==inix-1)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)					//successful attack on white
					{
						black_attack(x,y);
						return 1;	
					}
					return 1;
				}
			}
			else if(eny==iniy-1 && enx==inix-2)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+1 && enx==inix-2)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+2 && enx==inix-1)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy+2 && enx==inix+1)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;	
				}
			}
			else if(eny==iniy+1 && enx==inix+2)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy-1 && enx==inix+2)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
			}
			else if(eny==iniy-2 && enx==inix+1)
			{
				if(board[eny][enx]==2) return 0;			//checking black
				else
				{
					if(board[eny][enx]==1)			//successful attack on a white
					{
						black_attack(x,y);
						return 1;
					}
					return 1;;
				}
			}
			else return 0;
		}//end knight

		if(bbishopselect<2)					//validity for black bishop
		{
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				bbishopselect=10;
				_invAlert=0;
				return 0;
			}
			int pox,poy,toy,tox;
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						++tox;
						if(board[toy][tox]==2) return 0;			//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;				//normal move
				}
				if(poy>7 || pox>7) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						--tox;
						if(board[toy][tox]==2) return 0;				//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;				//normal move
				}
				if(poy<0 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						--tox;
						if(board[toy][tox]==2) return 0;				//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;
				}
				if(poy>7 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						++tox;
						if(board[toy][tox]==2) return 0;			//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;
				}
				if(poy<0 || pox>7) break;
			}
			return 0;				//invalid move	
		}//end bishop

		if(bqueenselect<1)
		{
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				bqueenselect=10;
				_invAlert=0;
				return 0;
			}
			int pox,poy,toy,tox;
			if(x == startX)
			{
				if(eny>iniy)		//forward
				{
					for(int p=iniy+1; p<=eny; p++)			//checking intermediate black
					{
						if(board[p][enx]==2) return 0;
					}
					for(int q=iniy+1; q<eny; q++)			//checking intermediate white
					{
						if(board[q][enx]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a white queen
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;
				}
				else				//reverse
				{
					for(int p=iniy-1; p>=eny; p--)				//checking intermediate black		
					{
						if(board[p][enx]==2) return 0;
					}
					for(int q=iniy-1; q>eny; q--)			//checking intermediate white
					{
						if(board[q][enx]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a black queen
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;
				}
			}
			else if(y == startY)
			{
				if(enx > inix)		//forward
				{
					for(int p=inix+1; p<=enx; p++)				//checking intermediate black
					{
						if(board[eny][p] == 2) return 0;	
					}
					for(int q=inix+1; q<enx; q++)			//checking intermediate white
					{
						if(board[eny][q]==1) return 0;
					}
					if(board[eny][enx]==1)					//successful attack on white by a black queen
					{
						black_attack(x,y);
						return 1;
					}
					return 1;
				}
				else			//reverse
				{
					for(int p=inix-1; p>=enx; p--)				//checking intermediate black		
					{
						if(board[eny][p]==2) return 0;
					}
					for(int q=inix-1; q>enx; q--)			//checking intermediate white
					{
						if(board[eny][q]==1) return 0;
					}
					if(board[eny][enx]==1)			//successful attack on white by a black queen
					{
						black_attack(x,y);
						return 1;		
					}
					return 1;	
				}
			}
			/*****************************bishop function in queen**************************/
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						++tox;
						if(board[toy][tox]==2) return 0;			//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;			//intermediate white
						}
					}
					return 1;				//normal move
				}
				if(poy>7 || pox>7) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						--tox;
						if(board[toy][tox]==2) return 0;				//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;				//intermediate white
						}
					}
					return 1;				//normal move
				}
				if(poy<0 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				++poy;
				--pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						++toy;
						--tox;
						if(board[toy][tox]==2) return 0;				//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;
				}
				if(poy>7 || pox<0) break;
			}
			poy = iniy;
			pox = inix;
			while(poy!=eny && pox!=enx)
			{
				--poy;
				++pox;
				if(poy==eny && pox==enx)
				{
					toy = iniy;
					tox = inix;
					while(toy!=eny && tox!=enx)
					{
						--toy;
						++tox;
						if(board[toy][tox]==2) return 0;			//intermediate black
						if(board[toy][tox]==1)				//attack on white
						{
							kill=0;
							black_attack(x,y);
							if(kill) return 1;
							else return 0;					//intermediate white
						}
					}
					return 1;
				}
				if(poy<0 || pox>7) break;
			}
			return 0;				//invalid move
		}

		if(bkingselect<1)					//validity for black king
		{
			if(board[eny][enx]==2)			//selecting other object
			{
				startX=endX;
				startY=endY;
				iniy=eny;
				inix=enx;
				bkingselect=10;
				_invAlert=0;
				return 0;
			}
			int a,b;
			int row[8]={-1,-1,-1,0,1,1,1,0};
			int col[8]={-1,0,1,1,1,0,-1,-1};
			for(int i=0; i<8; i++)
			{
				a = iniy+row[i];
				b = inix+col[i];
				if(a==eny && b==enx && board[eny][enx]==1)			//successful attack on white
				{
					black_attack(x,y);
					return 1;	
				}
				else if(a==eny && b==enx && board[eny][enx]==2) return 0;
				else if(a==eny && b==enx && board[eny][enx]==0) return 1;
			}
			return 0;
		}//end
	}
}

void selectbox()
{
	iSetColor(0,139,0);
	iRectangle(startX,startY,80,80);
	iRectangle(startX+1,startY+1,78,78);
	iRectangle(startX+2,startY+2,77,77);	
}

void wpawn()		//white pawn
{
	int color1,color2,k=0,m;
	for(int i=0; i<8; i++)
	{
		if(wPawn_alive[i]==0)				//removing the dead pawns out of the board
		{
			white_pawn[i].x = 1320;
			white_pawn[i].y = 0;
		}
		color1 = white_pawn[i].x + white_pawn[i].y;
		color2 = (white_pawn[i].x > white_pawn[i].y) ? white_pawn[i].x - white_pawn[i].y : white_pawn[i].y - white_pawn[i].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wPawn_alive[i]==1)
			{
				iShowBMP(white_pawn[i].x,white_pawn[i].y,"pawnwhite_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && wPawn_alive[i]==1) iShowBMP(white_pawn[i].x,white_pawn[i].y,"pawnwhite_blk_bckgrnd.bmp");
	}
	if(click1 && play1)
	{
		for(int i=0; i<8; i++)
		{
			if(startX==white_pawn[i].x && startY==white_pawn[i].y)
			{
				wpawnselect = i;
				selectbox();
				//showValidmove(startX,startY);
			}
		}
	}
	else if(!click1 && wpawnselect<8)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_pawn[wpawnselect].x = endX;
		white_pawn[wpawnselect].y= endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wPawn_alive[wpawnselect]==1)
			{
				iShowBMP(white_pawn[wpawnselect].x,white_pawn[wpawnselect].y,"pawnwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wPawn_alive[wpawnselect]==1) iShowBMP(white_pawn[wpawnselect].x,white_pawn[wpawnselect].y,"pawnwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		wpawnselect = 10;
		wpawnx=enx;
		wpawny=eny;
		check_blackCheckMate();
		check_black();					//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}
}

void bpawn()			//black pawn
{
	int color1,color2,k=0,m;
	for(int i=0; i<8; i++)
	{
		if(bPawn_alive[i]==0)				//removing the dead pawns out of the board
		{
			black_pawn[i].x = 1320;
			black_pawn[i].y = 0;
		}
		color1 = black_pawn[i].x + black_pawn[i].y;
		color2 = (black_pawn[i].x > black_pawn[i].y) ? black_pawn[i].x - black_pawn[i].y : black_pawn[i].y - black_pawn[i].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bPawn_alive[i]==1)
			{
				iShowBMP(black_pawn[i].x,black_pawn[i].y,"pawnblack_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(!m && bPawn_alive[i]==1) iShowBMP(black_pawn[i].x,black_pawn[i].y,"pawnblack_blk_bckgrnd.bmp");
	}
	if(click1 && play2)
	{
		for(int i=0; i<8; i++)
		{
			if(startX==black_pawn[i].x && startY==black_pawn[i].y)
			{
				bpawnselect = i;
				selectbox();
			}
		}
	}
	else if(!click1 && bpawnselect<8)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_pawn[bpawnselect].x = endX;
		black_pawn[bpawnselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bPawn_alive[bpawnselect]==1)
			{
				iShowBMP(black_pawn[bpawnselect].x,black_pawn[bpawnselect].y,"pawnblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bPawn_alive[bpawnselect]==1) iShowBMP(black_pawn[bpawnselect].x,black_pawn[bpawnselect].y,"pawnblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		bpawnselect = 10;
		bpawnx=enx;
		bpawny=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)						//switching players
		{
			blackmove_done = 0;
			play1 = 1;
			play2 = 0;
		}
	}
}

void wrook()				//white rook
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(wRook_alive[q]==0)					//removing dead rook
		{
			white_rook[q].x = 1320;
			white_rook[q].y = 0;
		}
		color1 = white_rook[q].x + white_rook[q].y;
		color2 = (white_rook[q].x > white_rook[q].y) ? white_rook[q].x - white_rook[q].y : white_rook[q].y - white_rook[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wRook_alive[q]==1)
			{
				iShowBMP(white_rook[q].x,white_rook[q].y,"rookwhite_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && wRook_alive[q]==1) iShowBMP(white_rook[q].x,white_rook[q].y,"rookwhite_blk_bckgrnd.bmp");
	}
	if(click1 && play1)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==white_rook[q].x && startY==white_rook[q].y)
			{
				wrookselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && wrookselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_rook[wrookselect].x = endX;
		white_rook[wrookselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wRook_alive[wrookselect]==1)
			{
				iShowBMP(white_rook[wrookselect].x,white_rook[wrookselect].y,"rookwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wRook_alive[wrookselect]==1) iShowBMP(white_rook[wrookselect].x,white_rook[wrookselect].y,"rookwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		if(wrookselect) wrightrook=1;
		else wleftrook=1;
		wrookx=enx;
		wrooky=eny;
		wrookselect = 10;
		check_blackCheckMate();
		check_black();//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}
}

void brook()			//black rook
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(bRook_alive[q]==0)					//removing dead rook
		{
			black_rook[q].x = 1320;
			black_rook[q].y = 0;
		}
		color1 = black_rook[q].x + black_rook[q].y;
		color2 = (black_rook[q].x > black_rook[q].y) ? black_rook[q].x - black_rook[q].y : black_rook[q].y - black_rook[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bRook_alive[q]==1)
			{
				iShowBMP(black_rook[q].x,black_rook[q].y,"rookblack_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && bRook_alive[q]==1) iShowBMP(black_rook[q].x,black_rook[q].y,"rookblack_blk_bckgrnd.bmp");
	}
	if(click1 && play2)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==black_rook[q].x && startY==black_rook[q].y)
			{
				brookselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && brookselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_rook[brookselect].x = endX;
		black_rook[brookselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bRook_alive[brookselect]==1)
			{
				iShowBMP(black_rook[brookselect].x,black_rook[brookselect].y,"rookblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bRook_alive[brookselect]==1) iShowBMP(black_rook[brookselect].x,black_rook[brookselect].y,"rookblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		if(brookselect) brightrook=1;
		else bleftrook=0;
		brookselect = 10;
		brookx=enx;
		brooky=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)				//switching players
		{
			blackmove_done = 0;
			play2 = 0;
			play1 = 1;
		}
	}
}

void wbishop()			//white bishop
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(wBishop_alive[q]==0)					//removing dead bishop
		{
			white_bishop[q].x = 1320;
			white_bishop[q].y = 0;
		}
		color1 = white_bishop[q].x + white_bishop[q].y;
		color2 = (white_bishop[q].x > white_bishop[q].y) ? white_bishop[q].x - white_bishop[q].y : white_bishop[q].y - white_bishop[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wBishop_alive[q]==1)
			{
				iShowBMP(white_bishop[q].x,white_bishop[q].y,"bishopwhite_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && wBishop_alive[q]==1) iShowBMP(white_bishop[q].x,white_bishop[q].y,"bishopwhite_blk_bckgrnd.bmp");
	}
	if(click1 && play1)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==white_bishop[q].x && startY==white_bishop[q].y)
			{
				wbishopselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && wbishopselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_bishop[wbishopselect].x = endX;
		white_bishop[wbishopselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wBishop_alive[wbishopselect]==1)
			{
				iShowBMP(white_bishop[wbishopselect].x,white_bishop[wbishopselect].y,"bishopwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wBishop_alive[wbishopselect]==1) iShowBMP(white_bishop[wbishopselect].x,white_bishop[wbishopselect].y,"bishopwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		wbishopselect = 10;
		wbishopx=enx;
		wbishopy=eny;
		check_blackCheckMate();
		check_black();//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}	
}

void bbishop()			//black bishop
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(bBishop_alive[q]==0)					//removing dead bishop
		{
			black_bishop[q].x = 1320;
			black_bishop[q].y = 0;
		}
		color1 = black_bishop[q].x + black_bishop[q].y;
		color2 = (black_bishop[q].x > black_bishop[q].y) ? black_bishop[q].x - black_bishop[q].y : black_bishop[q].y - black_bishop[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bBishop_alive[q]==1)
			{
				iShowBMP(black_bishop[q].x,black_bishop[q].y,"bishopblack_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && bBishop_alive[q]==1) iShowBMP(black_bishop[q].x,black_bishop[q].y,"bishopblack_blk_bckgrnd.bmp");
	}
	if(click1 && play2)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==black_bishop[q].x && startY==black_bishop[q].y)
			{
				bbishopselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && bbishopselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_bishop[bbishopselect].x = endX;
		black_bishop[bbishopselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bBishop_alive[bbishopselect]==1)
			{
				iShowBMP(black_bishop[bbishopselect].x,black_bishop[bbishopselect].y,"bishopblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bBishop_alive[bbishopselect]==1) iShowBMP(black_bishop[bbishopselect].x,black_bishop[bbishopselect].y,"bishopblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		bbishopselect = 10;
		bbishopx=enx;
		bbishopy=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)				//switching players
		{
			blackmove_done = 0;
			play2 = 0;
			play1 = 1;
		}
	}
}

void wknight()			//white knight
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(wKnight_alive[q]==0)					//removing dead knight
		{
			white_knight[q].x = 1320;
			white_knight[q].y = 0;
		}
		color1 = white_knight[q].x + white_knight[q].y;
		color2 = (white_knight[q].x > white_knight[q].y) ? white_knight[q].x - white_knight[q].y : white_knight[q].y - white_knight[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wKnight_alive[q]==1)
			{
				iShowBMP(white_knight[q].x,white_knight[q].y,"knightwhite_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && wKnight_alive[q]==1) iShowBMP(white_knight[q].x,white_knight[q].y,"knightwhite_blk_bckgrnd.bmp");
	}
	if(click1 && play1)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==white_knight[q].x && startY==white_knight[q].y)
			{
				wknightselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && wknightselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_knight[wknightselect].x = endX;
		white_knight[wknightselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wKnight_alive[wknightselect]==1)
			{
				iShowBMP(white_knight[wknightselect].x,white_knight[wknightselect].y,"knightwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wKnight_alive[wknightselect]==1) iShowBMP(white_knight[wknightselect].x,white_knight[wknightselect].y,"knightwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		wknightselect = 10;
		wknightx=enx;
		wknighty=eny;
		check_blackCheckMate();
		check_black();	//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}
}

void bknight()			//black knight
{
	int color1,color2,k = 0,m;
	for(int q=0; q<2; q++)
	{
		if(bKnight_alive[q]==0)					//removing dead knight
		{
			black_knight[q].x = 1320;
			black_knight[q].y = 0;
		}
		color1 = black_knight[q].x + black_knight[q].y;
		color2 = (black_knight[q].x > black_knight[q].y) ? black_knight[q].x - black_knight[q].y : black_knight[q].y - black_knight[q].x;
		m = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bKnight_alive[q]==1)
			{
				iShowBMP(black_knight[q].x,black_knight[q].y,"knightblack_wht_bckgrnd.bmp");
				m = 1;
				break;
			}
		}
		if(m==0 && bKnight_alive[q]==1) iShowBMP(black_knight[q].x,black_knight[q].y,"knightblack_blk_bckgrnd.bmp");
	}
	if(click1 && play2)
	{
		for(int q=0; q<2; q++)
		{
			if(startX==black_knight[q].x && startY==black_knight[q].y)
			{
				bknightselect = q;
				selectbox();
			}
		}
	}
	else if(!click1 && bknightselect<2)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_knight[bknightselect].x = endX;
		black_knight[bknightselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bKnight_alive[bknightselect]==1)
			{
				iShowBMP(black_knight[bknightselect].x,black_knight[bknightselect].y,"knightblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bKnight_alive[bknightselect]==1) iShowBMP(black_knight[bknightselect].x,black_knight[bknightselect].y,"knightblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		bknightselect = 10;
		bknightx=enx;
		bknighty=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)				//switching players
		{
			blackmove_done = 0;
			play2 = 0;
			play1 = 1;
		}
	}
}

void wking()		//white king
{
	int color1,color2,k = 0,m;
	if(wKing_alive==0)					//removing dead king
	{
		white_king[0].x = 1320;
		white_king[0].y = 0;
		endGame();
	}
	color1 = white_king[0].x + white_king[0].y;
	color2 = (white_king[0].x > white_king[0].y) ? white_king[0].x - white_king[0].y : white_king[0].y - white_king[0].x;
	m = 0;
	for(int j=0; j<7; j++)
	{
		if((color1==whity[j] || color2==whity[j]) && wKing_alive==1)
		{
			iShowBMP(white_king[0].x,white_king[0].y,"kingwhite_wht_bckgrnd.bmp");
			m = 1;
			break;
		}
	}
	if(m==0 && wKing_alive==1) iShowBMP(white_king[0].x,white_king[0].y,"kingwhite_blk_bckgrnd.bmp");
	if(click1 && play1)
	{
		if(startX==white_king[0].x && startY==white_king[0].y)
		{
			wkingselect = 0;
			selectbox();
		}
	}
	else if(!click1 && wkingselect<1)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_king[wkingselect].x = endX;
		white_king[wkingselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wKing_alive==1)
			{
				iShowBMP(white_king[wkingselect].x,white_king[wknightselect].y,"kingwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wKing_alive==1) iShowBMP(white_king[wkingselect].x,white_king[wkingselect].y,"kingwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		if(!wkingselect) wkingmove=1;
		wkingselect = 10;
		wkingx=enx;
		wkingy=eny;
		check_blackCheckMate();
		check_black();//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}
}

void bking()		//black king
{
	int color1,color2,k = 0,m;
	if(bKing_alive==0)					//removing dead king
	{
		black_king[0].x = 1320;
		black_king[0].y = 0;
		endGame();
	}
	color1 = black_king[0].x + black_king[0].y;
	color2 = (black_king[0].x > black_king[0].y) ? black_king[0].x - black_king[0].y : black_king[0].y - black_king[0].x;
	m = 0;
	for(int j=0; j<7; j++)
	{
		if((color1==whity[j] || color2==whity[j]) && bKing_alive==1)
		{
			iShowBMP(black_king[0].x,black_king[0].y,"kingblack_wht_bckgrnd.bmp");
			m = 1;
			break;
		}
	}
	if(m==0 && bKing_alive==1) iShowBMP(black_king[0].x,black_king[0].y,"kingblack_blk_bckgrnd.bmp");
	if(click1 && play2)
	{
		if(startX==black_king[0].x && startY==black_king[0].y)
		{
			bkingselect = 0;
			selectbox();
		}
	}
	else if(!click1 && bkingselect<1)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_king[bkingselect].x = endX;
		black_king[bkingselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bKing_alive==1)
			{
				iShowBMP(black_king[bkingselect].x,black_king[bkingselect].y,"kingblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bKing_alive==1) iShowBMP(black_king[bkingselect].x,black_king[bkingselect].y,"kingblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		if(!bkingselect) bkingmove=1;
		bkingselect = 10;
		bkingx=enx;
		bkingy=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)				//switching players
		{
			blackmove_done = 0;
			play2 = 0;
			play1 = 1;
		}
	}
}

void wqueen()			//white queen
{
	int color1,color2,k = 0,m;
	if(wQueen_alive==0)					//removing dead queen
	{
		white_queen[0].x = 1320;
		white_queen[0].y = 0;
	}
	color1 = white_queen[0].x + white_queen[0].y;
	color2 = (white_queen[0].x > white_queen[0].y) ? white_queen[0].x - white_queen[0].y : white_queen[0].y - white_queen[0].x;
	m = 0;
	for(int j=0; j<7; j++)
	{
		if((color1==whity[j] || color2==whity[j]) && wQueen_alive==1)
		{
			iShowBMP(white_queen[0].x,white_queen[0].y,"queenwhite_wht_bckgrnd.bmp");
			m = 1;
			break;
		}
	}
	if(m==0 && wQueen_alive==1) iShowBMP(white_queen[0].x,white_queen[0].y,"queenwhite_blk_bckgrnd.bmp");
	if(click1 && play1)
	{
		if(startX==white_queen[0].x && startY==white_queen[0].y)
		{
			wqueenselect = 0;
			selectbox();
		}
	}
	else if(!click1 && wqueenselect<1)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		white_queen[wqueenselect].x = endX;
		white_queen[wqueenselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && wQueen_alive==1)
			{
				iShowBMP(white_queen[wqueenselect].x,white_queen[wqueenselect].y,"queenwhite_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && wQueen_alive==1) iShowBMP(white_queen[wqueenselect].x,white_queen[wqueenselect].y,"queenwhite_blk_bckgrnd.bmp");
		whitemove_done = 1;
		wqueenselect = 10;
		wqueenx=enx;
		wqueeny=eny;
		check_blackCheckMate();
		check_black();//checking check for black
		if(whitemove_done)				//switching players
		{
			whitemove_done = 0;
			play2 = 1;
			play1 = 0;
		}
	}	
}

void bqueen()			//black queen
{
	int color1,color2,k = 0,m;
	if(bQueen_alive==0)					//removing dead queen
	{
		black_queen[0].x = 1320;
		black_queen[0].y = 0;
	}
	color1 = black_queen[0].x + black_queen[0].y;
	color2 = (black_queen[0].x > black_queen[0].y) ? black_queen[0].x - black_queen[0].y : black_queen[0].y - black_queen[0].x;
	m = 0;
	for(int j=0; j<7; j++)
	{
		if((color1==whity[j] || color2==whity[j]) && bQueen_alive==1)
		{
			iShowBMP(black_queen[0].x,black_queen[0].y,"queenblack_wht_bckgrnd.bmp");
			m = 1;
			break;
		}
	}
	if(m==0 && bQueen_alive==1) iShowBMP(black_queen[0].x,black_queen[0].y,"queenblack_blk_bckgrnd.bmp");
	if(click1 && play2)
	{
		if(startX==black_queen[0].x && startY==black_queen[0].y)
		{
			bqueenselect = 0;
			selectbox();
		}
	}
	else if(!click1 && bqueenselect<1)
	{
		color1 = endX + endY;
		color2 = (endX>endY)?endX-endY:endY-endX;
		black_queen[bqueenselect].x = endX;
		black_queen[bqueenselect].y = endY;
		
		k = 0;
		for(int j=0; j<7; j++)
		{
			if((color1==whity[j] || color2==whity[j]) && bQueen_alive==1)
			{
				iShowBMP(black_queen[bqueenselect].x,black_queen[bqueenselect].y,"queenblack_wht_bckgrnd.bmp");
				k = 1;
				break;
			}
		}
		if(!k && bQueen_alive==1) iShowBMP(black_queen[bqueenselect].x,black_queen[bqueenselect].y,"queenblack_blk_bckgrnd.bmp");
		blackmove_done = 1;
		bqueenselect = 10;
		bqueenx=enx;
		bqueeny=eny;
		check_whiteCheckMate();
		check_white();		//checking checkmate for white
		if(blackmove_done)				//switching players
		{
			blackmove_done = 0;
			play2 = 0;
			play1 = 1;
		}
	}	
}


void setboard()			//sets the board with chess pieces
{
	wpawn();			//draws white pawn
	bpawn();			//draws black pawn
	wrook();			//draws white rook
	brook();			//draws black rook
	wbishop();			//draws white bishop
	bbishop();			//draws black bishop
	wknight();			//draws white knight
	bknight();			//draws black knight
	wking();			//draws white king
	bking();			//draws black king
	wqueen();			//draws white queen
	bqueen();			//draws black queen
}

void klock()			//called by the timer
{
	++s;
	if(s==60)
	{
		s=0;
		++min;
		if(min==60)
		{
			min=0;
			++h;
		}
	}
}

void klock1()			//called by the timer
{
	++s1;
	if(s1==60)
	{
		s1=0;
		++min1;
		if(min1==60)
		{
			min1=0;
			++h1;
		}
	}
}
void klock2()			//called by the timer
{
	++s2;
	if(s2==60)
	{
		s2=0;
		++min2;
		if(min2==60)
		{
			min2=0;
			++h2;
		}
	}
}
void drawClock()
{
	iSetColor(0,0,255);
	iRectangle(719,579,302,82);
	iSetColor(0,0,0);
	iFilledRectangle(720,580,300,80);
	iFilledRectangle(1150,524,122,47);
	iFilledRectangle(1150,254,122,47);
	iSetColor(128 ,0,0);
	iRectangle(721,581,298,78);
	iSetColor(0,154,205);
	iText(745,630,"TIME  COUNTDOWN",GLUT_BITMAP_TIMES_ROMAN_24);
	itoa(s1,sec1,10);
	itoa(s,sec,10);
	itoa(s2,sec2,10);
	itoa(min1,minute1,10);
	itoa(min2,minute2,10);
	itoa(min,minute,10);
	itoa(h,hour,10);
	itoa(h1,hour1,10);
	itoa(h2,hour2,10);
	iSetColor(0,154,205);
	iText(820,590,hour,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(840,590,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(860,590,minute,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(880,590,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(900,590,sec,GLUT_BITMAP_TIMES_ROMAN_24);

	iText(1163,533,hour1,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1183,533,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1203,533,minute1,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1223,533,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1243,533,sec1,GLUT_BITMAP_TIMES_ROMAN_24);

	iText(1163,263,hour2,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1183,263,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1203,263,minute2,GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1223,263,":",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1243,263,sec2,GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(139,0,0);
	iRectangle(1150,524,122,47);
	iRectangle(1150,254,122,47);
}

void drawAlert()
{
	if(blackCheck==1)
	{
		++countBcheck;
		play2=0;
		tango=1;
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  CHECK  BLACK!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"skull_crossbones.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);
	}
	if(bCheckmate==1)
	{
		play2=0;
		tango=1;
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  CHECKMATE BLACK!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"skull_crossbones.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);
	}
	if(whiteCheck==1)
	{
		++countWcheck;
		play1=0;
		tango=1;
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  CHECK  WHITE!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"skull_crossbones.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);
	}
	if(wCheckmate==1)
	{
		++countWcheck;
		play1=0;
		tango=1;
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  CHECKMATE  WHITE!",GLUT_BITMAP_TIMES_ROMAN_24);
		//iShowBMP(552,302,"skull_crossbones.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);
	}
	if(showAlert)
	{
		tango=1;
		iSetColor(30,144,255);
		iFilledRectangle(550,300,300,100);
		iSetColor(54,100,139);
		iRectangle(550,300,300,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,297,80);
		iSetColor(54,100,139);
		iRectangle(552,302,297,80);
		iSetColor(238,0,0);
		iText(640,330,"INVALID  MOVE!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"invalid_alert.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(820,382,30,18);
		iSetColor(205,0,0);
		iLine(820,382,850,400);
		iLine(820,400,850,382);	
	}
	if(wGameover)
	{
		play1=0;
		play2=0;
		tango=1;
		iPauseTimer(watch_main);
		iPauseTimer(watch1);
		iPauseTimer(watch2);
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  BLACK  WINS!!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"kingblack_wht_bckgrnd.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);							
	}
	if(bGameover)
	{
		play1=0;
		play2=0;
		tango=1;
		iPauseTimer(watch_main);
		iPauseTimer(watch1);
		iPauseTimer(watch2);
		iSetColor(100,150,150);
		iFilledRectangle(550,300,350,100);
		iSetColor(54,100,139);
		iRectangle(550,300,350,100);
		iSetColor(255,255,255);
		iFilledRectangle(552,302,347,80);
		iSetColor(54,100,139);
		iRectangle(552,302,347,80);
		iSetColor(0,0,0);
		iText(632,330,"  WHITE  WINS!!",GLUT_BITMAP_TIMES_ROMAN_24);
		iShowBMP(552,302,"kingwhite_wht_bckgrnd.bmp");
		iSetColor(81,81,81);
		iFilledRectangle(870,382,30,18);
		iSetColor(205,0,0);
		iLine(870,382,900,400);
		iLine(870,400,900,382);							
	}
}

void set_reset()
{
	int i,k,j;
	for(k=0; k<8; k++)
	{
		for(j=0; j<8; j++) board[k][j]=0;
	}
	int r = 20;
	for(i=0; i<8; i++)
	{
		white_pawn[i].x = r;
		white_pawn[i].y = 80;
		black_pawn[i].x = r;
		black_pawn[i].y = 480;
		r+=80;
	}
	for(int p=0; p<2; p++)
	{
		for(int q=0; q<8; q++) board[p][q] = 1;
	}
	for(int u=6; u<8; u++)
	{
		for(int v=0; v<8; v++) board[u][v] = 2;
	}
	white_rook[0].x = 20;
	white_rook[0].y = 0;
	white_rook[1].x = 580;
	white_rook[1].y = 0;
	black_rook[0].x = 20;
	black_rook[0].y = 560;
	black_rook[1].x = 580;
	black_rook[1].y = 560;
	white_bishop[0].x = 180;
	white_bishop[0].y = 0;
	white_bishop[1].x = 420;
	white_bishop[1].y = 0;
	black_bishop[0].x = 180;
	black_bishop[0].y = 560;
	black_bishop[1].x = 420;
	black_bishop[1].y = 560;
	white_knight[0].x = 100;
	white_knight[0].y = 0;
	white_knight[1].x = 500;
	white_knight[1].y = 0;
	black_knight[0].x = 100;
	black_knight[0].y = 560;
	black_knight[1].x = 500;
	black_knight[1].y = 560;
	white_king[0].x = 340;
	white_king[0].y = 0;
	black_king[0].x = 340;
	black_king[0].y = 560;
	white_queen[0].x=260;
	white_queen[0].y=0;
	black_queen[0].x=260;
	black_queen[0].y=560;
	down=0;
	bpawnselect = wpawnselect = wrookselect = brookselect = wbishopselect = bbishopselect=10;
	whitemove_done =blackmove_done = 0;
	wknightselect = bknightselect = wkingselect = bkingselect = wqueenselect = bqueenselect=10;
	for(i=0;i<8; i++)
	{
		wPawn_alive[i]=1;
		bPawn_alive[i]=1;
	}
	for(i=0;i<2;i++)
	{
		wRook_alive[i] = 1;
		bRook_alive[i] = 1;
		wBishop_alive[i] = 1;
		bBishop_alive[i] = 1;
		wKnight_alive[i] = 1;
		bKnight_alive[i] = 1;	
	}
	wKing_alive =bKing_alive =wQueen_alive=bQueen_alive=1;
	play1 = 1;play2 = 0;count_valid = 0;
	wpawnx=wpawny=wknightx=wknighty=wbishopx=wbishopy=wrookx=wrooky=wqueenx=wqueeny=wkingx=wkingy=0;
    bpawnx=bpawny=brookx=brooky=bknightx=bknighty=bbishopx=bbishopy=bqueenx=bqueeny=bkingx=bkingy=0;
	h = 0;
	min = 0;
	s = 0;
	s1=h1=min1=s2=h2=min2=0;
	iPauseTimer(watch2);
	iResumeTimer(watch_main);
	iResumeTimer(watch1);
}

void checkPromo()
{
	int open=0;
	if(play2)
	{
		for(int i=0; i<8; i++)
		{
			if(white_pawn[i].y==560 && wQueen_alive==0)
			{
				wQueen_alive=1;
				white_queen[0].x=endX;
				white_queen[0].y=endY;
				wPawn_alive[i]=0;
				open=1;
			}
			else if(white_pawn[i].y==560 && (wRook_alive[0]==0 || wRook_alive[1]==0))
			{
				if(wRook_alive[0]==0) 
				{
					wRook_alive[0]=1;
					white_rook[0].x=endX;
					white_rook[0].y=endY;
				}
				else 
				{
					wRook_alive[1]=1;
					white_rook[1].x=endX;
					white_rook[1].y=endY;
				}
				wPawn_alive[i]=0;
				open=1;
			}
			else if(white_pawn[i].y==560 && (wKnight_alive[0]==0 || wKnight_alive[1]==0))
			{
				if(wKnight_alive[0]==0) 
				{
					wKnight_alive[0]=1;
					white_knight[0].x=endX;
					white_knight[0].y=endY;
				}
				else 
				{
					wKnight_alive[1]=1;
					white_knight[1].x=endX;
					white_knight[1].y=endY;
				}
				wPawn_alive[i]=0;
				open=1;
			}
			else if(white_pawn[i].y==560 && (wBishop_alive[0]==0 || wBishop_alive[1]==0))
			{
				if(wBishop_alive[0]==0) 
				{
					wBishop_alive[0]=1;
					white_bishop[0].x=endX;
					white_bishop[0].y=endY;
				}
				else 
				{
					wBishop_alive[1]=1;
					white_bishop[1].x=endX;
					white_bishop[1].y=endY;
				}
				wPawn_alive[i]=0;
				open=1;
			}
		}
		if(!open) showAlert=1;
	}
	if(play1)
	{
		for(int i=0; i<8; i++)
		{
			if(black_pawn[i].y==560 && bQueen_alive==0)
			{
				bQueen_alive=1;
				black_queen[0].x=endX;
				black_queen[0].y=endY;
				bPawn_alive[i]=0;
				open=1;
			}
			else if(black_pawn[i].y==560 && (bRook_alive[0]==0 || bRook_alive[1]==0))
			{
				if(bRook_alive[0]==0) 
				{
					bRook_alive[0]=1;
					black_rook[0].x=endX;
					black_rook[0].y=endY;
				}
				else 
				{
					bRook_alive[1]=1;
					black_rook[1].x=endX;
					black_rook[1].y=endY;
				}
				bPawn_alive[i]=0;
				open=1;
			}
			else if(black_pawn[i].y==560 && (bKnight_alive[0]==0 || bKnight_alive[1]==0))
			{
				if(bKnight_alive[0]==0) 
				{
					bKnight_alive[0]=1;
					black_knight[0].x=endX;
					black_knight[0].y=endY;
				}
				else 
				{
					bKnight_alive[1]=1;
					black_knight[1].x=endX;
					black_knight[1].y=endY;
				}
				bPawn_alive[i]=0;
				open=1;
			}
			else if(black_pawn[i].y==560 && (bBishop_alive[0]==0 || bBishop_alive[1]==0))
			{
				if(bBishop_alive[0]==0) 
				{
					bBishop_alive[0]=1;
					black_bishop[0].x=endX;
					black_bishop[0].y=endY;
				}
				else 
				{
					bBishop_alive[1]=1;
					black_bishop[1].x=endX;
					black_bishop[1].y=endY;
				}
				bPawn_alive[i]=0;
				open=1;
			}
		}
		if(!open) showAlert=1;
	}
}

void checkCastling()
{
	if(play1)
	{
		if(!wkingmove && !wleftrook && !board[0][1] && !board[0][2] && !board[0][3] && !countWcheck)
		{
			white_king[0].x=100;
			white_king[0].y=0;
			white_rook[0].x=180;
			white_rook[0].y=0;
		}
		else if(!wkingmove && !wrightrook && !board[0][6] && !board[0][5] && !countWcheck)
		{
			white_king[0].x=500;
			white_king[0].y=0;
			white_rook[1].x=420;
			white_rook[1].y=0;
		}
		else showAlert=1;
	}
	if(play2)
	{
		if(!bkingmove && !bleftrook && !board[7][1] && !board[7][2] && !board[7][3] && !countWcheck)
		{
			black_king[0].x=100;
			black_king[0].y=560;
			black_rook[0].x=180;
			black_rook[0].y=560;
		}
		else if(!bkingmove && !brightrook && !board[7][6] && !board[7][5] && !countWcheck)
		{
			black_king[0].x=500;
			black_king[0].y=560;
			black_rook[1].x=420;
			black_rook[1].y=560;
		}
		else showAlert=1;
	}
}

void promotion()
{
	double x[4]={1200,1320,1320,1220};
	double y[4]={0,0,25,25};
	iSetColor(113,113,198);
	iFilledPolygon(x,y,4);
	iSetColor(0,0,0);
	iText(1230,5,"PROMOTION",GLUT_BITMAP_HELVETICA_12);
	iSetColor(0,0,0);
	iPolygon(x,y,4);
}
void castling()
{
	double x[4]={1080,1200,1200,1100};
	double y[4]={0,0,25,25};
	iSetColor(113,113,198);
	iFilledPolygon(x,y,4);
	iSetColor(0,0,0);
	iText(1110,5,"CASTLING",GLUT_BITMAP_HELVETICA_12);
	iSetColor(0,0,0);
	iPolygon(x,y,4);
}
void fromPassivity()
{
	if(clickNewGame && !tango)
	{
		iSetColor(58,95,205);
		iRectangle(passX,passY,80,80);
		iRectangle(passX+1,passY+1,78,78);
		iRectangle(passX+2,passY+2,77,77);
	}
} 
void save()
{
	fp=fopen("game.txt","w");
	int i,j;
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++) fprintf(fp,"%d\n",board[i][j]);
	}
	for(i=0; i<8; i++)
	{
		fprintf(fp,"%d\n",white_pawn[i].x);
		fprintf(fp,"%d\n",white_pawn[i].y);
	}
	for(i=0; i<8; i++)
	{
		fprintf(fp,"%d\n",black_pawn[i].x);
		fprintf(fp,"%d\n",black_pawn[i].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",white_rook[j].x);
		fprintf(fp,"%d\n",white_rook[j].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",black_rook[j].x);
		fprintf(fp,"%d\n",black_rook[j].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",white_bishop[j].x);
		fprintf(fp,"%d\n",white_bishop[j].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",black_bishop[j].x);
		fprintf(fp,"%d\n",black_bishop[j].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",white_knight[j].x);
		fprintf(fp,"%d\n",white_knight[j].y);
	}
	for(j=0; j<2; j++)
	{
		fprintf(fp,"%d\n",black_knight[j].x);
		fprintf(fp,"%d\n",black_knight[j].y);
	}
	fprintf(fp,"%d\n",white_queen[0].x);
	fprintf(fp,"%d\n",white_queen[0].y);
	fprintf(fp,"%d\n",black_queen[0].x);
	fprintf(fp,"%d\n",black_queen[0].y);
	fprintf(fp,"%d\n",white_king[0].x);
	fprintf(fp,"%d\n",white_king[0].y);
	fprintf(fp,"%d\n",black_king[0].x);
	fprintf(fp,"%d\n",black_king[0].y);
	for(i=0;i<8; i++)
	{
		fprintf(fp,"%d\n",wPawn_alive[i]);
		fprintf(fp,"%d\n",bPawn_alive[i]);
	}
	for(i=0;i<2;i++)
	{
		fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n",wRook_alive[i],bRook_alive[i],wBishop_alive[i],bBishop_alive[i],wKnight_alive[i],bKnight_alive[i]);	
	}
	fprintf(fp,"%d\n%d\n%d\n%d\n",wKing_alive,bKing_alive,wQueen_alive,bQueen_alive);
	fprintf(fp,"%d\n%d\n%d\n",play1,play2,down);
	fprintf(fp,"%s\n%s\n",player1,player2);
	fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",s,h,min,s1,h1,min1,s2,h2,min2);
	fclose(fp);
}
void load()
{
	fp=fopen("game.txt","r");
	int i,j;
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++) fscanf(fp,"%d",&board[i][j]);
	}
	for(i=0; i<8; i++)
	{
		fscanf(fp,"%d",&white_pawn[i].x);
		fscanf(fp,"%d",&white_pawn[i].y);
	}
	for(i=0; i<8; i++)
	{
		fscanf(fp,"%d",&black_pawn[i].x);
		fscanf(fp,"%d",&black_pawn[i].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&white_rook[j].x);
		fscanf(fp,"%d",&white_rook[j].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&black_rook[j].x);
		fscanf(fp,"%d",&black_rook[j].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&white_bishop[j].x);
		fscanf(fp,"%d",&white_bishop[j].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&black_bishop[j].x);
		fscanf(fp,"%d",&black_bishop[j].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&white_knight[j].x);
		fscanf(fp,"%d",&white_knight[j].y);
	}
	for(j=0; j<2; j++)
	{
		fscanf(fp,"%d",&black_knight[j].x);
		fscanf(fp,"%d",&black_knight[j].y);
	}
	fscanf(fp,"%d",&white_queen[0].x);
	fscanf(fp,"%d",&white_queen[0].y);
	fscanf(fp,"%d",&black_queen[0].x);
	fscanf(fp,"%d",&black_queen[0].y);
	fscanf(fp,"%d",&white_king[0].x);
	fscanf(fp,"%d",&white_king[0].y);
	fscanf(fp,"%d",&black_king[0].x);
	fscanf(fp,"%d",&black_king[0].y);
	for(i=0;i<8; i++)
	{
		fscanf(fp,"%d",&wPawn_alive[i]);
		fscanf(fp,"%d",&bPawn_alive[i]);
	}
	for(i=0;i<2;i++)
	{
		fscanf(fp,"%d%d%d%d%d%d",&wRook_alive[i],&bRook_alive[i],&wBishop_alive[i],&bBishop_alive[i],&wKnight_alive[i],&bKnight_alive[i]);	
	}
	fscanf(fp,"%d%d%d%d",&wKing_alive,&bKing_alive,&wQueen_alive,&bQueen_alive);
	fscanf(fp,"%d%d%d",&play1,&play2,&down);
	fscanf(fp,"%s%s",&player1,&player2);
	fscanf(fp,"%d%d%d%d%d%d%d%d%d",&s,&h,&min,&s1,&h1,&min1,&s2,&h2,&min2);
	fclose(fp);
	iResumeTimer(watch_main);
	if(play1) iResumeTimer(watch1);
	else iResumeTimer(watch2);
	showname1=1;
	showname2=1;
}
void divider()
{
	iSetColor(150,150,150);
	iFilledRectangle(20,319,639,4);
	iSetColor(128,0,0);
	iRectangle(20,319,639,4);
}
void iDraw()
{
	iClear();
	if(bckgrnd) prebck();
	else 
	{
		drawbackgrnd();
		drawBoard();
		divider();
		boxPlayer1();
		boxPlayer2();
		drawCommand();
		if(clickNewGame)
		{
			if(!prompt) drawPrompt();		//draw text box for entering player names
			setboard();
			drawClock();
			drawAlert();
			showmove();
			promotion();
			fromPassivity();
			castling();
			//colorMove();
		}
	}
}


void iMouseMove(int mx, int my)
{
	
}


void iMouse(int button, int state, int mx, int my)
{
	int i,j,k=0,l=0,valid;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mx>=0 && mx<95 && my>=660 && my<=680)		//start a new game
		{
			prompt = 0;
			ent_name = 0;
			showname1 = 0;
			showname2 = 0;
			clickNewGame = 1;
			set_reset();
		}
		if(mx>1180 && mx<1320 && my>327 && my<357 && clickNewGame==1)
		{
			wGameover=1;
		}
		if(mx>1180 && mx<1320 && my>57 && my<87 && clickNewGame==1)
		{
			bGameover=1;
		}
		if(mx>870 && mx<1050 && my>625 && my<665 && clickNewGame==0)
		{
			bckgrnd=0;
			dev=0;
			tool=0;
		}
		if(mx>845 && mx<1070 && my>550 && my<605 && clickNewGame==0)
		{
			dev=1;	
			tool=0;
		}
		if(mx>890 && mx<1040 && my>500 && my<550 && clickNewGame==0)
		{
			dev=0;	
			tool=1;
		}
		if(mx>1200 && mx<=1320 && my>=0 && my<=25 && clickNewGame==1)
		{
			checkPromo();
		}
		if(mx>1080 && mx<=1200 && my>=0 && my<=25 && clickNewGame==1)
		{
			checkCastling();
		}
		if(mx>=870 && mx<=900 && my>=382 && my<=400)		//cross bar of check alert message
		{
			if(blackCheck==1 || bCheckmate==1)
			{
				blackCheck=0;
				play2=1;
				bCheckmate=0;
			}
			if(whiteCheck==1)
			{
				whiteCheck=0;
				play1=1;
			}
			if(wGameover) wGameover=0;
			if(bGameover) bGameover=0;
			tango=0;
		}
		if(mx>=820 && mx<=850 && my>=382 && my<=400)		//cross bar of alert message
		{
			showAlert=0;
		}
		if(mx>95 && mx<200 && my>=660 && my<=680)		//end a game
		{
			save();
		}
		if(mx>200 && mx<305 && my>=660 && my<=680)
		{
			load();
			clickNewGame=1;
		}
		if(mx>305 && mx<410 && my>=660 && my<=680)
		{
			exit(0);
		}
		if(mx>=20 && mx<=660 && my>=0 && my<=640 && clickNewGame==1)
		{
			++down;
			tango=1;
			++count_valid;
			if(down%2==0) click1 = 0;
			else click1 = 1;
			for(i=1; i<9; i++)
			{
				if(mx>colX[i-1] && mx<colX[i])		//searching x coordinate of the selected position
				{
					if(click1)
					{
						startX = colX[i-1];
						inix = i-1;
					}
					else
					{
						endX = colX[i-1];
						enx = i-1;
					}
					for(j=1; j<9; j++)
					{
						if(my>rowY[j-1] && my<rowY[j])  //searching y coordinate of the selected position
						{
							if(click1) 
							{
								startY = rowY[j-1];
								iniy = j-1;
							}
							else 
							{
								endY = rowY[j-1];
								eny = j-1;
							}
						}
					}
				}
			}
			if(!click1)
			{
				_invAlert=1;
				valid = checkValidity(endX,endY);
				if(valid)
				{
					if(play1)								//changing to the current board status
					{
						board[eny][enx] = 1;
						board[iniy][inix] = 0;
						wht[0]=inix+1+64;
						wht[1]=iniy+1+48;
						wht[2]=32;
						wht[3]=45;
						wht[4]=32;
						wht[5]=enx+1+64;
						wht[6]=eny+1+48;
						wht[7]='\0';
						iPauseTimer(watch1);
						iResumeTimer(watch2);
					}
					if(play2)
					{
						board[iniy][inix] = 0;
						board[eny][enx] = 2;
						blk[0]=inix+1+64;
						blk[1]=iniy+1+48;
						blk[2]=32;
						blk[3]=45;
						blk[4]=32;
						blk[5]=enx+1+64;
						blk[6]=eny+1+48;
						blk[7]='\0';
						iPauseTimer(watch2);
						iResumeTimer(watch1);
					}
					tango=0;
				}
				else
				{
					click1 = 1;
					down++;
					if(_invAlert) showAlert=1;
					else showAlert=0;
				}
			} 
		}

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
	/*for(int y=0; y<8; y++)
	{
		for(int z=0; z<8; z++)
		{
			printf("%d ",board[y][z]);
		}
		printf("\n");
	}
	printf("\n");*/
}
void iPassiveMouseMove(int mx,int my)
{
	int i,j;
	if(mx>=20 && mx<=660 && my>=0 && my<=640 && clickNewGame==1)
	{
		for(i=1; i<9; i++)
		{
			if(mx>colX[i-1] && mx<colX[i])		//searching x coordinate of the selected position
			{
				passX= colX[i-1];
			}
			if(my>rowY[i-1] && my<rowY[i])  //searching y coordinate of the selected position
			{
				passY= rowY[i-1];
			}
		}
	}
}

void iKeyboard(unsigned char key)
{
	if(!ent_name)		//accepting name for player1
	{
		if(key=='\b')
		{
			player1[col1 - 1] = player1[col1];
			col1--;
			Xcursor1-=9;
		}
		else if(key=='\r')
		{
			player1[col1]=NULL;
			showname1 = 1;
		}
		else
		{
			player1[col1] = key;
			col1++;
			Xcursor1+=9;
		}
	}
	else				//accepting name for player2
	{
		if(key=='\b')
		{
			player2[col2-1] = player2[col2];
			col2--;
			Xcursor2-=9;
		}
		else if(key=='\r')
		{
			player2[col2]=NULL;
			showname2 = 1;
		}
		else
		{
			player2[col2] = key;
			col2++;
			Xcursor2+=9;
		}
	}
}


void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_F2)
	{
		save();	
	}
	if(key==GLUT_KEY_F3)
	{
		load();
		clickNewGame=1;
	}
	if(key == GLUT_KEY_F1)
	{
		clickNewGame = 1;
		prompt = 0;
		ent_name = 0;
		showname1 = 0;
		showname2 = 0;
		set_reset();
	}
	if(key==GLUT_KEY_F4) exit(0);
}

void blinkCursor()
{
	if(cursor)
    {
        br=255;  bg=255;  bb=255;
        cursor = 0;
    }
    else
    {
        br=0;  bg=0;  bb=0;
        cursor = 1;
    }
}

int main()
{
	col1 = 0;
	col2 = 0;
	recX = 20;
	recY = 0;
	Xcursor1 = 490;
	Xcursor2 = 490;
	watch_main=iSetTimer(1000,klock);
	watch1=iSetTimer(1000,klock1);
	watch2=iSetTimer(1000,klock2);
	iSetTimer(500,blinkCursor);
	iInitialize(1320, 680, "Chess");
	return 0;
}	