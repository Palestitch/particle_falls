//
// Created by fabio on 29.11.18.
//

#ifndef FINAL_PROJECT_IMAGE_HPP
#define FINAL_PROJECT_IMAGE_HPP


#include <cstdlib>
#include "Waterfall.hpp"
#include "Color.hpp"

using namespace std;
class Waterfall;

class Image {

    vector<vector<Color>> image;
    vector<int> starting_pixels;
    vector<int> ending_pixels;
    vector<int> rows_with_white;
    int width;
    int height;
    unsigned char *data;
    Waterfall *waterfall;

    void read_in_image(char*, int);

public:

    Image(char *);
    Image();
    vector<vector<Color>> get_image();
    vector<int> get_starting_pixels();
    vector<int> get_ending_pixels();
    vector<int> get_rows_with_white();
    int get_width();
    int get_height();
    unsigned char* get_data();
    Waterfall* get_waterfall();

};


#endif //FINAL_PROJECT_IMAGE_HPP
