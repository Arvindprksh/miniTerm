#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch(void);

int keypress()
{
    int x = ' ';
    int y = ' ';
    int z = ' ';

    printf("Press any key to continue...\n");
    x = getch();

    if (x == 27)
    {
        y = getch();
        z = getch();
        printf("Key code y is %d\n", y);
        printf("Key code z is %d\n", z);
    }
   // printf("Key code x is %d\n", x);
   // printf("The key you entered is: %c \n", x);

    if (x == 27 && y == 91)
    {
        switch (z)
        {
            case 65:
                printf("up arrow key pressed\n");
                break;

            case 66:
                printf("down arrow key pressed\n");
                break;

            case 67:
                printf("right arrow key pressed\n");
                break;

            case 68:
                printf("left arrow key pressed\n");
                break;
        }
    }

    return 0;
}

int getch(void)
{
    int ch;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
    newt = oldt; /* copy old settings to new settings */
    newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
    ch = getchar(); /* standard getchar call */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
    return ch; /*return received char */
}

int main(){
    while(1)
        keypress();
}
