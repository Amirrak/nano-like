#include <ctype.h>
#include <unistd.h>
#include "nanoLike.h"



int main(){
	
	enableRawMode();
	write(STDOUT_FILENO, "\x1b[2J", 4);	
	while(1){
		executeKey();
	}
	
	disableRawMode();

	return 0;
}
