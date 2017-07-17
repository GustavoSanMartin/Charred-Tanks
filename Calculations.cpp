//Gustavo San Martin ICS3U 2015
#include "Tanks.h"

long double DegToRad(float AngDeg){//Convert from degrees to radians
	return (AngDeg * (2 * Pi) / 360);	
}

long double RadToDeg(float AngDeg){ //convert from radians to degrees
	return (AngDeg * 360 / (2 * Pi));	
}

bool hitWall(float y, float x){//Determine if shot hits tree
	if (y > (scry / 2 + 295) && x > (scrx / 2 - 1) && x < (scrx / 2 + 1)){
		return true;
	}
	return false;
}
bool hitTank(int TankX, int TankY, float ShotX, float ShotY){
	//determines if shot hits enemy tank
	if (ShotX > (TankX - 27) && ShotX < (TankX + 27) && ShotY > (TankY - 17) 
		&& ShotY < (TankY + 0)){
		return true;
	}	
	return false;
}
float ConvertAngle(int Angle){
	//converts standard 360 degree circle into allegro's 256 degree circle
	return (Angle) / (1.40625); //360 / 256 = 1.4
}

float DetermineAng(float a, int x, float s, float t){
	//calculate angle of parabola when leaving tanks position
	float DeterminedAng = 0, y = 0, Angle = 0;
	y = a * ((x + 1 - s) * (x + 1 - t)); //factored form: y = a(x-s)(x-t)
	Angle = (RadToDeg(atan(y/ 1)));//convert to degrees
	DeterminedAng = ConvertAngle(Angle + 180);//convert to allegro 256 degree circle
	return DeterminedAng;
}


void input(Tank &User1, Tank &Multi1){
	//user input
	if (key[KEY_LEFT] && User1.x > 0)//move left / right
		User1.x -= 1;
		
	if (key[KEY_RIGHT] && User1.x < scrx / 2 -75)
		User1.x += 1;
		
	if (key[KEY_X] && User1.v < 200) //increase / decrease power
		User1.v += 1;
		
	if (key[KEY_Z] && User1.v > 10)
		User1.v -= 1;
		
	if (key[KEY_UP] && User1.AngDeg < 80){//increase / decrease angle
		User1.AngDeg += 1;
		User1.Angle -= 1;
	}	
	if (key[KEY_DOWN] && User1.AngDeg > 1){
		User1.AngDeg -= 1;
		User1.Angle += 1;
	}
	if (key[KEY_S]) //easter egg (slow motion)
		rest(100);
	
	//second user input
	if (mouse_x < Multi1.x + 60 && Multi1.x > scrx / 2 + 10)
		Multi1.x -= 1;
		
	if (mouse_x > Multi1.x - 25 && Multi1.x < scrx -10)
		Multi1.x += 1;
	
	Multi1.v = mouse_z;//mousewheel scroll for velocity
	
	//angle
	if (mouse_y <= scry - 20 && mouse_y >= scry - 100){
		Multi1.AngDeg = scry - mouse_y - 20;
		Multi1.Angle = scry - mouse_y - 91;
		
	}
}

