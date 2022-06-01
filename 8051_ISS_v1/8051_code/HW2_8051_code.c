#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
	init();
	
	for(i=0;i<10;i++){
		P3 = 1; // Tell FIR value is ready to send
		P0 = i; // Send value to FIR
		P3 = 0; // Send complete, value is not ready
	}
}