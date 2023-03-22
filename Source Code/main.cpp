#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<Windows.h>
#include<GL/glut.h>
int stop_flag = 0, move_flag = 0, f = 0;
float h1 = 249, h2 = 251, v1 = 20, v2 = 40;
int m1 = 50, m2 = 150, m3 = 250, m4 = 450, initial = 0;
int count = 0, j2 = 7, j3 = count;								//j2 denotes no of arrows to be displayed initially
int xm, ym, xmin, ymin;											//Values to draw the gun during motion
int choose = 0, choice0 = 0, choice1 = 0, choice2 = 0, choice3 = 0, prev_choice = 0;
int xglobal;													//x value in move function
int b1 = 1;														//initial gun display variable
int play_flag = 0, run_flag = 0, disp_flag = 0;
int reset_flag = 0;
int pause_flag = 0, instr_flag = 1;
int p0_x1max, p0_x2max, p0_x1min, p0_x2min, p1_x1max, p1_x2max, p1_x1min, p1_x2min, p2_x1max, p2_x2max, p2_x1min, p2_x2min, p3_x1max, p3_x2max, p3_x1min, p3_x2min;
int p4_x1max, p4_x2max, p4_x1min, p4_x2min, p5_x1max, p5_x2max, p5_x1min, p5_x2min, p6_x1max, p6_x2max, p6_x1min, p6_x2min, p7_x1max, p7_x2max, p7_x1min, p7_x2min;
int p8_x1max, p8_x2max, p8_x1min, p8_x2min;
int points_x, points = 0;
int z = 0, bg, counter = 0;										//z is index to c;bg1 for background1,counter to slow down background change
float p[4][2] = { { 0, 0 }, { 0, 500 }, { 500, 500 }, { 500, 0 } };
float c0[3] = { 0.3, 0.2, 0.1 };
float c1[3] = { 0.1, 0.3, 0.2 };
float c2[3] = { 0.2, 0.3, 0.1 };
float c3[3] = { 0.1, 0.2, 0.3 };
char str[20];
int release_count = 0, arrow_count = 4;
size_t i;
char k1;
int mode_flag = 0;
int cover_flag = 0, load_flag = 0;
void display1();
void instructions();
void reset_flags();
void front_display();
void mode_selection();
int yht;
int begin_flag = 1;

/*	stop_flag=1 when left click of button is released. Draws line nd release position of gun
	run_flag=0 when the board is moving initially when mouse has not yet been pressed
	play_flag=1 when play button has been pressed
	move_flag=1 when we start gun movement after left click down */

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}
void mytimer(int v)
{
	counter++;
	if (bg == 1 && counter == 100) {
		if (z < 3) {
			c0[z] += 0.1;
			c1[z] += 0.1;
			c2[z] += 0.1;
			c3[z] += 0.1;
			z++;
			if (c0[z] > 1)
				c0[z] = 0.1;
			if (c1[z] > 1)
				c1[z] = 0.1;
			if (c2[z] > 1)
				c2[z] = 0.1;
			if (c3[z] > 1)
				c3[z] = 0.1;
		}
		else
			z = 0;
		if (counter == 100)
			counter = 0;
	}
	if (stop_flag != 1 && run_flag != 0 && pause_flag == 0) {

		if (choose == 0)										//indicates left to right board movement
		{
			choice0++;
			m1++; m2--; m3++;
			if (m1 > 500)
				m1 = 50, m2 = 150, m3 = 250, count++;
			glutTimerFunc(5, mytimer, 20);
			glutPostRedisplay();
		}
		if (choose == 1)										//indicates right to left board movement
		{
			choice1++;
			m1 = m4;
			m1--; m2++; m3--, m4--;
			if (m1 < 0)
				m1 = m4 = 450, m2 = 150, m3 = 250, count++;
			glutTimerFunc(5, mytimer, 20);
			glutPostRedisplay();
		}
		if (choose == 2)										//indicates right-to-left top-to-down board movement
		{
			choice2++;
			m1 = m4;
			if (m3 > 150)
				m1--, m2--, m3--, m4--;
			else
				m1--, m2 += 2, m4--;

			if (m1 < 240)
				m1--, m3++, m2 -= 2, m4--;


			if (m1 < 70)
				m1--, m2 += 2, m3 += 5, m4--;

			if (m1 < 0)
				m1 = 450, m2 = 150, m3 = 250, m4 = 450;
			glutTimerFunc(5, mytimer, 5);
			glutPostRedisplay();
		}
		if (choose == 3)										//indicates left-to-right top-to-down board movement
		{
			choice3++;
			if (m1 < 150)
				m1++, m2--, m3--;
			else
				m1++, m2 += 2;

			if (m1 > 270)
				m1++, m2 -= 5;

			if (m1 > 440)
				m1++, m2 += 5;

			if (m1 > 500)
				m1 = 50, m2 = 150, m3 = 250;
			glutTimerFunc(5, mytimer, 5);
			glutPostRedisplay();
		}
	}
	if (run_flag == 0 && pause_flag == 0) {

		if (choose == 0)										//indicates left to right board movement
		{
			choice0++;
			m1++; m2--; m3++;
			if (m1 > 500)
				m1 = 50, m2 = 150, m3 = 250, count++;
			glutPostRedisplay();
		}
		if (choose == 1)										//indicates right to left board movement
		{
			choice1++;
			m1 = m4;
			m1--; m2++; m3--, m4--;
			if (m1 < 0)
				m1 = 450, m2 = 150, m3 = 250, m4 = 450, count++;
			glutPostRedisplay();
		}
		if (choose == 2)										//indicates right-to-left top-to-down board movement
		{
			choice2++;
			m1 = m4;

			if (m3 > 150)
				m1--, m2--, m3--, m4--;
			else
				m1--, m2 += 2, m4--;

			if (m1 < 240)
				m1--, m3++, m2 -= 2, m4--;


			if (m1 < 70)
				m1--, m2 += 2, m3 += 5, m4--;

			if (m1 < 0)
				m1 = 450, m2 = 150, m3 = 250, m4 = 450;

			glutPostRedisplay();
		}
		if (choose == 3)										//indicates left-to-right top-to-down board movement
		{
			choice3++;
			if (m1 < 150)
				m1++, m2--, m3--;
			else
				m1++, m2 += 2;

			if (m1 > 270)
				m1++, m2 -= 5;

			if (m1 > 440)
				m1++, m2 += 5;

			if (m1 > 500)
				m1 = 50, m2 = 150, m3 = 250;

			glutPostRedisplay();
		}
	}

}

