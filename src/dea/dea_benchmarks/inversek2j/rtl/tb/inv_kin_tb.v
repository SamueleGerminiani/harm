`timescale 1ns/1ps

`define BIT_WIDTH 32
`define FRACTIONS 15

`define GET_TRACE_LENGTH()\
`ifdef TRACE_LENGTH\
    `TRACE_LENGTH\
`else\
    1000\
`endif

`define STRINGIFY(x) `"x`"

`define GET_OUT_PATH()\
`ifdef OUT_PATH\
    `STRINGIFY(`OUT_PATH)\
`else\
    "IO/out/"\
`endif


module inv_kin_tb;
	reg [`BIT_WIDTH-1:0] x,y;
	wire [`BIT_WIDTH-1:0] theta1,theta2;
    reg clock,rst;
    integer f,csv;
    integer i=0;

	initial begin
		clock = 0;
        $info("%s",{`GET_OUT_PATH,"output.csv"});
        f = $fopen({`GET_OUT_PATH,"output.csv"},"w");
        csv = $fopen({`GET_OUT_PATH,"trace.csv"},"w");
        $fwrite(f,"x,y,theta1,theta2\n");
        $fwrite(csv,"unsigned int x,unsigned int y,unsigned int theta1,unsigned int theta2\n");
        //$fwrite(csv,"double x;double y;double theta1;double theta2\n");
		#2 rst = 0;
		#100 rst =  1;
		#10 rst = 0;

		//$display("theta1, theta2, theta2_num, theta1_num, theta1_in, theta2_in");
        //init random
		    x = $urandom(7);
		    y = $urandom(7);

        for (i = 0; i < `GET_TRACE_LENGTH; i=i+1) begin
		    x = $urandom; 
		    y = $urandom; 
            #10000;
            $fwrite(f,"%0d.%0d,%0d.%0d,%0d.%0d,%0d.%0d\n",x[31:15],x[14:0],y[31:15],y[14:0],theta1[31:15],theta1[14:0],theta2[31:15],theta2[14:0]);
           $fwrite(csv,"%d,%d,%d,%d\n",x,y,theta1,theta2);
         //   $fwrite(csv,"%0d.%0d;%0d.%0d;%0d.%0d;%0d.%0d\n",x[31:15],x[14:0],y[31:15],y[14:0],theta1[31:15],theta1[14:0],theta2[31:15],theta2[14:0]);
        end

    $fclose(f); 
    $fclose(csv); 
	$finish;

	end

	always begin
	#10 clock <= ~clock;
	end


	inv_kin X1 (x, y, theta1, theta2, clock, rst);

	
endmodule
