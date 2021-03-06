#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#define _WIN32_WINNT 0x0500 
#include <windows.h> 
#include <iostream> 
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <random>
#include <chrono>

using namespace sf;
using namespace std;

struct point
{
	double x, y;
};


int main()
{
	IntRect rectsource(0, 0, 162, 87);
	int px = 0, py = 0, moony = +10, pxm = 0;
	int platform = 8;
	bool E = false, Q = false;
	srand(time(NULL));
	bool enemyspawned = false;
	bool rocket = false;
	bool rocketspawn = false;
	
	random_device rd;
	long int seed = rd();
	default_random_engine gen(seed);

	Clock clock;
	bool lose = false;
	SoundBuffer buffer1;
	SoundBuffer buffer;
	buffer.loadFromFile("images/jump.wav");
	buffer1.loadFromFile("images/projectile.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	
	
	sf::Music music;
	music.openFromFile("images/pada.wav");
	sf::Music projectile1;
	projectile1.openFromFile("images/projectile.wav");
	
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);// hiding console window i found code on a forum 

	

	RenderWindow app(VideoMode(700, 931), "By Iraj Mohtasham");//creating window
	app.setFramerateLimit(60);//limting fps u can change it to increase or decrease game speed

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, spritesheet, temp;
	

	
t1.loadFromFile("images/background.png");//loading textures
t2.loadFromFile("images/platform.png");
t3.loadFromFile("images/doodlel.png");
t4.loadFromFile("images/lose.png");
t5.loadFromFile("images/enter.png");
t6.loadFromFile("images/rockets.png");
t7.loadFromFile("images/rocket.png");
t8.loadFromFile("images/moon.png");
t10.loadFromFile("images/projectile.png");
t9.loadFromFile("images/nose.png");
t11.loadFromFile("images/jupiter.png");
spritesheet.loadFromFile("images/untitled.png");

Sprite sBackground(t1), sPlat(t2), Doodler(t3), Lose(t4), enter(t5), rockets(t6), Rocket(t7), nose(t9), projectile(t10), moon(t8), jupiter(t11);//making sprits (read on sfml website )
	sBackground.setScale(1.25, 1.25);
	sPlat.setScale(1.75, 1.75);
	Sprite enemysprite(spritesheet, rectsource);
	point plat[20];//an array of x and y inherited by point struct
	
	for (int i = 0; i < platform; i++)
	{	uniform_real_distribution<double> uni_realx(0, 700);
		uniform_real_distribution<double> uni_realy(0, 1050);
		plat[i].x = uni_realx(gen);
		plat[i].y = uni_realy(gen);
		

		}
	//ranomize platform location (needs improvements plz help if u can fix spawning additional platforms)

	int x =300, y = 100, h = 500;//x , y , h(h is a height which when doodles reaches there other platform move down so player thinks its going up)
	float  dy = 0;//it  acts like gravity dy>0 means doodel is going down dy<0 means doodle is going up

	while (app.isOpen())
	{

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}
		if (!lose) {
			
		

			if (x < 640)
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					x += 5.25;//event keypress for player
					if (!Keyboard::isKeyPressed(Keyboard::Space))
					t3.loadFromFile("images/doodler.png");
					E = true;
					Q = false;

				}
			if (x > -20)
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					E = false;
					Q = true;
					x -= 5.25;
					if (!Keyboard::isKeyPressed(Keyboard::Space))
					t3.loadFromFile("images/doodlel.png");
				}
			double chance = 0;
			double chance1 = 0;
		//randomizing objects spawn
			chance = 1 + (std::rand() % (4000 - 1 + 1));
			chance1 = 1 + (std::rand() % (4000 - 1 + 1));
			if (chance ==500)
				rocketspawn = true;
			if (chance1 == 300)
				enemyspawned = true;
			

			if(rocketspawn == true) {
				
				
				if ((x > plat[1].x - 40 && x < plat[1].x + 40) && (y > plat[1].y - 250 && y < plat[1].y + 30)) {
					rocket = true;
					rocketspawn = false;
					//rocket->when doodle is in a rocket rocketspawn->if is spawning
				}
				
			}
			if (!rocket) {
				dy += 0.35;
				y += dy;
				//if in normal mode
			}
			if (rocket) {//if in rocket mode
				dy -= 0.356;
					y += dy;
					if (dy < -70)
						rocket = !rocket;
			
			}
			if (enemyspawned == true) {
				if (plat[3].y > 930)
					enemyspawned = false;
				if ((x > plat[3].x - 110 && x < plat[3].x + 145) && (y > plat[3].y - 210 && y < plat[3].y - 50) && !rocket)//if enemy is hit by doodle
				{
					lose = true;
					enemyspawned = false;
					
				}
			}
			
			
			
		


			if (y < h)//if doodle reaches h
			{//moon goes down +1 
				moony += 1;
				for (int i = 0; i < platform; i++)
				{
					y = h;//prevent farther height increase
					plat[i].y = plat[i].y - dy;
					if (plat[i].y >931)
					{
						plat[i].y = 0;
						uniform_real_distribution<double> uni_realx(20, 700);
						plat[i].x = uni_realx(gen);
					}
				}
			}

			for (int i = 0; i <platform; i++)
				if ((x + 87.5 > plat[i].x&&x < plat[i].x + 84)
					&& (y + 120 > plat[i].y&&y + 70 < plat[i].y + 14) && (dy > 0)) {
					dy = -20;
					sound.play();
					//if doodle hits a platform

				}
		
			moon.setPosition(660, moony);
			jupiter.setPosition(0, moony - 1000);
			app.draw(sBackground);
			app.draw(moon);
			app.draw(jupiter);
			if (!rocket) {//if not rocketed this will draw doodle
				Doodler.setPosition(x, y);
				Rocket.setPosition(4000, 4000);
				app.draw(Doodler);
				if (!enemyspawned)
					enemysprite.setPosition(4000, 4000);
			}
			if (rocket) { // if rocketed this will draw rocket instead of doodler
				Rocket.setPosition(x, y);

				Doodler.setPosition(4000, 4000);
				app.draw(Rocket);
			}
			for (int i = 0; i < platform; i++)
			{//draws platforms
				sPlat.setPosition(plat[i].x, plat[i].y);
				app.draw(sPlat);
			}if (rocketspawn) {//draws rockets(spawn)
				rockets.setPosition(plat[1].x + 20, plat[1].y - 110);
				app.draw(rockets);
			}
			//this piece of code i got from a forum will animate a tile which is in /images/yntitled.png in my game
			if (clock.getElapsedTime().asMilliseconds()>70.0f) {
			if (rectsource.left == 640)
			rectsource.left = 0;
			else
			rectsource.left += 160;

			enemysprite.setTextureRect(rectsource);
			clock.restart();
			}//

		
			if (enemyspawned) {//draws enemy sprite
			enemysprite.setPosition(plat[3].x + 20, plat[3].y - 110);
				app.draw(enemysprite);
			}
			if (enemyspawned) {//deletes enemy if hit by projectile
				if ((px > plat[3].x - 110 && px < plat[3].x + 145) && (py > plat[3].y - 210 && py < plat[3].y - 50) && !rocket)
					enemyspawned = false;
				
			}
			
	if(!rocket)
				if (Keyboard::isKeyPressed(Keyboard::Space)) {
					pxm = 0;//mode 0 nose up
				if (Keyboard::isKeyPressed(Keyboard::Space) && !(Keyboard::isKeyPressed(Keyboard::E)) && !(Keyboard::isKeyPressed(Keyboard::Q)))
					
					if(!(pxm==1||pxm==2))pxm = 0;
				nose.setPosition(x + 49, y + 7);
				
				nose.setRotation(0);
				px = x+45;
				py = y + 10;

					t3.loadFromFile("images/doodles.png");
				if (Keyboard::isKeyPressed(Keyboard::E)) {

					pxm = 1;//mode 1 nose up right
			
					nose.setPosition(x + 75, y + 13);
					nose.setRotation(45);

					px = x+55;
					py = y + 10;
				}	
				if (Keyboard::isKeyPressed(Keyboard::Q)) {
					
					nose.setPosition(x + 20, y + 35);
					nose.setRotation(-45);
					pxm = 2;//mode 2 nose up left
					px = x;
					py = y + 15;
				}
				app.draw(Doodler);
				app.draw(nose);
				projectile1.play();

			}
			
	//resets doodle texture like how it was before shooting
			if (!Keyboard::isKeyPressed(Keyboard::Space))
				if (E == true && Q == false)
					t3.loadFromFile("images/doodler.png");
				else
				{
					t3.loadFromFile("images/doodlel.png");
				}
			py -= 30;
			if (pxm == 1) {
				px +=  25;
			}if (pxm == 2) {
				px -= 25;
			}
			if (pxm == 0) {
				px += 0;
			}
			
				projectile.setPosition(px, py);
				app.draw(projectile);
				
			
				if (y > 1100)
			{//if fall lose =true
				lose = true;
				music.play();

			}

			

			
			
		}
		if (lose) {//luanches when u lose
			
			
			Lose.setScale(1.5, 1.5);
			enter.setScale(1.5, 1.5);
			app.draw(sBackground);
			Lose.setPosition(20, 400);
			enter.setPosition(20, 600);
			app.draw(Lose);
			app.draw(enter);
			
			

			if (moony < 2500)
				moony = -50;

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				lose = false;
				app.clear();
				y = 0;
				dy = -10;
			
				
				
			}
		}
		//

		app.display();
	}
	

	return 0;
}
 //1: x and y is location of CENTER of platform so i have to add 4 statements to add borders of platform to hit statement
//platform spawn is a little buggy help me if u can
//this code was provided by iraj mohtasham u can use it for any purpose 
