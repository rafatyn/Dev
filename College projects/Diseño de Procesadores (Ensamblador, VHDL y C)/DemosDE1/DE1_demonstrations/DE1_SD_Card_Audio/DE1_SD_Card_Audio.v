// --------------------------------------------------------------------
// Copyright (c) 2005 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------
//
// Major Functions:	DE1 TOP LEVEL
//
// --------------------------------------------------------------------
//
// Revision History :
// --------------------------------------------------------------------
//   Ver  :| Author            :|   Mod. Date :|   Changes Made:
//   V1.0 :| Johnny Chen       :| 06/08/30    :|  Initial Revision
//   V2.0 :| Dee Zeng          :| 10/12/2012  :|  Upgrade to Q11.1SP2
// --------------------------------------------------------------------

module DE1_SD_Card_Audio
	(
		////////////////////	Clock Input	 	////////////////////	 
		CLOCK_24,						//	24 MHz
		CLOCK_27,						//	27 MHz
		CLOCK_50,						//	50 MHz
		EXT_CLOCK,						//	External Clock
		////////////////////	Push Button		////////////////////
		KEY,							//	Pushbutton[3:0]
		////////////////////	DPDT Switch		////////////////////
		SW,								//	Toggle Switch[9:0]
		////////////////////	7-SEG Dispaly	////////////////////
		HEX0,							//	Seven Segment Digit 0
		HEX1,							//	Seven Segment Digit 1
		HEX2,							//	Seven Segment Digit 2
		HEX3,							//	Seven Segment Digit 3
		////////////////////////	LED		////////////////////////
		LEDG,							//	LED Green[7:0]
		LEDR,							//	LED Red[9:0]
		////////////////////////	UART	////////////////////////
		UART_TXD,						//	UART Transmitter
		UART_RXD,						//	UART Receiver
		/////////////////////	SDRAM Interface		////////////////
		DRAM_DQ,						//	SDRAM Data bus 16 Bits
		DRAM_ADDR,						//	SDRAM Address bus 12 Bits
		DRAM_LDQM,						//	SDRAM Low-byte Data Mask 
		DRAM_UDQM,						//	SDRAM High-byte Data Mask
		DRAM_WE_N,						//	SDRAM Write Enable
		DRAM_CAS_N,						//	SDRAM Column Address Strobe
		DRAM_RAS_N,						//	SDRAM Row Address Strobe
		DRAM_CS_N,						//	SDRAM Chip Select
		DRAM_BA_0,						//	SDRAM Bank Address 0
		DRAM_BA_1,						//	SDRAM Bank Address 0
		DRAM_CLK,						//	SDRAM Clock
		DRAM_CKE,						//	SDRAM Clock Enable
		////////////////////	Flash Interface		////////////////
		FL_DQ,							//	FLASH Data bus 8 Bits
		FL_ADDR,						//	FLASH Address bus 22 Bits
		FL_WE_N,						//	FLASH Write Enable
		FL_RST_N,						//	FLASH Reset
		FL_OE_N,						//	FLASH Output Enable
		FL_CE_N,						//	FLASH Chip Enable
		////////////////////	SRAM Interface		////////////////
		SRAM_DQ,						//	SRAM Data bus 16 Bits
		SRAM_ADDR,						//	SRAM Address bus 18 Bits
		SRAM_UB_N,						//	SRAM High-byte Data Mask 
		SRAM_LB_N,						//	SRAM Low-byte Data Mask 
		SRAM_WE_N,						//	SRAM Write Enable
		SRAM_CE_N,						//	SRAM Chip Enable
		SRAM_OE_N,						//	SRAM Output Enable
		////////////////////	SD_Card Interface	////////////////
		SD_DAT,							//	SD Card Data
		SD_DAT3,						//	SD Card Data 3
		SD_CMD,							//	SD Card Command Signal
		SD_CLK,							//	SD Card Clock
		////////////////////	USB JTAG link	////////////////////
		TDI,  							// CPLD -> FPGA (data in)
		TCK,  							// CPLD -> FPGA (clk)
		TCS,  							// CPLD -> FPGA (CS)
	    TDO,  							// FPGA -> CPLD (data out)
		////////////////////	I2C		////////////////////////////
		I2C_SDAT,						//	I2C Data
		I2C_SCLK,						//	I2C Clock
		////////////////////	PS2		////////////////////////////
		PS2_DAT,						//	PS2 Data
		PS2_CLK,						//	PS2 Clock
		////////////////////	VGA		////////////////////////////
		VGA_HS,							//	VGA H_SYNC
		VGA_VS,							//	VGA V_SYNC
		VGA_R,   						//	VGA Red[3:0]
		VGA_G,	 						//	VGA Green[3:0]
		VGA_B,  						//	VGA Blue[3:0]
		////////////////	Audio CODEC		////////////////////////
		AUD_ADCLRCK,					//	Audio CODEC ADC LR Clock
		AUD_ADCDAT,						//	Audio CODEC ADC Data
		AUD_DACLRCK,					//	Audio CODEC DAC LR Clock
		AUD_DACDAT,						//	Audio CODEC DAC Data
		AUD_BCLK,						//	Audio CODEC Bit-Stream Clock
		AUD_XCK,						//	Audio CODEC Chip Clock
		////////////////////	GPIO	////////////////////////////
		GPIO_0,							//	GPIO Connection 0
		GPIO_1							//	GPIO Connection 1
	);

