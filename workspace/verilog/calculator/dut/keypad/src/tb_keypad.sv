/*-------------------------------------
 M A T R I X   K E Y P A D  
 T E S T B E N C H

Author: adeswand
Date  : 03/10/2016

Description:
This matrix keypad accepts row, col and
latches the input on the posedge
of the key_in signal. Decodes and outputs 
the key pressed.

  1  2  3  +     
  4  5  6  -
  7  8  9  *
  0  C  =  /

Revision History:

When        Who       What
03/10/2016  adeswand  First Draft
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

  row = 1;
  col = 2;
  key_in = 1;
  
  #140
  $display("Row %d, Col %d, Out Key %d, Valid %d", row, col, key, valid);
	
  row = 0;
  col = 0;
  key_in = 1;
  
  #140
  $display("Row %d, Col %d, Out Key %d, Valid %d", row, col, key, valid);
  $finish;
end

// Instantiate the DUT
dut_keypad dut(.clk(clk), .row(row), .col(col), .key_in(key_in), .key(key), .valid(valid));

endmodule

