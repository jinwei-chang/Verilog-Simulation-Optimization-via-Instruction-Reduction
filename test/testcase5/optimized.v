module dut (out, in);
	output[9:0] out;
	input[29:0] in;
	wire xformtmp31;
	wire xformtmp29;
	wire xformtmp28;
	wire xformtmp27;
	wire xformtmp26;
	wire xformtmp25;
	wire xformtmp11;
	wire xformtmp10;
	wire xformtmp9;
	wire xformtmp8;
	wire xformtmp7;
	wire xformtmp6;
	wire xformtmp2;
	wire xformtmp1;
	wire xformtmp3;
	wire xformtmp4;
	wire xformtmp5;
	wire xformtmp12;
	wire xformtmp13;
	wire xformtmp14;
	wire xformtmp15;
	wire xformtmp16;
	wire xformtmp17;
	wire xformtmp18;
	wire xformtmp19;
	wire xformtmp20;
	wire xformtmp21;
	wire xformtmp22;
	wire xformtmp23;
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
