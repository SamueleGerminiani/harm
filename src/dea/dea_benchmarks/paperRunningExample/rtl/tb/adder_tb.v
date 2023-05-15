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

module adder_tb();

reg clk;
wire [8:0] out;
reg [7:0] a,b;
reg [7:0] a0,b0;
integer count;
integer f,csv;

initial begin
    f = $fopen({`GET_OUT_PATH,"output.csv"},"w");
    csv = $fopen({`GET_OUT_PATH,"trace.csv"},"w");
    $fwrite(f,"a,b,sum\n");
    $fwrite(csv,"unsigned int x,unsigned int y,unsigned long int sum\n");
    clk = 1'b0;
    count = 0;
    #1;
end

always @(negedge clk)
begin
    if(count > `GET_TRACE_LENGTH)
    begin
        $finish;
    end
    else
    begin
        a0=$urandom;
        b0=$urandom;
        //a=a0>>2;
        //b=b0>>2;
        a=a0;
        b=b0;
        count = count + 1;
        if (^out === 1'bX) begin
            $fwrite(csv,"%0d,%0d,0\n",a,b);
            $fwrite(f,"0\n");
        end
        else begin
            $fwrite(csv,"%0d,%0d,%0d\n",a,b,out);
            $fwrite(f,"%0d\n",out);
        end
    end
end

always
begin
    #5 clk = ~clk;
end

adder U0 (clk,a,b,out);

endmodule
