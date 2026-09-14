#define _DEFAULT_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

enum
{
    W = 42,
    H = 20,
    MAX = W * H,
    MAX_ROCKS = 18
};
typedef struct
{
    int x, y;
} Point;
static struct termios saved;
static bool raw_mode;
static int high_score;

static void restore(void)
{
    if (raw_mode)
    {
        tcsetattr(0, TCSAFLUSH, &saved);
        printf("\033[?25h\033[0m\n");
    }
}
static void raw(void)
{
    if (tcgetattr(0, &saved) == -1)
        return;
    struct termios t = saved;
    t.c_lflag &= (tcflag_t) ~(ICANON | ECHO);
    t.c_cc[VMIN] = 0;
    t.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &t);
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
    raw_mode = true;
    atexit(restore);
    printf("\033[2J\033[?25l");
}
static int read_key(void)
{
    char c;
    return read(0, &c, 1) == 1 ? c : 0;
}
static bool contains(const Point *items, int count, int x, int y)
{
    for (int i = 0; i < count; i++)
        if (items[i].x == x && items[i].y == y)
            return true;
    return false;
}
static Point free_spot(const Point *snake, int length, const Point *rocks, int rock_count)
{
    Point p;
    do
    {
        p.x = rand() % W;
        p.y = rand() % H;
    } while (contains(snake, length, p.x, p.y) || contains(rocks, rock_count, p.x, p.y));
    return p;
}
static void draw(const Point *snake, int length, Point food, const Point *rocks, int rock_count, int score, bool paused)
{
    int level = score / 50 + 1;
    printf("\033[H\n");
    printf("  \033[1;35m+==========================================+\033[0m\n");
    printf("  \033[1;35m|\033[0m          \033[1;37mN E O N   S N A K E\033[0m           \033[1;35m|\033[0m\n");
    printf("  \033[1;35m+==========================================+\033[0m\n");
    printf("  \033[2m  SCORE\033[0m \033[1;33m%-5d\033[0m  \033[2mBEST\033[0m \033[1;36m%-5d\033[0m  \033[2mLEVEL\033[0m \033[1;32m%-2d\033[0m %s\n\n", score, high_score, level, paused ? "\033[1;33m[ PAUSED ]\033[0m" : "");
    printf("  \033[1;36m+");
    for (int x = 0; x < W; x++)
        putchar('=');
    puts("+\033[0m");
    for (int y = 0; y < H; y++)
    {
        printf("  \033[1;36m|\033[0m");
        for (int x = 0; x < W; x++)
        {
            char tile = ' ';
            if (x == food.x && y == food.y)
                tile = '@';
            if (contains(rocks, rock_count, x, y))
                tile = '#';
            for (int i = 0; i < length; i++)
                if (snake[i].x == x && snake[i].y == y)
                    tile = i ? 'o' : 'O';
            if (tile == '@')
                printf("\033[1;31m@\033[0m");
            else if (tile == '#')
                printf("\033[2;37m#\033[0m");
            else if (tile == 'O')
                printf("\033[1;32mO\033[0m");
            else if (tile == 'o')
                printf("\033[32mo\033[0m");
            else
                putchar(' ');
        }
        puts("\033[1;36m|\033[0m");
    }
    printf("  \033[1;36m+");
    for (int x = 0; x < W; x++)
        putchar('=');
    puts("+\033[0m");
    printf("  \033[2mARROWS / WASD\033[0m move     \033[2mP\033[0m pause     \033[2mQ\033[0m quit\n");
    printf("  \033[1;31m@\033[0m food   \033[32mO\033[0m snake   \033[2;37m#\033[0m barrier\n");
    fflush(stdout);
}
static int normalize_key(int key)
{
    if (key != 27)
        return key;
    (void)read_key();
    key = read_key();
    if (key == 'A')
        return 'w';
    if (key == 'B')
        return 's';
    if (key == 'C')
        return 'd';
    if (key == 'D')
        return 'a';
    return 0;
}
static bool game(void)
{
    Point snake[MAX] = {{W / 2, H / 2}, {W / 2 - 1, H / 2}, {W / 2 - 2, H / 2}}, rocks[MAX_ROCKS];
    int length = 3, rock_count = 0, dx = 1, dy = 0, score = 0;
    Point food = free_spot(snake, length, rocks, rock_count);
    bool paused = false;
    for (;;)
    {
        int key = normalize_key(read_key());
        if (key == 'q' || key == 'Q')
            return false;
        if (key == 'p' || key == 'P')
            paused = !paused;
        if ((key == 'w' || key == 'W') && dy != 1)
        {
            dx = 0;
            dy = -1;
        }
        if ((key == 's' || key == 'S') && dy != -1)
        {
            dx = 0;
            dy = 1;
        }
        if ((key == 'a' || key == 'A') && dx != 1)
        {
            dx = -1;
            dy = 0;
        }
        if ((key == 'd' || key == 'D') && dx != -1)
        {
            dx = 1;
            dy = 0;
        }
        if (!paused)
        {
            Point head = {snake[0].x + dx, snake[0].y + dy};
            if (head.x < 0 || head.x >= W || head.y < 0 || head.y >= H || contains(snake, length, head.x, head.y) || contains(rocks, rock_count, head.x, head.y))
                break;
            for (int i = length; i > 0; i--)
                snake[i] = snake[i - 1];
            snake[0] = head;
            if (head.x == food.x && head.y == food.y)
            {
                length++;
                score += 10;
                if (score % 50 == 0 && rock_count < MAX_ROCKS)
                {
                    Point rock = free_spot(snake, length, rocks, rock_count);
                    rocks[rock_count++] = rock;
                }
                food = free_spot(snake, length, rocks, rock_count);
            }
            if (score > high_score)
                high_score = score;
        }
        draw(snake, length, food, rocks, rock_count, score, paused);
        int speed_ms = 120 - (score / 50) * 12;
        if (speed_ms < 45)
            speed_ms = 45;
        struct timespec delay = {0, (long)speed_ms * 1000000L};
        nanosleep(&delay, NULL);
    }
    if (score > high_score)
        high_score = score;
    printf("\033[H\n\n  \033[1;31m+==========================================+\033[0m\n  \033[1;31m|\033[0m               G A M E   O V E R            \033[1;31m|\033[0m\n  \033[1;31m+==========================================+\033[0m\n\n  FINAL SCORE  \033[1;33m%-5d\033[0m       BEST SCORE  \033[1;36m%-5d\033[0m\n\n  \033[1;32m[R]\033[0m PLAY AGAIN        \033[1;33m[Q]\033[0m QUIT\n", score, high_score);
    fflush(stdout);
    for (;;)
    {
        int key = read_key();
        if (key == 'r' || key == 'R')
            return true;
        if (key == 'q' || key == 'Q')
            return false;
        struct timespec wait = {0, 30000000};
        nanosleep(&wait, NULL);
    }
}
int main(void)
{
    srand((unsigned)time(NULL));
    raw();
    bool again = true;
    while (again)
        again = game();
    return 0;
}
