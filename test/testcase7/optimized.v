module dut (out, in);
    output[29:0] out;
    input[14:0] in;
	assign out[11:0] = 12'b011011101000;
	assign out[13:12] = in[1:0];
	assign out[15:14] = 2'b10;
	assign out[18:16] = in[6:4];
	wire xformtmp2;
	assign xformtmp2 = ~in[7];
	assign out[19] = in[7] & xformtmp2;
	wire xformtmp3;
	assign xformtmp3 = ~in[8];
	assign out[20] = in[8] | xformtmp3;
	assign out[21] = in[9];
	assign out[22] = ~in[10];
	assign out[26:23] = 4'b0110;
	assign out[29:27] = in[14:12];
endmodule

module tb();
	reg[29:0] results[1];
	reg[14:0] data[1];
	dut duttest(results[0], data[0]);
	initial begin
		$readmemb("data.txt", data);
		$display("data = [%15b]", data[0]);
		#1
		$display("results = [%30b]", results[0]);
		$writememb("results.txt", results);
	end
endmodule
