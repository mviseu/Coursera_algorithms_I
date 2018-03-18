#pragma once

class Point {
public:
Point(int xCoor, int yCoor) : x(xCoor), y(yCoor) {} 
int GetX() const {return x;}
int GetY() const {return y;}

private:	
int x = 0;
int y = 0;
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
bool operator<(const Point& lhs, const Point& rhs);
bool operator<=(const Point& lhs, const Point& rhs);
bool operator>(const Point& lhs, const Point& rhs);
bool operator>=(const Point& lhs, const Point& rhs);