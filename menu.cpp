#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include "menu.hpp"
#include "player.hpp"

int change_colour(sf::RenderWindow & window)
{
	sf::Texture menuTexture;
	menuTexture.loadFromFile("images/color.jpg");
	sf::Sprite menu1(menuTexture);
	bool isMenu = true;
	bool exit = false;
	int menuNum = 0;
	menu1.setScale(0.88, 0.88);
	menu1.setPosition(0, 0);
	
	sf::Image play_image;
	play_image.loadFromFile("images/all_colors.jpg");
 	Player player(play_image, 0, 0, 352, 352);
	player.sprite.setScale(1, 1);
	player.sprite.setPosition(300, 50);
	
	while(isMenu)
	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}		
		window.clear();
		
		if (sf::IntRect(104, 482, 91, 91).contains(sf::Mouse::getPosition(window))){
			player.sprite.setTextureRect(sf::IntRect(0, 0, 352, 352));
			menuNum = 1;
			exit = true;
		}
		if (sf::IntRect(254, 482, 91, 91).contains(sf::Mouse::getPosition(window))){
			player.sprite.setTextureRect(sf::IntRect(383, 0, 352, 352));
			menuNum = 2;
			exit = true;
		}
		if (sf::IntRect(404, 482, 91, 91).contains(sf::Mouse::getPosition(window))){
			player.sprite.setTextureRect(sf::IntRect(766, 0, 352, 352));
			menuNum = 3;
			exit = true;
		}
		if (sf::IntRect(554, 482, 91, 91).contains(sf::Mouse::getPosition(window))){
			player.sprite.setTextureRect(sf::IntRect(1149, 0, 352, 352));
			menuNum = 4;
			exit = true;
		}
		if (sf::IntRect(704, 482, 91, 91).contains(sf::Mouse::getPosition(window))){
			player.sprite.setTextureRect(sf::IntRect(1532, 0, 352, 352)); 
			menuNum = 5;
			exit = true;
		}
		
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))&&(exit))
			isMenu = false;
		
		window.draw(menu1);
		window.draw(player.sprite);
		window.display();
	}
	return menuNum;
}

int menu(sf::RenderWindow & window) 
{
	sf::Texture menuTexture;
	menuTexture.loadFromFile("images/menu.jpg");
	sf::Sprite menu1(menuTexture);
	bool isMenu = true;
	int menuNum = 0;
	int colour = 0;
	menu1.setScale(0.88, 0.88);
	menu1.setPosition(0, 0);
	
	while(isMenu)
	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}		
		window.clear();
		
		if (sf::IntRect(340, 388, 224, 94).contains(sf::Mouse::getPosition(window))) 
			menuNum = 1;
		if (sf::IntRect(340, 526, 224, 94).contains(sf::Mouse::getPosition(window)))
			menuNum = 2;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (menuNum == 1){
				colour = change_colour(window);
				isMenu = false;
				return colour;
			}
			if (menuNum == 2) {
				isMenu = false;
				window.close();			
			}
		}
		
		window.draw(menu1);
		window.display();
	}
}

int lose_menu(sf::RenderWindow & window, int chet)
{
	sf::Font font;
	font.loadFromFile("123.ttf");
	sf::Text text("", font, 50);
	text.setStyle(sf::Text::Bold);
	std::ifstream fin("record.txt", std::ios_base::in|std::ios_base::out|std::ios_base::binary);
	
	sf::Image lose_menu_image;
	lose_menu_image.loadFromFile("images/lose_menu.png");
	sf::Texture l_menu;
	l_menu.loadFromImage(lose_menu_image);
	sf::Sprite lose_sp;
	lose_sp.setTexture(l_menu);
	lose_sp.setScale(0.7, 0.7);
	lose_sp.setPosition(chet+350, 350);
	
	std::wostringstream playerScore;
	std::wostringstream record;
	bool isMenu = true;
	int menuNum = 0;
	playerScore << chet;
	char get_file[10];
	fin.getline(get_file, 10);
	record << get_file;
	fin.close();
	
	int recor = atoi(get_file);
	if(chet > recor){
		std::ofstream out("record.txt", std::ios_base::out|std::ios_base::binary);
		out << chet;
		out.close();
	}
	
	std::wstring str = L"Итоговый счет: " + playerScore.str();
	std::wstring rec = L"Рекорд: " + record.str();
		
	while(isMenu)
	{
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		text.setString(str);
		text.setPosition(chet+220, 150);
		window.draw(text);		
		text.setString(rec);
		text.setPosition(chet+330, 220);
		window.draw(text);
		
		if (sf::IntRect(350, 350, 240, 94).contains(sf::Mouse::getPosition(window)))
			menuNum = 1;
		if (sf::IntRect(350, 490, 240, 94).contains(sf::Mouse::getPosition(window)))
			menuNum = 2;
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if (menuNum == 1){
				fin.close();
				isMenu = false;
				return 1;
			}
			if (menuNum == 2){
				isMenu = false;			
			}
		}
		
		window.draw(lose_sp);
		window.display();
	}
	
	fin.close();
	return 2;
}