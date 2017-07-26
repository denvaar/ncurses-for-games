#include <locale.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>

#define DELAY 20000

typedef struct {
    int     x;
    int     y;
    int     next_x;
    int     next_y;
    int     direction_x;
    int     direction_y;
    char*   glyph;
} player;

char* get_user_input(WINDOW *screen, player *player) {
    char *last_input = "";
    if (getch() == '\033') {
        getch();
        int arrow_code = getch();
        switch (arrow_code) {
            case 65: // up
                last_input = "↑";
                player->direction_y = -1;
                break;
            case 66: // down
                last_input = "↓";
                player->direction_y = 1;
                break;
            case 67: // right
                last_input = "→";
                player->direction_x = 1;
                break;
            case 68: // left
                last_input = "←";
                player->direction_x = -1;
                break;
            default:
                player->direction_x = 0;
                player->direction_y = 0;
        }
    } else {
        player->direction_x = 0;
        player->direction_y = 0;
    }

    player->x = player->x + player->direction_x;
    player->y = player->y + player->direction_y;

    return last_input;
}

void draw_borders(WINDOW *screen) {
    int x, y, i;
    getmaxyx(screen, y, x); // 4 corners
    mvwprintw(screen, 0, 0, "┌");
    mvwprintw(screen, y - 1, 0, "└");
    mvwprintw(screen, 0, x - 1, "┐");
    mvwprintw(screen, y - 1, x - 1, "┘");
    // sides
    for (i = 1; i < (y - 1); i++) {
        mvwprintw(screen, i, 0, "│");
        mvwprintw(screen, i, x - 1, "│");
    }
    // top and bottom
    for (i = 1; i < (x - 1); i++) {
        mvwprintw(screen, 0, i, "─");
        mvwprintw(screen, y - 1, i, "─");
    }
}


int main(int argc, char *argv[]) {

    int max_x, max_y;

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);
    getmaxyx(stdscr, max_y, max_x);

    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    /* create window with `height`, `width` at `y`, `x` */
    WINDOW *window = newwin(5, max_x, 0, 0);

    char *last_input = "";

    player player_1 = { 10, 10, 0, 0, 0, 0, "☠" };

    while (1) {
        clear();
        last_input = get_user_input(window, &player_1);

        draw_borders(window); // generic function to draw borders on window
        wbkgd(window, COLOR_PAIR(1));
        mvwaddstr(window, 2, 2, "Use the arrow keys to move around.");
        mvwprintw(window, 1, 50, "Position:  (%d, %d)", player_1.x, player_1.y);
        mvwaddstr(window, 2, 50, "Last direction: ");
        mvwaddstr(window, 2, 67, last_input);
        wrefresh(window);


        mvprintw(player_1.y, player_1.x, player_1.glyph);


        refresh();
        usleep(DELAY);
    }

    delwin(window);
    endwin(); // restore terminal
    return 0;
}
