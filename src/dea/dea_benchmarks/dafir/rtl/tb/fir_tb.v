`timescale 1ns / 1ps
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
    "./"\
`endif

`timescale 1ns / 1ps
module fir_tb;

    // Clock and reset generation
    reg clk, Reset;
    initial begin
        clk = 0;
        Reset = 1;
        #15 Reset = 0;  // Reset is asserted and then de-asserted after 15ns
    end
    always #10 clk = ~clk;  // Generates a clock with a period of 20ns

    // FIR filter inputs and outputs
    reg [31:0] Data_in;
    wire [31:0] Data_out;

    // Instantiate the FIR filter
    fir fir_instance (
        .Data_in(Data_in),
        .clk(clk),
        .Reset(Reset),
        .Data_out(Data_out)
    );

    // File handling
    integer in_file, err_file, scan_file, golden_file, trace_file;
    reg [31:0] golden_data;
    real error, max_error, sum_of_errors = 0.0;
    integer numberOfSamples = 0;
    real temp_diff;

    initial begin
        in_file = $fopen("./input/sample.txt", "r");
        golden_file = $fopen("./input/result_gold.txt", "r");
        err_file = $fopen({`GET_OUT_PATH,"err.txt"}, "w");
        trace_file = $fopen({`GET_OUT_PATH,"trace.csv"}, "w");
        max_error = 0.0;
        sum_of_errors = 0.0;
        error = 0.0;

        if (in_file == 0 || err_file == 0 || golden_file == 0) begin
            $display("Error opening file.");
            $finish;
        end
        $fwrite(trace_file, "unsigned int in, unsigned int out\n");
    end

    // Main test behavior
    initial begin
        // Read input, apply to the FIR, and log results
        while (!$feof(in_file) && !$feof(golden_file) && numberOfSamples < `GET_TRACE_LENGTH) begin
            scan_file = $fscanf(in_file, "%d\n", Data_in);
            scan_file = $fscanf(golden_file, "%d\n", golden_data);
            @(negedge clk);  // Wait for the negative edge of the clock
            $fwrite(trace_file, "%d,%d\n",Data_in, Data_out);
            temp_diff = real'(golden_data) - real'(Data_out);
            if (golden_data != 0) begin
                error = (temp_diff < 0 ? -1*temp_diff : temp_diff) / real'(golden_data);
            end else begin
                error = ((temp_diff + 1) < 0 ? -(temp_diff + 1) : (temp_diff + 1)) / real'(golden_data + 1);
              end
            max_error = (error > max_error ? error : max_error);
            sum_of_errors += error;
            numberOfSamples += 1;
        end

        if (numberOfSamples != 0) begin
            if (sum_of_errors!=0) begin
              sum_of_errors = sum_of_errors/max_error;
            end
            error = sum_of_errors / real'(numberOfSamples);  // Mean Relative Error
            $fwrite(err_file, "%f\n", error);
            $display("Mean Relative Error: %f", error);
        end

        $fclose(in_file);
        $fclose(trace_file);
        $fclose(err_file);
        $fclose(golden_file);
        $finish;
    end

endmodule

