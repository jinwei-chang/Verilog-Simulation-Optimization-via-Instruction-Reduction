module dut (out, in);
	output[1:0] out;
	input[1:0] in;
	wire xformtmp7;
	assign xformtmp7 = in[0];
	assign out[0] = ~xformtmp7;
	wire xformtmp49;
	assign xformtmp49 = ~in[0];
	wire xformtmp50;
	assign xformtmp50 = xformtmp49;
	assign out[1] = in[1] ^ xformtmp50;
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
