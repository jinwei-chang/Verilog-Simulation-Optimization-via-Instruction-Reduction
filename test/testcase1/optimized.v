module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	wire xformtmp9;
	assign xformtmp9 = in[4] | in[16];
	wire xformtmp5;
	assign xformtmp5 = in[2] | xformtmp9;
	wire xformtmp1;
	assign xformtmp1 = xformtmp5 ^ in[6];
	wire xformtmp6;
	assign xformtmp6 = in[10] ^ in[15];
	wire xformtmp12;
	assign xformtmp12 = xformtmp6 & in[6];
	wire xformtmp22;
	assign xformtmp22 = xformtmp12 ^ in[7];
	wire xformtmp7;
	assign xformtmp7 = in[11] & in[0];
	wire xformtmp16;
	assign xformtmp16 = in[9] | xformtmp7;
	wire xformtmp11;
	assign xformtmp11 = xformtmp22 ^ xformtmp16;
	wire xformtmp3;
	assign xformtmp3 = xformtmp1 & xformtmp11;
	wire xformtmp14;
	assign xformtmp14 = in[6] | in[16];
	wire xformtmp20;
	assign xformtmp20 = in[7] | in[10];
	wire xformtmp10;
	assign xformtmp10 = xformtmp20 | in[2];
	wire xformtmp2;
	assign xformtmp2 = in[17] | xformtmp10;
	wire xformtmp13;
	assign xformtmp13 = in[17] & in[10];
	wire xformtmp15;
	assign xformtmp15 = xformtmp2 & xformtmp13;
	wire xformtmp4;
	assign xformtmp4 = xformtmp14 ^ xformtmp15;
	wire xformtmp8;
	assign xformtmp8 = in[14] | in[3];
	wire xformtmp21;
	assign xformtmp21 = xformtmp8 ^ in[4];
	wire xformtmp19;
	assign xformtmp19 = xformtmp4 | xformtmp21;
	assign out[0] = xformtmp3 ^ xformtmp19;
	wire xformtmp24;
	assign xformtmp24 = in[13] & in[12];
	wire xformtmp23;
	assign xformtmp23 = in[18] | xformtmp24;
	wire xformtmp25;
	assign xformtmp25 = in[1] | xformtmp23;
	assign out[1] = xformtmp25 ^ in[1];
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
