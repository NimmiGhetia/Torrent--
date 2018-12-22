#include "global.h"
struct termios initialrsettings, newrsettings;
struct winsize w;

int getch();
int kbhit();
int kbesc();
int kbget();
void movecursor();

void enterCommand()
{
    movecursor();
}

void movecursor()
{
    int c;
    bool flag = true;
    setcursor(0, 0);
    clearscreen();
    while (flag)
    {
        write(STDOUT_FILENO, "\x1b[2J", 4);
        char cmd[1024];
        cin >> cmd;
        if (strcmp(cmd, "share") == 0)
        {
            struct metafile mtorrent;
            shareFile(mtorrent);
        }
        break;
    }
}

int getch()
{
    int c = 0;
    tcgetattr(0, &initialrsettings);
    memcpy(&newrsettings, &initialrsettings, sizeof(newrsettings));
    newrsettings.c_lflag &= ~(ICANON | ECHO);
    newrsettings.c_cc[VMIN] = 1;
    newrsettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newrsettings);
    c = getchar();
    tcsetattr(0, TCSANOW, &initialrsettings);
    return c;
}

int kbhit()
{
    int c = 0;

    tcgetattr(0, &initialrsettings);
    memcpy(&newrsettings, &initialrsettings, sizeof(newrsettings));
    newrsettings.c_lflag &= ~(ICANON | ECHO);
    newrsettings.c_cc[VMIN] = 1;
    newrsettings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &newrsettings);
    c = getchar();
    tcsetattr(0, TCSANOW, &initialrsettings);
    if (c != -1)
        ungetc(c, stdin);
    return ((c != -1) ? 1 : 0);
}
int kbesc(void)
{
    int c;

    if (!kbhit())
        return KEY_ESCAPE;
    c = getch();
    if (c == '[')
    {
        switch (getch())
        {
        case 'A':
            c = KEY_UP;
            break;
        case 'B':
            c = KEY_DOWN;
            break;
        case 'C':
            c = KEY_RIGHT;
            break;
        case 'D':
            c = KEY_LEFT;
            break;
        default:
            c = 0;
            break;
        }
    }
    else
    {
        c = 0;
    }
    if (c == 0)
        while (kbhit())
            getch();
    return c;
}
int kbget(void)
{
    int c;

    c = getch();
    return (c == KEY_ESCAPE) ? kbesc() : c;
}