////////////////////////	Clock Input	 	////////////////////////
input	[1:0]	CLOCK_24;				//	24 MHz
input	[1:0]	CLOCK_27;				//	27 MHz
input			CLOCK_50;				//	50 MHz
input			EXT_CLOCK;				//	External Clock
////////////////////////	Push Button		////////////////////////
input	[3:0]	KEY;					//	Pushbutton[3:0]
////////////////////////	DPDT Switch		////////////////////////
input	[9:0]	SW;						//	Toggle Switch[9:0]
////////////////////////	7-SEG Dispaly	////////////////////////
output	[6:0]	HEX0;					//	Seven Segment Digit 0
output	[6:0]	HEX1;					//	Seven Segment Digit 1
output	[6:0]	HEX2;					//	Seven Segment Digit 2
output	[6:0]	HEX3;					//	Seven Segment Digit 3
////////////////////////////	LED		////////////////////////////
output	[7:0]	LEDG;					//	LED Green[7:0]
output	[9:0]	LEDR;					//	LED Red[9:0]
////////////////////////////	UART	////////////////////////////
output			UART_TXD;				//	UART Transmitter
input			UART_RXD;				//	UART Receiver
///////////////////////		SDRAM Interface	////////////////////////
inout	[15:0]	DRAM_DQ;				//	SDRAM Data bus 16 Bits
output	[11:0]	DRAM_ADDR;				//	SDRAM Address bus 12 Bits
output			DRAM_LDQM;				//	SDRAM Low-byte Data Mask 
output			DRAM_UDQM;				//	SDRAM High-byte Data Mask
output			DRAM_WE_N;				//	SDRAM Write Enable
output			DRAM_CAS_N;				//	SDRAM Column Address Strobe
output			DRAM_RAS_N;				//	SDRAM Row Address Strobe
output			DRAM_CS_N;				//	SDRAM Chip Select
output			DRAM_BA_0;				//	SDRAM Bank Address 0
output			DRAM_BA_1;				//	SDRAM Bank Address 0
output			DRAM_CLK;				//	SDRAM Clock
output			DRAM_CKE;				//	SDRAM Clock Enable
////////////////////////	Flash Interface	////////////////////////
inout	[7:0]	FL_DQ;					//	FLASH Data bus 8 Bits
output	[21:0]	FL_ADDR;				//	FLASH Address bus 22 Bits
output			FL_WE_N;				//	FLASH Write Enable
output			FL_RST_N;				//	FLASH Reset
output			FL_OE_N;				//	FLASH Output Enable
output			FL_CE_N;				//	FLASH Chip Enable
////////////////////////	SRAM Interface	////////////////////////
inout	[15:0]	SRAM_DQ;				//	SRAM Data bus 16 Bits
output	[17:0]	SRAM_ADDR;				//	SRAM Address bus 18 Bits
output			SRAM_UB_N;				//	SRAM High-byte Data Mask 
output			SRAM_LB_N;				//	SRAM Low-byte Data Mask 
output			SRAM_WE_N;				//	SRAM Write Enable
output			SRAM_CE_N;				//	SRAM Chip Enable
output			SRAM_OE_N;				//	SRAM Output Enable
////////////////////	SD Card Interface	////////////////////////
inout			SD_DAT;					//	SD Card Data
inout			SD_DAT3;				//	SD Card Data 3
inout			SD_CMD;					//	SD Card Command Signal
output			SD_CLK;					//	SD Card Clock
////////////////////////	I2C		////////////////////////////////
inout			I2C_SDAT;				//	I2C Data
output			I2C_SCLK;				//	I2C Clock
////////////////////////	PS2		////////////////////////////////
input		 	PS2_DAT;				//	PS2 Data
input			PS2_CLK;				//	PS2 Clock
////////////////////	USB JTAG link	////////////////////////////
input  			TDI;					// CPLD -> FPGA (data in)
input  			TCK;					// CPLD -> FPGA (clk)
input  			TCS;					// CPLD -> FPGA (CS)
output 			TDO;					// FPGA -> CPLD (data out)
////////////////////////	VGA			////////////////////////////
output			VGA_HS;					//	VGA H_SYNC
output			VGA_VS;					//	VGA V_SYNC
output	[3:0]	VGA_R;   				//	VGA Red[3:0]
output	[3:0]	VGA_G;	 				//	VGA Green[3:0]
output	[3:0]	VGA_B;   				//	VGA Blue[3:0]
////////////////////	Audio CODEC		////////////////////////////
inout			AUD_ADCLRCK;			//	Audio CODEC ADC LR Clock
input			AUD_ADCDAT;				//	Audio CODEC ADC Data
inout			AUD_DACLRCK;			//	Audio CODEC DAC LR Clock
output			AUD_DACDAT;				//	Audio CODEC DAC Data
inout			AUD_BCLK;				//	Audio CODEC Bit-Stream Clock
output			AUD_XCK;				//	Audio CODEC Chip Clock
////////////////////////	GPIO	////////////////////////////////
inout	[35:0]	GPIO_0;					//	GPIO Connection 0
inout	[35:0]	GPIO_1;					//	GPIO Connection 1
////////////////////////////////////////////////////////////////////

