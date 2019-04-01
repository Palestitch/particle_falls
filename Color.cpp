//
// Created by fabio on 26.11.18.
//

#include "Color.hpp"

/* Add two Vectors together
    (a, b, c) + (d, e, f) = (a + d, b + e, c + f)
 */
Color Color::operator+(const Color& p)
{
    return Color(this->v_x + p.v_x, this->v_y + p.v_y, this->v_z + p.v_z);
}

/* Finds the difference between two Vectors
    (a, b, c) + (d, e, f) = (a - d, b - e, c - f)
 */
Color Color::operator-(const Color& p)
{
    return Color(this->v_x - p.v_x, this->v_y - p.v_y, this->v_z - p.v_z);
}

/* Scales a Color by a float
    (a, b, c) * f = (a * f, b * f, c * f)
 */
Color Color::operator*(float f)
{
    return Color(this->v_x * f, this->v_y * f, this->v_z * f);
}

//???
Color Color::operator*(Color f)
{
    return Color(this->v_x * f.x(), this->v_y * f.y(), this->v_z * f.z());
}

/* Divides a Color by a float
    (a, b, c) / f = (a / f, b / f, c / f)
 */
Color Color::operator/(float f)
{
    if(f != 0){
        return Color(this->v_x / f, this->v_y / f, this->v_z / f);
    }
    else{
        return Color(0,0,0);
    }
}

/* Returns the x-component of the Color */
float Color::x(){
    return v_x;
}

/* Returns the y-component of the Color */
float Color::y(){
    return v_y;
}

/* Returns the z-component of the Color */
float Color::z(){
    return v_z;
}