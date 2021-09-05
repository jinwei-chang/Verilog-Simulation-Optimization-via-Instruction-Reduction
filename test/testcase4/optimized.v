module dut (out, in);
	output[1:0] out;
	input[1:0] in;
	assign out[0] = ~in[0];
	wire xformtmp51;
	assign xformtmp51 = ~in[0];
	assign out[1] = in[1] ^ xformtmp51;
endmodule

module tb();
    reg[1:0] results[1];
    reg[1:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%2b]", data[0]);
        #1
        $display("results = [%2b]", results[0]);
        $writememb("results.txt", results);
    end 
endmodule
