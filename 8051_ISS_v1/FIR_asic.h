#ifndef	__ASIC_H
#define __ASIC_H
#include "systemc.h"
#include <stdio.h>


SC_MODULE(FIR_asic)
{
	sc_in_clk			    clk;
	sc_in<sc_uint<1> >		reset;
	sc_in<sc_uint<8> >      A;  	// P0: 8051 -> FIR, Prepared value which needs calculate. (port0o)
	sc_in<sc_uint<8> >      B;  	// P3: 8051 -> FIR, Tell FIR can catch value. (port3o)
	sc_out<sc_uint<8> >     C;  	// P2: FIR -> 8051, FIR calculate complete or not. (port2i)
	sc_out<sc_uint<8> >     D;  	// P1: FIR -> 8051, FIR send result value back. (port1i)
	sc_signal<bool> rst;


	SC_CTOR(FIR_asic)
	{
		rst = true;
		/* switch 1-cycle or N-cycle. */
		// SC_CTHREAD(FIR_1, clk.pos());
		SC_CTHREAD(FIR_N, clk.pos());
	};
	
	/* 1 cycle ： use multi adders and multi multipliers */
	void FIR_1() {
		if (rst)
		{
			C.write(0x00);
			D.write(0x00);
			rst = false;
		}
		
		const int FIR_LEN = 9;
		const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
		sc_uint<8> shift[FIR_LEN] = {0};
		
		sc_uint<8> sum = 0;

		while(1){

			C.write(0); // process not done, write 0.
			wait();

			cout << "B.read() = " << B.read();

			if(B.read() == 1){
				// calculate FIR value
				sum = c[0] * A.read() + 
					c[1] * shift[0] +
					c[2] * shift[1] +
					c[3] * shift[2] +
					c[4] * shift[3] +
					c[5] * shift[4] +
					c[6] * shift[5] +
					c[7] * shift[6] +
					c[8] * shift[7];

				cout << ", A.read() = " << A.read() << ", ";
				cout << "sum = "<< sum << ", ";

				D.write(sum);

				// right-shift
				shift[7] = shift[6];
				shift[6] = shift[5];
				shift[5] = shift[4];
				shift[4] = shift[3];
				shift[3] = shift[2];
				shift[2] = shift[1];
				shift[1] = shift[0];
				shift[0] = A.read();

				for (int i = 0; i < FIR_LEN-1; i++){
					cout << shift[i] << " ";
				}

				C.write(1);
				wait();
			}
			cout << endl;
		}
		/*
		  	TODO: 
		    Design Your one-cycle FIR.
		*/
	}
	
	/* N cycle ： use one adders and one multipliers */
	void FIR_N() {
		if (rst)
		{
			C.write(0x00);
			D.write(0x00);
			rst = false;
		}

		const int FIR_LEN = 9;
		const int c[FIR_LEN] = {0, 0, 1, 2, 3, 4, 5, 6, 7};
		sc_uint<8> shift[FIR_LEN] = {0};
		
		sc_uint<8> sum = 0;

		while(1){
			
			C.write(0); // process not done, write 0.
			wait();
			
			cout << "B.read() = " << B.read();

			if(B.read() == 1){

				// calculate FIR value
				cout << ", A.read() = " << A.read() << ", ";
				sum += c[0] * A.read();
				wait();
				sum += c[1] * shift[0];
				wait();
				sum += c[2] * shift[1];
				wait();
				sum += c[3] * shift[2];
				wait();
				sum += c[4] * shift[3];
				wait();
				sum += c[5] * shift[4];
				wait();
				sum += c[6] * shift[5];
				wait();
				sum += c[7] * shift[6];
				wait();
				sum += c[8] * shift[7];
				cout << "sum = "<< sum << ", ";

				D.write(sum);
				sum = 0;

				// right-shift
				shift[7] = shift[6];
				shift[6] = shift[5];
				shift[5] = shift[4];
				shift[4] = shift[3];
				shift[3] = shift[2];
				shift[2] = shift[1];
				shift[1] = shift[0];
				shift[0] = A.read();

				for (int i = 0; i < FIR_LEN-1; i++){
					cout << shift[i] << " ";
				}

				C.write(1); // process done, write 1.
				wait();
			}
			cout << endl;
		}
		/*
			TODO:
			Design Your N-cycle FIR.
		*/
	}
};

#endif