#pragma once
/**
 * @brief random Kruskal Algorithm
 */
#include <iostream>
#include <vector>
#include <stack>
#include <array>
#include <ncurses.h>

struct Point: std::pair<int, int> {
    Point() {
        first = 0;
        second = 0;
    }
    Point(int x, int y) {
        first = x;
        second = y;
    }
    const int& x() const noexcept {
        return first;
    }
    const int& y() const noexcept {
        return second;
    }
    Point operator+ (const Point& p) const noexcept {
        return Point(p.first + this->first, p.second + this->second);
    }
    Point operator- (const Point& p) const noexcept {
        return Point(this->first - p.first, this->second - p.second);
    }
    Point operator+= (const Point& p) noexcept {
        first += p.first;
        second += p.second;
    }
};

const std::array<Point, 4> dirs = {Point(1, 0), Point(-1, 0), Point(0, 1), Point(0, -1)};

class Kruskal {
public:
    Kruskal(int w, int h): w(w), h(h) {
        map = new uint16_t* [h];
        for (int i = 0; i < h; i++)
            map[i] = new uint16_t [w];
    }
    ~Kruskal() {
        for (int i = 0; i < h; i++) {
            delete[] map[i];
        }
        delete[] map;
    }
public:
    void initialize(std::vector<Point>& walls);
    void randomBreakWall(std::vector<Point>& walls);
    void drawMaps(WINDOW* const win) const;
private:
    void mergeFloors(Point pt, uint16_t min_val);
private:
    uint16_t** map;
    const int w, h;
};