module block4(Q0,Q1,Q2,Q3,din,clk);
output Q0,Q1,Q2,Q3;
input clk,din;
reg Q0,Q1,Q2,Q3;
always @(posedge clk)
    begin
    	Q3<=Q2;
    	Q1<=Q0;
    	Q2<=Q1;
    	Q0<=din;
    end
endmodule

`timescale 1ns/1ps
module tb_block4;
reg clk,din;
wire Q0,Q1,Q2,Q3;
block4 uut(.Q0(Q0),.Q1(Q1),.Q2(Q2),.Q3(Q3),.din(din),.clk(clk));
initial begin clk=0; forever #10 clk=~clk; end
initial begin
    din=0; #5;
    din=1; #20; din=0; #500; 
    $finish;
end 
endmodule

module shifter(din,clk,clr,dout);
input din,clk,clr;
output[7:0] dout;
reg[7:0] dout;
always @(posedge clk)
    begin
    	if (clr)  dout<= 8'b0;              //同步清0，高电平有效
    else
        begin
        	dout <= dout << 1;     //输出信号左移一位
        	dout[0] <= din;    //输入信号补充到输出信号的最低位
        end
    end
endmodule
