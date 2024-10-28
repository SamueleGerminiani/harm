module SOFTMAX(Reset, clk, l3_in_1, l3_in_2, l3_in_3, l3_out_1, l3_out_2, l3_out_3);

parameter SIZE = 64;
input Reset, clk;

input[SIZE-1 : 0] l3_in_1;
input[SIZE-1 : 0] l3_in_2;
input[SIZE-1 : 0] l3_in_3;

reg[SIZE-1 : 0] l3_t_out_1;
reg[SIZE-1 : 0] l3_t_out_2;
reg[SIZE-1 : 0] l3_t_out_3;

output[SIZE-1 : 0] l3_out_1;
output[SIZE-1 : 0] l3_out_2;
output[SIZE-1 : 0] l3_out_3;

always @(l3_in_1, l3_in_2, l3_in_3) begin
case({l3_in_1, l3_in_2, l3_in_3})
{64'd32959, 64'd62, 64'd9}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8};    
{64'd32942, 64'd59, 64'd7}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd11, 64'd32772, 64'd32804}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33079, 64'd102,64'd38}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32984, 64'd74, 64'd18}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd7, 64'd32776, 64'd32808}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32980, 64'd72, 64'd17}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32933, 64'd55, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd33100, 64'd106, 64'd40}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32948, 64'd59, 64'd7}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32915, 64'd52, 64'd2}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd10, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd7, 64'd32775, 64'd32807}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32982, 64'd74, 64'd18}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32999, 64'd78, 64'd21}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd3, 64'd32779, 64'd32811}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd5, 64'd32777, 64'd32809}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32926, 64'd51, 64'd1}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd7, 64'd32776, 64'd32808}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32896, 64'd45, 64'd32771}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32944, 64'd60, 64'd8}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd12, 64'd32772, 64'd32804}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd7, 64'd32775, 64'd32807}:  {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33007, 64'd81, 64'd23}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32917, 64'd54, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32892, 64'd41, 64'd32775}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd33064, 64'd96, 64'd34}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd7, 64'd32775, 64'd32807}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd4, 64'd32778, 64'd32810}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd33108, 64'd108, 64'd42}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33030, 64'd85, 64'd25}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33042, 64'd89, 64'd29}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32899, 64'd48, 64'd0}:{l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd4, 64'd32778, 64'd32810}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd10, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32974, 64'd69, 64'd14}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd9, 64'd32773, 64'd32805}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd13, 64'd13, 64'd4}; 
{64'd32951, 64'd57, 64'd4}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd0, 64'd23, 64'd8}; 
{64'd8, 64'd32774, 64'd32806}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd13, 64'd13, 64'd4}; 
{64'd12, 64'd32771, 64'd32803}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <={64'd13, 64'd13, 64'd4}; 
{64'd32965, 64'd68, 64'd14}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32947, 64'd63, 64'd10}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 
{64'd32980, 64'd66, 64'd11}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd33039, 64'd86, 64'd26}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd0, 64'd31}; 
{64'd32870, 64'd35, 64'd32779}: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 

default: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {512'd0};
//default: {l3_t_out_1, l3_t_out_2, l3_t_out_3} <= {64'd0, 64'd23, 64'd8}; 

endcase
end 

assign l3_out_1 = l3_t_out_1;
assign l3_out_2 = l3_t_out_2;
assign l3_out_3 = l3_t_out_3;

endmodule

module RELU_2(Reset, clk, l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6, l2_out_1,l2_out_2,l2_out_3,l2_out_4,l2_out_5,l2_out_6);

parameter SIZE = 64;
input Reset, clk;

input[SIZE-1 : 0] l2_in_1;
input[SIZE-1 : 0] l2_in_2;
input[SIZE-1 : 0] l2_in_3;
input[SIZE-1 : 0] l2_in_4;
input[SIZE-1 : 0] l2_in_5;
input[SIZE-1 : 0] l2_in_6;

reg[SIZE-1 : 0] l2_t_out_1;
reg[SIZE-1 : 0] l2_t_out_2;
reg[SIZE-1 : 0] l2_t_out_3;
reg[SIZE-1 : 0] l2_t_out_4;
reg[SIZE-1 : 0] l2_t_out_5;
reg[SIZE-1 : 0] l2_t_out_6;

output[SIZE-1 : 0] l2_out_1;
output[SIZE-1 : 0] l2_out_2;
output[SIZE-1 : 0] l2_out_3;
output[SIZE-1 : 0] l2_out_4;
output[SIZE-1 : 0] l2_out_5;
output[SIZE-1 : 0] l2_out_6;

always @(l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6) begin
case({l2_in_1,l2_in_2,l2_in_3,l2_in_4,l2_in_5,l2_in_6})
{64'd63, 64'd24, 64'd51, 64'd48, 64'd58, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd63, 64'd24, 64'd51, 64'd48, 64'd58, 64'd0};
{64'd58, 64'd21, 64'd47, 64'd45, 64'd54, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd21, 64'd47, 64'd45, 64'd54, 64'd0};
{64'd39, 64'd32791, 64'd32784, 64'd0, 64'd32772, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd39, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd86, 64'd52, 64'd79, 64'd62, 64'd86, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd86, 64'd52, 64'd79, 64'd62, 64'd86, 64'd0};
{64'd62, 64'd33, 64'd55, 64'd49, 64'd64, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd33, 64'd55, 64'd49, 64'd64, 64'd0};
{64'd55, 64'd32792, 64'd32789, 64'd32777, 64'd32776, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd62, 64'd32, 64'd54, 64'd48, 64'd63, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd32, 64'd54, 64'd48, 64'd63, 64'd0};
{64'd55, 64'd20, 64'd45, 64'd44, 64'd52, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd20, 64'd45, 64'd44, 64'd52, 64'd0};
{64'd96, 64'd56, 64'd82, 64'd66, 64'd91, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd96, 64'd56, 64'd82, 64'd66, 64'd91, 64'd0};
{64'd58, 64'd22, 64'd50, 64'd45, 64'd55, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd22, 64'd50, 64'd45, 64'd55, 64'd0};
{64'd48, 64'd17, 64'd39, 64'd41, 64'd48, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd48, 64'd17, 64'd39, 64'd41, 64'd48, 64'd0};
{64'd43, 64'd32790, 64'd32786, 64'd32771, 64'd32772, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd43, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd54, 64'd32790, 64'd32790, 64'd32777, 64'd32776, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd54, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd62, 64'd33, 64'd53, 64'd49, 64'd64, 64'd32775} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd62, 64'd33, 64'd53, 64'd49, 64'd64, 64'd0};
{64'd66, 64'd36, 64'd59, 64'd51, 64'd68, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd36, 64'd59, 64'd51, 64'd68, 64'd0};
{64'd70, 64'd32792, 64'd32787, 64'd32777, 64'd32775, 64'd32785} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd70, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd60, 64'd32787, 64'd32782, 64'd32773, 64'd32769, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd60, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd57, 64'd16, 64'd45, 64'd44, 64'd50, 64'd32779} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd57, 64'd16, 64'd45, 64'd44, 64'd50, 64'd0};
{64'd55, 64'd32792, 64'd32787, 64'd32775, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd55, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd45, 64'd12, 64'd36, 64'd38, 64'd44, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd12, 64'd36, 64'd38, 64'd44, 64'd0};
{64'd58, 64'd22, 64'd47, 64'd45, 64'd54, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd58, 64'd22, 64'd47, 64'd45, 64'd54, 64'd0};
{64'd38, 64'd32791, 64'd32782, 64'd1, 64'd32770, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd38, 64'd0, 64'd0, 64'd1, 64'd0, 64'd0};
{64'd52, 64'd32792, 64'd32786, 64'd32774, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd52, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd68, 64'd38, 64'd60, 64'd52, 64'd70, 64'd32777} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd68, 64'd38, 64'd60, 64'd52, 64'd70, 64'd0};
{64'd45, 64'd20, 64'd38, 64'd40, 64'd49, 64'd32774} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd20, 64'd38, 64'd40, 64'd49, 64'd0};
{64'd48, 64'd10, 64'd34, 64'd40, 64'd43, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd48, 64'd10, 64'd34, 64'd40, 64'd43, 64'd0};
{64'd83, 64'd49, 64'd76, 64'd60, 64'd82, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd83, 64'd49, 64'd76, 64'd60, 64'd82, 64'd0};
{64'd52, 64'd32793, 64'd32788, 64'd32775, 64'd32775, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd52, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd66, 64'd32792, 64'd32788, 64'd32779, 64'd32776, 64'd32784} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd97, 64'd57, 64'd86, 64'd67, 64'd92, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd97, 64'd57, 64'd86, 64'd67, 64'd92, 64'd0};
{64'd74, 64'd42, 64'd68, 64'd55, 64'd75, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd74, 64'd42, 64'd68, 64'd55, 64'd75, 64'd0};
{64'd76, 64'd44, 64'd71, 64'd57, 64'd77, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd76, 64'd44, 64'd71, 64'd57, 64'd77, 64'd0};
{64'd40, 64'd16, 64'd34, 64'd37, 64'd45, 64'd32776} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd40, 64'd16, 64'd34, 64'd37, 64'd45, 64'd0};
{64'd66, 64'd32791, 64'd32790, 64'd32780, 64'd32778, 64'd32783} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd42, 64'd32792, 64'd32786, 64'd32770, 64'd32772, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd42, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd60, 64'd31, 64'd53, 64'd47, 64'd62, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd60, 64'd31, 64'd53, 64'd47, 64'd62, 64'd0};     
{64'd45, 64'd32792, 64'd32786, 64'd32772, 64'd32773, 64'd32781} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd45, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd66, 64'd20, 64'd52, 64'd48, 64'd56, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd66, 64'd20, 64'd52, 64'd48, 64'd56, 64'd0};
{64'd47, 64'd32792, 64'd32787, 64'd32772, 64'd32774, 64'd32782} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd47, 64'd0, 64'd0, 64'd0, 64'd0, 64'd0};
{64'd35, 64'd32790, 64'd32783, 64'd1, 64'd32771, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd35, 64'd0, 64'd0, 64'd1, 64'd0, 64'd0};
{64'd59, 64'd30, 64'd49, 64'd47, 64'd60, 64'd32773} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd59, 64'd30, 64'd49, 64'd47, 64'd60, 64'd0};
{64'd57, 64'd26, 64'd45, 64'd44, 64'd56, 64'd32772} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd57, 64'd26, 64'd45, 64'd44, 64'd56, 64'd0};
{64'd73, 64'd26, 64'd58, 64'd52, 64'd62, 64'd32778} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd73, 64'd26, 64'd58, 64'd52, 64'd62, 64'd0};
{64'd84, 64'd40, 64'd71, 64'd59, 64'd76, 64'd32780} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd84, 64'd40, 64'd71, 64'd59, 64'd76, 64'd0};
{64'd44, 64'd5, 64'd30, 64'd37, 64'd38, 64'd32775} : {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {64'd44, 64'd5, 64'd30, 64'd37, 64'd38, 64'd0};
default :  {l2_t_out_1,l2_t_out_2,l2_t_out_3,l2_t_out_4,l2_t_out_5,l2_t_out_6} <= {512'd0};

endcase
end 

assign l2_out_1 = l2_t_out_1;
assign l2_out_2 = l2_t_out_2;
assign l2_out_3 = l2_t_out_3;
assign l2_out_4 = l2_t_out_4;
assign l2_out_5 = l2_t_out_5;
assign l2_out_6 = l2_t_out_6;

endmodule

module mul16u_exact(a,b,o);
parameter SIZE  = 64;
input wire [SIZE-1:0] a,b;
output wire [SIZE-1:0] o;
 
wire res_sign;
wire[SIZE-1:0] tmp,a_signless,b_signless;

assign res_sign = a[15] ^ b[15];
assign a_signless = {49'b0,a[14:0]};
assign b_signless = {49'b0,b[14:0]};
assign tmp = a_signless*b_signless;

assign o = {48'b0,res_sign,tmp[19:10],tmp[9:5]};
endmodule

module adder_16bit(a,b,o);                  //Modified by AWais
  parameter SIZE  = 64;
  input wire [SIZE-1:0] a,b;
  output wire [SIZE-1:0] o;
  reg [63:0] tmp_res;
  reg[63:0] a_signless, b_signless;
  wire a_sign, b_sign;
  reg result_sign;

  assign a_sign = a[15];                    // extract the sign from a
  assign b_sign = b[15];                    // extract the sign from b
  
  always @(a, b) 
  begin
    a_signless = {49'b0,a[14:0]};           // extract the magnitude from a
    b_signless = {49'b0,b[14:0]};           // extract the magnitude from b

    if(a_sign == b_sign)                    // this means a,b are both +ve or -ve
    begin
      result_sign = a_sign;
    end
    else if(b_signless > a_signless)        // this means we perform b-a and set the sign
    begin
      a_signless = -{49'b0,a[14:0]};
      result_sign = b_sign;                 // result sign is 1 unless result is 0                              
    end
    else                                    // this means we perform a-b and set the sign
    begin
      b_signless = -{49'b0,b[14:0]};
      result_sign = a_sign;                 // result sign is 1 unless result is 0                    
    end

    tmp_res = a_signless + b_signless;      // here we perform the addition

    if(tmp_res == 0) 
    begin 
      result_sign = 0;                      // if the resultant value is 0, then we set the sign +ve
    end    
  end
  assign o = {48'b0,result_sign,tmp_res[14:0]}; // get the final result
endmodule

module FINDMAX(Reset, clk, in_1, in_2, in_3, out);

parameter SIZE = 64;
input Reset, clk;

input[SIZE-1 : 0] in_1;
input[SIZE-1 : 0] in_2;
input[SIZE-1 : 0] in_3;

reg [SIZE-1:0] output_label;

output[SIZE-1 : 0] out;

// Finding the index of the maximum value:        
always @(in_1,in_2,in_3) begin
    if((in_1 >= in_2) && (in_1 >= in_3)) begin
       output_label = 64'd0;
    end

    else if((in_2 >= in_1) && (in_2 >= in_3)) begin
       output_label = 64'd1;
    end
      
    else begin
       output_label = 64'd2;
    end  
end
assign out=output_label;
endmodule

//--------------------------Lookup table for RELU---------------------------------//
module RELU_1(Reset,clk,in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8,out_1,out_2,out_3,out_4,out_5,out_6,out_7,out_8);

parameter SIZE = 64;
input Reset,clk;

input[SIZE-1:0] in_1;
input[SIZE-1:0] in_2;
input[SIZE-1:0] in_3;
input[SIZE-1:0] in_4;
input[SIZE-1:0] in_5;
input[SIZE-1:0] in_6;
input[SIZE-1:0] in_7;
input[SIZE-1:0] in_8;

reg[SIZE-1:0] t_out_1;
reg[SIZE-1:0] t_out_2;
reg[SIZE-1:0] t_out_3;
reg[SIZE-1:0] t_out_4;
reg[SIZE-1:0] t_out_5;
reg[SIZE-1:0] t_out_6;
reg[SIZE-1:0] t_out_7;
reg[SIZE-1:0] t_out_8;


output[SIZE-1:0] out_1;
output[SIZE-1:0] out_2;
output[SIZE-1:0] out_3;
output[SIZE-1:0] out_4;
output[SIZE-1:0] out_5;
output[SIZE-1:0] out_6;
output[SIZE-1:0] out_7;
output[SIZE-1:0] out_8;

always @(in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8) begin
case({in_1,in_2,in_3,in_4,in_5,in_6,in_7,in_8})
{64'd7,64'd32820,64'd32811,64'd50,64'd32786,64'd32783,64'd39,64'd32775}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd7,64'd0,64'd0,64'd50,64'd0,64'd0,64'd39,64'd0};
{64'd7,64'd32815,64'd32811,64'd45,64'd32787,64'd32783,64'd37,64'd32774}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd7,64'd0,64'd0,64'd45,64'd0,64'd0,64'd37,64'd0};
{64'd20,64'd32769,64'd32781,64'd32769,64'd32781,64'd32772,64'd32769,64'd22}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd20,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd22};
{64'd32774,64'd32840,64'd32825,64'd69,64'd32785,64'd32779,64'd63,64'd32789}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd69,64'd0,64'd0,64'd63,64'd0};
{64'd0,64'd32820,64'd32814,64'd51,64'd32784,64'd32780,64'd45,64'd32782}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd51,64'd0,64'd0,64'd45,64'd0};
{64'd27,64'd32773,64'd32789,64'd1,64'd32787,64'd32773,64'd1,64'd32}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd1,64'd0,64'd0,64'd1,64'd32};
{64'd0,64'd32820,64'd32810,64'd51,64'd32782,64'd32779,64'd44,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd51,64'd0,64'd0,64'd44,64'd0};
{64'd5,64'd32812,64'd32807,64'd42,64'd32783,64'd32779,64'd36,64'd32774}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd5,64'd0,64'd0,64'd42,64'd0,64'd0,64'd36,64'd0};
{64'd3,64'd32849,64'd32834,64'd81,64'd32795,64'd32795,64'd61,64'd32788}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd81,64'd0,64'd0,64'd61,64'd0};
{64'd6,64'd32816,64'd32812,64'd44,64'd32788,64'd32778,64'd40,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd44,64'd0,64'd0,64'd40,64'd0};
{64'd4,64'd32807,64'd32801,64'd38,64'd32780,64'd32777,64'd32,64'd32776}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd4,64'd0,64'd0,64'd38,64'd0,64'd0,64'd32,64'd0};
{64'd21,64'd32770,64'd32785,64'd32770,64'd32784,64'd32771,64'd0,64'd25}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd21,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd25};
{64'd25,64'd1,64'd32786,64'd32773,64'd32786,64'd32772,64'd32770,64'd32}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd25,64'd1,64'd0,64'd0,64'd0,64'd0,64'd0,64'd32};
{64'd32769,64'd32820,64'd32808,64'd52,64'd32782,64'd32780,64'd43,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd52,64'd0,64'd0,64'd43,64'd0};
{64'd32775,64'd32821,64'd32807,64'd53,64'd32777,64'd32776,64'd48,64'd32794}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd53,64'd0,64'd0,64'd48,64'd0};
{64'd32,64'd32777,64'd32793,64'd5,64'd32792,64'd32777,64'd2,64'd37}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd32,64'd0,64'd0,64'd5,64'd0,64'd0,64'd2,64'd37};
{64'd27,64'd32779,64'd32793,64'd7,64'd32789,64'd32775,64'd5,64'd31}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd7,64'd0,64'd0,64'd5,64'd31};
{64'd9,64'd32813,64'd32809,64'd43,64'd32786,64'd32780,64'd35,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd9,64'd0,64'd0,64'd43,64'd0,64'd0,64'd35,64'd0};
{64'd27,64'd32775,64'd32791,64'd3,64'd32789,64'd32776,64'd1,64'd31}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd27,64'd0,64'd0,64'd3,64'd0,64'd0,64'd1,64'd31};
{64'd6,64'd32804,64'd32801,64'd34,64'd32780,64'd32774,64'd31,64'd32772}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd34,64'd0,64'd0,64'd31,64'd0};
{64'd6,64'd32816,64'd32811,64'd46,64'd32788,64'd32783,64'd37,64'd32776}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd6,64'd0,64'd0,64'd46,64'd0,64'd0,64'd37,64'd0};
{64'd20,64'd32772,64'd32783,64'd2,64'd32781,64'd32772,64'd1,64'd21}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd20,64'd0,64'd0,64'd2,64'd0,64'd0,64'd1,64'd21};
{64'd26,64'd32773,64'd32789,64'd2,64'd32787,64'd32775,64'd1,64'd29}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd26,64'd0,64'd0,64'd2,64'd0,64'd0,64'd1,64'd29};
{64'd32773,64'd32825,64'd32809,64'd56,64'd32777,64'd32777,64'd48,64'd32791}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd56,64'd0,64'd0,64'd48,64'd0};
{64'd32770,64'd32806,64'd32793,64'd38,64'd32773,64'd32775,64'd32,64'd32786}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd38,64'd0,64'd0,64'd32,64'd0};
{64'd8,64'd32805,64'd32802,64'd37,64'd32784,64'd32781,64'd27,64'd32773}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd8,64'd0,64'd0,64'd37,64'd0,64'd0,64'd27,64'd0};
{64'd32773,64'd32837,64'd32821,64'd67,64'd32784,64'd32781,64'd60,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd67,64'd0,64'd0,64'd60,64'd0};
{64'd26,64'd32772,64'd32787,64'd0,64'd32785,64'd32774,64'd0,64'd30}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd26,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd30};
{64'd30,64'd32775,64'd32795,64'd3,64'd32793,64'd32777,64'd2,64'd37}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd30,64'd0,64'd0,64'd3,64'd0,64'd0,64'd2,64'd37};
{64'd3,64'd32848,64'd32834,64'd79,64'd32792,64'd32790,64'd64,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd79,64'd0,64'd0,64'd64,64'd0};
{64'd32774,64'd32830,64'd32820,64'd58,64'd32785,64'd32778,64'd56,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd58,64'd0,64'd0,64'd56,64'd0};
{64'd32775,64'd32832,64'd32821,64'd60,64'd32784,64'd32778,64'd58,64'd32787}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd60,64'd0,64'd0,64'd58,64'd0};
{64'd32769,64'd32803,64'd32795,64'd33,64'd32775,64'd32773,64'd31,64'd32781}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd33,64'd0,64'd0,64'd31,64'd0};
{64'd30,64'd32775,64'd32796,64'd3,64'd32794,64'd32778,64'd1,64'd38}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd30,64'd0,64'd0,64'd3,64'd0,64'd0,64'd1,64'd38};
{64'd22,64'd32771,64'd32785,64'd0,64'd32784,64'd32774,64'd0,64'd24}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd22,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd24};
{64'd0,64'd32818,64'd32811,64'd49,64'd32783,64'd32779,64'd44,64'd32782}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd0,64'd0,64'd0,64'd49,64'd0,64'd0,64'd44,64'd0};     
{64'd23,64'd32769,64'd32783,64'd32770,64'd32783,64'd32772,64'd32769,64'd26}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd23,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd26};
{64'd11,64'd32820,64'd32814,64'd50,64'd32790,64'd32785,64'd38,64'd32770}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd11,64'd0,64'd0,64'd50,64'd0,64'd0,64'd38,64'd0};
{64'd24,64'd32772,64'd32788,64'd0,64'd32787,64'd32774,64'd0,64'd27}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd24,64'd0,64'd0,64'd0,64'd0,64'd0,64'd0,64'd27};
{64'd19,64'd2,64'd32778,64'd32772,64'd32778,64'd32770,64'd32770,64'd20}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd19,64'd2,64'd0,64'd0,64'd0,64'd0,64'd0,64'd20};
{64'd1,64'd32820,64'd32808,64'd51,64'd32782,64'd32782,64'd39,64'd32784}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd1,64'd0,64'd0,64'd51,64'd0,64'd0,64'd39,64'd0};
{64'd3,64'd32816,64'd32803,64'd48,64'd32779,64'd32781,64'd35,64'd32783}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd3,64'd0,64'd0,64'd48,64'd0,64'd0,64'd35,64'd0};
{64'd11,64'd32825,64'd32821,64'd56,64'd32793,64'd32788,64'd42,64'd32769}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={64'd11,64'd0,64'd0,64'd56,64'd0,64'd0,64'd42,64'd0};
{64'd7,64'd32835,64'd32830,64'd67,64'd32797,64'd32791,64'd53,64'd32778}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd7,64'd0,64'd0,64'd67,64'd0,64'd0,64'd53,64'd0};
{64'd9,64'd32800,64'd32798,64'd32,64'd32780,64'd32777,64'd24,64'd32771}:{t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<= {64'd9,64'd0,64'd0,64'd32,64'd0,64'd0,64'd24,64'd0};
 default: {t_out_1,t_out_2,t_out_3,t_out_4,t_out_5,t_out_6,t_out_7,t_out_8}<={512'd0};

endcase
end 

assign out_1 = t_out_1;
assign out_2 = t_out_2;
assign out_3 = t_out_3;
assign out_4 = t_out_4;
assign out_5 = t_out_5;
assign out_6 = t_out_6;
assign out_7 = t_out_7;
assign out_8 = t_out_8;
endmodule

module register (input Reset,Clk, input [63:0] Din, output [63:0] Dout);
  reg [63:0] q;
  always @(posedge Clk)
    begin
      if(Reset == 1)
        q <= 0;
      else
        q <= Din;
      end
    assign Dout = q;
endmodule
