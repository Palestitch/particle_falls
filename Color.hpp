//
// Created by fabio on 26.11.18.
//

#ifndef FINAL_PROJECT_VECTOR_HPP
#define FINAL_PROJECT_VECTOR_HPP


class Color {
private:
    float v_x, v_y, v_z;

public:
    Color() : v_x(0.0), v_y(0.0), v_z(0.0){}
    Color(float x, float y, float z): v_x(x), v_y(y), v_z(z){}

    Color operator+(const Color& v);
    Color operator-(const Color& v);
    Color operator*(float f);
    Color operator*(Color f);
    Color operator/(float f);

    float x();
    float y();
    float z();
};



#endif //FINAL_PROJECT_VECTOR_HPP
