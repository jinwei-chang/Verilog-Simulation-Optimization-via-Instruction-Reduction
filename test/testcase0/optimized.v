module dut (out, in);
	output[9:0] out;
	input[19:0] in;
	assign out[0] = 1'b0;
	wire xformtmp4;
	assign xformtmp4 = in[4] & in[6];
	wire xformtmp2;
	assign xformtmp2 = in[2] & xformtmp4;
	wire xformtmp6;
	assign xformtmp6 = in[10] & in[11];
	assign out[1] = xformtmp2 & xformtmp6;
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
