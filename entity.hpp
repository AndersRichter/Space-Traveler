#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <SFML/Graphics.hpp>

class Entity {

	public:
		float dx, dy, x, y, speed;
		int w,h,health;
		bool life;
		sf::Texture texture;
		sf::Sprite sprite;
	
	Entity(sf::Image &image, float X, float Y, int W, int H)
	{
		x = X; 
		y = Y; 
		w = W; 
		h = H;
		speed = 0; 
		health = 100; 
		dx = 0; 
		dy = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};


#endif