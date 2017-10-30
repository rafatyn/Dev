module microc(input wire clk, reset, s_inc, s_inm, we3, entI, SalR, SalI, s_jr, c_jr, s_rel, input wire [2:0] op, input wire [7:0] EntS1, EntS2, EntS3, EntS4, output wire z, output wire [5:0] opcode, output wire [7:0] ESal1, ESal2, ESal3, ESal4, output wire [9:0] SalPc);

wire [9:0] SalMux10Pc, SalMux10Jr, SalMux10Sum, SalSum, SalJr;
wire [15:0] SalMem;
wire [7:0] SalMux8, SalAlu, SalR1, SalR2, SalMux8I, SalMux8Ent, SalMux8Sal;
reg [7:0] SalIntR, SalIntI;
reg [9:0] RegJr;
wire SalDec1, SalDec2, SalDec3, SalDec4;

always @(clk)
  if(c_jr)
    RegJr = SalSum;

registro #(10) jr(clk, reset, RegJr, SalJr);
mux2 #(10) mux10jr(SalJr, SalMem[9:0], s_jr, SalMux10Jr);

registro #(10) pc(clk, reset, SalMux10Pc, SalPc);
mux2 #(10) mux10pc(SalMux10Jr, SalSum, s_inc, SalMux10Pc);

mux2 #(10) mux10sum(10'b000000001, SalMem[9:0], s_rel, SalMux10Sum);
sum pc1(SalPc, SalMux10Sum, SalSum);
memprog meminst(clk, SalPc, SalMem);

assign opcode = SalMem[15:10];

regfile banreg(clk, we3, SalMem[11:8], SalMem[7:4], SalMem[3:0], SalMux8, SalR1, SalR2);
mux2 #(8) mux8alu(SalAlu, SalMux8I, s_inm, SalMux8);
alu alu8(SalR1, SalR2, op, SalAlu, z);

always @(SalR)
  if(SalR)
    SalIntR = SalR2;
  else
    SalIntR = 8'b00000000;
  
always @(SalI)
  if(SalI)
    SalIntI = SalMem[9:2];
  else
    SalIntI = 8'b00000000;
    
mux4 #(8) mux8sent(EntS1, EntS2, EntS3, EntS4, SalMem[9:8], SalMux8Ent);
mux2 #(8) mux8inm(SalMux8Ent, SalMem[11:4], entI, SalMux8I);

mux2 #(8) mux8sal(SalIntR, SalIntI, SalI, SalMux8Sal);

registroCE #(8) sal1(clk, reset, SalDec1, SalMux8Sal, ESal1);
registroCE #(8) sal2(clk, reset, SalDec2, SalMux8Sal, ESal2);
registroCE #(8) sal3(clk, reset, SalDec3, SalMux8Sal, ESal3);
registroCE #(8) sal4(clk, reset, SalDec4, SalMux8Sal, ESal4);

dec2 dec8ssal((SalI|SalR), SalMem[1:0], SalDec1, SalDec2, SalDec3, SalDec4);

endmodule
