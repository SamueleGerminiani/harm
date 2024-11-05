
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

//`define USE_CSV_INPUT

module UBBKA_31_0_31_0_tb;
wire [32:0] s;
reg [31:0] x;
reg [31:0] y;
reg [32:0] my_out;
integer f, csv, input_csv,ass_file;
reg [1023:0] line; // Buffer for each line read from CSV
integer ret, value_x, value_y;

initial begin
    $info("%s",{`GET_OUT_PATH,"output.csv"});
    f = $fopen({`GET_OUT_PATH,"output.csv"},"w");
    csv = $fopen({`GET_OUT_PATH,"trace.csv"},"w");
    ass_file = $fopen({`GET_OUT_PATH,"ass.txt"},"w");
    $fwrite(f,"sum\n");
    $fwrite(csv,"unsigned int x,unsigned int y,unsigned long int sum\n");

`ifdef USE_CSV_INPUT
    input_csv = $fopen("input/xy.csv", "r"); // Open CSV with input values

    if (input_csv == 0) begin
        $display("Error: Could not open input_values.csv");
        $finish;
    end

    // Loop to read from CSV until end of file
    while (!$feof(input_csv)) begin
        ret = $fgets(line, input_csv); // Read line
        if (ret != 0) begin
            ret = $sscanf(line, "%d,%d", value_x, value_y); // Parse x and y from line
            if (ret == 2) begin
                x = value_x;
                y = value_y;
                #10;  // Small delay for stable results
                if (^s === 1'bX) begin
                    $fwrite(csv,"%0d,%0d,0\n",x,y);
                    $fwrite(f,"0\n");
                end else begin
                    $fwrite(csv,"%0d,%0d,%0d\n",x,y,s);
                    $fwrite(f,"%0d\n",s);
                    $fwrite(ass_file,"G(x==%0d && y==%0d -> sum==%0d)\n",x,y,s);
                end
            end
        end
    end

    $fclose(input_csv); // Close input file after reading

`else // Random input mode
    repeat(`GET_TRACE_LENGTH) begin
        #1;
        x = $urandom;
        y = $urandom;
        if (^s === 1'bX) begin
            $fwrite(csv,"%0d,%0d,0\n",x,y);
            $fwrite(f,"0\n");
        end else begin
            $fwrite(csv,"%0d,%0d,%0d\n",x,y,s);
            $fwrite(f,"%0d\n",s);
            $fwrite(ass_file,"G(x==%0d && y==%0d -> sum==%0d)\n",x,y,s);
        end
    end

`endif

    // Close output files and end simulation
    $fclose(f);
    $fclose(csv);
    $finish;
end

UBBKA_31_0_31_0 U0(s,x,y);
endmodule


