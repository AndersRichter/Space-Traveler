#ifndef _BULLET_HPP_
#define _BULLET_HPP_

#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Bullet: public Entity
{
	public:
		Bullet(sf::Image &image, float X, float Y, int W, int H): Entity(image, X, Y, W, H)
		{
			sprite.setScale(0.02, 0.02);
		}
		
		void update(float time)
		{
			dx = speed;
			x += dx*time;
			speed = 0;
			sprite.setPosition(x,y);
		}
};

#endif