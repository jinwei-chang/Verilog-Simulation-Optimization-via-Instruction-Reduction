module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	wire origtmp1;
	wire origtmp2;
	assign origtmp1 = in[0] ^ in[1];
	assign origtmp2 = in[5] ^ in[6];
	assign out[0] = origtmp1 ^ origtmp2;
	assign out[1] = origtmp2 ^ origtmp1;
	assign out[2] = in[5] ^ in[6];
	assign out[3] = in[5] ^ in[6];
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
