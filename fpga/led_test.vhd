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
			  PUSH : in STD_LOGIC_VECTOR(0 to 3);
           LED : out  STD_LOGIC_VECTOR (23 downto 0)
			  );
end led_test;

architecture Behavioral of led_test is
	type reg_typ is array (1 downto 0) of STD_LOGIC_VECTOR(7 downto 0);
	signal reg : reg_typ;
	signal led_buf : STD_LOGIC_VECTOR(7 downto 0);
	type mod_states is (reduce, amplify, swap2, swap1, msb_flip, ands);
	signal mod_state : mod_states;
	alias PUSH_L is PUSH(3);
	alias PUSH_R is PUSH(0);
begin
-- LEDs
	LED(7 downto 0) <= GPIO_IN;
	--LED(15 downto 8) <= led_buf;
	with mod_state select LED(15 downto 8) <=
		(8+0=>'1', others=>'0') when reduce,
		(8+1=>'1', others=>'0') when amplify,
		(8+2=>'1', others=>'0') when swap2,
		(8+3=>'1', others=>'0') when swap1,
		(8+4=>'1', others=>'0') when msb_flip,
		(8+5=>'1', others=>'0') when ands,
		(others => '0') when others;
	LED(23 downto 16) <= GPIO_OUT;
	
--	process (mod_state) is
--	begin
--		mod_state 
--	end process;
		
	process (CLK) is
		constant delay_max : integer := 20000000; -- 0.2 sec, 4 scans
		variable delay : integer range 0 to delay_max;
	begin
		if rising_edge(CLK) then
			if delay >= delay_max then
				delay := 0;
				if PUSH_L = '0' then
					if mod_state = reduce then
						mod_state <= amplify;
					elsif mod_state = amplify then
						mod_state <= swap2;
					elsif mod_state = swap2 then
						mod_state <= swap1;
					elsif mod_state = swap1 then
						mod_state <= msb_flip;
					elsif mod_state = msb_flip then
						mod_state <= ands;
					elsif mod_state = ands then
						mod_state <= reduce;
					end if;
				elsif PUSH_R = '0' then
					if mod_state = reduce then
						mod_state <= ands;
					elsif mod_state = amplify then
						mod_state <= reduce;
					elsif mod_state = swap2 then
						mod_state <= amplify;
					elsif mod_state = swap1 then
						mod_state <= swap2;
					elsif mod_state = msb_flip then
						mod_state <= swap1;
					elsif mod_state = ands then
						mod_state <= msb_flip;
					end if;
				end if;
			elsif PUSH_L = '0' or PUSH_R = '0' then
				delay := delay + 1;
			else
				delay := 0;
			end if;
		end if;
	end process;
	
	process (GPIO_IN) is
		variable gin: integer range -255 to 255;
		
		type swap2_states is (fill_a, fill_b, stream_a, stream_b);
		variable swap2_state : swap2_states:=fill_a;
		
		type swap1_states is (fill, stream);
		variable swap1_state : swap1_states:=fill;
		
		variable last : STD_LOGIC_VECTOR(7 downto 0);
	begin
		if mod_state = reduce then
			gin := to_integer(unsigned(GPIO_IN));
			if gin >= 127 then -- positive
				GPIO_OUT <= std_logic_vector(to_unsigned(127+(gin-127)/2, GPIO_OUT'length));
			else --negative
				GPIO_OUT <= std_logic_vector(to_unsigned(127-(127-gin)/2, GPIO_OUT'length));
			end if;
		elsif mod_state = amplify then
			gin := (to_integer(unsigned(GPIO_IN))-128)*2+128;
			if gin > 255 then
				gin := 255;
			elsif gin < 0 then
				gin := 0;
			end if;
			GPIO_OUT <= std_logic_vector(to_unsigned(gin, GPIO_OUT'length));
		elsif mod_state = swap2 then
			if last /= GPIO_IN then
				if swap2_state = fill_a then
					swap2_state := fill_b;
					GPIO_OUT <= reg(0);
					reg(0) <= GPIO_IN;
				elsif swap2_state = fill_b then
					swap2_state := stream_a;
					GPIO_OUT <= reg(1);
					reg(1) <= GPIO_IN;
				elsif swap2_state = stream_a then
					swap2_state := stream_b;
					GPIO_OUT <= GPIO_IN;
				elsif swap2_state = stream_b then
					swap2_state := fill_a;
					GPIO_OUT <= GPIO_IN;
				end if;
				last := GPIO_IN;
			end if;			
		elsif mod_state = swap1 then
			if last /= GPIO_IN th1en
				if swap1_state = fill then
					swap1_state := stream;
					GPIO_OUT <= last;
				else
					swap1_state := fill;
					GPIO_OUT <= GPIO_IN;
				end if;
				last := GPIO_IN;
			end if;			
		elsif mod_state = msb_flip then
			GPIO_OUT <= not GPIO_IN(7) & GPIO_IN(6 downto 0);
		elsif mod_state = ands then
			GPIO_OUT(6 downto 0) <= GPIO_IN(6 downto 0) and GPIO_IN(7 downto 1);
--				GPIO_OUT(0) <= GPIO_IN(0) and GPIO_IN(1);
--				GPIO_OUT(1) <= GPIO_IN(1) and GPIO_IN(2);
--				GPIO_OUT(2) <= GPIO_IN(2) and GPIO_IN(3);
--				GPIO_OUT(3) <= GPIO_IN(3) and GPIO_IN(4);
--				GPIO_OUT(4) <= GPIO_IN(4) and GPIO_IN(5);
--				GPIO_OUT(5) <= GPIO_IN(5) and GPIO_IN(6);
--				GPIO_OUT(6) <= GPIO_IN(6) and GPIO_IN(7);
			GPIO_OUT(7) <= GPIO_IN(7);
		end if;
	end process;
	
-- half volume
--	process (GPIO_IN)is
--		variable gin: integer range 0 to 255;
--	begin
--		gin := to_integer(unsigned(GPIO_IN));
--		if gin >= 127 then -- positive
--			GPIO_OUT <= std_logic_vector(to_unsigned(127+(gin-127)/2, GPIO_OUT'length));
--		else --negative
--			GPIO_OUT <= std_logic_vector(to_unsigned(127-(127-gin)/2, GPIO_OUT'length));
--		end if;
--	end process;
--	

-- 2 times amplify volume
--	process (GPIO_IN)is
--		variable gin: integer range -255 to 255;
--	begin
--		gin := (to_integer(unsigned(GPIO_IN))-128)*2+128;
--		if gin > 255 then
--			gin := 255;
--		elsif gin < 0 then
--			gin := 0;
--		end if;
--		GPIO_OUT <= std_logic_vector(to_unsigned(gin, GPIO_OUT'length));
--	end process;

-- swap 2 bytes
--	process (GPIO_IN) is
--		type states is (fill_a, fill_b, stream_a, stream_b);
--		variable state : states:=fill_a;
--		variable last : STD_LOGIC_VECTOR(7 downto 0);
--	begin
--		if last /= GPIO_IN then
--			if state = fill_a then
--				state := fill_b;
--				GPIO_OUT <= reg(0);
--				reg(0) <= GPIO_IN;
--			elsif state = fill_b then
--				state := stream_a;
--				GPIO_OUT <= reg(1);
--				reg(1) <= GPIO_IN;
--			elsif state = stream_a then
--				state := stream_b;
--				GPIO_OUT <= GPIO_IN;
--			elsif state = stream_b then
--				state := fill_a;
--				GPIO_OUT <= GPIO_IN;
--			end if;
--			last := GPIO_IN;
--		end if;
--	end process;

-- Or each bits
--	GPIO_OUT(0) <= GPIO_IN(0) or GPIO_IN(1);
--	GPIO_OUT(1) <= GPIO_IN(1) or GPIO_IN(2);
--	GPIO_OUT(2) <= GPIO_IN(2) or GPIO_IN(3);
--	GPIO_OUT(3) <= GPIO_IN(3) or GPIO_IN(4);
--	GPIO_OUT(4) <= GPIO_IN(4) or GPIO_IN(5);
--	GPIO_OUT(5) <= GPIO_IN(5) or GPIO_IN(6);
--	GPIO_OUT(6) <= GPIO_IN(6) or GPIO_IN(7);
--	GPIO_OUT(7) <= GPIO_IN(7) or GPIO_IN(0);

-- swap 1 byte
--	process (GPIO_IN) is
--		type states is (fill, stream);
--		variable state : states:=fill;
--		variable last : STD_LOGIC_VECTOR(7 downto 0);
--	begin
--		if last /= GPIO_IN then
--			if state = fill then
--				state := stream;
--				GPIO_OUT <= last;
--			else
--				state := fill;
--				GPIO_OUT <= GPIO_IN;
--			end if;
--			last := GPIO_IN;
--		end if;
--	end process;

-- flipped msb
--	GPIO_OUT <= not GPIO_IN(7) & GPIO_IN(6 downto 0);

end Behavioral;