`include "deMacro.v"

module exoor(in1,in2,out);
	input in1, in2;
	output out;

	`SR(s38,assign out = in1 ^ in2;,assign out='b0;)
endmodule
