module uc(input wire clk, z, input wire [5:0] opcode, output wire s_inc, s_inm, we3, entI, SalR, SalI, s_jr, c_jr, s_rel, output wire [2:0] op);

reg rz;
initial
begin
   rz = 1'b0;
end
always @(opcode[5], z)
if(opcode[5] == 1)
  rz = (s_inc & z);
  
  
assign s_inc = (((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 0)&(opcode[1] == 0)&(opcode[0] == 0))|((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 0)&(opcode[1] == 1)&(opcode[0] == rz))|((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 1)&(opcode[1] == 0)&(opcode[0] == 0))|((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 1)&(opcode[1] == 0)&(opcode[0] == 1)))? 0:1;  // Mux Salto
assign s_inm = (((opcode[5] == 0)&(opcode[4] == 1))|((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 1)&(opcode[2] == 0)&(opcode[1] == 0)&(opcode[0] == 0)))? 1:0;  // Mux carga reg
assign we3 = (((opcode[5] == 0)&(opcode[4] == 1))|((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 1)&(opcode[2] == 0)&(opcode[1] == 0)&(opcode[0] == 0))|(opcode[5] == 1))? 1:0; // Enable banco reg
assign op = opcode[4:2];
assign entI = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 1)&(opcode[2] == 0)&(opcode[1] == 0)&(opcode[0] == 0))? 0:1; // Mux carga inm
assign SalR = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 1)&(opcode[2] == 0)&(opcode[1] == 1)&(opcode[0] == 0))? 1:0; // Mux sal reg
assign SalI = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 1)&(opcode[2] == 0)&(opcode[1] == 1)&(opcode[0] == 1))? 1:0; // Mux sal reg
assign s_jr = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 1)&(opcode[1] == 0)&(opcode[0] == 1))? 0:1; // JR
assign c_jr = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 1)&(opcode[1] == 0)&(opcode[0] == 0))? 1:0; // JAL
assign s_rel = ((opcode[5] == 0)&(opcode[4] == 0)&(opcode[3] == 0)&(opcode[2] == 1)&(opcode[1] == 1)&(opcode[0] == 0))? 1:0; // Salto relativo

endmodule