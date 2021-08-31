#include "kruskal.hpp"

void Kruskal::initialize(std::vector<Point>& walls) {
    walls.clear();
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            map[i][j] = 0;
    uint16_t cnt = 1;
    for (int i = 1; i < h - 1; i += 2)
        for (int j = 1; j < w - 1; j += 2)
            map[i][j] = (cnt++);
    int max_h = (h & 1) ? h - 1 : h - 2, max_w = (w & 1) ? w - 1 : w - 2;
    for (int i = 1; i < max_h; i++) {
        if ((i & 1) == 1) {
            for (int j = 2; j < max_w; j += 2)
                walls.emplace_back(j, i);
        } else {
            for (int j = 1; j < max_w; j += 2)
                walls.emplace_back(j, i);
        }
    } 
}

void Kruskal::mergeFloors(Point pos, uint16_t min_val) {
    std::stack<Point> st;
    st.push(pos);
    while (st.empty() == false) {
        const Point p = st.top();
        st.pop();
        map[p.y()][p.x()] = min_val;
        for (int i = 0; i < 4; i++) {
            Point cur = p + dirs[i];
            uint16_t val = map[cur.y()][cur.x()];
            if (val > 0 && val != min_val)
                st.push(cur);
        }
    }
}

void Kruskal::randomBreakWall(std::vector<Point>& walls) {
    srand(time(NULL));
    while (walls.empty() == false) {
        int rnum = rand() % walls.size();
        const Point wall = walls[rnum];
        for (int i = 0; i < 3; i += 2) {
            Point one_size = wall + dirs[i], the_other = wall + dirs[i + 1];
            uint16_t v1 = map[one_size.y()][one_size.x()], v2 = map[the_other.y()][the_other.x()];
            if (v1 != v2) {
                map[wall.y()][wall.x()] = std::min(v1, v2);
                mergeFloors(wall, std::min(v1, v2));
                break;
            }
        }
        std::swap(walls[rnum], walls.back());
        walls.pop_back();
    }
}

void Kruskal::drawMaps(WINDOW* const win) const {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] > 0) {
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win, i, j, " ");
                wattroff(win, COLOR_PAIR(1));
            } else {
                wattron(win, COLOR_PAIR(2));
                mvwprintw(win, i, j, " ");
                wattroff(win, COLOR_PAIR(2));
            } 
        }
    }
}
