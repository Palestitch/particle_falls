//
// Created by fabio on 29.11.18.
//

#include <cstdio>
#include <cmath>
#include <climits>
#include "Waterfall.hpp"

using namespace std;

/*
 * Constructor approximating the dimension of the waterfall
 */
Waterfall::Waterfall(vector<int> *begin_pixels, vector<int> *end_pixels, vector<int> *begin_rows_with_white) {
    vector<int> end_rows_with_white = *begin_rows_with_white;
    int precision = 3; //How many rows need to be white subsequently to be considered a waterfall
    do { //Remove first pixel (due to it most likely being sky)
        begin = calc_avg(*begin_pixels);
        std_dev_begin = calc_deviation(*begin_pixels, begin);
        begin_pixels->erase(begin_pixels->begin());
        begin_rows_with_white->erase(begin_rows_with_white->begin());
    } while(std_dev_begin > 15 && begin_pixels->size() > 0);
    do {
        end = calc_avg(*end_pixels);
        std_dev_end = calc_deviation(*end_pixels, end);
        end_pixels->erase(end_pixels->begin());
        end_rows_with_white.erase(end_rows_with_white.begin());
    } while(std_dev_end > 15 && end_pixels->size() > 0);
    int top_beg = waterfall_calc_top(*begin_rows_with_white, precision);
    int bot_beg = waterfall_calc_bot(*begin_rows_with_white, precision);
    int top_end = waterfall_calc_top(end_rows_with_white, precision);
    int bot_end = waterfall_calc_bot(end_rows_with_white, precision);
    top = min(top_beg, top_end);
    bot = max(bot_beg, bot_end);
    if (top == INT_MAX || bot == -1){ //If waterfall top or bottom couldn't be determind we loosen how white pixels need to be to be considered a waterfall
        printf("We struggled determining the waterfall location and will rerun the image with different parameters.\n");
        return;
    }
    width = end-begin;
    height = bot-top;
    int first_beg = begin_pixels->front();
    int last_beg = begin_pixels->back();
    if (first_beg < last_beg){
        widening_factor = first_beg/last_beg;
    }
}

float Waterfall::calc_avg(vector<int> values) {
    float sum = 0;
    for (int v : values){
        sum += v;
    }
    float mean = sum/values.size();
    return mean;
}

float Waterfall::calc_deviation(vector<int> values, float mean) {
    float sum_square = 0;
    for (int v : values){
        sum_square += pow(v - mean, 2);
    }
    return sqrt(sum_square/values.size());
}

int Waterfall::waterfall_calc_top(vector<int> values, int precision){
    for (int v = 0; v <= values.size() - precision; v++) {
        for (int i = 0; i <= precision; i++) {
            if (values[v] + i != values[v + i]) {
                break;
            }
            if (i == precision){
                return values[v];
            }
        }
    }
    return INT_MAX;
}

int Waterfall::waterfall_calc_bot(vector<int> values, int precision) {
    for (int v = values.size(); v >= precision; v--) {
        for (int i = precision; i >= 0; i--) {
            if (values[v] - i != values[v - i]) {
                break;
            }
            if (i == 0){
                return values[v];
            }
        }
    }
    return -1;
}
int Waterfall::get_waterfall_height() {
    return this->height;
}

float Waterfall::get_waterfall_begin() {
    return this->begin;
}

float Waterfall::get_waterfall_end() {
    return this->end;
}

float Waterfall::get_waterfall_width() {
    return this->width;
}

int Waterfall::get_waterfall_top() {
    return this->top;
}

int Waterfall::get_waterfall_bot() {
    return this->bot;
}

float Waterfall::wat_widening_factor() {
    return widening_factor;
}

