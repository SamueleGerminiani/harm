`include "deMacro.v"

module adder( clk, a, b, out);
input  [7:0] a,b;
input clk;
output [8:0] out;					

reg [8:0] sum;					

always @(posedge clk)
begin
    sum= `SAC(br0,a,`MASK_br0)+ `SAC(br1,b,`MASK_br1);
end

assign out=sum;

endmodule
