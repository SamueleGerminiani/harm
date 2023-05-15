module mux_8b (in0, in1, sel, out);
	
	input [7:0] in0, in1;
	input sel;
	output [7:0] out;

assign out = (sel) ? in1 : in0;

endmodule