wire	CPU_CLK;
wire	CPU_RESET;
wire	CLK_18_4;
wire	CLK_25;

//	Flash
assign	FL_RST_N	=	1'b1;

//	All inout port turn to tri-state
assign	AUD_ADCLRCK	=	AUD_DACLRCK;
assign	GPIO_0		=	36'hzzzzzzzzz;
assign	GPIO_1		=	36'hzzzzzzzzz;

//	Set SD Card to SD Mode
assign	SD_DAT3		=	1'b1;

Reset_Delay	delay1	(.iRST(KEY[0]),.iCLK(CLOCK_50),.oRESET(CPU_RESET));

SDRAM_PLL 	PLL1	(.inclk0(CLOCK_50),.c0(DRAM_CLK),.c1(CPU_CLK),.c2(CLK_25));
Audio_PLL 	PLL2	(.areset(!CPU_RESET),.inclk0(CLOCK_27[0]),.c0(CLK_18_4));

		
system_0 u0 (
        .clk_clk_in_clk                                              (CPU_CLK),                                              //                      clk_clk_in.clk
		  .clk_clk_in_reset_reset_n                                    (CPU_RESET),                                    //                clk_clk_in_reset.reset_n
		  
		  .switch_pio_external_connection_export                       (SW),                       //  switch_pio_external_connection.export
        .button_pio_external_connection_export                       (KEY),                       //  button_pio_external_connection.export
		 
		  .sd_dat_external_connection_export                           (SD_DAT),                           //      sd_dat_external_connection.export
        .sd_cmd_external_connection_export                           (SD_CMD),                           //      sd_cmd_external_connection.export
        .sd_clk_external_connection_export                           (SD_CLK),                           //      sd_clk_external_connection.export

		  .tri_state_bridge_0_bridge_0_out_tri_state_bridge_0_data     (FL_DQ),     // tri_state_bridge_0_bridge_0_out.tri_state_bridge_0_data
        .tri_state_bridge_0_bridge_0_out_tri_state_bridge_0_readn    (FL_OE_N),    //                                .tri_state_bridge_0_readn
        .tri_state_bridge_0_bridge_0_out_write_n_to_the_cfi_flash_0  (FL_WE_N),  //                                .write_n_to_the_cfi_flash_0
        .tri_state_bridge_0_bridge_0_out_tri_state_bridge_0_address  (FL_ADDR),  //                                .tri_state_bridge_0_address
        .tri_state_bridge_0_bridge_0_out_select_n_to_the_cfi_flash_0 (FL_CE_N), //                                .select_n_to_the_cfi_flash_0

		  .sdram_0_wire_addr                                           (DRAM_ADDR),                                           //                    sdram_0_wire.addr
        .sdram_0_wire_ba                                             ({DRAM_BA_1,DRAM_BA_0}),                                             //                                .ba
        .sdram_0_wire_cas_n                                          (DRAM_CAS_N),                                          //                                .cas_n
        .sdram_0_wire_cke                                            (DRAM_CKE),                                            //                                .cke
        .sdram_0_wire_cs_n                                           (DRAM_CS_N),                                           //                                .cs_n
        .sdram_0_wire_dq                                             (DRAM_DQ),                                             //                                .dq
        .sdram_0_wire_dqm                                            ({DRAM_UDQM,DRAM_LDQM}),                                            //                                .dqm
        .sdram_0_wire_ras_n                                          (DRAM_RAS_N),                                          //                                .ras_n
        .sdram_0_wire_we_n                                           (DRAM_WE_N),                                           //                                .we_n

		  .uart_0_external_connection_rxd                              (UART_RXD),                              //      uart_0_external_connection.rxd
        .uart_0_external_connection_txd                              (UART_TXD),                              //                                .txd
        
		  .led_red_external_connection_export                          (LEDR),                          //     led_red_external_connection.export
        .led_green_external_connection_export                        (LEDG),                        //   led_green_external_connection.export
        
		  .seg7_display_conduit_end_oSEG0                              (HEX0),                              //        seg7_display_conduit_end.oSEG0
        .seg7_display_conduit_end_oSEG1                              (HEX1),                              //                                .oSEG1
        .seg7_display_conduit_end_oSEG2                              (HEX2),                              //                                .oSEG2
        .seg7_display_conduit_end_oSEG3                              (HEX3),                              //                                .oSEG3

		  .audio_0_avalon_slave_0_export_oAUD_DATA                     (AUD_DACDAT),                     //   audio_0_avalon_slave_0_export.oAUD_DATA
        .audio_0_avalon_slave_0_export_oAUD_LRCK                     (AUD_DACLRCK),                     //                                .oAUD_LRCK
        .audio_0_avalon_slave_0_export_oAUD_BCK                      (AUD_BCLK),                      //                                .oAUD_BCK
        .audio_0_avalon_slave_0_export_oAUD_XCK                      (AUD_XCK),                      //                                .oAUD_XCK
        .audio_0_avalon_slave_0_export_iCLK_18_4                     (CLK_18_4),                      //                                .iCLK_18_4

	     .sram_16bit_512k_0_avalon_slave_0_export_DQ                  (SRAM_DQ),                  // sram_16bit_512k_0_avalon_slave_0_export.DQ
        .sram_16bit_512k_0_avalon_slave_0_export_ADDR                (SRAM_ADDR),                //                                        .ADDR
        .sram_16bit_512k_0_avalon_slave_0_export_UB_N                (SRAM_UB_N),                //                                        .UB_N
        .sram_16bit_512k_0_avalon_slave_0_export_LB_N                (SRAM_LB_N),                //                                        .LB_N
        .sram_16bit_512k_0_avalon_slave_0_export_WE_N                (SRAM_WE_N),                //                                        .WE_N
        .sram_16bit_512k_0_avalon_slave_0_export_CE_N                (SRAM_CE_N),                //                                        .CE_N
        .sram_16bit_512k_0_avalon_slave_0_export_OE_N                (SRAM_OE_N)                 //                                        .OE_N
	);

					 
I2C_AV_Config 	u1	(	//	Host Side
						.iCLK(CLOCK_50),
						.iRST_N(KEY[0]),
						//	I2C Side
						.I2C_SCLK(I2C_SCLK),
						.I2C_SDAT(I2C_SDAT)	);

endmodule