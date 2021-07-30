module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	wire xformtmp2;
	wire xformtmp1;
	assign xformtmp1 = in[0] ^ in[1];
	assign xformtmp2 = in[5] ^ in[6];
	assign out[0] = xformtmp1 ^ xformtmp2;
	assign out[1] = out[0];
	assign out[2] = xformtmp2;
	assign out[3] = xformtmp2;
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
