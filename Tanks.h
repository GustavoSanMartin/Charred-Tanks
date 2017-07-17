//Gustavo San Martin ICS3I 2015
#include <allegro.h>
#include <alfont.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>

#define BLACK makecol(0, 0, 0)
#define WHITE makecol(255, 255, 255)
#define RED   makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define BLUE  makecol(0, 0, 255)

//structures
struct Tank{
	int x;
	float v;
	float AngDeg;
	int Angle;
	int score;
	BITMAP *Tank;
	BITMAP *Turret;
};
struct Tank1{
	float aiX;
	float a;
	BITMAP *Tank;
	BITMAP *Turret;
};
struct Back2{
	BITMAP *Back1;
	BITMAP *Tree;	
	ALFONT_FONT *arial;
};
struct Score{
	int User1;
	int User2;	
};

//global variables
const int scrx = 900;		//window width
const int scry = 900;		// window height
const long double Pi = 3.14159265358979323846264338327950288;
const int Y0 = 25; //tank height
const float g = 9.8; //gravity
const float a = -0.005; // Ai slope

//prototypes
//calculations
bool hitWall(float y, float x);
long double DegToRad(float AngDeg);
long double RadToDeg(float AngDeg);
bool hitTank(int TankX, int TankY, float ShotX, float ShotY);
float ConvertAngle(int Angle);
float DetermineAng(float a, int x, float s, float t);

//screens
int Menu(BITMAP *buffer, ALFONT_FONT *arial, int *time);
void input(Tank &User1, Tank &Multi1);
void PrintStats(Tank User1, Tank Multi1, BITMAP *buffer, Back2 Ground, 
				int position, Score score, int msec, int time);
bool end(Score score, int position, ALFONT_FONT *arial, BITMAP *buffer);
void Control();
int SingleMenu(BITMAP *buffer, ALFONT_FONT *arial);

//AI
bool AI(Tank User1, BITMAP *buffer, Tank1 &Ai, SAMPLE *SndFx);
float AIShot(float &x, float s, float t, BITMAP *buffer);
void printAI(BITMAP *buffer, Tank User1, Tank1 Ai);

//User 1
void User(BITMAP *buffer, Tank User1, Tank1 &Ai, Tank Multi1, Score &score, 
		  int position, BITMAP *Explosion, SAMPLE *SndFx);
float UserShot(float &x, float Ang, float Vel, int tankX, BITMAP *buffer);
void printUser(BITMAP *buffer, Tank User1);
void Explode(int xAtExplode, BITMAP *Explosion, BITMAP *buffer, bool explode1);

//User 2
void Multi(BITMAP *buffer, Tank Multi1, Tank User1, Score &score, SAMPLE *SndFx);
void printMulti(BITMAP *buffer, Tank Multi1);
float MultiShot(float &x, float Ang, float Vel, int tankX, BITMAP *buffer);
