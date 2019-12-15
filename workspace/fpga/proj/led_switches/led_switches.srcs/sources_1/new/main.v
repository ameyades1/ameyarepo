`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/23/2019 10:45:44 AM
// Design Name: 
// Module Name: main
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module main(
    input [3:0] btn,
    output reg [1:0] led,
    output reg led4_b,
    output reg led4_g
    );
    
    always @(*) begin
        led[1] <= btn[3];
        led[0] <= btn[2];
        led4_b <= btn[1];
        led4_g <= btn[0];
    end
    
endmodule