void paused()
{
	size_t k;
	char str4[20] = "PAUSED";
	glColor3f(1, 1, 1);
	glRasterPos2i(230, 250);
	for (k = 0; k < strlen(str4); k++)							//displays message that the game is paused
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str4[k]);
	glutSwapBuffers();
	glFlush();
}
void mykey(unsigned char k, int x, int y)
{
	char str3[] = "!EXIT APPLICATION";
	char str5[] = "Do you really want to quit?";
	char str6[] = "Y            N";
	size_t j;

	if (mode_flag == 1)
	{															//set bg based on user input
		if (k == '1')
			bg = 1;
		else if (k == '2')
			bg = 2;
		else if (k == '3')
			bg = 3;
		mode_flag = 0;
		play_flag = 2;
		glutPostRedisplay();
	}


	if (k == 'P' || k == 'p')
	{															//game is paused upon pressing 'p' or 'P'
		pause_flag = 1;
		paused();
	}
	else if (k == 'Q' || k == 'q')
	{															//to quit the game upon pressing 'q' or 'Q'
		glColor3f(1, 1, 1);
		glRasterPos2i(200, 260);
		for (j = 0; j < strlen(str3); j++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str3[j]);
		glRasterPos2i(200, 240);
		for (j = 0; j < strlen(str5); j++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str5[j]);
		glRasterPos2i(225, 215);
		for (j = 0; j < strlen(str6); j++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str6[j]);
		glutSwapBuffers();
		glFlush();
		pause_flag = 1;
		k1 = k;

	}
	else if ((k1 == 'Q' || k1 == 'q') && (k == 'Y' || k == 'y')) {

		stop_flag = 0, move_flag = 0, f = 0;
		h1 = 249, h2 = 251, v1 = 20, v2 = 40;
		m1 = 50, m2 = 150, m3 = 250, count = 0;
		xm, ym, xmin, ymin;										//Values to draw the gun during motion
		xglobal;												//x value in move function
		b1 = 1;													//initial gun display variable
		play_flag = 0, run_flag = 0, disp_flag = 0;
		reset_flag = 0;
		pause_flag = 0, instr_flag = 1;
		counter = 0;
		j2 = 6, j3 = count, points = 0, z = 0, release_count = 0;

		Sleep(100);
		glutPostRedisplay();
	}
	else if (k != 'P' || k != 'p') {
		pause_flag = 0;
		glutPostRedisplay();
	}
}
void mode_selection() {
	char mode_str[] = "SELECT MODE        PRESS";
	char mode_str1[] = "  DYNAMIC                  1";
	char mode_str2[] = "  CLASSIC                    2";
	char mode_str3[] = " GREY WAVE              3";
	size_t j;
	mode_flag = 1;
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	glColor3f(0.7, 0.4, 0.5);
	glVertex2f(0, 0);
	glColor3f(0.1, 0.1, 0.3);
	glVertex2f(0, 500);
	glColor3f(0.45, 0.56, 0.78);
	glVertex2f(500, 500);
	glColor3f(0.56, 0.6, 0.8);
	glVertex2f(500, 0);
	glEnd();
	//asks the player to input the mode in which he wishes to play
	glColor3f(0.8, 0.8, 0.8);
	glRasterPos2i(200, 380);
	for (j = 0; j < strlen(mode_str); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mode_str[j]);
	glRasterPos2i(200, 300);
	for (j = 0; j < strlen(mode_str1); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mode_str1[j]);
	glRasterPos2i(200, 220);
	for (j = 0; j < strlen(mode_str2); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mode_str2[j]);
	glRasterPos2i(200, 140);
	for (j = 0; j < strlen(mode_str3); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mode_str3[j]);
	play_flag = 0;
	glutSwapBuffers();
	glFlush();
}
void mymouse(int b, int s, int x, int y)
{

	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
	{
		if (play_flag == 0)
			if ((x < 728) && (x > 621) && (y > 364) && (y < 402))	//user is asked to chose among three modes
			{
				instr_flag = 0;
				mode_selection();
			}
		if (instr_flag == 1)									//instructions are displayed
		{
			if ((x < 781) && (x > 567) && (y > 429) && (y < 469))
				instr_flag = 2;
			instructions();
		}

		if (instr_flag == 2)
		{
			if ((x > 620) && (y > 492) && (x < 727) && (y < 530)) {
				instr_flag = 0;
				mode_selection();
			}
		}

		if (play_flag == 2)
		{
			b1 = 0;
			run_flag = 1;
			glutTimerFunc(5, mytimer, 20);
			xm = 0;
			ym = 20;
			f = 1;
			glColor3f(1, 0, 0);
			glLogicOp(GL_XOR);
		}
	}
	if (b == GLUT_LEFT_BUTTON && s == GLUT_UP)
	{
		if (play_flag == 1)
			play_flag = 2;

		if (play_flag == 2)
		{
			stop_flag = 1;
			display1();
			release_count++;
		}
	}
	if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)				//on right click program terminates
		exit(0);
}
void move(int x, int y)
{
	if (pause_flag == 0) {
		b1 = 0;
		move_flag = 1;
		glutPostRedisplay();
		xglobal = x;
		if (xglobal > 400) {
			xglobal = 400;
		}
		if (xglobal < 100) {
			xglobal = 100;
		}
	}
}

