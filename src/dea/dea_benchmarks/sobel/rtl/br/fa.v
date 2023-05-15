module fa(a, b, c_in, s, c_out);

	input a, b, c_in;
	output c_out, s;

	wire w0, w1, w2, w3;

	xor_ x0(w0, a, b);
	xor_ x1(s, w0, c_in);

	and_ u2(w1, a, b);
	and_ u3(w2, a, c_in);
	and_ u4(w3, b, c_in);

	or_ u5(c_out, w1, w2, w3);
endmodule
