#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <inttypes.h>
#include <time.h>
#include <complex.h>
#include <math.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON

#include "ANSI_COLOR_CODES.h"

#define OPTIONS "h:w:m:"

typedef struct Point {
    double x;
    double y;
} Point;

void draw_screen(Point bottom_left, Point top_right) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    size_t max_height = w.ws_row, max_width = w.ws_col ;
    //getmaxyx(stdscr, max_height, max_width);

    size_t screen_height = max_height - 2, screen_width = max_width;
    
    double y_diff = (top_right.y - bottom_left.y);
    double x_diff = (top_right.x - bottom_left.x);
    for (size_t i = 0; i < screen_height; i++) {
        for (size_t j = 0; j < screen_width; j++) {
            double x0 = (x_diff * j) / screen_width + bottom_left.x; 
            double y0 = (y_diff * i) / screen_height + bottom_left.y; 
            
            double x = 0, y = 0;

            size_t iteration = 0, max_iteration = 2000;

            while (x * x + y * y <= 2 * 2 && iteration < max_iteration) {
                double xtemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtemp;
                ++iteration;
            }
            
            if (iteration < 5) {
                printf(BLUHB " " reset);

            }
            else if (iteration < 10) {
                printf(REDHB " " reset);
            }
            else if (iteration < 15) {
                printf(YELHB " " reset);
            }
            else if (iteration < 20) {
                printf(GRNHB " " reset);
            }
            else if (iteration < 30) {
                printf(CYNHB " " reset);
            }
            else if (iteration < 40) {
                printf(MAGHB " " reset);
            }
            else if (iteration < 50) {
                printf(BLUHB " " reset);
            }
            else if (iteration < 100) {
                printf(REDHB " " reset);
            }
            else if (iteration < 200) {
                printf(YELHB " " reset);
            }
            else if (iteration < 300) {
                printf(GRNHB " " reset);
            }
            else if (iteration < 400) {
                printf(CYNHB " " reset);
            }
            else if (iteration < 500) {
                printf(MAGHB " " reset);
            }
            else if (iteration < 600) {
                printf(BLUHB " " reset);
            }
            else if (iteration < 700) {
                printf(REDHB " " reset);
            }
            else if (iteration < 800) {
                printf(YELHB " " reset);
            }
            else if (iteration < 900) {
                printf(GRNHB " " reset);
            }
            else if (iteration < 1000) {
                printf(CYNHB " " reset);
            }
            else if (iteration < 1100) {
                printf(MAGHB " " reset);
            }
            else if (iteration < 1200) {
                printf(BLUHB " " reset);
            }
            else if (iteration < 1300) {
                printf(REDHB " " reset);
            }
            else if (iteration < 1400) {
                printf(YELHB " " reset);
            }
            else if (iteration < 1500) {
                printf(GRNHB " " reset);
            }
            else if (iteration < 1600) {
                printf(CYNHB " " reset);
            }
            else if (iteration < 1700) {
                printf(MAGHB " " reset);
            }
            else if (iteration < 1800) {
                printf(WHTHB " " reset);
            }
            else {
                printf(" ");
            }
        }
    }
}

int main(int argc, char *argv[]) {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int opt;
    while((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            default:
                break;
        }
    }

    Point bottom_left, top_right;
    float scale = 1;
    bottom_left.x = -1;
    bottom_left.y = -1;
    top_right.x = 1;
    top_right.y = 1;
    draw_screen(bottom_left, top_right);
    char c;
    printf("\e[?25l");
    while (true) {
        c = getchar();
        printf("\033[1D");
        if (c == 'i') scale *= 2;
        if (c == 'o') scale /= 2;
        if (c == '+' || c == '=') {
            scale /= 2;
            float mid_x = (top_right.x + bottom_left.x) / 2, mid_y = (top_right.y + bottom_left.y) / 2;
            bottom_left.x += fabs(mid_x - bottom_left.x) / 2;
            bottom_left.y += fabs(mid_y - bottom_left.y) / 2;
            top_right.x   -= fabs(top_right.x - mid_x) / 2;
            top_right.y   -= fabs(top_right.y - mid_y ) / 2;
        }
        if (c == '_' || c == '-') {
            scale *= 2;
            float mid_x = (top_right.x + bottom_left.x) / 2, mid_y = (top_right.y + bottom_left.y) / 2;
            bottom_left.x -= fabs(mid_x - bottom_left.x) / 2;
            bottom_left.y -= fabs(mid_y - bottom_left.y) / 2;
            top_right.x   += fabs(mid_x - top_right.x) / 2;
            top_right.y   += fabs(mid_y - top_right.y) / 2;
        }
        if (c == 'a' || c == 'd') {
            bottom_left.x += 0.2 * (c == 'a' ? -1 : 1) * scale;
            top_right.x += 0.2 * (c == 'a' ? -1 : 1) * scale;
        }
        if (c == 'w' || c == 's') {
            bottom_left.y += (0.2 * (c == 'w' ? -1 : 1)) * scale;
            top_right.y += (0.2 * (c == 'w' ? -1 : 1)) * scale;
        }
        
        draw_screen(bottom_left, top_right);
        printf("[scale: %f] [center: (%f, %f)]\n", scale, (top_right.x + bottom_left.x) / 2, (top_right.y + bottom_left.y) / 2);
        if (c == 27) break;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return 0;
}
