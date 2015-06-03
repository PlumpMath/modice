--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   17:26:35 05/20/2015
-- Design Name:   
-- Module Name:   D:/ISE/TFT_LCD/TestBench_TFT_LCD.vhd
-- Project Name:  TFT_LCD
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: TFT_LCD
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY TestBench_TFT_LCD IS
END TestBench_TFT_LCD;
 
ARCHITECTURE behavior OF TestBench_TFT_LCD IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT TFT_LCD
    PORT(
         CLK : IN  std_logic;
         RSTB : IN  std_logic;
         data_out : OUT  std_logic_vector(15 downto 0);
         de : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal RSTB : std_logic := '0';

 	--Outputs
   signal data_out : std_logic_vector(15 downto 0);
   signal de : std_logic;

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: TFT_LCD PORT MAP (
          CLK => CLK,
          RSTB => RSTB,
          data_out => data_out,
          de => de
        );

   -- Clock process definitions
   CLK_process :process
   begin
		CLK <= '0';
		wait for CLK_period/2;
		CLK <= '1';
		wait for CLK_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for CLK_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
