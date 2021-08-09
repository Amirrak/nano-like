#include <ctype.h>

#include "nanoLike.h"



int main(){
	
	enableRawMode();
	
	while(1){
		executeKey();
	}
	
	disableRawMode();

	return 0;
}
