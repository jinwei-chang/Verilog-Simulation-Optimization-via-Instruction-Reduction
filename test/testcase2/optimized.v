module dut (out, in);
	output[29:0] out;
	input[49:0] in;
endmodule

module tb();
    reg[29:0] results[1];
    reg[49:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%50b]", data[0]);
        #1
        $display("results = [%30b]", results[0]);
        $writememb("results.txt", results);
    end 
endmodule
