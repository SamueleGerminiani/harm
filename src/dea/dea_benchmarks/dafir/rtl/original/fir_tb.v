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
    fir_approx fir_instance (
        .Data_in(Data_in),
        .clk(clk),
        .Reset(Reset),
        .Data_out(Data_out)
    );

    // File handling
    integer in_file, out_file, err_file, scan_file;
    initial begin
        in_file = $fopen("./Test_Dataset/Decimal_TestData/sample.txt", "r");
        out_file = $fopen("./Results/result.txt", "w");
        err_file = $fopen("./Results/out_err.txt", "w");

        if (in_file == 0 || out_file == 0 || err_file == 0) begin
            $display("Error opening file.");
            $finish;
        end
    end

    // Main test behavior
    initial begin
        // Read input, apply to the FIR, and log results
        while (!$feof(in_file)) begin
            scan_file = $fscanf(in_file, "%d\n", Data_in);
            @(negedge clk);  // Wait for the negative edge of the clock
            $fwrite(out_file, "%d\n", Data_out);
        end

        $fclose(in_file);
        $fclose(out_file);
        $fclose(err_file);
        $finish;
    end

endmodule

