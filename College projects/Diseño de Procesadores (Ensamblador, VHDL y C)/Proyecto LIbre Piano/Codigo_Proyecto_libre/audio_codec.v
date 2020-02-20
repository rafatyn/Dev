module audio_codec (
output			oAUD_DATA,
output			oAUD_LRCK,
output reg		oAUD_BCK,
input	[1:0]	iSrc_Select,
input			iCLK_18_4,
input			iRST_N,
input [15:0]    var_Rate,
input [15:0]    arm_Rate
						);

parameter	REF_CLK			=	18432000;	//	18.432	MHz
parameter	DATA_WIDTH		=	16;			//	16		Bits
parameter   SAMPLE_RATE    =  48000;      // 48    KHz
parameter	CHANNEL_NUM		=	2;			   //	Dual Channel

parameter	SIN_SAMPLE_DATA	=	48;

////////////	Input Source Number	//////////////
parameter	SIN_SANPLE		=	0;
//////////////////////////////////////////////////
//	Internal Registers and Wires
reg		[3:0]	BCK_DIV;
reg		[8:0]	LRCK_1X_DIV;
reg		[7:0]	LRCK_2X_DIV;
reg		[6:0]	LRCK_4X_DIV;
reg 		[9:0] Sel_Clk;
reg		[5:0]	select;
reg 		[9:0] Sel_Clk_Arm;
reg		[5:0]	select_Arm;
reg		[3:0]	SEL_Cont;
wire     [15:0]sound_out;
wire     [15:0]sound_2;
wire     [15:0]sound_1;
////////////////////////////////////
reg				LRCK_1X;
reg				LRCK_2X;
reg				LRCK_4X;

////////////	AUD_BCK Generator	//////////////
always@(posedge iCLK_18_4 or negedge iRST_N)
begin
	if(!iRST_N)
	begin
		BCK_DIV		<=	0;
		oAUD_BCK	<=	0;
	end
	else
	begin
		if(BCK_DIV >= REF_CLK/(SAMPLE_RATE*DATA_WIDTH*CHANNEL_NUM*2)-1 )
		begin
			BCK_DIV		<=	0;
			oAUD_BCK	<=	~oAUD_BCK;
		end
		else
		BCK_DIV		<=	BCK_DIV+1;
	end
end

//////////////////////////////////////////////////
////////////	AUD_LRCK Generator	//////////////
always@(posedge iCLK_18_4 or negedge iRST_N)
begin
	if(!iRST_N)
	begin
		LRCK_1X_DIV	<=	0;
		LRCK_2X_DIV	<=	0;
		LRCK_4X_DIV	<=	0;
		LRCK_1X		<=	0;
		LRCK_2X		<=	0;
		LRCK_4X		<=	0;
	end
	else
	begin
		//	LRCK 1X
		if(LRCK_1X_DIV >= REF_CLK/(SAMPLE_RATE*2)-1 )
		begin
			LRCK_1X_DIV	<=	0;
			LRCK_1X	<=	~LRCK_1X;
		end
		else
		LRCK_1X_DIV		<=	LRCK_1X_DIV+1;
		//	LRCK 2X
		if(LRCK_2X_DIV >= REF_CLK/(SAMPLE_RATE*4)-1 )
		begin
			LRCK_2X_DIV	<=	0;
			LRCK_2X	<=	~LRCK_2X;
		end
		else
		LRCK_2X_DIV		<=	LRCK_2X_DIV+1;
		//	LRCK 4X
		if(LRCK_4X_DIV >= REF_CLK/(SAMPLE_RATE*8)-1 )
		begin
			LRCK_4X_DIV	<=	0;
			LRCK_4X	<=	~LRCK_4X;
		end
		else
		LRCK_4X_DIV		<=	LRCK_4X_DIV+1;
	end
end
assign	oAUD_LRCK	=	LRCK_1X;

//////////////////////////////////////////////////
////////////////	Sound Out	////////////////////
assign sound_out = (sound_1 + sound_2)/2;

always@(negedge oAUD_BCK or negedge iRST_N)
begin
	if(!iRST_N)
		SEL_Cont	<=	0;
	else
		SEL_Cont	<=	SEL_Cont+1;
end

assign oAUD_DATA = sound_out[~SEL_Cont];

////////////	Select Generator	//////////////
always@(posedge iCLK_18_4 or negedge iRST_N)
begin
	if(!iRST_N)
	begin
		Sel_Clk  <=	0;
		select	<=	0;
	end
	else
	begin
		if(Sel_Clk >= REF_CLK/(var_Rate*64) )
		begin
			Sel_Clk		<=	0;
			select	<=	select+1;
		end
		else
		Sel_Clk		<=	Sel_Clk+1;
	end
end

sin_table Stable(select, sound_1);

////////////	Armonic 1 Generator	//////////////
always@(posedge iCLK_18_4 or negedge iRST_N)
begin
	if(!iRST_N)
	begin
		Sel_Clk_Arm  <=	0;
		select_Arm	<=	0;
	end
	else
	begin
		if(Sel_Clk_Arm >= REF_CLK/(arm_Rate*48) )
		begin
			Sel_Clk_Arm		<=	0;
			select_Arm	<=	select_Arm+1;
		end
		else
		Sel_Clk_Arm		<=	Sel_Clk_Arm+1;
	end
end

sin_table2 S1table(select_Arm, sound_2);

endmodule
