#include <ncurses.h>
#include <iostream>
#include <array>

const std::array<std::string, 6> strs = {
    "Interactive Control Panel",
    "[Q] to quit the whole interactive panel",
    "[A] to switch on/off front end debug",
    "[S] to switch on/off back end debug",
    "[D] to pause/resume",
    "[F] to have fun"
};

const std::array<std::string, 3> state_str = {"OFF ", " ON ", "NICE"};
const std::array<std::string, 4> state_names = {
    "Front End Debug:", "Back End Debug:", "Pause:", "Have fun:"
};

std::array<bool, 4> status = {
    false, false, false, false
};

void centeringPrint(WINDOW* win, int win_width, int y, std::string str) {
    int len = str.size();
    int start_pos = (win_width - static_cast<int>(str.size())) / 2;
    mvwprintw(win, y, start_pos, str.c_str());
}

void drawStatus(WINDOW* win) {
    for (int i = 0; i < 3; i++) {
        mvwprintw(win, 11 + i * 2, 28, state_names[i].c_str());
        if (status[i] == true) {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win, 11 + i * 2, 45, state_str[1].c_str());
            wattroff(win, COLOR_PAIR(1));
        } else {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, 11 + i * 2, 45, state_str[0].c_str());
            wattroff(win, COLOR_PAIR(2));
        }
    }
    mvwprintw(win, 17, 28, state_names[3].c_str());
    if (status[3] == true) {
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win, 17, 45, state_str[2].c_str());
        wattroff(win, COLOR_PAIR(3));
    } else {
        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, 17, 45, state_str[1].c_str());
        wattroff(win, COLOR_PAIR(2));
    }
    wattron(win, A_BLINK);
    mvwprintw(win, 20, 21, "The interative control panel is on");
    wattroff(win, A_BLINK);
}

// this window is 80 * 24
void windowBase(WINDOW* win, int win_width = 80) {
    box(win, '#', '#');
    wattron(win, A_BOLD);
    centeringPrint(win, win_width, 1, strs[0]);
    wattroff(win, A_BOLD);
    for (size_t i = 1; i < 6lu; i++)
        centeringPrint(win, win_width, 2 + i, strs[i]);
}


int main(int argc, char** argv) {
    initscr();			
	cbreak();			
    noecho();
	keypad(stdscr, true);
    nodelay(stdscr, true);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_WHITE, COLOR_YELLOW);
    curs_set(0);
    WINDOW* win = newwin(24, 80, 0, 0);
    int ch = 0;
    while (true) {
        windowBase(win, 80);
        drawStatus(win);
        wrefresh(win);
        ch = wgetch(win);
        switch (ch)
        {
        case 'q':
            endwin();
            return 0;
            break;
        case 'a':
            status[0] = !status[0];
            break;
        case 's':
            status[1] = !status[1];
            break;
        case 'd':
            status[2] = !status[2];
            break;
        case 'f':
            status[3] = !status[3];
            break;
        default:
            break;
        }
    }
    endwin();
    return 0;
}