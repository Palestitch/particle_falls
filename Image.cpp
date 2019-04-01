//
// Created by fabio on 29.11.18.
//

#include <vector>
#include <algorithm>
#include "Image.hpp"
#include "stb_image.hpp"

using namespace std;

/**
 *
 * @param filename of the image to be read in
 * @param whiteness how white does a pixel need to be to bed considered part of the image
 */
void Image::read_in_image(char * filename, int whiteness) {
    int image_width,image_height,n;
    data = stbi_load(filename, &image_width, &image_height, &n, 3);
    if (!data){
        perror("Failed to read in image");
        return;
    }
    int column_counter = 0;
    int subsequent_white_pixels = 0;
    int old_row = 0;
    this->width = image_width;
    this->height = image_height;
    int first_column = 0;
    int last_column = 0;
    vector<vector<Color>> image_rgb_vec ((unsigned long) this->width, vector<Color>((unsigned long) this->height));
    image = image_rgb_vec;
    for(int i = 0; i < width*height*3; i += 3) {
        int r, g, b;
        r = data[i];
        g = data[i+1];
        b = data[i+2];
        int current_row = i/(3*width);
        Color pixel = *new Color(r,g,b);
        if (r > whiteness && g > whiteness && b > whiteness){
            subsequent_white_pixels++;
            if (first_column == 0){
                first_column = column_counter;
            }
            last_column = column_counter;
        } else {
            if (old_row != current_row){ //we changed row
                if (subsequent_white_pixels >= width/40) { //If we have significantly many white pixels in a row we use the data further
                    if (rows_with_white.size() == 0 || rows_with_white.back() != current_row) {
                        rows_with_white.push_back(current_row);
                    }
                    starting_pixels.push_back(first_column);
                    ending_pixels.push_back(last_column);
                }
                subsequent_white_pixels = 0;
                column_counter = 0;
                first_column = 0;
                last_column = 0;
            }
        }
        if (old_row != current_row) { //we changed row
            subsequent_white_pixels = 0;
            column_counter = 0;
            first_column = 0;
            last_column = 0;
        }
        image[column_counter][current_row] = pixel;
        column_counter++;
        old_row = current_row;
    }
}

Image::Image(char* filename) {
    int whiteness = 210;
    do { //Repeat until a waterfall is actually read in
        read_in_image(filename, whiteness);
        if (this->get_data() == NULL) {
            return;
        }
        this->waterfall = new Waterfall(&starting_pixels, &ending_pixels, &rows_with_white);
        whiteness -= 10;
    } while (this->waterfall == NULL);
}

Image::Image() {

}

vector<vector<Color>> Image::get_image() {
    return this->image;
}

vector<int> Image::get_starting_pixels() {
    return this->starting_pixels;
}

vector<int> Image::get_ending_pixels() {
    return this->ending_pixels;
}

vector<int> Image::get_rows_with_white() {
    return this->rows_with_white;
}

int Image::get_width() {
    return this->width;
}

int Image::get_height() {
    return this->height;
}

unsigned char *Image::get_data() {
    return this->data;
}

Waterfall *Image::get_waterfall() {
    return this->waterfall;
}


