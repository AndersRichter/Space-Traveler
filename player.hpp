#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "entity.hpp"

class Player: public Entity
{
	public:
		float get_x();
		float get_y();
		void update(float time);
		void control(float chet);
		boost::numeric::ublas::vector<float> coord;
		boost::numeric::ublas::vector<float> speed;
		boost::numeric::ublas::matrix<float> create_matrix_zvezd(float x, float y);
		
	
	Player(sf::Image &image, float X, float Y, int W, int H): Entity(image, X, Y, W, H)
	{
		coord.resize(2);
		speed.resize(2);
		coord(0) = X;
		coord(1) = Y;
		sprite.setTextureRect(sf::IntRect(0, 0, w, h));
		sprite.setScale(0.27, 0.27);
 	}
};


#endif