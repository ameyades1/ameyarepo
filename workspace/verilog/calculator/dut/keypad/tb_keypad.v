/*-------------------------------------
MATRIX KEYPAD TESTBENCH

Author: adeswand
Date  : 03/10/2016

---------------------------------------*/



module tb_keypad();

// Customizable parameters         
parameter KEY_ROW = 4;         
parameter KEY_COL = 4;
parameter CLK_CYC = 20;
 
// Inputs
reg [KEY_ROW-1 : 0] row;    
reg [KEY_COL-1 : 0] col;
reg                 key_in;
 
// Outputs
wire [KEY_ROW-1 : 0] key;
wire                 valid;

reg clk;

initial begin
  clk = 0;
  forever clk =#CLK_CYC ~clk;
end

initial begin
  #100;
  
  row = 6;
  col = 1;
  key_in = 1;
  
  #140
  $display("Row %d, Col %d, Out Key %d, Valid %d", row, col, key, valid);

  $finish;
end

dut_keypad dut(.clk(clk), .row(row), .col(col), .key_in(key_in), .key(key), .valid(valid));

endmodule














