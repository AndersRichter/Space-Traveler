#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include <SFML/Graphics.hpp>

sf::View view;//объект камеры

void camera_move(float chet) 
{
	view.setCenter(chet+450, 348);
}

#endif