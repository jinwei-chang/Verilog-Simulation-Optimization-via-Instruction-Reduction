module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	wire xformtmp9;
	assign xformtmp9 = in[4] | in[16];
	wire xformtmp5;
	assign xformtmp5 = in[2] | xformtmp9;
	wire xformtmp1;
	assign xformtmp1 = in[6] ^ xformtmp5;
	wire xformtmp7;
	assign xformtmp7 = in[0] & in[11];
	wire xformtmp16;
	assign xformtmp16 = in[9] | xformtmp7;
	wire xformtmp6;
	assign xformtmp6 = in[10] ^ in[15];
	wire xformtmp12;
	assign xformtmp12 = in[6] & xformtmp6;
	wire xformtmp22;
	assign xformtmp22 = in[7] ^ xformtmp12;
	wire xformtmp11;
	assign xformtmp11 = xformtmp16 ^ xformtmp22;
	wire xformtmp3;
	assign xformtmp3 = xformtmp1 & xformtmp11;
	wire xformtmp13;
	assign xformtmp13 = in[10] & in[17];
	wire xformtmp14;
	assign xformtmp14 = in[6] | in[16];
	wire xformtmp4;
	assign xformtmp4 = xformtmp13 ^ xformtmp14;
	wire xformtmp8;
	assign xformtmp8 = in[3] | in[14];
	wire xformtmp21;
	assign xformtmp21 = in[4] ^ xformtmp8;
	wire xformtmp19;
	assign xformtmp19 = xformtmp4 | xformtmp21;
	assign out[0] = xformtmp3 ^ xformtmp19;
	wire xformtmp24;
	assign xformtmp24 = in[12] & in[13];
	wire xformtmp23;
	assign xformtmp23 = in[18] | xformtmp24;
	wire xformtmp25;
	assign xformtmp25 = ~in[1];
	assign out[1] = xformtmp23 & xformtmp25;
	assign out[2] = in[5];
	assign out[3] = in[19];
	assign out[9:4] = 6'b100001;
endmodule

module tb();
    reg[9:0] results[1];
    reg[19:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%20b]", data[0]);
        #1
        $display("results = [%10b]", results[0]);
        $writememb("results.txt", results);
    end 
endmodule
