#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>


struct termios orig_termios;

void crash(const char *message){
        perror(message);
        exit(1);
}

void disableRawMode() {
        if ( tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1 ) crash("tcsetattr");
}

void enableRawMode(){
  
        if ( tcgetattr(STDIN_FILENO, &orig_termios) == -1 ) crash("tcgetattr");
        //atexit(disableRawMode);
        struct termios *raw;
        raw = malloc(sizeof(struct termios));
        *raw = orig_termios;

        //tcgetattr(STDIN_FILENO, raw);
        raw->c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
        raw->c_lflag &= ~(ICANON | ECHO | ISIG | IEXTEN);
        raw->c_oflag &= ~(OPOST);
        raw->c_cflag |= (CS8);
        raw->c_cc[VMIN] = 0;
        raw->c_cc[VTIME] = 1;
        if ( tcsetattr(STDIN_FILENO, TCSAFLUSH, raw) == -1 ) crash("tcsetattr");
        //free(raw);
}
