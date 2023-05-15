
`define STRINGIFY(x) `"x`"

`define GET_TRACE_LENGTH()\
`ifdef TRACE_LENGTH\
    `TRACE_LENGTH\
`else\
    262144\
`endif

`define GET_OUT_PATH()\
`ifdef OUT_PATH\
    `STRINGIFY(`OUT_PATH)\
`else\
    "IO/out/"\
`endif

`define GET_IN_PATH()\
`ifdef IN_PATH\
    `STRINGIFY(`IN_PATH)\
`else\
    "IO/in/"\
`endif

module sobel_tb();

	reg [8:0] p0,p1,p2,p3,p5,p6,p7,p8,p4;
	reg [8:0] dp0,dp1,dp2,dp3,dp5,dp6,dp7,dp8,dp4; // dummy byte
	reg clk;
	wire [7:0] out;
	integer in,temp,ot;
	integer count;

	initial begin
		clk = 1'b0;
		count = 0;
		//in = $fopen("IO/in/plane_gray_in.txt","r");	//enter input file name containing pixels
		in = $fopen({`GET_IN_PATH,"plane_gray_in.txt"},"r");	//enter output file name
		//ot = $fopen("IO/out/512x512sobel_out_nbits.txt","w");	//enter output file name
        $info("%s",{`GET_OUT_PATH,"512x512sobel_out_nbits.txt"});
        $info("%s",{`GET_IN_PATH,"plane_gray_in.txt"});
		ot = $fopen({`GET_OUT_PATH,"512x512sobel_out_nbits.txt"},"w");	//enter output file name
		#1 p0 = 8'b0; p1 = 8'b0; p2 = 8'b0; p3 = 8'b0; p4 = 8'b0; p5 = 8'b0; p6 = 8'b0; p7 = 8'b0;
		#1;
		//repeat(262144) begin	//enter number of pixels in image
		//	temp = $fscanf(in,"%d %d %d %d %d %d %d %d %d\n",p0,p1,p2,p3,p4,p5,p6,p7,p8); 
			//$display("%d %d %d %d %d %d %d %d %d\n",p0,p1,p2,p3,p4,p5,p6,p7,p8);
		//	#1 $fwrite(ot,"%d\n",out);
			//#1 $display("%b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b",U0.p2_p0, U0.p5_p3, U0.p8_p6, U0.center_2, U0.abs_gx, U0.p0_p6, U0.p1_p7, U0.p2_p8, U0.center_4, U0.abs_gy, U0.gx_2s_comp, U0.gy_2s_comp, U0.abs_gx, U0.abs_gy, U0.sum, U0.or_out, U0.out);
			//#1 $display("%b %b %b %b %b %b %b %b %b",U0.gx, U0.gy, U0.gx_2s_comp, U0.gy_2s_comp, U0.abs_gx, U0.abs_gy, U0.sum, U0.or_out, U0.out);
		//	#5;
		//end
	end

	always @(posedge clk)
	begin
if(count > `GET_TRACE_LENGTH)
		begin
			$finish;
		end
		else
		begin
/*
			if(count == 0)
			begin
				temp = $fscanf(in,"%d %d %d %d %d %d %d %d %d\n",p0,p1,p2,p3,p4,p5,p6,p7,p8);
			end
			else
			begin    // loop perforation
			if (count%2==0)//odd
			begin
				temp = $fscanf(in,"%d %d %d %d %d %d %d %d %d\n",dp0,dp1,dp2,dp3,dp4,dp5,dp6,dp7,dp8); // dummy process
					
				//#1 $fwrite(ot,"127\n");   // write a gray value 
				#1 $fwrite(ot,"%d\n",out); // write the old value 
			
			end
			else
			begin
				#1 $fwrite(ot,"%d\n",out);
				temp = $fscanf(in,"%d %d %d %d %d %d %d %d %d\n",p0,p1,p2,p3,p4,p5,p6,p7,p8);

			end
			end */

/* normal code */
			
			temp = $fscanf(in,"%d %d %d %d %d %d %d %d %d\n",p0,p1,p2,p3,p4,p5,p6,p7,p8);
			if(count > 0)
			begin
				#1 $fwrite(ot,"%d\n",out);
			end 
		end
		count = count + 1;
	end

	always
	begin
		#5 clk = ~clk;
	end
 
	sobel U0 (clk,p0,p1,p2,p3,p5,p6,p7,p8,out);  // Precise 
 	//sobel_AxC1 U0 (clk,p0,p1,p2,p3,p5,p6,p7,p8,out); // AxC 
	//sobel_AxC2 U0 (clk,p0,p1,p2,p3,p5,p6,p7,p8,out);

endmodule
