module ffnn_tb ();

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
    "prediction/"\
`endif

`define GET_IN_PATH()\
`ifdef IN_PATH\
    `STRINGIFY(`IN_PATH)\
`else\
    "input/"\
`endif


parameter SIZE = 64;

reg  Reset, clk;

reg [SIZE-1:0] a;
reg [SIZE-1:0] b;
reg [SIZE-1:0] c;
reg [SIZE-1:0] d;

wire [SIZE-1:0] result;

integer input_data_1, input_data_2, input_data_3, input_data_4;
integer csv_file, ep_file, goldp_file, temp, inferencecount;
integer eof1, eof2, eof3, eof4;
integer counter;
integer gold_prediction;
integer wrongPredictions;

initial begin

	clk = 1'b0;
	Reset = 1'b1;
	inferencecount = 0;
    counter = 0;
    gold_prediction = 0;
    wrongPredictions = 0;
	// Initialize EOF flags
	eof1 = 0;
	eof2 = 0;
	eof3 = 0;
	eof4 = 0;

    $info("%s", {`GET_IN_PATH,"iris_test_input_feature1.txt"});

	// Open input data files
	input_data_1 = $fopen({`GET_IN_PATH,"iris_test_input_feature1.txt"},"r");
	input_data_2 = $fopen({`GET_IN_PATH,"iris_test_input_feature2.txt"},"r");
	input_data_3 = $fopen({`GET_IN_PATH,"iris_test_input_feature3.txt"},"r");
	input_data_4 = $fopen({`GET_IN_PATH,"iris_test_input_feature4.txt"},"r");
    $info("%s",{`GET_OUT_PATH,"results.csv"});
	csv_file = $fopen({`GET_OUT_PATH,"trace.csv"},"w");
	ep_file = $fopen({`GET_OUT_PATH,"ep.txt"},"w");
	goldp_file = $fopen({`GET_IN_PATH,"gold_prediction.txt"},"r");

	// Write the CSV header
	$fwrite(csv_file, "int a,int b,int c,int d,int pred\n");


	// Read the first set of inputs
	temp = $fscanf(input_data_1,"%d\n",a);
	if ($feof(input_data_1)) eof1 = 1;

	temp = $fscanf(input_data_2,"%d\n",b);
	if ($feof(input_data_2)) eof2 = 1;

	temp = $fscanf(input_data_3,"%d\n",c);
	if ($feof(input_data_3)) eof3 = 1;

	temp = $fscanf(input_data_4,"%d\n",d);
	if ($feof(input_data_4)) eof4 = 1;

    gold_prediction = $fscanf(goldp_file,"%d\n",gold_prediction);

	#1 Reset = 1'b0;


    while (1) begin

	    if (counter > 10)
	    begin


	      $fwrite(csv_file, "%d,%d,%d,%d,%d\n", a, b, c, d, result);

          if (result!=gold_prediction) wrongPredictions = wrongPredictions + 1;
            

	      inferencecount = inferencecount + 1;
	      if (inferencecount >= `GET_TRACE_LENGTH) begin
	      	$fclose(csv_file);
	      	$finish;
	      end

	      if (eof1 || eof2 || eof3 || eof4) begin
	      	// Check if any input file reached EOF prematurely
	      	if (eof1 != eof2 || eof1 != eof3 || eof1 != eof4) begin
	      		$error("Error: One of the input files is shorter than the others.");
	      	end
	      	$fclose(csv_file);
            $display("--------->WP: %d", wrongPredictions);
            $display("--------->EP: %f", real'(wrongPredictions)/inferencecount);
            $fwrite(ep_file, "%f\n", real'(wrongPredictions)/inferencecount);
	      	$finish;
	      end

          @(negedge clk);

	      // Read the next set of inputs
	      temp = $fscanf(input_data_1,"%d\n",a);
	      if ($feof(input_data_1)) eof1 = 1;

	      temp = $fscanf(input_data_2,"%d\n",b);
	      if ($feof(input_data_2)) eof2 = 1;

	      temp = $fscanf(input_data_3,"%d\n",c);
	      if ($feof(input_data_3)) eof3 = 1;

	      temp = $fscanf(input_data_4,"%d\n",d);
	      if ($feof(input_data_4)) eof4 = 1;

          temp=$fscanf(goldp_file,"%d\n",gold_prediction);

          counter = 0;

        end
        else
        begin
          @(posedge clk);
          counter = counter + 1;
        end  

    end
end

always begin
  #5 clk = ~clk;
end

// Instantiate the FFNN module
ffnn_approx UUT(Reset, clk, a, b, c, d, result);

endmodule

