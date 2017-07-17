//Gustavo San Martin ICS3U 2015
#include "Tanks.h"

void User(BITMAP *buffer, Tank User1, Tank1 &Ai, Tank Multi1, Score &score, 
			int position, BITMAP *Explosion, SAMPLE *SndFx){
	//Value remains in variable even when function doesnt run
	static float vAtShot, counter, angAtShot, flipY;
	static int xAtShot, ExplodeX;
	static bool space, explode1;
	
	//save coordinates when tank shoots	
	if(key[KEY_SPACE] && space == false){	
		play_sample(SndFx, 255, 128, 2000, 0);
		xAtShot = User1.x;
		counter = 0;
		vAtShot = User1.v;
		angAtShot = User1.AngDeg;
		space = true;
		
	}
	//reset when tank is hit + explode
	if (hitTank(Ai.aiX , scry - 25, counter + xAtShot, flipY) && position == 1){
		space = false;
		explode1 = true;
		flipY = 0;
		score.User1++;
		ExplodeX = Ai.aiX;
		Ai.aiX	= scrx - 50;
	}
	//Display explosion animation
	Explode(ExplodeX, Explosion, buffer, explode1);
	explode1 = false;
	
	//Determine if shot collides with enemy user
	if (hitTank(Multi1.x , scry - 25, counter + xAtShot, flipY) && position == 2){
		space = false;
		flipY = 0;
		score.User1++;	
	}
	//stop shot if hits ground or tree
	if (flipY > scry || (hitWall(flipY, counter))){
		space = false;
		flipY = 0;	
	}
	//Calculate parabola for tank shot
	if (space == true){
		flipY = UserShot(counter, angAtShot, vAtShot, xAtShot, buffer);
	}
	//Collision detection
	if (flipY > scry || (hitWall(flipY, counter + xAtShot + 20))){
		space = false;
		flipY = 0;	
	}
	//Print tank
	printUser(buffer, User1);
}

float UserShot(float &x, float Ang, float Vel, int tankX, BITMAP *buffer){
	float y = 0, flipY = 0;
	x += 1; //speed	
	
	Ang = DegToRad(Ang);//convert to Rad (for SIN and COS to work (comp is set to RAD))

	y = Y0 + x * tan(Ang) - g * (x*x) / (2 * pow(Vel * cos(Ang), 2));//kinematic formula
	
	flipY = scry - y; //flip y axis(y is at top, not bottom)
	
	circlefill(buffer, x + tankX + 18, flipY, 2, BLACK); //print shot
		
	return flipY;
}
void printUser(BITMAP *buffer, Tank User1){	
	//Display tank
	float TurretAng = ConvertAngle(User1.Angle  + 284);//Convert to allegro 256 degree
	pivot_sprite(buffer, User1.Turret, User1.x + 21, scry - 30, 0 , 0, itofix(TurretAng)); //Draw turret
	draw_sprite(buffer, User1.Tank, User1.x, scry - 35);	//user tank
}
void Explode(int xAtExplode, BITMAP *Explosion, BITMAP *buffer, bool explode1){
	//Declaring variables
	static int frame, time;
	static int x;
	static bool explosion;
	
	//Determine and save where explosion wshould happen
	if (frame == 0 && explode1){
		x = xAtExplode;
		explosion = true;	
	}
	//end of animation: reset
	if (frame == 12){
		explosion = false;
		frame = 0;
	}
	//print explosion
	if (frame < 12 && explosion){
		masked_blit(Explosion, buffer, frame * 135, 0, x - 25, scry - 120, 130, 130);
		time++;
		//frame rate
		if (time % 5 == 0)
			frame++;
	}
}
