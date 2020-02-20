module switch(input wire clk, reset, input wire [7:0] select, output reg [15:0] sample_rate, arm_Rate);

always@(select, reset)
begin
	if(reset)
	begin
		sample_rate <= 0;
		arm_Rate <= 0;
	end
	else
	begin
		case(select)
			8'b00000111:	
			begin
				sample_rate <= 1046;
				arm_Rate <= 300;
			end
			8'b00001011:	
			begin
				sample_rate <= 1174;
				arm_Rate <= 250;
			end
			8'b00001101:
			begin
				sample_rate <= 1318;
				arm_Rate <= 200;
			end
			8'b00001110:
			begin
				sample_rate <= 1396;
				arm_Rate <= 100;
			end
			default:	
			begin
				sample_rate <= 0;
				arm_Rate <= 0;
			end
		endcase
	end
end

endmodule

