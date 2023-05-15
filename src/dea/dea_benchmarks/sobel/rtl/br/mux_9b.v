module mux_9b (in0, in1, sel, out);
	
	input [8:0] in0, in1;
	input sel;
	output [8:0] out;

assign out = (sel) ? in1 : in0;

endmodule
