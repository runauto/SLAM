/******************************************************************************
 Author		: Lichao Ma
 Date  		: Mar 19,2016
 Version	: v0.3
 Description :
	-v0.3	Create a base class for static variables reference
	-v0.2	Use template to extend the application,e.g.,float point
	-v0.1	Pointer class for occupancy grid map
 *****************************************************************************/
#include "Point.h"

const std::size_t PointBase::DirectionSize=4;
//Must define these values in clockwise/counter-clockwise manner
const int PointBase::Up=0;
const int PointBase::Right=1;
const int PointBase::Down=2;
const int PointBase::Left=3;

namespace pnt{
int abs(Point<unsigned int> &a,Point<unsigned int> &b){
	int x = a.x > b.x ? a.x - b.x : b.x - a.x;
	int y = a.y > b.y ? a.y - b.y : b.y - a.y;
	return x+y;
}
int dis(Point<unsigned int> &a,Point<unsigned int> &b){
	int x = a.x > b.x ? a.x - b.x : b.x - a.x;
	int y = a.y > b.y ? a.y - b.y : b.y - a.y;
	return x*x+y*y;
}

float abs(Point<float> &a,Point<float> &b){
	int x = a.x > b.x ? a.x - b.x : b.x - a.x;
	int y = a.y > b.y ? a.y - b.y : b.y - a.y;
	return x+y;
}
float dis(Point<float> &a,Point<float> &b){
	int x = a.x > b.x ? a.x - b.x : b.x - a.x;
	int y = a.y > b.y ? a.y - b.y : b.y - a.y;
	return x*x+y*y;
}
}
