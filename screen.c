//Gustavo San Martin ICS3U 2015
#include "tanks.h"

void PrintStats(Tank User1, Tank Multi1, BITMAP *buffer, Back2 Ground, 
				int position, Score score, int msec, int time){
	alfont_set_font_size(Ground.arial, 16);	
	//Background
	draw_sprite(buffer, Ground.Back1, 0, 0);
	draw_sprite(buffer, Ground.Tree, scrx / 2 - 27, scry - 150);
	//User1 stats
	alfont_textprintf_aa_ex(buffer, Ground.arial, 25, 100, BLACK, -1, 
							"Angle: %.0f%c", User1.AngDeg, 176); 
	alfont_textprintf_aa_ex(buffer, Ground.arial, 25, 50, BLACK, -1, 
							"Power: %.0f", User1.v); 
   	//User 2 stats + multiplayer score
   	if (position == 2){
		alfont_textprintf_aa_ex(buffer, Ground.arial, scrx - 100, 100, BLACK, -1,
								 "Angle: %.0f%c", Multi1.AngDeg, 176); 
		alfont_textprintf_aa_ex(buffer, Ground.arial, scrx - 100, 50, BLACK, -1, 
								"Power: %.0f", Multi1.v);
		alfont_set_font_size(Ground.arial, 32); 
		alfont_textprintf_aa_ex(buffer, Ground.arial, scrx/2 - 30, 50, GREEN, -1, 
								"%d  -  %d", score.User1, score.User2);
		alfont_set_font_size(Ground.arial, 16);	
		alfont_textprintf_aa_ex(buffer, Ground.arial, scrx/2 - 50, 10, BLUE, -1, 
								"press 'ESC' to end");
	}
	//single player score + time
	else{
		alfont_textprintf_aa_ex(buffer, Ground.arial, scrx/2, 50, BLACK, -1, 
								"Score: %d", score.User1);
		if (time < 300)
			alfont_textprintf_aa_ex(buffer, Ground.arial, scrx - 50, 50, BLACK, -1, 
								"%ds", msec/1000);
	}
}

int Menu(BITMAP *buffer, ALFONT_FONT *arial, int *time){
	ALFONT_FONT *Title = alfont_load_font("28 Days Later.ttf");//load font
	int position = 3;
	*time = 0;
	while (position == 3){
		while(!(mouse_b & 1)) {
			clear_to_color(buffer, makecol(0, 100, 0));	
			//print mouse
			circlefill(buffer, mouse_x, mouse_y, 3, WHITE); 
			
			//Determine which option to highlight based on mous position
			if (mouse_y < 400)
				position = 1;	
			else if (mouse_y < 550)
				position = 2;
			else
				position = 3;
			
			//Display options	
			alfont_set_font_size(Title, 60);
			alfont_textprintf_aa_ex(buffer, Title, scrx / 2 - 220, 100, RED, -1, 
									"CHARred TANKS"); 
			alfont_set_font_size(Title, 30);
			alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 110, scry/2 - 150, 
									WHITE, -1, "SINGLE PLAYER"); 	
			alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 100, scry/2, WHITE, -1, 
									"TWO PLAYER");
			alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 90, scry/2 + 150, 
									WHITE, -1, "CONTROLS");
			
			//Highlight option depending on where mouse is
			alfont_set_font_size(arial, 30);
			if (position == 1)
				alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 110, 
										scry / 2 - 145, RED, -1, "____________"); 
			else if (position == 2)
				alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 100, 
										scry / 2 + 5, RED, -1, "__________");
			else if (position == 3){
				alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 90, 
										scry / 2 + 155, RED, -1, "________");
			}	
				
			blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
		}
		rest(200);//prevent sticky mouse
		if (position == 1)
				*time = SingleMenu(buffer, arial);	
		else if (position == 3)
			Control();
	}	
	return position;
}
void Control(){
	BITMAP *Control = load_bitmap("Control.bmp", NULL);	
	draw_sprite(screen, Control, 0, 0);
	while (!key[KEY_ESC]) {}
}

