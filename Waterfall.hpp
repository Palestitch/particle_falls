//
// Created by fabio on 29.11.18.
//

#ifndef FINAL_PROJECT_WATERFALL_HPP
#define FINAL_PROJECT_WATERFALL_HPP


#include <vector>
#include "Image.hpp"

using namespace std;

class Waterfall {

    float end;
    int bot;
    int top;
    float width;
    int height;
    float std_dev_begin;
    float std_dev_end;
    float begin;
    float widening_factor = 1;

    float calc_avg(vector<int>);
    float calc_deviation(vector<int>, float);
    int waterfall_calc_bot(vector<int>, int);
    int waterfall_calc_top(vector<int>, int);

public:
    Waterfall(vector<int> *, vector<int> *, vector<int> *);
    float get_waterfall_begin();
    float get_waterfall_end();
    float get_waterfall_width();
    int get_waterfall_top();
    int get_waterfall_bot();
    int get_waterfall_height();
    float wat_widening_factor();

};


#endif //FINAL_PROJECT_WATERFALL_HPP
