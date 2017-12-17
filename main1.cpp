#include <iostream>

void intersection(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2)
{
	float v1, v2, v3, v4;
	v1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
   	v2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
  	v3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
  	v4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);
	bool inter = ((v1*v2<0)&&(v3*v4<0));
	return inter;
}


int main () 
{
	pro(2,2,6,6,2,6,6,4);
	std::cout << "////////////////" << std::endl;
	pro(2,2,6,6,4,2,2,5);
	std::cout << "////////////////" << std::endl;
	pro(2,2,6,6,1,3,6,4);
}