// 2069. Walking Robot Simulation II
// Created automatically
// Created at 2026-04-07 13:42:16

#include <bits/stdc++.h>
using namespace std;

class Robot {
private:
    int width_;
    int height_;
    int perimeter_;
    int dist_ = 0;
    bool moved_ = false;

public:
    Robot(int width, int height) : width_(width), height_(height) {
        perimeter_ = 2 * (width_ + height_) - 4;
    }
    
    void step(int num) {
        if (num == 0) {
            return;
        }
        dist_ = (dist_ + num) % perimeter_;
        moved_ = true;
    }
    
    vector<int> getPos() {
        if (dist_ < width_) {
            return {dist_, 0};
        }

        int d = dist_ - (width_ - 1);
        if (d < height_) {
            return {width_ - 1, d};
        }

        d -= (height_ - 1);
        if (d < width_) {
            return {width_ - 1 - d, height_ - 1};
        }

        d -= (width_ - 1);
        return {0, height_ - 1 - d};
    }
    
    string getDir() {
        if (dist_ == 0) {
            return moved_ ? "South" : "East";
        }
        if (dist_ <= width_ - 1) {
            return "East";
        }
        if (dist_ <= width_ + height_ - 2) {
            return "North";
        }
        if (dist_ <= 2 * width_ + height_ - 3) {
            return "West";
        }
        return "South";
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
