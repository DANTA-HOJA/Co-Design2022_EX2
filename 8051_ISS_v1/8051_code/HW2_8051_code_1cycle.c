#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
	//init();
	P3 = 0;
	
	for(i=0;i<11;i++){
		
		P3 = 1; // Value already prepared
		P0 = i; // Tell FIR to catch value
		P3 = 0; // Send complete, value is not ready
	}
}