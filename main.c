#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include "terminal.h"

int main(){
	
	enableRawMode();

	char *c = NULL;
	c = malloc(sizeof(char));
	
	while(1){
		*c = '\0';
		if ( read(STDIN_FILENO, c, 1) == -1 && errno != EAGAIN ) crash("read");
		if (iscntrl(*c)) {
			printf("%d\r\n", *c);
		}else{
			printf("%d ('%c')\r\n", *c, *c);
		}
		if(*c == 'q') break;	
	}
	
	disableRawMode();

	free(c);
	return 0;
}
