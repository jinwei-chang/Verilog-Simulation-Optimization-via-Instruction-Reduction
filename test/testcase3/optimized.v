module dut (out, in);
	output[79:0] out;
	input[149:0] in;
endmodule

module tb();
    reg[79:0] results[1];
    reg[149:0] data[1];
    dut duttest(results[0], data[0]);
    initial begin
        $readmemb("data.txt", data);
        $display("data = [%150b]", data[0]);
        #1
        $display("results = [%80b]", results[0]);
        $writememb("results.txt", results);
    end 
endmodule
