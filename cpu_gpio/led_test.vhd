----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:35:36 03/18/2015 
-- Design Name: 
-- Module Name:    led_test - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;

entity led_test is
    Port ( CLK: in STD_LOGIC;
			  GPIO_IN : inout STD_LOGIC_VECTOR(7 downto 0);
--			  CPU_DATA : inout  STD_LOGIC_VECTOR(15 downto 0);
			  GPIO_OUT : inout  STD_LOGIC_VECTOR(7 downto 0);
           LED : out  STD_LOGIC_VECTOR (23 downto 0)
			  );
end led_test;

architecture Behavioral of led_test is
--	type LED_ARRAY is array(3 downto 0) of std_logic_vector(7 downto 0);
--	signal leds : LED_ARRAY;
--	signal ind : integer range 0 to 2;
begin
--	LED_PROC : process(CLK) is
--	begin
--		for ind in 0 to 2 loop
--			leds(ind)<=I;
--		end loop;
--	end process;
--	LEDS_PROC : process(leds) is
--	begin
--		for ind in 0 to 2 loop
--			O(8*ind+7 downto 8*ind) <= leds(ind);
--		end loop;
--	end process;
--	LED(7 downto 0) <= GPIO_IN;
--	LED(23 downto 8) <= (others =>'0');
--	CPU_DATA <= (others => '0');
--	LED(15 downto 0) <= CPU_DATA;
--	LED(23 downto 16) <= GPIO_IN;
--	GPIO_OUT <= GPIO_IN(6 downto 0) & GPIO_IN(7);
	LED(7 downto 0) <= GPIO_IN;
	LED(15 downto 8) <= (others => '0');
	LED(23 downto 16) <= GPIO_OUT;
--	GPIO_OUT(7 downto 0) <= (others => '1');

	process (clk)is
		variable gin: integer range 0 to 255;
	begin
		if rising_edge(clk) then
			gin := to_integer(unsigned(GPIO_IN));
			if gin >= 127 then -- positive
				GPIO_OUT <= std_logic_vector(to_unsigned(127+(gin-127)/2, GPIO_OUT'length));
			else --negative
				GPIO_OUT <= std_logic_vector(to_unsigned(127-(127-gin)/2, GPIO_OUT'length));
			end if;
		end if;
	end process;
end Behavioral;