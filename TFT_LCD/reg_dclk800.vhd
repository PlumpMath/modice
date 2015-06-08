----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:58:39 04/08/2015 
-- Design Name: 
-- Module Name:    clock_divider - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity reg_dclk800 is
	port( 
		clk : in STD_LOGIC;	 
		cnt: out STD_LOGIC_VECTOR(9 downto 0);
		dclk : out STD_LOGIC
		);
end reg_dclk800;

architecture Behavioral of reg_dclk800 is

signal cnt_data:STD_LOGIC_VECTOR(9 downto 0);
	
begin
	process(clk)
	begin
		cnt_data<=(others=>'0');
		dclk<='0';
		if clk'event and clk='1' then
			if cnt_data=x"320" then
				cnt_data<=(others=>'0');
				dclk<='0';
			elsif cnt_data=x"190" then
				dclk<='1';
				cnt_data<=cnt_data+1;
			else
				cnt_data<=cnt_data+1;
			end if;
		end if;
	end process;
	
	cnt<= cnt_data;

end Behavioral;