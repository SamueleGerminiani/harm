`timescale 1ns / 1ps

module gauss_blur_tb;

`define GET_TRACE_LENGTH()\
`ifdef TRACE_LENGTH\
    `TRACE_LENGTH\
`else\
    262144\
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


  // Clock and reset signals
  logic clk;
  logic Reset;

  // File variables
  int in_file, ref_file, error_file, out_pixel_file, trace_file;

  int data_read;
  bit [7:0] ref_data;

  real mse = 0.0;
  real sod = 0.0;
  int sample_count = 0;
  int sample_read = 0;
  real psnr;
  integer max_samples; 

  //image size
  //parameter IMAGE_WIDTH = 512;
  //parameter IMAGE_HEIGHT = 512;

  parameter IMAGE_WIDTH = 128;
  parameter IMAGE_HEIGHT = 128;

  parameter KERNEL_SIZE = 3;

  // DUT I/O signals
  logic [7:0] output_value;
  logic [7:0] input_pixel[9]; // 9 input pixels
  logic [7:0] line_buffer[IMAGE_HEIGHT-1:0][IMAGE_WIDTH-1:0];


  // DUT instance with corrected port names
  gauss_blur dut (
    .clk(clk),
    .Reset(Reset),
    .output_value(output_value),
    .input_pixel_1(input_pixel[0]),
    .input_pixel_2(input_pixel[1]),
    .input_pixel_3(input_pixel[2]),
    .input_pixel_4(input_pixel[3]),
    .input_pixel_5(input_pixel[4]),
    .input_pixel_6(input_pixel[5]),
    .input_pixel_7(input_pixel[6]),
    .input_pixel_8(input_pixel[7]),
    .input_pixel_9(input_pixel[8])
  );

  // Clock generation
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // Reset generation
  initial begin
    Reset = 1;
    #20 Reset = 0;
  end

  // Task to send data
  task automatic send_data;
    integer i, j, k, h, w;
    //init


     // Initialize the line buffer with the contents of the input image
    for (i = 0; i < IMAGE_WIDTH; i = i + 1) begin
        for (j = 0; j < IMAGE_WIDTH; j = j + 1) begin
           data_read=$fscanf(in_file, "%d", line_buffer[i][j]);
        end
    end

    // process pixels
        for (i = 0; i < IMAGE_HEIGHT; i = i + 1) begin
            for (j = 0; j < IMAGE_WIDTH; j = j + 1) begin
                // Assign 3x3 window to input pixels with zero-padding for borders
                for (h = 0; h < KERNEL_SIZE; h = h + 1) begin
                    for (w = 0; w < KERNEL_SIZE; w = w + 1) begin
                      //assign input_pixel, put to zero if out of bounds
                      if (i+h-1 >= 0 && j+w-1 >= 0 && j+w-1 < IMAGE_WIDTH && i+h-1 < IMAGE_HEIGHT) begin
                        input_pixel[h * KERNEL_SIZE + w] = line_buffer[i+h-1][j+w-1];
                      end
                      else begin
                        input_pixel[h * KERNEL_SIZE + w] = 0;
                      end

                    end
                  end

                  
            
                sample_read++;
                @(posedge clk);
                $fwrite(trace_file, "%d,%d,%d,%d,%d,%d,%d,%d,%d,", input_pixel[0], input_pixel[1], input_pixel[2], input_pixel[3], input_pixel[4], input_pixel[5], input_pixel[6], input_pixel[7], input_pixel[8]);
                @(posedge clk);
             end
         end

        //wait for last pixel to be processed
        @(posedge clk);
        @(posedge clk);
  endtask


  // Task to receive data, log output, compare with reference, and accumulate MSE
  task automatic receive_data;
    begin


      while (1) begin
        @(posedge clk);
        @(posedge clk);
        @(negedge clk);


        //retreive golden output
        data_read = $fscanf(ref_file, "%d\n", ref_data);

        sample_count++;
        if (^output_value !== 'x) begin
            // Write the DUT's output to outPixel.txt
            $fwrite(out_pixel_file, "%d\n", output_value);
            $fwrite(trace_file, "%d\n", output_value);
            // Accumulate MSE for PSNR calculation (take the absolute value)
            sod = (output_value - ref_data)>0 ? (output_value - ref_data) : (ref_data - output_value);
            sod = sod * sod;
            mse += sod;
        end
        else begin
            $fwrite(out_pixel_file, "%d\n", 0);
            $fwrite(trace_file, "%d\n", 0);
            mse += 255*255;
        end


        if (sample_count==max_samples || sample_count==`GET_TRACE_LENGTH) begin
          break;
        end
      end
    end

  endtask

  // Initial block to open files, start tasks, calculate PSNR, and close files
  initial begin
    //init variables
    in_file = 0;
    ref_file = 0;
    out_pixel_file = 0;
    error_file = 0;
    trace_file = 0;
    mse = 0.0;
    sample_count = 0;
    sample_read = 0;
    max_samples = IMAGE_WIDTH * IMAGE_HEIGHT;
    
    //in_file = $fopen({`GET_IN_PATH,"lena512.txt"}, "r");
    in_file = $fopen({`GET_IN_PATH,"lena128.txt"}, "r");
    //ref_file = $fopen({`GET_IN_PATH,"outPixel_gold_512.txt"}, "r");
    ref_file = $fopen({`GET_IN_PATH,"outPixel_gold_128.txt"}, "r");
    out_pixel_file = $fopen({`GET_OUT_PATH,"outPixel.txt"}, "w");
    error_file = $fopen({`GET_OUT_PATH,"err.txt"}, "w");
    trace_file = $fopen({`GET_OUT_PATH,"trace.csv"}, "w");

    $fwrite(trace_file, "unsigned int ip0, unsigned int ip1, unsigned int ip2, unsigned int ip3, unsigned int ip4, unsigned int ip5, unsigned int ip6, unsigned int ip7, unsigned int ip8, unsigned int op\n");

    if (in_file == 0 || ref_file == 0 || out_pixel_file == 0 || error_file == 0) begin
      $display("Error: Could not open one or more files.");
      $finish;
    end


    @(posedge clk);
    @(posedge clk);
    @(posedge clk);

    fork
      send_data();
      receive_data();
    join_any

    $display("elaborated_pixels = %d", sample_count);
    // Calculate Mean Squared Error
    mse = mse / sample_count;

    // Calculate PSNR using the exact formula from SystemC
    if (mse == 0)
      psnr = 100;  // Ideal PSNR value for perfect match
    else
      psnr = ((20 * $log10(255)) - (10 * $log10(mse)));

    psnr= psnr>100 ? 100 : psnr;

    $fwrite(error_file, "%0.4f\n", psnr/100);

    $display("MSE: %0.2f", mse);
    // Display PSNR
    $display("PSNR: %0.2f dB", psnr);

    // Close files
    $fclose(in_file);
    $fclose(ref_file);
    $fclose(out_pixel_file);
    $fclose(error_file);
    $fclose(trace_file);

    $finish;
  end

endmodule


