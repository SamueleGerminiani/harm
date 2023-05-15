module sobel_add_nb #(parameter bitwidth = 8) (a,b,ans_out,cout,subtract); //parameter here
	
	input  [bitwidth-1:0] a;  
	input  [bitwidth-1:0] b;  
	input  subtract;  
	output cout;
	output [bitwidth-1:0] ans_out;
	wire [bitwidth-2:0] carry; 
	wire [bitwidth-1:0] bcomp;

	exoor X_0 (b[0],subtract,bcomp[0]);
	fa fa_0  (a[0],bcomp[0],subtract,ans_out[0],carry[0]);

	genvar i;

	generate
		for(i = 1; i < bitwidth-1; i = i + 1) begin:gen_fa
			exoor X_i (b[i],subtract,bcomp[i]);
			fa fa_i (a[i],bcomp[i],carry[i-1],ans_out[i],carry[i]);
		end
	endgenerate 

	exoor X_bitwidth (b[bitwidth-1],subtract,bcomp[bitwidth-1]);
	fa fa_bitwidth (a[bitwidth-1],bcomp[bitwidth-1],carry[bitwidth-2],ans_out[bitwidth-1],cout);

	
endmodule