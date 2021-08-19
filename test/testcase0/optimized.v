module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	// assign origtmp1 = in[1] ^ in[3];
	// assign origtmp2 = in[2] ^ in[4];
	assign out[1:0] = in[2:1] ^ in[4:3];
	assign out[5:2] = ~in[8:5];
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
