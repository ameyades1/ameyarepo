library verilog;
use verilog.vl_types.all;
entity tb_keypad is
    generic(
        KEY_ROW         : integer := 4;
        KEY_COL         : integer := 4;
        CLK_CYC         : integer := 20
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of KEY_ROW : constant is 1;
    attribute mti_svvh_generic_type of KEY_COL : constant is 1;
    attribute mti_svvh_generic_type of CLK_CYC : constant is 1;
end tb_keypad;