void front_display()
{
	size_t i;
	char str1[20] = "PLAY", str2[20] = "INSTRUCTIONS";

	if (play_flag == 0)
	{															//used to display name of the game and buttons
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_POLYGON);									//displays the letter 'B'
		glColor3f(0.3, 0.5, 0.5);
		glVertex2f(0, 0);
		glColor3f(0.9, 0.9, 0.9);
		glVertex2f(0, 500);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(500, 500);
		glColor3f(0.75, 0.6, 0.8);
		glVertex2f(500, 0);
		glEnd();

		glLineWidth(5);

		glBegin(GL_TRIANGLES);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(135, 400);
		glColor3f(0.2, 0.1, 0.1);
		glVertex2f(135, 350);
		glColor3f(0.3, 0.3, 0.2);
		glVertex2f(160, 375);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(135, 400);
		glColor3f(0.2, 0.1, 0.1);
		glVertex2f(135, 450);
		glColor3f(0.3, 0.3, 0.2);
		glVertex2f(160, 425);
		glEnd();

		glBegin(GL_LINE_STRIP);									//displays the letter 'U'
		glColor3f(0.15, 0.1, 0.13);
		glVertex2f(165, 425);
		glColor3f(0.2, 0.21, 0.22);
		glVertex2f(165, 350);
		glColor3f(0.13, 0.14, 0.16);
		glVertex2f(185, 350);
		glColor3f(0.25, 0.25, 0.25);
		glVertex2f(185, 425);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(195, 425);
		glColor3f(0.15, 0.15, 0.15);
		glVertex2f(195, 350);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(210, 350);
		glEnd();

		glBegin(GL_LINE_STRIP);									//displays the letter 'L'
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(215, 425);
		glColor3f(0.15, 0.15, 0.15);
		glVertex2f(215, 350);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(235, 350);
		glEnd();

		glBegin(GL_LINE_STRIP);									//displays the letter 'L'
		glColor3f(0.25, 0.25, 0.25);
		glVertex2f(240, 335);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(260, 375);
		glColor3f(0.7, 0.7, 0.7);
		glVertex2f(240, 400);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(260, 440);
		glEnd();

		glBegin(GL_LINES);										//displays the letter 'S'
		glColor3f(0.75, 0.75, 0.75);
		glVertex2f(236, 335);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(257, 380);
		glColor3f(0.3, 0.35, 0.35);
		glVertex2f(243, 395);
		glColor3f(0.1, 0.15, 0.2);
		glVertex2f(262, 434);
		glEnd();

		glBegin(GL_LINE_STRIP);									//displays the letter 'E'
		glColor3f(0.1, 0.15, 0.12);
		glVertex2f(290, 350);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(270, 350);
		glColor3f(0.27, 0.27, 0.27);
		glVertex2f(270, 425);
		glColor3f(0.3, 0.29, 0.33);
		glVertex2f(290, 425);
		glEnd();

		glBegin(GL_LINES);										//displays the letter 'Y'
		glVertex2f(270, 387);
		glColor3f(0.25, 0.25, 0.25);
		glVertex2f(285, 387);
		glColor3f(0.33, 0.33, 0.33);
		glVertex2f(300, 350);
		glColor3f(0.12, 0.12, 0.12);
		glVertex2f(330, 425);
		glColor3f(0.4, 0.4, 0.4);
		glVertex2f(300, 425);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(315, 387);
		glEnd();

		glBegin(GL_LINE_STRIP);									//displays the letter 'E'
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(355, 350);
		glColor3f(0.25, 0.25, 0.25);
		glVertex2f(335, 350);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(335, 425);
		glColor3f(0.19, 0.19, 0.19);
		glVertex2f(355, 425);
		glEnd();

		glBegin(GL_LINES);
		glVertex2f(335, 387);
		glVertex2f(350, 387);
		glEnd();

		glColor3f(0.25, 0.25, 0.25);							//displays the play button
		glBegin(GL_POLYGON);
		glVertex2f(230, 210);
		glVertex2f(270, 210);
		glVertex2f(270, 240);
		glVertex2f(230, 240);
		glEnd();

		glColor3f(0.25, 0.25, 0.25);							//displays the instruction button
		glBegin(GL_POLYGON);
		glVertex2f(210, 162);
		glVertex2f(290, 162);
		glVertex2f(290, 193);
		glVertex2f(210, 193);
		glEnd();

		glColor3f(0, 1, 1);
		glRasterPos2i(238, 218);
		for (i = 0; i < strlen(str1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]);

		glRasterPos2i(218, 170);
		for (i = 0; i < strlen(str2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[i]);
	}
}

