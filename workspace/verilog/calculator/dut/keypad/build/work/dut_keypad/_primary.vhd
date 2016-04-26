library verilog;
use verilog.vl_types.all;
entity dut_keypad is
    generic(
        KEY_ROW         : integer := 4;
        KEY_COL         : integer := 4
    );
    port(
        clk             : in     vl_logic;
        row             : in     vl_logic_vector;
        col             : in     vl_logic_vector;
        key_in          : in     vl_logic;
        valid           : out    vl_logic;
        key             : out    vl_logic_vector
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of KEY_ROW : constant is 1;
    attribute mti_svvh_generic_type of KEY_COL : constant is 1;
end dut_keypad;
