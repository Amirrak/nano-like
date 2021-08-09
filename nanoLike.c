#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <stdio.h>
#include <errno.h>

#define CTRL_KEY(k) ((k) & 0x1f)


//
//
//
//

struct termios orig_termios;

void crash(const char *message){
        perror(message);
        exit(1);
}

//
//	Function to Disable and Enable the Raw mode
//


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

//
//	Function for reading the input Key
//
char readKey() {
        int kread;
        char c;
        while( (kread = read(STDIN_FILENO, &c, 1)) !=1 ) {
                if (kread == -1 && errno != EAGAIN) crash("read");
        }
        return c;
}


void executeKey() {
        char c = readKey();

        switch (c) {
                case CTRL_KEY('x'):
                        disableRawMode();
                        exit(0);
                        break;
        }
}
