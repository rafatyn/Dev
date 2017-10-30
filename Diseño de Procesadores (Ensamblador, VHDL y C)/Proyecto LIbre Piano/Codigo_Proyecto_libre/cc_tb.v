// Testbench ejemplo

`timescale 1 ns / 10 ps //Directiva que fija la unidad de tiempo de simulación y el paso de simulación

module micro_tb; //Declaracion de modulo del testbench


//declaracion de señales

reg clk, reset; //las señales de entrada al modulo a testear cuenta1. Se han declarado reg porque queremos inicializarlas
reg [7:0] test_EntS1, test_EntS2, test_EntS3, test_EntS4;
wire [7:0] test_ESal1, test_ESal2, test_ESal3, test_ESal4;
wire [9:0] test_PC;

//implementacion reloj
always
begin
  clk = 1;
  #10;
  clk = 0;
  #10;
end

//instancia del modulo a testear
caminocompleto cc_test(clk, reset, test_EntS1, test_EntS2, test_EntS3, test_EntS4, test_ESal1, test_ESal2, test_ESal3, test_ESal4, test_PC);

initial
begin
  $monitor("tiempo=%0d reloj=%b reset=%b EntS1=%b EntS2=%b EntS3=%b EntS4=%b ESal1=%b ESal2=%b ESal3=%b ESal4=%b PC=%b", $time, clk, reset, test_EntS1, test_EntS2, test_EntS3, test_EntS4, test_ESal1, test_ESal2, test_ESal3, test_ESal4, test_PC);
  $dumpfile("cc_tb.vcd");
  $dumpvars;

  clk = 1;
  reset = 1;
  test_EntS1 = 8'b00000000;
  test_EntS2 = 8'b00000111;
  test_EntS3 = 8'b00000000;
  test_EntS4 = 8'b00000000;
  #15;
  reset = 0;
  #100;
  test_EntS1 = 8'b00000011;
  #150
  test_EntS2 = 8'b00000101;
  #200;
  test_EntS2 = 8'b00000000;
  #200
  $finish;  //fin simulacion

end
endmodule 
