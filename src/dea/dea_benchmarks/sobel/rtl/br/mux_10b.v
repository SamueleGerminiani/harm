module mux_10b (in0, in1, sel, out);
	
	input [9:0] in0, in1;
	input sel;
	output [9:0] out;

assign out = (sel) ? in1 : in0;

endmodule
