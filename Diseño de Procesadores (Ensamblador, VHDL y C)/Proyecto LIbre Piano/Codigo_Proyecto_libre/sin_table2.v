module sin_table2 (input wire [5:0] select, output reg [15:0] wave);

always@(select[5:0])
begin
    case(select[5:0])
 0 :wave=0;
 1 :wave=4000;
 2 :wave=8000;
 3 :wave=12000;
 4 :wave=16000;
 5 :wave=20000;
 6 :wave=24000;
 7 :wave=28000;
 8 :wave=32000;
 9 :wave=36000;
 10 :wave=40000;
 11 :wave=44000;
 12 :wave=48000;
 13 :wave=44000;
 14 :wave=40000;
 15 :wave=36000;
 16 :wave=32000;
 17 :wave=28000;
 18 :wave=24000;
 19 :wave=20000;
 20 :wave=16000;
 21 :wave=12000;
 22 :wave=8000;
 23 :wave=4000;
 24 :wave=0;
 25 :wave=-4000;
 26 :wave=-8000;
 27 :wave=-12000;
 28 :wave=-16000;
 29 :wave=-20000;
 30 :wave=-24000;
 31 :wave=-28000;
 32 :wave=-32000;
 33 :wave=-36000;
 34 :wave=-40000;
 35 :wave=-44000;
 36 :wave=-48000;
 37 :wave=-44000;
 38 :wave=-40000;
 39 :wave=-36000;
 40 :wave=-32000;
 41 :wave=-28000;
 42 :wave=-24000;
 43 :wave=-20000;
 44 :wave=-16000;
 45 :wave=-12000;
 46 :wave=-8000;
 47 :wave=-4000;
 48 :wave=0;
default :wave=0;
        endcase
end

endmodule
