//Gustavo San Martin ICS3U 2015
#include "Tanks.h"
void Multi(BITMAP *buffer, Tank Multi1, Tank User1, Score &score, SAMPLE *SndFx){
	//Declaring variables
	static float vAtShot, counter, angAtShot, flipY;
	static int xAtShot;
	static bool space;
	
	circlefill(buffer, mouse_x, mouse_y, 3, WHITE); //draw mouse
	//save coordinates of tank when shot is fired (mouse click)
	if(mouse_b & 1 && space == false){
		play_sample(SndFx, 255, 128, 2000, 0);//play sound
		xAtShot = Multi1.x;
		counter = 0;
		vAtShot = Multi1.v;
		angAtShot = Multi1.AngDeg;
		space = true;	
	}
	//check for collision with enemy tank
	if (hitTank(User1.x , scry - 25, counter + xAtShot, flipY)){
		space = false;
		flipY = 0;
		score.User2++;//increase score if hit
	}
	//off screen/collision
	if (flipY > scry || (hitWall(flipY, counter + xAtShot))){
		space = false;
		flipY = 0;	
	}
	//print shot
	else if (space)
		flipY = MultiShot(counter, angAtShot, vAtShot, xAtShot, buffer);

	printMulti(buffer, Multi1);//print tank
}

float MultiShot(float &x, float Ang, float Vel, int tankX, BITMAP *buffer){
	//Declaring variables
	float y = 0, flipY = 0;
	
	x -= 1; //speed	 of shot
	
	Ang = DegToRad(85 - (Ang + 90)); //convert from DEG to RAD
	//Determine y value based on x value using kinematics
	y = Y0 + x * tan(Ang) - g * (x*x) / (2 * pow(Vel * cos(Ang), 2));
	
	flipY = scry - y; //flip y axis
	
	circlefill(buffer, x + tankX + 24, flipY, 2, BLACK); //print shot
		
	return flipY;
}

void printMulti(BITMAP *buffer, Tank Multi1){	
	float TurretAng = ConvertAngle(Multi1.Angle + 250);//print turret
	pivot_sprite(buffer, Multi1.Turret, Multi1.x + 27, scry - 25, 0 , 0, itofix(TurretAng));
	draw_sprite(buffer, Multi1.Tank, Multi1.x, scry - 35);	//user tank
}
