/*******************************************************************************
*Gustavo San Martin						ICS3U			     	   June 7, 2015*
*Tank game: Has both single player and multiplayer options with a high score   *
*			table for single player and mouse controls for 2 player mode. 	   *
*						Controls explained in controls menu					   *
*******************************************************************************/
#include "Tanks.h"

int main() {
	allegro_init(); alfont_init();
	
	//initialise allegro
	install_mouse(); install_keyboard(); 
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "A"); 
	set_window_title("Charred Tanks");
	
	//set graphics mode,
  	set_color_depth(desktop_color_depth());
  	set_gfx_mode(GFX_AUTODETECT_WINDOWED, scrx, scry, 0, 0);
    
    //load / create images and fonts
    ALFONT_FONT *arial = alfont_load_font("C:\\WINDOWS\\Fonts\\verdanab.ttf"); 
    SAMPLE *SndFx = load_sample("Explosion.wav");
    BITMAP *Back = load_bitmap("Background.bmp", NULL);
	BITMAP *Tree = load_bitmap("Tree.bmp", NULL);
    BITMAP *TurretA = load_bitmap("TurretA.bmp", NULL);
    BITMAP *TurretB = load_bitmap("TurretB.bmp", NULL);
	BITMAP *TankA = load_bitmap("TankA.bmp", NULL);
	BITMAP *TankB = load_bitmap("TankB.bmp", NULL);
	BITMAP *Explosion = load_bitmap("Explosion.bmp", NULL);
    BITMAP *buffer = create_bitmap(scrx, scry);//buffer
    
    bool Again = true;//to enter loop
    
    while (Again){
		//Declare variables
		bool Dead = false;
		int x = 0, x2 = scrx -60, y = scry - 10, TurretAng = 0, Angle = 0, Angle2 = 0, 
			Uscore = 0, Mscore, position = 3, time = 0;	  
		float aiX = scrx - 50, TurretAngleAI = 0, v = 75, v2 = 75,  
			AngDeg = 75, AngDeg2 = 75;
		
		//declare structures
		Tank User1 = {x, v, AngDeg, Angle, Uscore, TankA, TurretA};
		Tank Multi1 = {x2, v2, AngDeg2, Angle2, Mscore, TankB, TurretB};
		Tank1 Ai = {aiX, a, TankB, TurretB};
		Back2 Ground = {Back, Tree, arial};
		Score score = {0, 0};
		
		//play background music
		SAMPLE *Back2 = load_sample("Rat.wav");
		play_sample(Back2, 255, 128, 1000, 1);	
		
		position = Menu(buffer, arial, &time);	//Menu screen
		clock_t start = clock(), diff; //start timer
		diff = 1;
		stop_sample(Back2);//no background music during actual gameplay
		
		while(!key[KEY_ESC] && diff/1000 <= time && Dead == false){
				//Determine what key is pressed
				input(User1, Multi1);
				//update background + angle + velocity stats
				PrintStats(User1, Multi1, buffer, Ground, position, score, diff, time);
				//User related calculations/processes
				User(buffer, User1, Ai, Multi1, score, position, Explosion, SndFx);
				
				if (position == 1){//Single player
					Dead = AI(User1, buffer, Ai, SndFx);//Ai processes
					if (time != 300) //timer
						diff = clock() - start;}//determine time since start
				else if (position == 2)//2 player
					Multi(buffer, Multi1, User1, score, SndFx);//Multiplayer
			
				blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer	
				rest(1);//set max frame rate
		}
		play_sample(Back2, 255, 128, 1000, 0);//restart background music
		Again = end(score, position, arial, buffer);//Game over screen
		destroy_sample(Back2);
	}
	//clean up and close allegro
	destroy_sample(SndFx);
	alfont_exit(); 
  	return(0);
}END_OF_MAIN()
