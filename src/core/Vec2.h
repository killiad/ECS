#ifndef VEC_2_H
#define VEC_2_H

#include <cmath>
#include <iostream>

//2 dimensional double vector
class Vec2{
    
    private:
        double coord_1;
        double coord_2;
        double length;

    public:

        static const Vec2 ZERO;
        static const Vec2 RIGHT;
        static const Vec2 LEFT;
        static const Vec2 DOWN;
        static const Vec2 UP;

        //scalar vector multiplication
        friend Vec2 operator*(const int&, const Vec2&);
        friend Vec2 operator*(const double&, const Vec2&);
        friend std::ostream& operator<<(std::ostream& os, const Vec2&);

        Vec2(double x = 0, double y = 0);

        //return corresponding vector of length one
        Vec2 getUnitVector();

        //Vector addition, subtraction, and scalar multiplication
        Vec2 operator+(const Vec2&);
        Vec2 operator-(const Vec2&);
        Vec2 operator*(const int&);
        Vec2 operator*(const double&);

        //returns first, coordinate, second coordinate, and the length respectively
        inline double x() const {return coord_1;};
        inline double y() const {return coord_2;};
        inline double getLength() {return length;};
};

#endif
