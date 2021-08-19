module dut (out, in);
    output[29:0] out;
    input[14:0] in;
	wire origtmp1;
	wire origtmp2;
	wire origtmp3;
	wire origtmp4;
	assign out[0] = 1'b0 & 1'b0;
	assign out[1] = 1'b0 & 1'b1;
	assign out[2] = 1'b1 & 1'b0;
	assign out[3] = 1'b1 & 1'b1;
	assign out[4] = 1'b0 | 1'b0;
	assign out[5] = 1'b0 | 1'b1;
	assign out[6] = 1'b1 | 1'b0;
	assign out[7] = 1'b1 | 1'b1;
	assign out[8] = 1'b0 ^ 1'b0;
	assign out[9] = 1'b0 ^ 1'b1;
	assign out[10] = 1'b1 ^ 1'b0;
	assign out[11] = 1'b1 ^ 1'b1;
	assign out[12] = in[0] & 1'b1;
	assign out[13] = in[1] | 1'b0;
	assign out[14] = in[2] & 1'b0;
	assign out[15] = in[3] | 1'b1;
	assign out[16] = in[4] & in[4];
	assign out[17] = in[5] | in[5];
	assign origtmp1 = ~in[6];
	assign out[18] = ~origtmp1;
	assign origtmp2 = ~in[7];
	assign out[19] = in[7] & origtmp2;
	assign origtmp3 = ~in[8];
	assign out[20] = in[8] | origtmp3;
	assign out[21] = in[9] ^ 1'b0;
	assign out[22] = in[10] ^ 1'b1;
	assign out[23] = in[11] ^ in[11];
	assign origtmp4 = ~in[12];
	assign out[24] = in[12] ^ origtmp4;
	assign out[25] = ~1'b0;
	assign out[26] = ~1'b1;
	assign out[27] = in[12];
	assign out[28] = in[13];
	assign out[29] = in[14];
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
