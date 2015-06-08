----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:23:32 05/27/2015 
-- Design Name: 
-- Module Name:    RegisterFile - Behavioral 
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

entity reg_8bit800 is
	port(
		clk: in STD_LOGIC; 
		--WR: in STD_LOGIC;
		input: in STD_LOGIC_VECTOR(7 downto 0);
		--addr_readA, addr_readB, addr_write: in STD_LOGIC_VECTOR(9 downto 0);
		output: out STD_LOGIC_VECTOR(7 downto 0)
	);
end reg_8bit800;


architecture Behavioral of reg_8bit800 is

	type mem_type is array(0 to 799) of STD_LOGIC_VECTOR(7 downto 0);	-- Address value of RegisterFile
	signal mem: mem_type;
	signal dclk: dclk;

begin

	process(clk)
		variable addr: integer range 0 to 799;	-- Address value of RegisterFile
	begin
		if clk'event and clk= '1' then
			--if WR= '1' then
				addr:= CONV_INTEGER(addr_write);	-- STD_LOGIC_VECTOR=> integer
				mem(addr)<= input;	-- Write address
			--end if;
		end if;
	end process;

	process(clk)
		variable addrA: integer range 0 to 799;
		variable addrB: integer range 0 to 799;
	begin
		if clk'event and clk= '1' then
			addrA:= CONV_INTEGER(addr_readA);
			outputA<= mem(addrA);	-- Read address
			addrB:= CONV_INTEGER(addr_readB);
			outputB<= mem(addrB);	-- Read address
		end if;
	end process;

end Behavioral;