int SingleMenu(BITMAP *buffer, ALFONT_FONT *arial){
	//Single player game mode menu
	ALFONT_FONT *Title = alfont_load_font("28 Days Later.ttf");//load font
	int position;
	
	while(!(mouse_b & 1)) {
		clear_to_color(buffer, makecol(0, 100, 0));	
		
		circlefill(buffer, mouse_x, mouse_y, 3, WHITE); //print mouse
		
		//determine which option to underline
		if (mouse_y < 400)
			position = 60;	
		else if (mouse_y < 550)
			position = 120;
		else
			position = 300;
		
		//print options	
		alfont_set_font_size(Title, 60);
		alfont_textprintf_aa_ex(buffer, Title, scrx / 2 - 150, 100, RED, -1, 
								"Select Level"); 
		alfont_set_font_size(Title, 30);
		alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 110, scry/2 - 150, WHITE, -1, 
								"1 MINUTE RUSH"); 	
		alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 100, scry/2, WHITE, -1, 
								"2 MINUTE RUSH");
		alfont_textprintf_aa_ex(buffer, Title, scrx/2 - 120, scry/2 + 150, WHITE, -1, 
								"PLAY UNTIL YOU DIE");
		
		//underline option
		alfont_set_font_size(arial, 30);
		if (position == 60)
			alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 110, scry / 2 - 145, 
									RED, -1, "__________"); 
		else if (position == 120)
			alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 100, scry / 2 + 5, 
									RED, -1, "___________");
		else if (position == 300)
			alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 120, scry / 2 + 155, 
									RED, -1, "_______________");	
	
		blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
	}
	
	return position;
}
bool end(Score score, int position, ALFONT_FONT *arial, BITMAP *buffer){
	//Declaring variables
	char ReadName[10][30] = {""}, Name[30] = ""; 
	int l = 0, x = 5, ReadScore[10] = {0}, win = 0;
	bool worst = true, again;
	
	clear_keybuf();//prevents key's pressed in game from showing in HS table
	
	//read in High score text file
	FILE*Hscore;
	Hscore = fopen("High Score.DoNotEdit", "r");
	while (fscanf(Hscore, "%s %d", ReadName[l], &ReadScore[l]) != EOF && l < 10){
          l++;
	}
	fclose(Hscore);

	//determines user's place in High score table
	for (int j = 0; j < 9; j++){
		if (score.User1 > ReadScore[j] && worst){
			win = j;	
			worst = false;	
		}
	}
	if (worst)
		win = l;
	
	//shift contents of array if user beats a high score
	for (int j = 9; j > win; j--){
			ReadScore[j] = ReadScore[j-1];
			strcpy(ReadName[j], ReadName[j-1]);		
	}
	//gives value to user's place in high score table
	ReadScore[win] = score.User1;
	strcpy(ReadName[win], "          ");	

	int i;
	//high score screen for single player
	if (position == 1){
		//single player end screen (high score)
		clear_to_color(buffer, BLACK);
		alfont_set_font_size(arial, 30);
		alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 120, 100, RED, -1, 
									"Enter Name:"); 
		blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
		
		rest(2000);//wait for user to stop pressing key
		while (key[KEY_UP] || key[KEY_DOWN] || key[KEY_LEFT] || key[KEY_RIGHT]){}
		clear_keybuf();
		while (!key[KEY_ENTER]){
			//Game over / high score screen
			clear_to_color(buffer, BLACK);
			alfont_set_font_size(arial, 120);
			alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 320, 100, RED, -1, 
									"GAME OVER"); 
			alfont_set_font_size(arial, 30);
	
			//input
			if (!key[KEY_BACKSPACE] && !key[KEY_ENTER] && !key[KEY_ESC] && i < 30)		
				ReadName[win][i] = readkey();
			
			//print high score (highlight users score + name)	
			for (int j = 0, x = 5; j < (l + 1); j++, x++){
				if (j == win){
				alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 120, (50 * x), 
					RED, -1, "%-10s%5d", ReadName[j], ReadScore[j]);}
				else{
				alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 120, (50 * x), 
					WHITE, -1, "%-10s%5d", ReadName[j], ReadScore[j]);}
			}
			
			//press backspace to delete last character and move vursor back 1
			if (key[KEY_BACKSPACE]){
				rest(50);
				ReadName[win][i-1] = ' ';
				ReadName[win][i] = ' ';
				if (i > 0)
					i--;	
			}
			//move cursor forward by 1
			if (keypressed && !key[KEY_BACKSPACE])
				i++;
		
			alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 320, scry - 100, RED, 
									-1, "press enter to continue"); 
		
			blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
		}
		
		ReadName[win][i] = ' ';//prevents printing of ENTER key
    	Hscore = fopen("High Score.DoNotEdit", "w");
    	for (int j = 0; j < l + 1; j++)
			fprintf(Hscore, "%s %d\n", ReadName[j], ReadScore[j]);
		fclose(Hscore);
	}
	else{
		//Multiplayer end screen
		clear_to_color(buffer, BLACK);
		alfont_set_font_size(arial, 120);
		alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 320, 100, RED, -1, 
								"GAME OVER"); 
		alfont_set_font_size(arial, 30);
		
		//Print who won (or tie)
		if (score.User1 > score.User2)
			alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 75, 400, BLUE, -1, 
									"User 1 wins"); 
		else if (score.User1 < score.User2)
			alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 75, 400, RED, -1, 
									"User 2 wins"); 
		else
			alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 25, 400, WHITE, -1, 
									"Tie");
		
		//print final score
		alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 110, scry/2 + 150, 
			WHITE, -1, "Final score: %d    %d", score.User1, score.User2);
		
		alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 320, scry - 100, RED, 
									-1, "press enter to continue"); 
			
		blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
	}
	while(!key[KEY_ENTER]) {}//pause
	
	while(!(mouse_b & 1)) {//while not click
		clear_to_color(buffer, BLACK);	
		circlefill(buffer, mouse_x, mouse_y, 3, WHITE); //print mouse
		//determine which option to underline
		if (mouse_y < scry / 2)
			again = true;	
		else if (mouse_y > scry / 2)
			again = false;
		 
		//print options
		alfont_set_font_size(arial, 30);
		alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 110, scry / 2 - 150, 
								WHITE, -1, "PLAY AGAIN"); 	
		alfont_textprintf_aa_ex(buffer, arial, scrx/2 - 60, scry / 2 + 150, 
								WHITE, -1, "EXIT");
		
		//print underline under option that mouse is hovering over
		if (again == true)
			alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 110, scry / 2 - 145,
									 RED, -1, "___________"); 
		else if (again == false)
			alfont_textprintf_aa_ex(buffer, arial, scrx / 2 - 60, scry / 2 + 155,
									 RED, -1, "____");	
	
		blit(buffer, screen, 0,0,0,0, scrx, scry);//write to buffer
	}
	return again;
}
