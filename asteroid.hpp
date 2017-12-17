#ifndef _ASTEROID_HPP_
#define _ASTEROID_HPP_

#include <SFML/Graphics.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#define HALF_ASTER 52*0.37
#define SQRT22_ASTER 37.8*0.37
#define COUNT_LINE 5
#define COUNT_ASTER 10

sf::String Asteroid1[COUNT_LINE] = {
	"          ",
	"          ",
	"          ",
	"          ",
	"          ",
};

sf::String Asteroid2[COUNT_LINE] = {
	"          ",
	"          ",
	"          ",
	"          ",
	"          ",
};

boost::numeric::ublas::matrix<float> create_matrix_aster(float x, float y)
{
	float xc = x + HALF_ASTER;
	float yc = y + HALF_ASTER;
	boost::numeric::ublas::matrix<float> aster (8,4);
	aster(0,0) = xc-HALF_ASTER;		aster(0,1) = yc; 				aster(0,2) = xc-SQRT22_ASTER;	aster(0,3) = yc-SQRT22_ASTER;
	aster(1,0) = xc-SQRT22_ASTER;	aster(1,1) = yc-SQRT22_ASTER; 	aster(1,2) = xc;				aster(1,3) = yc-HALF_ASTER;
	aster(2,0) = xc;				aster(2,1) = yc-HALF_ASTER; 	aster(2,2) = xc+SQRT22_ASTER;	aster(2,3) = yc-SQRT22_ASTER;
	aster(3,0) = xc+SQRT22_ASTER;	aster(3,1) = yc-SQRT22_ASTER; 	aster(3,2) = xc+HALF_ASTER;		aster(3,3) = yc;
	aster(4,0) = xc+HALF_ASTER;		aster(4,1) = yc; 				aster(4,2) = xc+SQRT22_ASTER;	aster(4,3) = yc+SQRT22_ASTER;
	aster(5,0) = xc+SQRT22_ASTER;	aster(5,1) = yc+SQRT22_ASTER; 	aster(5,2) = xc;				aster(5,3) = yc+HALF_ASTER;
	aster(6,0) = xc;				aster(6,1) = yc+HALF_ASTER; 	aster(6,2) = xc-SQRT22_ASTER;	aster(6,3) = yc+SQRT22_ASTER;
	aster(7,0) = xc-SQRT22_ASTER;	aster(7,1) = yc+SQRT22_ASTER; 	aster(7,2) = xc-HALF_ASTER;		aster(7,3) = yc;
	
	return aster;
}

#endif