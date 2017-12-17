#include <SFML/Graphics.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "player.hpp"

void Player::update(float time) {
	coord = coord + speed*time*2;
	speed(0) = 0;
	speed(1) = 0;
 	sprite.setPosition(coord(0), coord(1));
}
	
float Player::get_x(){
	return coord(0);
}
		
float Player::get_y(){
	return coord(1);
}

void Player::control(float chet){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		speed(0) = -0.1;
		speed(1) = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
		if (get_x() <= chet+770){				
			speed(0) = 0.1;
			speed(1) = 0;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (get_y() > 92){						
			speed(0) = 0;
			speed(1) = -0.1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (get_y() <= 504){					
			speed(0) = 0;
			speed(1) = 0.1;
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
		if (get_y() <= 92){
			speed(0) = -0.1;
			speed(1) = 0;
		}
		else{
			speed(0) = -0.07;
			speed(1) = -0.07;
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) { 
		if (get_y() >= 504){
			speed(0) = -0.1;
			speed(1) = 0;
		}
		else{
			speed(0) = -0.07;
			speed(1) = 0.07;
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){ 
		if ((get_y() < 504)&&(get_x() < 770+chet)){
			speed(0) = 0.07;
			speed(1) = 0.07;
		}
		if ((get_x() >= 770+chet)&&(get_y() < 504)){
			speed(0) = 0;
			speed(1) = 0.1;
		}
		if ((get_y() >= 504)&&(get_x() < 770+chet)){
			speed(0) = 0.1;
			speed(1) = 0;
		}
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
		if ((get_x() < 770+chet)&&(get_y() > 92)){
			speed(0) = 0.07;
			speed(1) = -0.07;
		}
		if ((get_x() < 770+chet)&&(get_y() <= 92)){
			speed(0) = 0.1;
			speed(1) = 0;
		}
		if ((get_x() >= 770+chet)&&(get_y() > 92)){
			speed(0) = 0;
			speed(1) = -0.1;
		}
	}
}

boost::numeric::ublas::matrix<float> Player::create_matrix_zvezd(float x, float y)
{
	float xc = x + 2*0.27;
	float yc = y + 50*0.27;
	boost::numeric::ublas::matrix<float> zvezd (10,4);
	zvezd(0,0) = xc-50;		zvezd(0,1) = yc-180*0.27; 	zvezd(0,2) = xc+148*0.27;	zvezd(0,3) = yc-290*0.27;  		//1-2
	zvezd(1,0) = xc+148*0.27;	zvezd(1,1) = yc-290*0.27; 	zvezd(1,2) = xc+205*0.27;	zvezd(1,3) = yc-114*0.27;	//2-3
	zvezd(2,0) = xc+205*0.27;	zvezd(2,1) = yc-114*0.27; 	zvezd(2,2) = xc+205*0.27;	zvezd(2,3) = yc-54*0.27;	//3-4
	zvezd(3,0) = xc+205*0.27;	zvezd(3,1) = yc-54*0.27; 	zvezd(3,2) = xc+335*0.27;	zvezd(3,3) = yc-17*0.27;	//4-5
	zvezd(4,0) = xc+335*0.27;	zvezd(4,1) = yc-17*0.27; 	zvezd(4,2) = xc+335*0.27;	zvezd(4,3) = yc+17*0.27;	//5-6
	zvezd(5,0) = xc+335*0.27;	zvezd(5,1) = yc+17*0.27; 	zvezd(5,2) = xc+205*0.27;	zvezd(5,3) = yc+54*0.27;	//6-7
	zvezd(6,0) = xc+205*0.27;	zvezd(6,1) = yc+54*0.27; 	zvezd(6,2) = xc+205*0.27;	zvezd(6,3) = yc+114*0.27;	//7-8
	zvezd(7,0) = xc+205*0.27;	zvezd(7,1) = yc+114*0.27; 	zvezd(7,2) = xc+148*0.27;	zvezd(7,3) = yc+250*0.27;	//8-9
	zvezd(8,0) = xc+148*0.27;	zvezd(8,1) = yc+250*0.27; 	zvezd(8,2) = xc-50;	zvezd(8,3) = yc+80*0.27;			//9-10
	zvezd(9,0) = xc-50;		zvezd(9,1) = yc+180*0.27; 	zvezd(9,2) = xc-50;	zvezd(9,3) = yc-80*0.27;				//10-1
	
	return zvezd;
}