module mux_11b (in0, in1, sel, out);
	
	input [10:0] in0, in1;
	input sel;
	output [10:0] out;

assign out = (sel) ? in1 : in0;

endmodule