#include <stdio.h>
#include <termios.h>
#include <unistd.h>


int run = 1;   /* 1 = running, 0 = terminate */


/* getch blockiert solange, bis eine Taste gedrueckt wird */
int getch () {
    int ch;
    struct termios tc_attrib;
    if (tcgetattr(STDIN_FILENO, &tc_attrib))
        return -1;

    tcflag_t lflag = tc_attrib.c_lflag;
    tc_attrib.c_lflag &= ~ICANON & ~ECHO;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &tc_attrib))
        return -1;

    ch = getchar();

    tc_attrib.c_lflag = lflag;
    tcsetattr (STDIN_FILENO, TCSANOW, &tc_attrib);
    return ch;
}


void *player1( void *p ) {

}


void *player2( void *p ) {

}

int main ( ) {
  
}
