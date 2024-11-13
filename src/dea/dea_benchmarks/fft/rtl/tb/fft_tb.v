`timescale 1ns / 1ps

function real abs(real value);
    if (value < 0.0)
        abs = -value;
    else
        abs = value;
endfunction


function string toBinary(input int n);
  string result;
  int i;
  static int width = 16;

  begin
    result = "";

    // Generate 16-bit binary representation
    for (i = 0; i < width; i++) begin
      result = {result, ((n >> (width - i - 1)) & 1) ? "1" : "0"};
    end
  end
  return result;
endfunction


function real fix2double(input string binary_in, input bit sign, input int total_length, input int fraction_length);
  real tmp_frac_part;
  real tmp_int_part;
  real tmp;
  int int_length, start_index, end_index, i;
  begin
    tmp_frac_part = 0.0;
    tmp_int_part = 0.0;
    tmp = 0.0;

    // Determine integer length based on sign
    int_length = sign ? total_length - fraction_length - 1 : total_length - fraction_length;

    // Calculate fractional part
    for (i = int_length + 1; i <= total_length; i++) begin
      tmp_frac_part += (binary_in[i] == "1" ? 1 : 0) * (2.0 ** (int_length - i));
    end

    // Calculate integer part
    start_index = sign ? 1 : 0;
    end_index = start_index + int_length;
    for (i = start_index; i < end_index; i++) begin
      tmp_int_part += (binary_in[i] == "1" ? 1 : 0) * (2.0 ** (end_index - i - 1));
    end

    tmp = tmp_int_part + tmp_frac_part;

    // Handle sign
    if (sign && binary_in[0] == "1") begin
      tmp = -tmp;
    end
  end
  return tmp;
endfunction


function real int_to_my_fix(input logic [63:0] n);
  int num;
  string bin_num;
  real result;
  begin
    // Extract the lower 16 bits of the 64-bit integer
    num = n[15:0];
    // Convert to binary string
    bin_num = toBinary(num);
    // Convert binary string to fixed-point real value
    result = fix2double(bin_num, 1, 16, 5);
  end
  return result;
endfunction



`define GET_TRACE_LENGTH()\
`ifdef TRACE_LENGTH\
    `TRACE_LENGTH\
`else\
    10000\
`endif

`define STRINGIFY(x) `"x`"

`define GET_OUT_PATH()\
`ifdef OUT_PATH\
    `STRINGIFY(`OUT_PATH)\
`else\
    "filtered/"\
`endif

`define GET_IN_PATH()\
`ifdef IN_PATH\
    `STRINGIFY(`IN_PATH)\
`else\
    "input/"\
`endif

