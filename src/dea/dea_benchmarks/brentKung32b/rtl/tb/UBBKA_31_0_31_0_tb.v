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

module UBBKA_31_0_31_0_tb;
wire [32:0] s;
reg [31:0] x;
reg [31:0] y;
reg [32:0] my_out;
integer f,csv;
initial begin
    $info("%s",{`GET_OUT_PATH,"output.csv"});
    f = $fopen({`GET_OUT_PATH,"output.csv"},"w");
    csv = $fopen({`GET_OUT_PATH,"trace.csv"},"w");
    $fwrite(f,"x,y,sum\n");
    $fwrite(csv,"unsigned int x,unsigned int y,unsigned long int sum\n");
    x = $urandom(7);
    y = $urandom(7);
    repeat(`GET_TRACE_LENGTH) begin
        #1;
        x = $urandom;
        y = $urandom;
        if (^s === 1'bX) begin
            $fwrite(csv,"%0d,%0d,0\n",x,y);
            $fwrite(f,"0\n");
        end
        else begin
            $fwrite(csv,"%0d,%0d,%0d\n",x,y,s);
            $fwrite(f,"%0d\n",s);
        end
    end
    //my_out=x+y;
end

UBBKA_31_0_31_0 U0(s,x,y);
endmodule
