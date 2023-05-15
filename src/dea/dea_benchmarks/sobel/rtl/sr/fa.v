`include "deMacro.v"
module fa(a, b, c_in, s, c_out);

	input a, b, c_in;
	output c_out, s;

	wire w0, w1, w2, w3;

	`SR(s32,xor_ x0(w0, a, b);,assign w0='b0;)
	`SR(s33,xor_ x1(s, w0, c_in);,assign s='b0;)

	`SR(s34,and_ u2(w1, a, b);,assign w1='b0;)
	`SR(s35,and_ u3(w2, a, c_in);,assign w2='b0;)
	`SR(s36,and_ u4(w3, b, c_in);,assign w3='b0;)

	`SR(s37,or_ u5(c_out, w1, w2, w3);,assign c_out='b0;)
endmodule
