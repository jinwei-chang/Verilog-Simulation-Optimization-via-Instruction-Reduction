module dut (out, in);
	output[9:0] out;
	input[29:0] in;
	assign out[0] = 1'b1;
	assign out[1] = in[28];
	assign out[8:2] = 7'b0011000;
	assign out[9] = in[29];
endmodule

module tb();
    reg[9:0] results[1];
    reg[29:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%30b]", data[0]);
        #1
        $display("results = [%10b]", results[0]);
        $writememb("results.txt", results);
    end 
endmodule
