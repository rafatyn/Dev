module caminocompleto(input wire clk, reset, AUD_ADCDAT, inout wire AUD_ADCLRCK, AUD_DACLRCK, AUD_BCLK, I2C_SDAT, output wire AUD_DACDAT, AUD_XCK, I2C_SCLK, input wire [7:0] EntS1, EntS2, EntS3, EntS4, output wire [7:0] ESal1, ESal2, ESal3, ESal4, output wire [9:0] SalPC, output wire [6:0] HEX0, HEX1, HEX2, HEX3, output wire [15:0] sample_rate);

wire s_inc, s_inm, we3, z, entI, SalR, SalI, s_jr, c_jr, s_rel;
wire [2:0] op;
wire [5:0] opcode;
wire [7:0] EntS2Mod;
assign EntS2Mod = {4'b0000,EntS2[3:0]};

assign HEX1 = ESal1;
assign HEX2 = ESal2;
assign HEX0 = 7'b0111111;
assign HEX3 = 7'b0111111;

wire [15:0] arm_Rate;
wire I2C_END;
wire AUD_CTRL_CLK;
assign	I2C_SDAT	=	1'bz;
assign	AUD_ADCLRCK	=	AUD_DACLRCK;
assign	AUD_XCK		=	AUD_CTRL_CLK;

microc micro1(clk, ~reset, s_inc, s_inm, we3, entI, SalR, SalI, s_jr, c_jr, s_rel, op, EntS1, EntS2Mod, EntS3, EntS4, z, opcode, ESal1, ESal2, ESal3, ESal4, SalPC);
uc uc1(clk, z, opcode, s_inc, s_inm, we3, entI, SalR, SalI, s_jr, c_jr, s_rel, op);

Aud_PLL pll(.areset(~I2C_END), .inclk0(clk), .c0(AUD_CTRL_CLK));

I2C_AV_Config  AV_Config(I2C_END, clk, reset, I2C_SCLK, I2C_SDAT);

audio_codec AC(AUD_DACDAT, AUD_DACLRCK, AUD_BCLK, 2'b00, AUD_CTRL_CLK, reset, sample_rate, arm_Rate);

switch sw(clk, ~reset, EntS2Mod, sample_rate, arm_Rate);

endmodule
