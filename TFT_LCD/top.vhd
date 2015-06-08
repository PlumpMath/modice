----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:34:07 05/20/2015 
-- Design Name: 
-- Module Name:    top - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity top is
	port(
		CLK: in STD_LOGIC;
		data_out: out std_logic_vector(15 downto 0);
		RSTB: in STD_LOGIC;
		de: out STD_LOGIC;
		GPIO_IN: inout std_logic_vector(7 downto 0);
		GPIO_OUT: inout std_logic_vector(7 downto 0);
		lcd_clk: out STD_LOGIC;
		LED : out  STD_LOGIC_VECTOR (23 downto 0)
	);
end top;


architecture Behavioral of top is

	signal RST_INV: STD_LOGIC;
	signal lcd_25m_clk: STD_LOGIC;
	
	signal lcd_den: STD_LOGIC;

	component clk_25m
	   port( 
			CLKIN_IN        : in    std_logic; 
         RST_IN          : in    std_logic; 
         CLKFX_OUT       : out   std_logic; 
         CLKIN_IBUFG_OUT : out   std_logic; 
         CLK0_OUT        : out   std_logic; 
         LOCKED_OUT      : out   std_logic
		);	
	end component;
	
	component TFT_LCD
	   port(
      CLK, RSTB : in std_logic;
      data_out : out std_logic_vector(15 downto 0);
      de : out std_logic;	-- data enable
		input: in STD_LOGIC_VECTOR(7 downto 0)	-- GPIO_IN
		);
	end component;

begin

	LED(7 downto 0) <= GPIO_IN;
	LED(15 downto 8) <= (others => '0');
	LED(23 downto 16) <= GPIO_OUT;

	process (GPIO_IN)is
		variable gin: integer range 0 to 255;
	begin
		gin := to_integer(unsigned(GPIO_IN));
		if gin >= 127 then -- positive
			GPIO_OUT <= std_logic_vector(to_unsigned(127+(gin-127)/2, GPIO_OUT'length));
		else --negative
			GPIO_OUT <= std_logic_vector(to_unsigned(127-(127-gin)/2, GPIO_OUT'length));
		end if;
	end process;

	u_clk_25m: clk_25m
		port map(
			CLKIN_IN=> CLK,
			RST_IN=> RST_INV,
			CLKFX_OUT=> lcd_25m_clk,
			CLKIN_IBUFG_OUT=> open,
			CLK0_OUT=> open,
			LOCKED_OUT=> open
		);

	u_tft_lcd: TFT_LCD
		port map(
			CLK=> lcd_25m_clk,
			RSTB=> RSTB,
			data_out=> data_out,
			input=> GPIO_IN,
			de=> lcd_den
		);
		
	de<= lcd_den;
	lcd_clk<= lcd_25m_clk;
	RST_INV<= not RSTB;
	
end Behavioral;