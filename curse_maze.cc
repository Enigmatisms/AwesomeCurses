#include "kruskal.hpp"

int main(int argc, char** argv) {
    Kruskal ks(80, 24);
    std::vector<Point> walls;
    ks.initialize(walls);
    ks.randomBreakWall(walls);
    initscr();			
	cbreak();			
    noecho();
	keypad(stdscr, true);
    nodelay(stdscr, true);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    curs_set(0);
    WINDOW* win = newwin(24, 80, 0, 0);
    ks.drawMaps(win);
    wrefresh(win);
    getchar();
    endwin();
    int ch = 0;
    return 0;
}