void reset_flags()
{																//to reset all the flags after the game
	reset_flag = 0;
	stop_flag = 0;
	run_flag = 0;
	move_flag = 0;
	b1 = 1;
}
void instructions()
{
	char instr1[] = "1. Hit the target to score points by holding left mouse button. Release the button to shoot.";
	char instr2[] = "2. You have only 6 arrows.";
	char instr3[] = "3. Arrows decrease if you fail to shoot or miss the board.";
	char instr4[] = "4. Press 'p' to pause, any key to resume.";
	char instr5[] = "5. Press 'q' to quit.";
	char instr6[] = "LET'S SEE HOW FAR YOU CAN GO !!!";
	char str[] = "PLAY";
	int i, n1;
	size_t j;

	glClearColor(0.3, 0.3, 0.3, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawBuffer(GL_BACK);

	for (i = 0; i < 6; i++)										//creates a display for  instructions page
	{
		glColor3f(0.2, 0.2, 0.2);
		n1 = 83.34 + 83.34 * i;

		glBegin(GL_QUADS);
		glVertex2f(n1 - 83.4, 0);
		glColor3f(0.25, 0.25, 0.25);
		glVertex2f(n1, 0);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(n1, 500);
		glColor3f(0.15, 0.15, 0.15);
		glVertex2f(n1 - 83.4, 500);
		glEnd();

	}
	glColor3f(1, 1, 1);

	glRasterPos2i(100, 350);									//displays instructions describing how to play the game
	for (j = 0; j < strlen(instr1); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr1[j]);

	glRasterPos2i(100, 320);
	for (j = 0; j < strlen(instr2); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr2[j]);

	glRasterPos2i(100, 290);
	for (j = 0; j < strlen(instr3); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr3[j]);

	glRasterPos2i(100, 260);
	for (j = 0; j < strlen(instr4); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr4[j]);

	glRasterPos2i(100, 230);
	for (j = 0; j < strlen(instr5); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr5[j]);

	glRasterPos2i(175, 170);
	for (j = 0; j < strlen(instr6); j++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instr6[j]);

	glColor3f(0, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex2f(230, 120);
	glVertex2f(230, 150);
	glVertex2f(270, 150);
	glVertex2f(270, 120);
	glEnd();

	glColor3f(0.9, 0.9, 0.25);
	glRasterPos2i(239, 129);
	for (j = 0; j < strlen(str); j++)							//indicates the play button 
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[j]);

	glutSwapBuffers();
	glFlush();
	//	PlaySound(TEXT("30"), NULL, SND_ALIAS);						//used to play sound when instructions page is opened
}
void background_display()
{																//displays appropriate background on the mode selected
	if (bg == 1)												//dynamic mode
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POLYGON);
		glColor3f(c0[0], c0[1], c0[2]);
		glVertex2fv(p[0]);
		glColor3f(c1[0], c1[1], c1[2]);
		glVertex2fv(p[1]);
		glColor3f(c2[0], c2[1], c2[2]);
		glVertex2fv(p[2]);
		glColor3f(c3[0], c3[1], c3[2]);
		glVertex2fv(p[3]);
		glEnd();
	}
	if (bg == 3)												//classic mode
	{
		int i = 0, j = 0;;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(0, 700);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(1350, 700);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(1350, 0);
		glEnd();
	}
	if (bg == 2)												//gray wave
	{
		int i = 0, j = 0;
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(0.4, 0.3, 0.3);
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glColor3f(0.2, 0.2, 0.2);
		glVertex2f(0, 700);
		glColor3f(0.1, 0.1, 0.1);
		glVertex2f(1350, 700);
		glColor3f(0.3, 0.3, 0.3);
		glVertex2f(1350, 0);
		glEnd();
	}
}
void gun_display()
{
	if (b1 == 1)
	{															//Initial display of Gun
		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(h1, v1);
		glVertex2f(h1, v2);
		glVertex2f(h2, v2);
		glVertex2f(h2, v1);
		glVertex2f(h1 - 10, v1);
		glVertex2f(h1 - 10, v1 + 5);
		glVertex2f(h2 + 10, v1 + 5);
		glVertex2f(h2 + 10, v1);
		glEnd();
	}

}
void board_movement()
{
	float r2 = 12, r3 = 18, theta, x1, x2, y1, y2, thetar, r4 = 24, r5 = 30, r1 = 6, r6 = 36, r7 = 42, r8 = 48, r9 = 0, r10 = 54;

	glColor3f(0, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)					//to draw the board or target
	{
		thetar = theta * 3.14 / 180;
		x1 = r9 * cos(thetar) + m1;
		y1 = r9 * sin(thetar) + m3;
		x2 = r1 * cos(thetar) + m1;
		y2 = r1 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			yht = y1 + m2;
			p0_x1max = x1;
			p0_x2max = x2;
		}
		if (theta == 180) {
			p0_x1min = x1;
			p0_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r1 * cos(thetar) + m1;
		y1 = r1 * sin(thetar) + m3;
		x2 = r2 * cos(thetar) + m1;
		y2 = r2 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p1_x1max = x1;
			p1_x2max = x2;
		}
		if (theta == 180) {
			p1_x1min = x1;
			p1_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r2 * cos(thetar) + m1;
		y1 = r2 * sin(thetar) + m3;
		x2 = r3 * cos(thetar) + m1;
		y2 = r3 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p2_x1max = x1;
			p2_x2max = x2;
		}
		if (theta == 180) {
			p2_x1min = x1;
			p2_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r3 * cos(thetar) + m1;
		y1 = r3 * sin(thetar) + m3;
		x2 = r4 * cos(thetar) + m1;
		y2 = r4 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p3_x1max = x1;
			p3_x2max = x2;
		}
		if (theta == 180) {
			p3_x1min = x1;
			p3_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r4 * cos(thetar) + m1;
		y1 = r4 * sin(thetar) + m3;
		x2 = r5 * cos(thetar) + m1;
		y2 = r5 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p4_x1max = x1;
			p4_x2max = x2;
		}
		if (theta == 180) {
			p4_x1min = x1;
			p4_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r5 * cos(thetar) + m1;
		y1 = r5 * sin(thetar) + m3;
		x2 = r6 * cos(thetar) + m1;
		y2 = r6 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p5_x1max = x1;
			p5_x2max = x2;
		}
		if (theta == 180) {
			p5_x1min = x1;
			p5_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r6 * cos(thetar) + m1;
		y1 = r6 * sin(thetar) + m3;
		x2 = r7 * cos(thetar) + m1;
		y2 = r7 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p6_x1max = x1;
			p6_x2max = x2;
		}
		if (theta == 180) {
			p6_x1min = x1;
			p6_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r7 * cos(thetar) + m1;
		y1 = r7 * sin(thetar) + m3;
		x2 = r8 * cos(thetar) + m1;
		y2 = r8 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p7_x1max = x1;
			p7_x2max = x2;
		}
		if (theta == 180) {
			p7_x1min = x1;
			p7_x2min = x2;
		}
	}
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	for (theta = 0; theta <= 360; theta += 10)
	{
		thetar = theta * 3.14 / 180;
		x1 = r8 * cos(thetar) + m1;
		y1 = r8 * sin(thetar) + m3;
		x2 = r10 * cos(thetar) + m1;
		y2 = r10 * sin(thetar) + m3;

		glVertex2f(x1, y1 + m2);
		glVertex2f(x2, y2 + m2);

		if (theta == 0) {
			p8_x1max = x1;
			p8_x2max = x2;
		}
		if (theta == 180) {
			p8_x1min = x1;
			p8_x2min = x2;
		}
	}
	glEnd();
}
void display_points(int n1, int n2)
{
	char str1[20], str2[] = "POOR SHOT!!!!";
	size_t i;

	if ((n1 != 0) && (n2 != 0))
	{
		if (bg == 1)
			glColor3f(1, 1, 0);
		if (bg == 2)
			glColor3f(0, 0.8, 0.8);
		if (bg == 3)
			glColor3f(0.8, 1, 1);
		_itoa_s(n1, str1, 10);
		glRasterPos2i(n2 + 2, yht + 55);						//yht=410
		for (i = 0; i < strlen(str1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]);//Display points on board after each hit
	}
	if ((n1 == 0) && (n2 == 0))
	{
		glColor3f(1, 1, 1);
		glRasterPos2i(225, 480);
		for (i = 0; i < strlen(str2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[i]);//indicates player aimed a poor shot
	}

	glFlush();
}
void points_calculation()
{
	char str1[] = "BULLSEYE!!!!!";
	int n1 = 0, n2 = 0;

	if (stop_flag == 1)											//stop_flag = 1 when left click of button is released
	{
		if ((points_x >= p0_x2min && points_x <= p0_x1min) || (points_x >= p0_x1max && points_x <= p0_x2max))
		{
			points += 45;
			n1 = 45;
			n2 = p0_x2min + 3;
			glColor3f(1, 1, 1);
			glRasterPos2i(225, 480);
			for (i = 0; i < strlen(str1); i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str1[i]);//'BULLSEYE!!!' display on hitting centre
			display_points(n1, n2);										//to display points

		}
		else if ((points_x >= p1_x2min && points_x <= p1_x1min) || (points_x >= p1_x1max && points_x <= p1_x2max))
		{
			points += 40;
			n1 = 40;
			n2 = p1_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p2_x2min && points_x <= p2_x1min) || (points_x >= p2_x1max && points_x <= p2_x2max))
		{
			points += 35;
			n1 = 35;
			n2 = p2_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p3_x2min && points_x <= p3_x1min) || (points_x >= p3_x1max && points_x <= p3_x2max))
		{
			points += 30;
			n1 = 30;
			n2 = p3_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p4_x2min && points_x <= p4_x1min) || (points_x >= p4_x1max && points_x <= p4_x2max))
		{
			points += 25;
			n1 = 25;
			n2 = p4_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p5_x2min && points_x <= p5_x1min) || (points_x >= p5_x1max && points_x <= p5_x2max))
		{
			points += 20;
			n1 = 20;
			n2 = p5_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p6_x2min && points_x <= p6_x1min) || (points_x >= p6_x1max && points_x <= p6_x2max))
		{
			points += 15;
			n1 = 15;
			n2 = p6_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p7_x2min && points_x <= p7_x1min) || (points_x >= p7_x1max && points_x <= p7_x2max))
		{
			points += 10;
			n1 = 10;
			n2 = p7_x2min + 3;
			display_points(n1, n2);
		}
		else if ((points_x >= p8_x2min && points_x <= p8_x1min) || (points_x >= p8_x1max && points_x <= p8_x2max))
		{
			points += 5;
			n1 = 5;
			n2 = p8_x2min + 3;
			display_points(n1, n2);
		}
		else
		{
			points += 0;
			n1 = 0;
			n2 = 0;
			display_points(n1, n2);
		}
	}
	glColor3f(0.25, 0.25, 0.25);								//Top Right Corner Button
	glBegin(GL_POLYGON);
	glVertex2f(450, 460);
	glVertex2f(450, 495);
	glVertex2f(485, 495);
	glVertex2f(485, 460);
	glEnd();

	glColor3f(1, 0.99, 0.23);
	glRasterPos2i(462, 470);
	_itoa_s((points), str, 10);
	for (i = 0; i < strlen(str); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);//Display of points

}
void gun_movement()
{
	if (move_flag == 1) {
		if (f == 0) {
			glBegin(GL_POLYGON);
			glVertex2f(xmin, ymin);
			glVertex2f(xmin + 2, ymin);
			glVertex2f(xmin + 2, ymin + 20);
			glVertex2f(xmin, ymin + 20);
			glEnd();
			glFlush();
		}
		xmin = xglobal;
		ymin = 20;
		glLogicOp(GL_XOR);

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymin + 20);
		glVertex2f(xmin + 2, ymin + 20);
		glVertex2f(xmin + 2, ymin);
		glVertex2f(xmin - 10, ymin);
		glVertex2f(xmin - 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin);
		glEnd();
		glFlush();
		f = 0;
	}															//Rubber band movement of Mouse - Drawing gun during motion

	if (stop_flag == 1) {
		glLogicOp(GL_XOR);
		glBegin(GL_POLYGON);
		glColor3f(0.6, 0.9, 0.1);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymin + 20);
		glVertex2f(xmin + 2, ymin + 20);
		glVertex2f(xmin + 2, ymin);
		glVertex2f(xmin - 10, ymin);
		glVertex2f(xmin - 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin);
		glEnd();

		glLogicOp(GL_COPY);
		glBegin(GL_POLYGON);
		glVertex2f(xmin, ymin);
		glVertex2f(xmin, ymin + 20);
		glVertex2f(xmin + 2, ymin + 20);
		glVertex2f(xmin + 2, ymin);
		glVertex2f(xmin - 10, ymin);
		glVertex2f(xmin - 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin + 5);
		glVertex2f(xmin + 2 + 10, ymin);
		glEnd();


		glColor3f(1, 0, 0);										//Drawing Vertical Line
		glBegin(GL_LINES);
		glVertex2f(xmin + 1, ymin + 20);
		glVertex2f(xmin + 1, yht);								//yht=ymin+20+360
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(xmin + 1, yht);
		glVertex2f(xmin + 1 - 4, yht - 20);
		glVertex2f(xmin + 1, yht - 10);
		glVertex2f(xmin + 1 + 4, yht - 20);
		glEnd();


		points_x = xmin + 1;
		reset_flag = 1;
		disp_flag = 1;
	}															//Drawing gun on release
}
void arrows_display(int j2)
{
	int i, i1 = 350;

	glColor3f(0.25, 0.25, 0.25);								//displays the box containing arrows
	glBegin(GL_POLYGON);
	glVertex2f(343, 470);
	glVertex2f(343, 493);
	glVertex2f(413, 493);
	glVertex2f(413, 470);
	glEnd();

	glColor3f(1, 0.15, 0.15);
	glLineWidth(1);												//indicates the arrow line width



	for (i = 0; i < j2; i++)									//displays the arrows remaining
	{
		glBegin(GL_LINES);
		glVertex2f(i1, 490);
		glVertex2f(i1, 470);
		glEnd();
		glBegin(GL_TRIANGLES);
		glVertex2f(i1, 490);
		glVertex2f(i1 - 5, 480);
		glVertex2f(i1, 484);
		glVertex2f(i1, 490);
		glVertex2f(i1 + 5, 480);
		glVertex2f(i1, 484);
		glEnd();
		i1 = i1 + 11;
	}
}
void loading()
{
	int k;
	int umin = 150, umax = 350, vmin = 40, vmax = 60;
	char loadstr[] = "Loading.....";
	glColor3f(1, 1, 1);
	glRasterPos2i(226, 80);
	for (i = 0; i < strlen(loadstr); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, loadstr[i]);

	load_flag = 1;
	glDrawBuffer(GL_FRONT);
	glColor3f(0, 0.2, 0);
	glBegin(GL_POLYGON);
	glVertex2f(umin, vmin);
	glVertex2f(umin, vmax);
	glVertex2f(umax, vmax);
	glVertex2f(umax, vmin);
	glEnd();

	glColor3f(0, 0.7, 0);
	if (begin_flag == 1) {
		k = umin;
		begin_flag = 0;
	}
	while (k <= umax - 10) {
		glBegin(GL_POLYGON);
		glVertex2f(k, vmin);
		glVertex2f(k, vmax);
		glVertex2f(k + 10, vmax);
		glVertex2f(k + 10, vmin);
		glEnd();
		k = k + 10;

		glFlush();
		Sleep(400);
	}

}
int cover_pg()
{
	char cvstr1[] = "DONE BY";
	char cvstr2[] = "SHANTANU";
	char cvstr3[] = "SUMITH";
	if (load_flag == 0)
	{
		glDrawBuffer(GL_FRONT);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 1, 1);
		glRasterPos2i(230, 400);
		for (i = 0; i < strlen(cvstr1); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cvstr1[i]);
		glRasterPos2i(220, 330);
		for (i = 0; i < strlen(cvstr2); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cvstr2[i]);
		glRasterPos2i(190, 290);
		for (i = 0; i < strlen(cvstr3); i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cvstr3[i]);

		glFlush();
	}
	loading();

	return 1;
}
void display1()
{
	char g_over[] = "GAME OVER!!!", score[] = "YOUR SCORE = ", str3[20];
	size_t j = 0;
	int stop = 0;

	if (cover_flag == 0)
		cover_flag = cover_pg();

	if (cover_flag == 1)
	{
		glDrawBuffer(GL_BACK);
		front_display();
	}
	glLineWidth(3);

	if (play_flag == 2 && instr_flag == 0)
	{

		glDrawBuffer(GL_BACK);

		background_display();

		gun_display();											//displays the gun

		if (run_flag == 0)
			glutTimerFunc(4, mytimer, 20);

		if (m1 <= 1 || m1 >= 500 || initial == 0)				//checks if the board is out of bound
		{
			initial = 1;
			prev_choice = choose;
			do {
				choose = rand() % 4;							//randomly selects one of the movement 
			} while (choose == prev_choice);

			if (choose == 0 || choose == 3)						//redefine boundary values
				m1 = 50, m2 = 150, m3 = 250;
			if (choose == 1 || choose == 2)
				m1 = 450, m2 = 150, m3 = 250;

		}
		board_movement();										//to draw the board

		if (count == j3 + 1) {									//calculates number of arrows remaining
			if (release_count == 0)
			{
				j2--;
				j3 = count;
			}
			else
			{
				j2 = j2 - release_count + 1;
			}
			arrow_count = j2;
			if (arrow_count < 1)
				arrow_count = 0;
		}

		stop = 6 - release_count;
		arrows_display(stop);									//displays the arrows remaining 
		gun_movement();											//displays the gun used to shoot 

		points_calculation();									//calculates points scored by the player

		if ((stop == 0) || (count >= 7))							//checks if all the six arrows are used and displays score of the player
		{
			glClearColor(0.3, 0.3, 0.2, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glColor3f(1, 0.8, 0.6);

			glRasterPos2i(220, 350);
			glColor3f(0.1, 0.5, 0.4);
			for (j = 0; j < strlen(g_over); j++)				//displays the message game over
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, g_over[j]);

			glRasterPos2i(215, 310);

			for (j = 0; j < strlen(score); j++)					//displays the score obtained by the user
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, score[j]);
			glColor3f(1, 0, 0);
			glRasterPos2i(282, 310);
			_itoa_s(points, str3, 10);
			glColor3f(0.5, 0.8, 0.9);
			for (j = 0; j < strlen(str3); j++)					//displays the message "YOUR SCORE"
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str3[j]);

			glFlush();
			count++;

			if (count > 7)										//if no more arrows are available, reset flags in the program for new game
			{
				//PlaySound(TEXT("10"), NULL, SND_ALIAS);			//plays sound indicated by the argument passed to TEXT
				play_flag = 0;
				run_flag = 0;
				disp_flag = 0;
				reset_flag = 0;
				pause_flag = 0;
				instr_flag = 1;
				stop_flag = 0;
				move_flag = 0;
				f = 0, h1 = 249, h2 = 251, v1 = 20, v2 = 40;
				m1 = 50, m2 = 150, m3 = 250, m4 = 450, count = 0;
				j2 = 7, j3 = count, b1 = 1, points = 0, z = 0, initial = 0, counter = 0;
				choice0 = 0, choice1 = 0, choice2 = 0, choice3 = 0, prev_choice = 0;
				release_count = 0;
			}

		}
	}

	glutSwapBuffers();
	glFlush();

	if (reset_flag == 1)
	{
		Sleep(1000);
		reset_flags();
	}
}

int main()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1350, 700);
	glEnable(GL_COLOR_LOGIC_OP);								//to apply logical operations
	glutCreateWindow("BULLSEYE");
	myinit();
	glutDisplayFunc(display1);
	glutMouseFunc(mymouse);										//initialize mouse function
	glutKeyboardFunc(mykey);									//initialize keyboard function	
	glutMotionFunc(move);
	glutMainLoop();
}