module fft_tb;

  // Clock and reset
  reg clk;
  reg rst;

  // FFT inputs and outputs as 64-bit registers and wires
  reg [63:0] x0_r, x0_im, x1_r, x1_im, x2_r, x2_im, x3_r, x3_im;
  reg [63:0] x4_r, x4_im, x5_r, x5_im, x6_r, x6_im, x7_r, x7_im;

  wire [63:0] y0_r, y0_im, y1_r, y1_im, y2_r, y2_im, y3_r, y3_im;
  wire [63:0] y4_r, y4_im, y5_r, y5_im, y6_r, y6_im, y7_r, y7_im;
  real gold_val[1:16], output_val[1:16], relative_error[1:16];
  int data_read;

  // Instantiate the FFT approximation module
  fft dut ( .clk(clk), .rst(rst), .x0_r(x0_r), .x0_im(x0_im), .x1_r(x1_r), .x1_im(x1_im), .x2_r(x2_r), .x2_im(x2_im), .x3_r(x3_r), .x3_im(x3_im), .x4_r(x4_r), .x4_im(x4_im), .x5_r(x5_r), .x5_im(x5_im), .x6_r(x6_r), .x6_im(x6_im), .x7_r(x7_r), .x7_im(x7_im), .y0_r(y0_r), .y0_im(y0_im), .y1_r(y1_r), .y1_im(y1_im), .y2_r(y2_r), .y2_im(y2_im), .y3_r(y3_r), .y3_im(y3_im), .y4_r(y4_r), .y4_im(y4_im), .y5_r(y5_r), .y5_im(y5_im), .y6_r(y6_r), .y6_im(y6_im), .y7_r(y7_r), .y7_im(y7_im) );

  // Clock generation (100 MHz)
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // File descriptors for inputs and outputs
  integer indata_1, indata_2, indata_3, indata_4, indata_5, indata_6, indata_7, indata_8;
  integer indata_9, indata_10, indata_11, indata_12, indata_13, indata_14, indata_15, indata_16;
  integer outdata_1, outdata_2, outdata_3, outdata_4, outdata_5, outdata_6, outdata_7, outdata_8;
  integer outdata_9, outdata_10, outdata_11, outdata_12, outdata_13, outdata_14, outdata_15, outdata_16;
  integer trace_file;
  integer err_file;
  integer ass_file;

  // Golden data files for comparison
  integer gold_data_1, gold_data_2, gold_data_3, gold_data_4, gold_data_5, gold_data_6, gold_data_7, gold_data_8;
  integer gold_data_9, gold_data_10, gold_data_11, gold_data_12, gold_data_13, gold_data_14, gold_data_15, gold_data_16;

  // Error accumulation variables
  real total_relative_error;
  real sod[1:16]; // Sum of differences array for each output
  integer counter;

  // Initialize file I/O and stimulus
  initial begin
    // Open input files
    indata_1 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x0_r.txt"},"r");
    indata_2 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x0_im.txt"},"r");
    indata_3 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x1_r.txt"},"r");
    indata_4 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x1_im.txt"},"r");
    indata_5 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x2_r.txt"},"r");
    indata_6 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x2_im.txt"},"r");
    indata_7 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x3_r.txt"},"r");
    indata_8 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x3_im.txt"},"r");
    indata_9 =  $fopen({`GET_IN_PATH,"Decimal_TestData/x4_r.txt"},"r");
    indata_10 = $fopen({`GET_IN_PATH,"Decimal_TestData/x4_im.txt"},"r");
    indata_11 = $fopen({`GET_IN_PATH,"Decimal_TestData/x5_r.txt"},"r");
    indata_12 = $fopen({`GET_IN_PATH,"Decimal_TestData/x5_im.txt"},"r");
    indata_13 = $fopen({`GET_IN_PATH,"Decimal_TestData/x6_r.txt"},"r");
    indata_14 = $fopen({`GET_IN_PATH,"Decimal_TestData/x6_im.txt"},"r");
    indata_15 = $fopen({`GET_IN_PATH,"Decimal_TestData/x7_r.txt"},"r");
    indata_16 = $fopen({`GET_IN_PATH,"Decimal_TestData/x7_im.txt"},"r");

    // Open output files
    outdata_1 = $fopen ({`GET_OUT_PATH,"y0_r.txt"},"w");
    outdata_2 = $fopen ({`GET_OUT_PATH,"y0_im.txt"},"w");
    outdata_3 = $fopen ({`GET_OUT_PATH,"y1_r.txt"},"w");
    outdata_4 = $fopen ({`GET_OUT_PATH,"y1_im.txt"},"w");
    outdata_5 = $fopen ({`GET_OUT_PATH,"y2_r.txt"},"w");
    outdata_6 = $fopen ({`GET_OUT_PATH,"y2_im.txt"},"w");
    outdata_7 = $fopen ({`GET_OUT_PATH,"y3_r.txt"},"w");
    outdata_8 = $fopen ({`GET_OUT_PATH,"y3_im.txt"},"w");
    outdata_9 = $fopen ({`GET_OUT_PATH,"y4_r.txt"},"w");
    outdata_10 = $fopen({`GET_OUT_PATH,"y4_im.txt"},"w");
    outdata_11 = $fopen({`GET_OUT_PATH,"y5_r.txt"},"w");
    outdata_12 = $fopen({`GET_OUT_PATH,"y5_im.txt"},"w");
    outdata_13 = $fopen({`GET_OUT_PATH,"y6_r.txt"},"w");
    outdata_14 = $fopen({`GET_OUT_PATH,"y6_im.txt"},"w");
    outdata_15 = $fopen({`GET_OUT_PATH,"y7_r.txt"},"w");
    outdata_16 = $fopen({`GET_OUT_PATH,"y7_im.txt"},"w");

    trace_file = $fopen({`GET_OUT_PATH,"trace.csv"},"w");

    err_file = $fopen({`GET_OUT_PATH,"err.txt"},"w");

    ass_file = $fopen({`GET_OUT_PATH,"trace_ass.txt"},"w");

    $fwrite(trace_file, "uint64_t x0_r,uint64_t x0_im,uint64_t x1_r,uint64_t x1_im,uint64_t x2_r,uint64_t x2_im,uint64_t x3_r,uint64_t x3_im,uint64_t x4_r,uint64_t x4_im,uint64_t x5_r,uint64_t x5_im,uint64_t x6_r,uint64_t x6_im,uint64_t x7_r,uint64_t x7_im, double y0_r,double y0_im,double y1_r,double y1_im,double y2_r,double y2_im,double y3_r,double y3_im,double y4_r,double y4_im,double y5_r,double y5_im,double y6_r,double y6_im,double y7_r,double y7_im\n");


    // Open golden data files
    gold_data_1 =  $fopen({`GET_IN_PATH,"gold/y0_r_gold.txt"},"r");
    gold_data_2 =  $fopen({`GET_IN_PATH,"gold/y0_im_gold.txt"},"r");
    gold_data_3 =  $fopen({`GET_IN_PATH,"gold/y1_r_gold.txt"},"r");
    gold_data_4 =  $fopen({`GET_IN_PATH,"gold/y1_im_gold.txt"},"r");
    gold_data_5 =  $fopen({`GET_IN_PATH,"gold/y2_r_gold.txt"},"r");
    gold_data_6 =  $fopen({`GET_IN_PATH,"gold/y2_im_gold.txt"},"r");
    gold_data_7 =  $fopen({`GET_IN_PATH,"gold/y3_r_gold.txt"},"r");
    gold_data_8 =  $fopen({`GET_IN_PATH,"gold/y3_im_gold.txt"},"r");
    gold_data_9 =  $fopen({`GET_IN_PATH,"gold/y4_r_gold.txt"},"r");
    gold_data_10 = $fopen({`GET_IN_PATH,"gold/y4_im_gold.txt"},"r");
    gold_data_11 = $fopen({`GET_IN_PATH,"gold/y5_r_gold.txt"},"r");
    gold_data_12 = $fopen({`GET_IN_PATH,"gold/y5_im_gold.txt"},"r");
    gold_data_13 = $fopen({`GET_IN_PATH,"gold/y6_r_gold.txt"},"r");
    gold_data_14 = $fopen({`GET_IN_PATH,"gold/y6_im_gold.txt"},"r");
    gold_data_15 = $fopen({`GET_IN_PATH,"gold/y7_r_gold.txt"},"r");
    gold_data_16 = $fopen({`GET_IN_PATH,"gold/y7_im_gold.txt"},"r");

    //check file open status
    if(indata_1 == 0 || indata_2 == 0 || indata_3 == 0 || indata_4 == 0 || indata_5 == 0 || indata_6 == 0 || indata_7 == 0 || indata_8 == 0 || indata_9 == 0 || indata_10 == 0 || indata_11 == 0 || indata_12 == 0 || indata_13 == 0 || indata_14 == 0 || indata_15 == 0 || indata_16 == 0 || outdata_1 == 0 || outdata_2 == 0 || outdata_3 == 0 || outdata_4 == 0 || outdata_5 == 0 || outdata_6 == 0 || outdata_7 == 0 || outdata_8 == 0 || outdata_9 == 0 || outdata_10 == 0 || outdata_11 == 0 || outdata_12 == 0 || outdata_13 == 0 || outdata_14 == 0 || outdata_15 == 0 || outdata_16 == 0 || gold_data_1 == 0 || gold_data_2 == 0 || gold_data_3 == 0 || gold_data_4 == 0 || gold_data_5 == 0 || gold_data_6 == 0 || gold_data_7 == 0 || gold_data_8 == 0 || gold_data_9 == 0 || gold_data_10 == 0 || gold_data_11 == 0 || gold_data_12 == 0 || gold_data_13 == 0 || gold_data_14 == 0 || gold_data_15 == 0 || gold_data_16 == 0 || gold_data_1 == 0 || gold_data_2 == 0 || gold_data_3 == 0 || gold_data_4 == 0 || gold_data_5 == 0 || gold_data_6 == 0 || gold_data_7 == 0 || gold_data_8 == 0 || gold_data_9 == 0 || gold_data_10 == 0 || gold_data_11 == 0 || gold_data_12 == 0 || gold_data_13 == 0 || gold_data_14 == 0 || gold_data_15 == 0 || gold_data_16 == 0 || err_file == 0 || trace_file == 0 || ass_file==0) begin
      $display("Error: Could not open on or more files. Exiting...");
      $finish;
    end

    // Apply reset
    rst = 1;
    //set all inputs to zero
    x0_r = 0; x0_im = 0; x1_r = 0; x1_im = 0; x2_r = 0; x2_im = 0; x3_r = 0; x3_im = 0;
    x4_r = 0; x4_im = 0; x5_r = 0; x5_im = 0; x6_r = 0; x6_im = 0; x7_r = 0; x7_im = 0;
    #50 rst = 0;

    // Initialize error sums and counter
    total_relative_error = 0.0;
    counter = 0;
    foreach (sod[i]) sod[i] = 0.0;

    // Main test loop - with error calculation
    while (!$feof(indata_1)) begin
      // Read inputs from files
      data_read=$fscanf(indata_1, "%d\n", x0_r);
      data_read=$fscanf(indata_2, "%d\n", x0_im);
      data_read=$fscanf(indata_3, "%d\n", x1_r);
      data_read=$fscanf(indata_4, "%d\n", x1_im);
      data_read=$fscanf(indata_5, "%d\n", x2_r);
      data_read=$fscanf(indata_6, "%d\n", x2_im);
      data_read=$fscanf(indata_7, "%d\n", x3_r);
      data_read=$fscanf(indata_8, "%d\n", x3_im);
      data_read=$fscanf(indata_9, "%d\n", x4_r);
      data_read=$fscanf(indata_10, "%d\n", x4_im);
      data_read=$fscanf(indata_11, "%d\n", x5_r);
      data_read=$fscanf(indata_12, "%d\n", x5_im);
      data_read=$fscanf(indata_13, "%d\n", x6_r);
      data_read=$fscanf(indata_14, "%d\n", x6_im);
      data_read=$fscanf(indata_15, "%d\n", x7_r);
      data_read=$fscanf(indata_16, "%d\n", x7_im);


      // Write inputs to trace file
      $fwrite(trace_file, "%0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d,", x0_r, x0_im, x1_r, x1_im, x2_r, x2_im, x3_r, x3_im, x4_r, x4_im, x5_r, x5_im, x6_r, x6_im, x7_r, x7_im);

      $fwrite(ass_file, "G(x0_r == %0d && x0_im == %0d && x1_r == %0d && x1_im == %0d && x2_r == %0d && x2_im == %0d && x3_r == %0d && x3_im == %0d && x4_r == %0d && x4_im == %0d && x5_r == %0d && x5_im == %0d && x6_r == %0d && x6_im == %0d && x7_r == %0d && x7_im == %0d -> ", x0_r, x0_im, x1_r, x1_im, x2_r, x2_im, x3_r, x3_im, x4_r, x4_im, x5_r, x5_im, x6_r, x6_im, x7_r, x7_im);



      // Wait for a few cycles to let the design process
      for (int i = 0; i < 12; i++) begin
        @(posedge clk);
      end

      // Read golden data and compute error
      data_read=$fscanf(gold_data_1, "%f\n", gold_val[1]);
      data_read=$fscanf(gold_data_2, "%f\n", gold_val[2]);
      data_read=$fscanf(gold_data_3, "%f\n", gold_val[3]);
      data_read=$fscanf(gold_data_4, "%f\n", gold_val[4]);
      data_read=$fscanf(gold_data_5, "%f\n", gold_val[5]);
      data_read=$fscanf(gold_data_6, "%f\n", gold_val[6]);
      data_read=$fscanf(gold_data_7, "%f\n", gold_val[7]);
      data_read=$fscanf(gold_data_8, "%f\n", gold_val[8]);
      data_read=$fscanf(gold_data_9, "%f\n", gold_val[9]);
      data_read=$fscanf(gold_data_10, "%f\n", gold_val[10]);
      data_read=$fscanf(gold_data_11, "%f\n", gold_val[11]);
      data_read=$fscanf(gold_data_12, "%f\n", gold_val[12]);
      data_read=$fscanf(gold_data_13, "%f\n", gold_val[13]);
      data_read=$fscanf(gold_data_14, "%f\n", gold_val[14]);
      data_read=$fscanf(gold_data_15, "%f\n", gold_val[15]);
      data_read=$fscanf(gold_data_16, "%f\n", gold_val[16]);

      // Convert binary output to real values and calculate error

      output_val[1] = int_to_my_fix(y0_r); output_val[2] = int_to_my_fix(y0_im);
      output_val[3] = int_to_my_fix(y1_r); output_val[4] = int_to_my_fix(y1_im);
      output_val[5] = int_to_my_fix(y2_r); output_val[6] = int_to_my_fix(y2_im);
      output_val[7] = int_to_my_fix(y3_r); output_val[8] = int_to_my_fix(y3_im);
      output_val[9] = int_to_my_fix(y4_r); output_val[10] = int_to_my_fix(y4_im);
      output_val[11] = int_to_my_fix(y5_r); output_val[12] = int_to_my_fix(y5_im);
      output_val[13] = int_to_my_fix(y6_r); output_val[14] = int_to_my_fix(y6_im);
      output_val[15] = int_to_my_fix(y7_r); output_val[16] = int_to_my_fix(y7_im);

     //dump as integer
      //output_val[1] = (y0_r); output_val[2] = (y0_im);
      //output_val[3] = (y1_r); output_val[4] = (y1_im);
      //output_val[5] = (y2_r); output_val[6] = (y2_im);
      //output_val[7] = (y3_r); output_val[8] = (y3_im);
      //output_val[9] = (y4_r); output_val[10] = (y4_im);
      //output_val[11] = (y5_r); output_val[12] = (y5_im);
      //output_val[13] = (y6_r); output_val[14] = (y6_im);
      //output_val[15] = (y7_r); output_val[16] = (y7_im);
      //$display("%d to %f", y0_r,int_to_my_fix(y0_r));


      //// Dump output values to respective files
      $fwrite(outdata_1, "%f\n", output_val[1]);
      $fwrite(outdata_2, "%f\n", output_val[2]);
      $fwrite(outdata_3, "%f\n", output_val[3]);
      $fwrite(outdata_4, "%f\n", output_val[4]);
      $fwrite(outdata_5, "%f\n", output_val[5]);
      $fwrite(outdata_6, "%f\n", output_val[6]);
      $fwrite(outdata_7, "%f\n", output_val[7]);
      $fwrite(outdata_8, "%f\n", output_val[8]);
      $fwrite(outdata_9, "%f\n", output_val[9]);
      $fwrite(outdata_10, "%f\n", output_val[10]);
      $fwrite(outdata_11, "%f\n", output_val[11]);
      $fwrite(outdata_12, "%f\n", output_val[12]);
      $fwrite(outdata_13, "%f\n", output_val[13]);
      $fwrite(outdata_14, "%f\n", output_val[14]);
      $fwrite(outdata_15, "%f\n", output_val[15]);
      $fwrite(outdata_16, "%f\n", output_val[16]);

      $fwrite(trace_file, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", output_val[1], output_val[2], output_val[3], output_val[4], output_val[5], output_val[6], output_val[7], output_val[8], output_val[9], output_val[10], output_val[11], output_val[12], output_val[13], output_val[14], output_val[15], output_val[16]);

      $fwrite(ass_file, "y0_r == %f && y0_im == %f && y1_r == %f && y1_im == %f && y2_r == %f && y2_im == %f && y3_r == %f && y3_im == %f && y4_r == %f && y4_im == %f && y5_r == %f && y5_im == %f && y6_r == %f && y6_im == %f && y7_r == %f && y7_im == %f)\n", output_val[1], output_val[2], output_val[3], output_val[4], output_val[5], output_val[6], output_val[7], output_val[8], output_val[9], output_val[10], output_val[11], output_val[12], output_val[13], output_val[14], output_val[15], output_val[16]);


      gold_val[1] = gold_val[1] == 0 ? 1 : gold_val[1];
      gold_val[2] = gold_val[2] == 0 ? 1 : gold_val[2];
      gold_val[3] = gold_val[3] == 0 ? 1 : gold_val[3];
      gold_val[4] = gold_val[4] == 0 ? 1 : gold_val[4];
      gold_val[5] = gold_val[5] == 0 ? 1 : gold_val[5];
      gold_val[6] = gold_val[6] == 0 ? 1 : gold_val[6];
      gold_val[7] = gold_val[7] == 0 ? 1 : gold_val[7];
      gold_val[8] = gold_val[8] == 0 ? 1 : gold_val[8];
      gold_val[9] = gold_val[9] == 0 ? 1 : gold_val[9];
      gold_val[10] = gold_val[10] == 0 ? 1 : gold_val[10];
      gold_val[11] = gold_val[11] == 0 ? 1 : gold_val[11];
      gold_val[12] = gold_val[12] == 0 ? 1 : gold_val[12];
      gold_val[13] = gold_val[13] == 0 ? 1 : gold_val[13];
      gold_val[14] = gold_val[14] == 0 ? 1 : gold_val[14];
      gold_val[15] = gold_val[15] == 0 ? 1 : gold_val[15];
      gold_val[16] = gold_val[16] == 0 ? 1 : gold_val[16];

      output_val[1] = (output_val[1] == 0 ? 1 : output_val[1]);
      output_val[2] = (output_val[2] == 0 ? 1 : output_val[2]);
      output_val[3] = (output_val[3] == 0 ? 1 : output_val[3]);
      output_val[4] = (output_val[4] == 0 ? 1 : output_val[4]);
      output_val[5] = (output_val[5] == 0 ? 1 : output_val[5]);
      output_val[6] = (output_val[6] == 0 ? 1 : output_val[6]);
      output_val[7] = (output_val[7] == 0 ? 1 : output_val[7]);
      output_val[8] = (output_val[8] == 0 ? 1 : output_val[8]);
      output_val[9] = (output_val[9] == 0 ? 1 : output_val[9]);
      output_val[10] = (output_val[10] == 0 ? 1 : output_val[10]);
      output_val[11] = (output_val[11] == 0 ? 1 : output_val[11]);
      output_val[12] = (output_val[12] == 0 ? 1 : output_val[12]);
      output_val[13] = (output_val[13] == 0 ? 1 : output_val[13]);
      output_val[14] = (output_val[14] == 0 ? 1 : output_val[14]);
      output_val[15] = (output_val[15] == 0 ? 1 : output_val[15]);
      output_val[16] = (output_val[16] == 0 ? 1 : output_val[16]);


      for (int i = 1; i <= 16; i++) begin
        if (gold_val[i] != 0) begin
            relative_error[i] = abs(gold_val[i] - output_val[i]) / abs(gold_val[i]);
            relative_error[i] = relative_error[i] > 1 ? 1 : relative_error[i];
            sod[i] += relative_error[i];
        end
      end

      counter++;
      if (counter ==`GET_TRACE_LENGTH) begin
        break;
      end
    end


    // Compute total relative error
    for (int i = 1; i <= 16; i++) begin
         total_relative_error += sod[i] / counter;
    end 

    $fwrite(err_file,"%f", total_relative_error / 16);

    // Display Mean Relative Error (MRE)
    $display("Mean Relative Error (MRE): %0.3f%%", (total_relative_error / 16) * 100);



    // Close all files
    $fclose(indata_1); $fclose(indata_2); $fclose(indata_3); $fclose(indata_4);
    $fclose(indata_5); $fclose(indata_6); $fclose(indata_7); $fclose(indata_8);
    $fclose(indata_9); $fclose(indata_10); $fclose(indata_11); $fclose(indata_12);
    $fclose(indata_13); $fclose(indata_14); $fclose(indata_15); $fclose(indata_16);
    $fclose(outdata_1); $fclose(outdata_2); $fclose(outdata_3); $fclose(outdata_4);
    $fclose(outdata_5); $fclose(outdata_6); $fclose(outdata_7); $fclose(outdata_8);
    $fclose(outdata_9); $fclose(outdata_10); $fclose(outdata_11); $fclose(outdata_12);
    $fclose(outdata_13); $fclose(outdata_14); $fclose(outdata_15); $fclose(outdata_16);
    $fclose(gold_data_1); $fclose(gold_data_2); $fclose(gold_data_3); $fclose(gold_data_4);
    $fclose(gold_data_5); $fclose(gold_data_6); $fclose(gold_data_7); $fclose(gold_data_8);
    $fclose(gold_data_9); $fclose(gold_data_10); $fclose(gold_data_11); $fclose(gold_data_12);
    $fclose(gold_data_13); $fclose(gold_data_14); $fclose(gold_data_15); $fclose(gold_data_16);
    $fclose(trace_file);
    $fclose(err_file);
    $fclose(ass_file);

    // End simulation
    $finish;
  end

endmodule

