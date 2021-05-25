#include "Vec2.h"

const Vec2 Vec2::ZERO(0,0);
const Vec2 Vec2::RIGHT(1,0);
const Vec2 Vec2::LEFT(-1,0);
const Vec2 Vec2::UP(0,-1);
const Vec2 Vec2::DOWN(0,1);

Vec2::Vec2(double x, double y) : coord_1(x), coord_2(y), length(std::sqrt(x*x + y*y)) {}

Vec2 Vec2::getUnitVector(){
    if(coord_1 == 0 && coord_2 == 0) return Vec2::ZERO;
    return Vec2(coord_1 / length, coord_2 / length);
}

Vec2 Vec2::operator+(const Vec2& v){
    return Vec2(this->coord_1 + v.coord_1, this->coord_2 + v.coord_2);
}

Vec2 Vec2::operator-(const Vec2& v){
    return Vec2(this->coord_1 - v.coord_1, this->coord_2 - v.coord_2);
}

Vec2 Vec2::operator*(const int& c){
    return Vec2(c*this->coord_1, c*this->coord_2);
}

Vec2 Vec2::operator*(const double& c){
    return Vec2(c*this->coord_1, c*this->coord_2);
}

Vec2 operator*(const int& c, const Vec2& v){
    return Vec2(c*v.x(), c*v.y());
}

Vec2 operator*(const double& c, const Vec2& v){
    return Vec2(c*v.x(), c*v.y());
}

std::ostream& operator<<(std::ostream& os, const Vec2& vec){
    os << vec.x() << ", " << vec.y();
    return os;
}
