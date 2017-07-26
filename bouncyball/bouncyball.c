#include <locale.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>

#define DELAY 20000

typedef struct {
    int     max_x;
    int     max_y;
} window;

typedef struct {
    int     x;
    int     y;
    int     next_x;
    int     next_y;
    int     direction_x;
    int     direction_y;
} ball;


void render_screen(window *window_data, ball *ball_data) {
    /* `stdscr` is global from call to `initscr()` */
    getmaxyx(stdscr, window_data->max_y, window_data->max_x);

    clear();
    mvprintw(ball_data->y, ball_data->x, "◯");
    refresh();
}

void detect_collision(window window_data, ball *ball_data) {
    if (ball_data->next_x >= window_data.max_x || ball_data->next_x < 0) {
        ball_data->direction_x *= -1;
    } else {
        ball_data->x += ball_data->direction_x;
    }

    if (ball_data->next_y >= window_data.max_y || ball_data-> next_y < 0) {
        ball_data->direction_y *= -1;
    } else {
        ball_data->y += ball_data->direction_y;
    }
}

int main(int argc, char *argv[]) {

    window window_data = { 0, 0 };
    ball ball_data = { 0, 0, 0, 0, 1, 1 };

    setlocale(LC_ALL, "");
    initscr();
    noecho();
    curs_set(FALSE);

    while (1) {
        render_screen(&window_data, &ball_data);
        usleep(DELAY);
        ball_data.next_y = ball_data.y + ball_data.direction_y;
        ball_data.next_x = ball_data.x + ball_data.direction_x;
        detect_collision(window_data, &ball_data);
    }

    endwin(); // Restore terminal
    return 0;
}
