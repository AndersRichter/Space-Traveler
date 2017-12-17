#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <chrono>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "map.hpp"
#include "view.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include "menu.hpp"
#include "asteroid.hpp"
#include "game.hpp"

#define LENGH_ASTER 104
#define BORT 92
#define START_ZAP 500

int id_menu = 2;
int colour = 0;

void set_rand(sf::String Asteroid[])
{
	int x, y;
	std::default_random_engine generator(
		(unsigned long) std::chrono::system_clock::now().time_since_epoch().count()
		);	
	std::uniform_int_distribution<int> distribution1 (0, 9);
	std::uniform_int_distribution<int> distribution2 (0, 4);
	
	for (int i = 0; i < COUNT_LINE; i++)
		for (int j = 0; j < COUNT_ASTER; j++)
			Asteroid[i][j] = ' ';
	
	for (int i = 0; i < 15; i++){
		x = distribution1(generator);
		y = distribution2(generator);
		Asteroid[y][x] = 's';
	}
}

bool intersection(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2)
{
	float v1, v2, v3, v4;
	v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
   	v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
  	v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
  	v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
	bool inter = ((v1*v2 < 0) && (v3*v4 < 0));
	return inter;
}

int startGame()
{
	sf::Music music;	//создаем объект музыки
	music.openFromFile("nintendo.ogg");	//загружаем файл
	//music.setVolume(80);
	music.play(); 	//воспроизводим музыку
	
	sf::SoundBuffer shootBuffer;//создаём буфер для звука
	shootBuffer.loadFromFile("piu.ogg");//загружаем в него звук
	sf::Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера
	//shoot.setVolume(10000);
	
	sf::SoundBuffer vzrBuffer;
	vzrBuffer.loadFromFile("vzr.ogg");
	sf::Sound vzr(vzrBuffer);
	//vzr.setVolume(10000);

	music.setLoop(true);
	
	sf::RenderWindow window(sf::VideoMode(900, 696), "Space Traveler");
	if (id_menu == 2) colour = menu(window);//вызов меню
	id_menu = 0;
	
	sf::Clock clock;
	
	sf::String file;
	switch(colour){
		case(1):{
			file = "images/3_red.png";
			break;
		}
		case(2):{
			file = "images/3_yellow.png";
			break;
		}
		case(3):{
			file = "images/3_blue.png";
			break;
		}
		case(4):{
			file = "images/3_green.png";
			break;
		}
		case(5):{
			file = "images/3_purple.png";
			break;
		}
	}
	
	sf::Image play_image;
	play_image.loadFromFile(file);
 	Player player(play_image, 5, 296, 352, 352);
	
	sf::Image bullet_image;
	bullet_image.loadFromFile("images/bullet.png");
	Bullet bull(bullet_image, 0, 0, 100, 100);
	
	view.reset(sf::FloatRect(0, 0, 900, 696));	//размер вида камеры
	
	sf::Image map_image;	//объект изображения для карты
	map_image.loadFromFile("images/3_map.jpg");	//файл для карты
	sf::Texture map;	//текстура карты
	map.loadFromImage(map_image);	//зарядка текстуры картинкой
	sf::Sprite s_map;	//создание спрайта для карты
	s_map.setTexture(map);	//заливка текстуры спрайтом
	
	sf::Image panel_image;
	sf::Image heart_image;
	sf::Image gun_image;
	panel_image.loadFromFile("images/panel.jpg");
	heart_image.loadFromFile("images/heart.png");
	gun_image.loadFromFile("images/gun.png");
	sf::Texture panel;
	sf::Texture heart;
	sf::Texture gun;
	panel.loadFromImage(panel_image);
	heart.loadFromImage(heart_image);
	gun.loadFromImage(gun_image);
	sf::Sprite s_panel;
	sf::Sprite s_heart;
	sf::Sprite s_gun;
	s_panel.setTexture(panel);
	s_heart.setTexture(heart);
	s_gun.setTexture(gun);
	s_panel.setScale(0.4, 0.4);
	s_heart.setScale(0.06,0.06);
	s_gun.setScale(0.28, 0.28);
	
	sf::Font font;
	font.loadFromFile("123.ttf");
	sf::Text text("", font, 25);
	text.setStyle(sf::Text::Bold);
	
	sf::Image aster_image;
	aster_image.loadFromFile("images/aster.png");
	sf::Texture aster;
	aster.loadFromImage(aster_image);
	sf::Sprite s_aster;
	s_aster.setTexture(aster);
	s_aster.setScale(0.37, 0.37);
	
	long double chet = 0;
	int povtor = 1;
	int mapx = 0;
	int ch1 = 1;
	int ch2 = 0;
	int uskor = 1000;
	bool isShot = false;
	int lifes = 3;
	double shot_time = 0;
	bool shot_anable = false;
	s_gun.setTextureRect(sf::IntRect(241, 0, 241, 114));
	
	set_rand(Asteroid1);
	set_rand(Asteroid2);
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		float time_map;
		float time_player;
		
		shot_time += time/1000;
		if(shot_time > 3000){
			shot_time = 0;
			shot_anable = true;
			s_gun.setTextureRect(sf::IntRect(0, 0, 241, 114));
		}
		
		clock.restart(); //перезагружает время
		if (uskor > 350)
			time_map = time/uskor;
		else
			time_map = time/350;//скорость игры
		time_player = time/500; //скорость игрока
		
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		std::wostringstream playerScore;
		playerScore << (int)chet;
		std::wstring str = playerScore.str();
		text.setString(str);
		text.setPosition(view.getCenter().x - 110, view.getCenter().y - 327);
		
		s_panel.setPosition(view.getCenter().x - 440, view.getCenter().y - 345);
		s_heart.setPosition(view.getCenter().x - 405, view.getCenter().y - 327);
		s_gun.setPosition(view.getCenter().x - 260, view.getCenter().y - 330);
		
		player.control(chet);
		
		if (player.get_x() <= chet+10)
		{
			player.speed(0) = 0.1;
			player.update(time_map);
		}
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space))&&(!isShot)&&(shot_anable)){
 			isShot = true;
			shot_anable = false;
			s_gun.setTextureRect(sf::IntRect(241, 0, 241, 114));
			shoot.play();
			bull.x = player.get_x() + 70;
			bull.y = player.get_y() + 40;
		}		
		if (isShot){
			bull.sprite.setTextureRect(sf::IntRect(0, 0, 900, 800));			
			bull.speed = 0.14;
			bull.update(time_player*2);
		}		
		if (bull.x > chet+910){  
			isShot = false;
			bull.sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));			
		}
		
		
		player.update(time_player);
		
		window.setView(view);	//"оживление" камеры
		window.clear();	
		camera_move(chet);
		
		for (int i = 0; i < WIDTH_MAP; i++){
			if (TileMap[i] == 's') s_map.setTextureRect(sf::IntRect(0, 0, 619, 696));
			if (TileMap[i] == 'p') s_map.setTextureRect(sf::IntRect(619, 0, 619, 696));
			if (TileMap[i] == 'i') s_map.setTextureRect(sf::IntRect(1238, 0, 619, 696));			
			s_map.setPosition(i * 619 + mapx*619*WIDTH_MAP, 0);
			window.draw(s_map);
		}
		if(chet > 619*WIDTH_MAP + 619*WIDTH_MAP*mapx)
			mapx++;
		
		for (int i = 0; i < COUNT_LINE; i++)
			for (int j = 0; j < COUNT_ASTER; j++)
			{
				if (Asteroid1[i][j] == 's')
				{
					bool flag = false;
					s_aster.setTextureRect(sf::IntRect(0, 0, 273, 273));
					boost::numeric::ublas::matrix<float> aster = create_matrix_aster(j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch1) + 400, i * LENGH_ASTER + 80);
					boost::numeric::ublas::matrix<float> zvezd = player.create_matrix_zvezd(player.get_x(), player.get_y());
					
					for (int iz = 0; iz < 10; iz++)
						for(int ia = 0; ia < 8; ia++)
						{
							if(intersection(zvezd(iz,0), zvezd(iz,1), zvezd(iz,2), zvezd(iz,3), aster(ia,0), aster(ia,1), aster(ia,2), aster(ia,3)))
							{
								flag = true;
								Asteroid1[i][j] = ' ';
								vzr.play();
								s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
								lifes--;
								break;
							}
							if (flag) break;
						}
					if ((bull.x > j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch1) + 400)&&(bull.x < j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch1) + LENGH_ASTER + 400)&&(bull.y > i * LENGH_ASTER + 80)&&(bull.y < i * LENGH_ASTER + 80 + LENGH_ASTER))
					{
						Asteroid1[i][j] = ' ';
						vzr.play();
						s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
						isShot = false;
						bull.sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
					}
					
				}
				if (Asteroid1[i][j] == ' ')
					s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
				s_aster.setPosition(j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch1) + 400, i * LENGH_ASTER + BORT);
				window.draw(s_aster);
			}
			
		for (int i = 0; i < COUNT_LINE; i++)
			for (int j = 0; j < COUNT_ASTER; j++)
			{
				if (Asteroid2[i][j] == 's')
				{
					bool flag = false;
					s_aster.setTextureRect(sf::IntRect(0, 0, 273, 273));				
					boost::numeric::ublas::matrix<float> aster = create_matrix_aster(j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch2) + 400, i * LENGH_ASTER + 80);
					boost::numeric::ublas::matrix<float> zvezd = player.create_matrix_zvezd(player.get_x(), player.get_y());
					
					for (int iz = 0; iz < 10; iz++)
						for(int ia = 0; ia < 8; ia++)
						{
							if(intersection(zvezd(iz,0), zvezd(iz,1), zvezd(iz,2), zvezd(iz,3), aster(ia,0), aster(ia,1), aster(ia,2), aster(ia,3)))
							{
								flag = true;
								Asteroid2[i][j] = ' ';
								vzr.play();
								s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
								lifes--;
								break;
							}
							if (flag) break;
						}
					
					if ((bull.x > j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch2) + 400)&&(bull.x < j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch2) + LENGH_ASTER + 400)&&(bull.y > i * LENGH_ASTER + 80)&&(bull.y < i * LENGH_ASTER + 80 + LENGH_ASTER))
					{
						Asteroid2[i][j] = ' ';
						vzr.play();
						s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
						isShot = false;
						bull.sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
					}					
				}
				if (Asteroid2[i][j] == ' ')
					s_aster.setTextureRect(sf::IntRect(0, 0, 30, 30));
				s_aster.setPosition(j * LENGH_ASTER + COUNT_ASTER*LENGH_ASTER*(ch2) + 400, i * LENGH_ASTER + BORT);
				window.draw(s_aster);
			}
		
		if (lifes == 2){
			player.sprite.setTextureRect(sf::IntRect(386, 0, 352, 352));
			s_heart.setTextureRect(sf::IntRect(0, 0, 1022, 467));
		}
		if (lifes == 1){
			player.sprite.setTextureRect(sf::IntRect(762, 0, 352, 352));
			s_heart.setTextureRect(sf::IntRect(0, 0, 511, 467));
		}
		
		if (chet > COUNT_ASTER*LENGH_ASTER*povtor+400){
			srand(time);
			povtor++;
			uskor -= 50;
			if (povtor % 2 == 0){
				set_rand(Asteroid2);
				ch2 +=2;
			}
			else{
				set_rand(Asteroid1);
				ch1 +=2;
			}
		}
		
		if (lifes <= 0)
			s_heart.setTextureRect(sf::IntRect(0, 0, 30, 30));
		
		window.draw(bull.sprite);
		window.draw(player.sprite);
		window.draw(s_panel);
		window.draw(s_heart);
		window.draw(s_gun);
		window.draw(text);
		window.display();
			
		chet += 0.1*time_map;
		
		if (lifes <= 0){
			id_menu = lose_menu(window, chet);
			return 1;
		}
	}
}

void gameRunning(){		////если startGame() == true, то вызов заново ф-ции isGameRunning, которая в свою очередь опять вызывает startGame()
	if (startGame() == 1) {
		gameRunning(); 
	}		 
}
