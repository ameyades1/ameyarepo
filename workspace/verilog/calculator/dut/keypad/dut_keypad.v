/*--------------------------------------
       M A T R I X   K E Y P A D 

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

-------------------------------------*/


module dut_keypad (clk, row, col, key_in, valid, key);

// Customizable parameters
parameter KEY_ROW = 4;
parameter KEY_COL = 4;

// Inputs
input wire [KEY_ROW-1 : 0] row;
input wire [KEY_COL-1 : 0] col;
input wire                 key_in;
input wire                 clk;

// Outputs
output reg [KEY_ROW-1 : 0] key;
output reg                 valid;

// Make sure a key is pressed, and no two rows or coloumns
// are simultaneously pressed
always @(posedge clk) begin
  if(key_in) begin
    if (row > 3 || col > 3) begin  
      key <= 0;
      valid <= 0;
    end
    else begin
      key <= KEY_COL * row + col;
      valid <= 1;
    end
  end
end

endmodule
