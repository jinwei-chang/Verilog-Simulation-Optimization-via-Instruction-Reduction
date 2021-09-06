module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	wire origtmp1;
	wire origtmp2;
    wire origtmp3;
	wire origtmp4;
    wire origtmp5;
	wire origtmp6;
	assign origtmp1 = in[1] & origtmp5;
	assign origtmp2 = in[2] & origtmp4;
	assign origtmp3 = ~in[1];
	assign origtmp4 = in[6] & in[4];
    assign origtmp5 = in[1] & in[3];
	assign origtmp6 = in[10] & in[11];
	assign out[0] = origtmp3 & origtmp5;
	assign out[1] = origtmp2 & origtmp6;
	assign out[2] = ~in[5];
	assign out[3] = ~in[6];
    assign out[4] = ~in[7];
    assign out[5] = ~in[8];
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
