module not_11b(in, out);

	input[10:0] in;
	output[10:0] out;

	assign out = ~(in);
endmodule