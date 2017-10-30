module sin_table (input wire [5:0] select, output reg [15:0] wave);

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
 13 :wave=52000;
 14 :wave=56000;
 15 :wave=60000;
 16 :wave=56000;
 17 :wave=52000;
 18 :wave=48000;
 19 :wave=44000;
 20 :wave=40000;
 21 :wave=36000;
 22 :wave=32000;
 23 :wave=28000;
 24 :wave=24000;
 25 :wave=20000;
 26 :wave=16000;
 27 :wave=12000;
 28 :wave=8000;
 29 :wave=4000;
 30 :wave=1000;
 31 :wave=0;
 32 :wave=-1000;
 33 :wave=-4000;
 34 :wave=-8000;
 35 :wave=-12000;
 36 :wave=-16000;
 37 :wave=-20000;
 38 :wave=-24000;
 39 :wave=-28000;
 40 :wave=-32000;
 41 :wave=-36000;
 42 :wave=-40000;
 43 :wave=-44000;
 44 :wave=-48000;
 45 :wave=-52000;
 46 :wave=-56000;
 47 :wave=-60000;
 48 :wave=-56000;
 49 :wave=-52000;
 50 :wave=-48000;
 51 :wave=-44000;
 52 :wave=-40000;
 53 :wave=-36000;
 54 :wave=-32000;
 55 :wave=-28000;
 56 :wave=-24000;
 57 :wave=-20000;
 58 :wave=-16000;
 59 :wave=-12000;
 60 :wave=-8000;
 61 :wave=-4000;
 62 :wave=-1000;
 63 :wave=0;
default :wave=0;
        endcase
end

endmodule
