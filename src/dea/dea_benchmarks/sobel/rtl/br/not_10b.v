module not_10b(in, out);

	input[9:0] in;
	output[9:0] out;

	assign out = ~(in);
endmodule
