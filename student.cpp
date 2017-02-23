
#include "ground.h"

#include <windows.h>


//************************************************************
//    this function will be called approximately 50 times a second
//
//    input_info:
//    contains the info wehre the mouse is and what keys or button are pressed
//    for the definition, right click on "input" in the argument list and click "go to definition"
//
//    draw_text ( CHARACTERARRAY, X-COORDINATE, Y-COORDINATE, RED,GREEN, BLUE); //color values between 0 and 255!
//
//    draw_line ( FROM X-COORDINATE, FROM Y-COORDINATE, TO X-COORDINATE, TO Y-COORDINATE, RED,GREEN, BLUE, WIDTH); //color values between 0 and 255! WIDTH .. in pixel
//
//    draw_pixel( X-COORDINATE, Y-COORDINATE, RED, GREEN, BLUE, PERMANENT);//color values between 0 and 255! PERMANENT: 0..temporary, 1..permanent
//
//**********************************************************
#define Start 0
#define gamebreak1 1
#define gameplay 2
#define gamebreak2 3
#define gamebreak3 4
#define gamebreak4 5
#define gamebreak5 6
#define Lose 7
int gf[500][500];


void draw_main(input input_info)
{
	static int lives1 = 3;
	static int lives2 = 3;
	char live1[100], live2[100];


	static int game = Start;
	if (game == Start)
	{
		draw_text("PLAY PLAY THE GAME", 175, 100, 0, 0, 0);
		draw_line(200, 200, 300, 200, 0, 0, 0, 2);
		draw_line(200, 150, 300, 150, 0, 0, 0, 2);
		draw_line(200, 150, 200, 200, 0, 0, 0, 2);
		draw_line(300, 150, 300, 200, 0, 0, 0, 2);
		draw_text("START", 230, 165, 0, 0, 0);
	}
	if (input_info.l_button_down && (input_info.x_mouse >= 200 && input_info.x_mouse <= 300))
	{
		if (input_info.l_button_down && (input_info.y_mouse >= 150 && input_info.y_mouse <= 200))
		{
			game = gameplay;
		}
	}
	if (game == Lose)
	{
		if (lives1 == 0 && lives2 != 0)
		{
			draw_text("PLAYER 1 LOSES", 175, 100, 0, 0, 0);
			draw_text("PLAYER 2 WINS", 175, 150, 0, 0, 0);
		}
		if (lives2 == 0 && lives1 != 0)
		{
			draw_text("PLAYER 2 LOSES", 175, 100, 0, 0, 0);
			draw_text("PLAYER 1 WINS", 175, 150, 0, 0, 0);
		}
		if (lives2 == 0 && lives1 == 0)
		{
			draw_text("TIE", 225, 100, 0, 0, 0);
			draw_text("GAME", 200, 150, 0, 0, 0);
		}
	}
	if (game == gameplay)
	{
		{
			//gamefield
			static int yo = 1;

			while (yo == 1)
			{
				for (int aa = 0; aa < 500; aa++)
					for (int bb = 0; bb < 500; bb++)
						gf[aa][bb] = 0;
				yo = 0;
			}

			//Lives
			sprintf(live1, "Player 1: %d", lives1);
			sprintf(live2, "Player 2: %d", lives2);
			draw_text(live1, 20, 20, 0, 0, 0);
			draw_text(live2, 400, 20, 0, 0, 0);


			//Starting positions
			//Player 1:
			static int playerpos_x = 100;
			static int playerpos_y = 250;

			//Player 2:
			static int x = 400;
			static int y = 250;

			//set
			//player 1
			gf[playerpos_x][playerpos_y] = 1;

			//player 2
			gf[x][y] = 1;

			//direction code
			//Player 1
			static int d = 3;
			if (d == 0)
				playerpos_y--;
			if (d == 1)
				playerpos_x--;
			if (d == 2)
				playerpos_y++;
			if (d == 3)
				playerpos_x++;

			//Player 2:
			static int e = 1;
			if (e == 0)
				y--;
			if (e == 1)
				x--;
			if (e == 2)
				y++;
			if (e == 3)
				x++;


			//user input for direction
			//Player 1
			if (input_info.w_key_down)
				if (d != 2)     //Allows for not doubling back
					d = 0;
			if (input_info.a_key_down)
				if (d != 3)
					d = 1;
			if (input_info.s_key_down)
				if (d != 0)
					d = 2;
			if (input_info.d_key_down)
				if (d != 1)
					d = 3;


			//Player 2
			if (input_info.up_cursor_down)
				if (e != 2)
					e = 0;
			if (input_info.left_cursor_down)
				if (e != 3)
					e = 1;
			if (input_info.down_cursor_down)
				if (e != 0)
					e = 2;
			if (input_info.right_cursor_down)
				if (e != 1)
					e = 3;


			//Collision Detection (Developed in 3 steps: Set, Move, check)
			//check


			//Player 1
			if (lives1 == 0)
			{
				game = Lose;
			}
			if (gf[playerpos_x][playerpos_y] == 1)
			{
				lives1--;
				game = gamebreak1;
			}
			if (playerpos_x == -4)
			{
				lives1--;
				game = gamebreak1;
			}
			if (playerpos_x == 504)
			{
				lives1--;
				game = gamebreak1;
			}
			if (playerpos_y == -4)
			{
				lives1--;
				game = gamebreak1;
			}
			if (playerpos_y == 504)
			{
				lives1--;
				game = gamebreak1;
			}

			//Player 2
			if (gf[x][y] == 1)
			{
				lives2--;
				game = gamebreak1;
			}
			if (x == -4)
			{
				lives2--;
				game = gamebreak1;
			}
			if (x == 504)
			{
				lives2--;
				game = gamebreak1;
			}
			if (y == -4)
			{
				lives2--;
				game = gamebreak1;
			}
			if (x == 504)
			{
				lives2--;
				game = gamebreak1;
			}
			/*
			CODE FOR PLAYER NAMES
			*/
			//Player 1:
			char text[100];
			strcpy(text, "Player 1");

			gf[playerpos_x][playerpos_y] = 1;
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					if (gf[aa][bb] == 1)
					{
						draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
					}
				}

			//player 2
			char Name2[100];
			strcpy(Name2, "Player 2");

			gf[x][y] = 1;
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					if (gf[aa][bb] == 1)
					{
						draw_text(Name2, x, y, 153, 0, 76);
					}
				}


			//drawing function
			//Player 1
			draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
			//Player 2
			draw_pixel(x, y, 255, 0, 0, 1);
		}
	}


	if (game == gamebreak1)
	{
		static int yo = 1;

		while (yo == 1)
		{
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					gf[aa][bb] = 0;
					draw_pixel(aa, bb, 255, 255, 255, 1);
				}
			yo = 0;
		}

		//Lives
		sprintf(live1, "Player 1: %d", lives1);
		sprintf(live2, "Player 2: %d", lives2);
		draw_text(live1, 20, 20, 0, 0, 0);
		draw_text(live2, 400, 20, 0, 0, 0);


		//Starting positions
		//Player 1:
		static int playerpos_x = 100;
		static int playerpos_y = 250;

		//Player 2:
		static int x = 400;
		static int y = 250;

		//set
		//player 1
		gf[playerpos_x][playerpos_y] = 1;

		//player 2
		gf[x][y] = 1;

		//direction code
		//Player 1
		static int d = 3;
		if (d == 0)
			playerpos_y--;
		if (d == 1)
			playerpos_x--;
		if (d == 2)
			playerpos_y++;
		if (d == 3)
			playerpos_x++;

		//Player 2:
		static int e = 1;
		if (e == 0)
			y--;
		if (e == 1)
			x--;
		if (e == 2)
			y++;
		if (e == 3)
			x++;


		//user input for direction
		//Player 1
		if (input_info.w_key_down)
			if (d != 2)     //Allows for not doubling back
				d = 0;
		if (input_info.a_key_down)
			if (d != 3)
				d = 1;
		if (input_info.s_key_down)
			if (d != 0)
				d = 2;
		if (input_info.d_key_down)
			if (d != 1)
				d = 3;


		//Player 2
		if (input_info.up_cursor_down)
			if (e != 2)
				e = 0;
		if (input_info.left_cursor_down)
			if (e != 3)
				e = 1;
		if (input_info.down_cursor_down)
			if (e != 0)
				e = 2;
		if (input_info.right_cursor_down)
			if (e != 1)
				e = 3;


		//Collision Detection (Developed in 3 steps: Set, Move, check)
		//check


		//Player 1
		if (lives1 == 0)
		{
			game = Lose;
		}
		if (gf[playerpos_x][playerpos_y] == 1)
		{
			lives1--;
			game = gamebreak2;
		}
		if (playerpos_x == -4)
		{
			lives1--;
			game = gamebreak2;
		}
		if (playerpos_x == 504)
		{
			lives1--;
			game = gamebreak2;
		}
		if (playerpos_y == -4)
		{
			lives1--;
			game = gamebreak2;
		}
		if (playerpos_y == 504)
		{
			lives1--;
			game = gamebreak2;
		}

		//Player 2
		if (lives2 == 0)
		{
			game = Lose;
		}
		if (gf[x][y] == 1)
		{
			lives2--;
			game = gamebreak2;
		}
		if (x == -4)
		{
			lives2--;
			game = gamebreak2;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak2;
		}
		if (y == -4)
		{
			lives2--;
			game = gamebreak2;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak2;
		}
		/*
		CODE FOR PLAYER NAMES
		*/
		//Player 1:
		char text[100];
		strcpy(text, "Player 1");

		gf[playerpos_x][playerpos_y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
				}
			}

		//player 2
		char Name2[100];
		strcpy(Name2, "Player 2");

		gf[x][y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(Name2, x, y, 153, 0, 76);
				}
			}


		//drawing function
		//Player 1
		draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
		//Player 2
		draw_pixel(x, y, 255, 0, 0, 1);
	}

	if (game == gamebreak2)
	{
		static int yo = 1;

		while (yo == 1)
		{
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					gf[aa][bb] = 0;
					draw_pixel(aa, bb, 255, 255, 255, 1);
				}
			yo = 0;
		}

		//Lives
		sprintf(live1, "Player 1: %d", lives1);
		sprintf(live2, "Player 2: %d", lives2);
		draw_text(live1, 20, 20, 0, 0, 0);
		draw_text(live2, 400, 20, 0, 0, 0);


		//Starting positions
		//Player 1:
		static int playerpos_x = 100;
		static int playerpos_y = 250;

		//Player 2:
		static int x = 400;
		static int y = 250;

		//set
		//player 1
		gf[playerpos_x][playerpos_y] = 1;

		//player 2
		gf[x][y] = 1;

		//direction code
		//Player 1
		static int d = 3;
		if (d == 0)
			playerpos_y--;
		if (d == 1)
			playerpos_x--;
		if (d == 2)
			playerpos_y++;
		if (d == 3)
			playerpos_x++;

		//Player 2:
		static int e = 1;
		if (e == 0)
			y--;
		if (e == 1)
			x--;
		if (e == 2)
			y++;
		if (e == 3)
			x++;


		//user input for direction
		//Player 1
		if (input_info.w_key_down)
			if (d != 2)     //Allows for not doubling back
				d = 0;
		if (input_info.a_key_down)
			if (d != 3)
				d = 1;
		if (input_info.s_key_down)
			if (d != 0)
				d = 2;
		if (input_info.d_key_down)
			if (d != 1)
				d = 3;


		//Player 2
		if (input_info.up_cursor_down)
			if (e != 2)
				e = 0;
		if (input_info.left_cursor_down)
			if (e != 3)
				e = 1;
		if (input_info.down_cursor_down)
			if (e != 0)
				e = 2;
		if (input_info.right_cursor_down)
			if (e != 1)
				e = 3;


		//Collision Detection (Developed in 3 steps: Set, Move, check)
		//check


		//Player 1
		if (lives1 == 0)
		{
			game = Lose;
		}
		if (gf[playerpos_x][playerpos_y] == 1)
		{
			lives1--;
			game = gamebreak3;
		}
		if (playerpos_x == -4)
		{
			lives1--;
			game = gamebreak3;
		}
		if (playerpos_x == 504)
		{
			lives1--;
			game = gamebreak3;
		}
		if (playerpos_y == -4)
		{
			lives1--;
			game = gamebreak3;
		}
		if (playerpos_y == 504)
		{
			lives1--;
			game = gamebreak3;
		}

		//Player 2
		if (lives2 == 0)
		{
			game = Lose;
		}
		if (gf[x][y] == 1)
		{
			lives2--;
			game = gamebreak3;
		}
		if (x == -4)
		{
			lives2--;
			game = gamebreak3;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak3;
		}
		if (y == -4)
		{
			lives2--;
			game = gamebreak3;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak3;
		}
		/*
		CODE FOR PLAYER NAMES
		*/
		//Player 1:
		char text[100];
		strcpy(text, "Player 1");

		gf[playerpos_x][playerpos_y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
				}
			}

		//player 2
		char Name2[100];
		strcpy(Name2, "Player 2");

		gf[x][y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(Name2, x, y, 153, 0, 76);
				}
			}


		//drawing function
		//Player 1
		draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
		//Player 2
		draw_pixel(x, y, 255, 0, 0, 1);
	}

	if (game == gamebreak3)
	{
		static int yo = 1;

		while (yo == 1)
		{
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					gf[aa][bb] = 0;
					draw_pixel(aa, bb, 255, 255, 255, 1);
				}
			yo = 0;
		}

		//Lives
		sprintf(live1, "Player 1: %d", lives1);
		sprintf(live2, "Player 2: %d", lives2);
		draw_text(live1, 20, 20, 0, 0, 0);
		draw_text(live2, 400, 20, 0, 0, 0);

		//Starting positions
		//Player 1:
		static int playerpos_x = 100;
		static int playerpos_y = 250;

		//Player 2:
		static int x = 400;
		static int y = 250;

		//set
		//player 1
		gf[playerpos_x][playerpos_y] = 1;

		//player 2
		gf[x][y] = 1;

		//direction code
		//Player 1
		static int d = 3;
		if (d == 0)
			playerpos_y--;
		if (d == 1)
			playerpos_x--;
		if (d == 2)
			playerpos_y++;
		if (d == 3)
			playerpos_x++;

		//Player 2:
		static int e = 1;
		if (e == 0)
			y--;
		if (e == 1)
			x--;
		if (e == 2)
			y++;
		if (e == 3)
			x++;


		//user input for direction
		//Player 1
		if (input_info.w_key_down)
			if (d != 2)     //Allows for not doubling back
				d = 0;
		if (input_info.a_key_down)
			if (d != 3)
				d = 1;
		if (input_info.s_key_down)
			if (d != 0)
				d = 2;
		if (input_info.d_key_down)
			if (d != 1)
				d = 3;


		//Player 2
		if (input_info.up_cursor_down)
			if (e != 2)
				e = 0;
		if (input_info.left_cursor_down)
			if (e != 3)
				e = 1;
		if (input_info.down_cursor_down)
			if (e != 0)
				e = 2;
		if (input_info.right_cursor_down)
			if (e != 1)
				e = 3;


		//Collision Detection (Developed in 3 steps: Set, Move, check)
		//check


		//Player 1
		if (lives1 == 0)
		{
			game = Lose;
		}
		if (gf[playerpos_x][playerpos_y] == 1)
		{
			lives1--;
			game = gamebreak4;
		}
		if (playerpos_x == -4)
		{
			lives1--;
			game = gamebreak4;
		}
		if (playerpos_x == 504)
		{
			lives1--;
			game = gamebreak4;
		}
		if (playerpos_y == -4)
		{
			lives1--;
			game = gamebreak4;
		}
		if (playerpos_y == 504)
		{
			lives1--;
			game = gamebreak4;
		}

		//Player 2
		if (lives2 == 0)
		{
			game = Lose;
		}
		if (gf[x][y] == 1)
		{
			lives2--;
			game = gamebreak4;
		}
		if (x == -4)
		{
			lives2--;
			game = gamebreak4;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak4;
		}
		if (y == -4)
		{
			lives2--;
			game = gamebreak4;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak4;
		}
		/*
		CODE FOR PLAYER NAMES
		*/
		//Player 1:
		char text[100];
		strcpy(text, "Player 1");

		gf[playerpos_x][playerpos_y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
				}
			}

		//player 2
		char Name2[100];
		strcpy(Name2, "Player 2");

		gf[x][y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(Name2, x, y, 153, 0, 76);
				}
			}


		//drawing function
		//Player 1
		draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
		//Player 2
		draw_pixel(x, y, 255, 0, 0, 1);
	}


	if (game == gamebreak4)
	{
		static int yo = 1;

		while (yo == 1)
		{
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					gf[aa][bb] = 0;
					draw_pixel(aa, bb, 255, 255, 255, 1);
				}
			yo = 0;
		}

		//Lives
		sprintf(live1, "Player 1: %d", lives1);
		sprintf(live2, "Player 2: %d", lives2);
		draw_text(live1, 20, 20, 0, 0, 0);
		draw_text(live2, 400, 20, 0, 0, 0);

		//Starting positions
		//Player 1:
		static int playerpos_x = 100;
		static int playerpos_y = 250;

		//Player 2:
		static int x = 400;
		static int y = 250;

		//set
		//player 1
		gf[playerpos_x][playerpos_y] = 1;

		//player 2
		gf[x][y] = 1;

		//direction code
		//Player 1
		static int d = 3;
		if (d == 0)
			playerpos_y--;
		if (d == 1)
			playerpos_x--;
		if (d == 2)
			playerpos_y++;
		if (d == 3)
			playerpos_x++;

		//Player 2:
		static int e = 1;
		if (e == 0)
			y--;
		if (e == 1)
			x--;
		if (e == 2)
			y++;
		if (e == 3)
			x++;


		//user input for direction
		//Player 1
		if (input_info.w_key_down)
			if (d != 2)     //Allows for not doubling back
				d = 0;
		if (input_info.a_key_down)
			if (d != 3)
				d = 1;
		if (input_info.s_key_down)
			if (d != 0)
				d = 2;
		if (input_info.d_key_down)
			if (d != 1)
				d = 3;


		//Player 2
		if (input_info.up_cursor_down)
			if (e != 2)
				e = 0;
		if (input_info.left_cursor_down)
			if (e != 3)
				e = 1;
		if (input_info.down_cursor_down)
			if (e != 0)
				e = 2;
		if (input_info.right_cursor_down)
			if (e != 1)
				e = 3;


		//Collision Detection (Developed in 3 steps: Set, Move, check)
		//check


		//Player 1
		if (lives1 == 0)
		{
			game = Lose;
		}
		if (gf[playerpos_x][playerpos_y] == 1)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_x == -4)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_x == 504)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_y == -4)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_y == 504)
		{
			lives1--;
			game = gamebreak5;
		}

		//Player 2
		if (lives2 == 0)
		{
			game = Lose;
		}
		if (gf[x][y] == 1)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == -4)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak5;
		}
		if (y == -4)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == 504)
		{
			lives2--;
			game = gamebreak5;
		}
		/*
		CODE FOR PLAYER NAMES
		*/
		//Player 1:
		char text[100];
		strcpy(text, "Player 1");

		gf[playerpos_x][playerpos_y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
				}
			}

		//player 2
		char Name2[100];
		strcpy(Name2, "Player 2");

		gf[x][y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(Name2, x, y, 153, 0, 76);
				}
			}


		//drawing function
		//Player 1
		draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
		//Player 2
		draw_pixel(x, y, 255, 0, 0, 1);
	}


	if (game == gamebreak5)
	{
		static int yo = 1;

		while (yo == 1)
		{
			for (int aa = 0; aa < 500; aa++)
				for (int bb = 0; bb < 500; bb++)
				{
					gf[aa][bb] = 0;
					draw_pixel(aa, bb, 255, 255, 255, 1);
				}
			yo = 0;
		}

		//Starting positions
		//Player 1:
		static int playerpos_x = 100;
		static int playerpos_y = 250;

		//Player 2:
		static int x = 400;
		static int y = 250;

		//set
		//player 1
		gf[playerpos_x][playerpos_y] = 1;

		//player 2
		gf[x][y] = 1;

		//direction code
		//Player 1
		static int d = 3;
		if (d == 0)
			playerpos_y--;
		if (d == 1)
			playerpos_x--;
		if (d == 2)
			playerpos_y++;
		if (d == 3)
			playerpos_x++;

		//Player 2:
		static int e = 1;
		if (e == 0)
			y--;
		if (e == 1)
			x--;
		if (e == 2)
			y++;
		if (e == 3)
			x++;


		//user input for direction
		//Player 1
		if (input_info.w_key_down)
			if (d != 2)     //Allows for not doubling back
				d = 0;
		if (input_info.a_key_down)
			if (d != 3)
				d = 1;
		if (input_info.s_key_down)
			if (d != 0)
				d = 2;
		if (input_info.d_key_down)
			if (d != 1)
				d = 3;


		//Player 2
		if (input_info.up_cursor_down)
			if (e != 2)
				e = 0;
		if (input_info.left_cursor_down)
			if (e != 3)
				e = 1;
		if (input_info.down_cursor_down)
			if (e != 0)
				e = 2;
		if (input_info.right_cursor_down)
			if (e != 1)
				e = 3;


		//Collision Detection (Developed in 3 steps: Set, Move, check)
		//check


		//Player 1
		if (lives1 == 0)
		{
			game = Lose;
		}
		if (gf[playerpos_x][playerpos_y] == 1)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_x == -1)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_x == 501)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_y == -1)
		{
			lives1--;
			game = gamebreak5;
		}
		if (playerpos_y == 501)
		{
			lives1--;
			game = gamebreak5;
		}

		//Player 2
		if (lives2 == 0)
		{
			game = Lose;
		}
		if (gf[x][y] == 1)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == -1)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == 501)
		{
			lives2--;
			game = gamebreak5;
		}
		if (y == -1)
		{
			lives2--;
			game = gamebreak5;
		}
		if (x == 501)
		{
			lives2--;
			game = gamebreak5;
		}
		/*
		CODE FOR PLAYER NAMES
		*/
		//Player 1:
		char text[100];
		strcpy(text, "Player 1");

		gf[playerpos_x][playerpos_y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(text, playerpos_x, playerpos_y, 0, 76, 153);
				}
			}

		//player 2
		char Name2[100];
		strcpy(Name2, "Player 2");

		gf[x][y] = 1;
		for (int aa = 0; aa < 500; aa++)
			for (int bb = 0; bb < 500; bb++)
			{
				if (gf[aa][bb] == 1)
				{
					draw_text(Name2, x, y, 153, 0, 76);
				}
			}


		//drawing function
		//Player 1
		draw_pixel(playerpos_x, playerpos_y, 0, 0, 255, 1);
		//Player 2
		draw_pixel(x, y, 255, 0, 0, 1);
	}
}