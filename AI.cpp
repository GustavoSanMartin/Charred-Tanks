//Gustavo San Martin ICS3U 2015
#include "tanks.h"

bool AI(Tank User1, BITMAP *buffer, Tank1 &Ai, SAMPLE *SndFx){
	//Declaring variables
	static bool shotInAir, direction;
	static float x, t, s, flipY;
	
	//move AI's tank
	if (direction == false){
		Ai.aiX -= 1;
		if (Ai.aiX <= scrx / 2 + 30)
			direction = true;
	}
	else{
		Ai.aiX += 1;
		if (Ai.aiX >= scrx - 50)
			direction = false;
	}

	//save coordinates of tank when shot is fired + play sound
	if (shotInAir == false){
		play_sample(SndFx, 255, 128, 1000, 0);
		x = Ai.aiX;
		t = Ai.aiX;//AI position	
		s = User1.x; //User position
		shotInAir = true;	
	}
	//Calculate shot y value with given x value
	if (shotInAir)
		flipY = AIShot(x, s, t, buffer);
	
	//Collision with user tank (AI wins)
	if (hitTank(User1.x , scry - 25, x, flipY)){
		return true;	
	}
	//stop shote if it hits ground or tree
	if ((shotInAir && x < s) || (hitWall(flipY, x))){	
		shotInAir = false;
	}
	//printf AI's tank
	printAI(buffer, User1, Ai);
	
	return false;
}

float AIShot(float &x, float s, float t, BITMAP *buffer){
	//declaring variables
	float y = 0, flipY = 0, a = -0.005;//a = slope
	
	x -= 1.5; //speed of shot
	y = a * ((x - s) * (x - t)); //determine y value of shot with given x value
	flipY = scry - y; //flip y axis (makes y axis at bottom instead of top
	
	circlefill(buffer, x + 32, flipY - 30, 2, BLACK); //print parabola	
	return flipY;
}

void printAI(BITMAP *buffer, Tank User1, Tank1 Ai){	
	float TurretAngleAI = DetermineAng(a, User1.x, User1.x, Ai.aiX);
	//print tank and turret
	pivot_sprite(buffer, Ai.Turret, Ai.aiX + 30, scry - 25, 0 , 0, itofix(TurretAngleAI));
	draw_sprite(buffer, Ai.Tank, Ai.aiX, scry - 35);
}
