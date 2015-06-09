----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:25:50 05/20/2015 
-- Design Name: 
-- Module Name:    TFT_LCD - Behavioral 
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

entity TFT_LCD is
   port(
      CLK, RSTB : in std_logic;
      data_out : out std_logic_vector(15 downto 0);
		input: in STD_LOGIC_VECTOR(7 downto 0);	-- GPIO_IN
      de : out std_logic--;	-- data enable
		--GPIO_IN : inout STD_LOGIC_VECTOR(7 downto 0);
      --GPIO_OUT : inout  STD_LOGIC_VECTOR(7 downto 0)
   );
end TFT_LCD;


architecture Behavioral of TFT_LCD is

	constant tHP  : integer := 928;   -- Hsync Period
	constant tHW  : integer := 48;   -- Hsync Pulse Width
	constant tHBP : integer := 40;   -- Hsync Back Porch
	constant tHV  : integer := 800;   -- Horizontal valid data width
	constant tHFP : integer := (tHP-tHW-tHBP-tHV);   -- Horizontal Front Port

	constant tVP  : integer := 525;   -- Vsync Period
	constant tVW  : integer := 3;   -- Vsync Pulse Width
	constant tVBP : integer := 29;   -- Vsync Back Portch
	constant tW   : integer := 480;   -- Vertical valid data width
	constant tVFP : integer := (tVP-tVW-tVBP-tW);   -- Vertical Front Porch

	signal hsync_cnt  : integer range 0 to (tHP+tHW);
	signal vsync_cnt  : integer range 0 to tVP;
	signal de_i: std_logic;

	signal r_data: std_logic_vector(4 downto 0);
	signal g_data: std_logic_vector(5 downto 0);
	signal b_data: std_logic_vector(4 downto 0);
	
	type mem_type is array(0 to 799) of STD_LOGIC_VECTOR(7 downto 0);	-- Address value of RegisterFile
	signal mem: mem_type;
	
	component reg_dclk800 is
		port(
			clk: in STD_LOGIC;
			cnt: out STD_LOGIC_VECTOR(9 downto 0);
			dclk: out STD_LOGIC
		);
	end component;
	
	--signal clk_count: STD_LOGIC_VECTOR(9 downto 0);
	
	signal dclk: STD_LOGIC;
	
--	input: 0~255 (7 downto 0)
-- center: tVW + tVBP + tW/2
-- tW: 480 pixels
-- input => 479~0
-- output= tW - input*479/255 -1 (479~0)


function  divide  (a : UNSIGNED; b : UNSIGNED) return UNSIGNED is
variable a1 : unsigned(a'length-1 downto 0):=a;
variable b1 : unsigned(b'length-1 downto 0):=b;
variable p1 : unsigned(b'length downto 0):= (others => '0');
variable i : integer:=0;

begin
for i in 0 to b'length-1 loop
p1(b'length-1 downto 1) := p1(b'length-2 downto 0);
p1(0) := a1(a'length-1);
a1(a'length-1 downto 1) := a1(a'length-2 downto 0);
p1 := p1-b1;
if(p1(b'length-1) ='1') then
a1(0) :='0';
p1 := p1+b1;
else
a1(0) :='1';
end if;
end loop;
return a1;

end divide;

begin

	-- 31250 clk count
	process(clk)
		variable cnt_data: integer range 0 to 31250:= 0;
	begin
		if(rising_edge(clk)) then
			if cnt_data=31250 then
				dclk<= not dclk;
				cnt_data:= 0;
			else
				cnt_data:= cnt_data + 1;
			end if;
		end if;
	end process;

	--C800: reg_dclk800 port map(clk=> clk, cnt=> clk_count);

	mem(0)<= input;
	process(dclk, input)
	begin
		for I in 1 to 799 loop
			mem(I)<= mem(I-1);
		end loop;
	end process;

	-- vsync, hsync 생성
	process(CLK, RSTB)         --  sync 계산
		begin
			if	(RSTB = '0')then
				hsync_cnt<= 0;
				vsync_cnt<= 0;
			elsif(rising_edge(CLK)) then
				if(hsync_cnt=tHP)then
					hsync_cnt<=0;
				else
					hsync_cnt<= hsync_cnt + 1;
				end if;
				if(hsync_cnt=tHP)then
					if(vsync_cnt=tVP)then
						vsync_cnt<=0;
					else
						vsync_cnt<=vsync_cnt + 1;
					end if;
				end if;
			end if;   
	end process;
	
	-- Data Enable 생성
	process(CLK, RSTB)         --Data Enable
   begin
      if(RSTB = '0')then
				de_i<='0';
      else
         if ((vsync_cnt >= (tVW + tVBP)) and (vsync_cnt <= (tVW + tVBP + tW ))) then
            if(hsync_cnt=(tHBP)) then
               de_i<='1';
            elsif(hsync_cnt=(tHV+tHBP)) then
               de_i<='0';
            else
               de_i<=de_i;
            end if;
         else
            de_i<='0';
         end if;
      end if;
   end process;
	
--	-- RGB 이미지가 출력될 영역 구분. 화면상의 출력될 실질적인 이미지 
--	process(CLK, RSTB)         --출력할 이미지. R,G,B가 화면상에 번갈아 출력
--   begin
--      if (RSTB='0')then
--         r_data<= (others=>'0');
--         g_data<= (others=>'0');
--         b_data<= (others=>'0');
--      elsif (rising_edge(CLK)) then
--         if ( (vsync_cnt >= (tVW + tVBP)) and (vsync_cnt <= (tVW + tVBP + tW )) ) then
--            if ( (hsync_cnt >= (tHW + tHBP-1)) and ( hsync_cnt <= (tHW + tHBP + 799)) ) then
--               if( ( vsync_cnt >= (tVW + tVBP -1 )) and ( vsync_cnt <= (tVW + tVBP +159))) then
--                  r_data <= "11111";
--                  g_data <= (others=>'0');
--                  b_data <= (others=>'0');
--               elsif ( ( vsync_cnt >= (tVW + tVBP +160 )) and ( vsync_cnt <= (tVW + tVBP +319))) then
--                  r_data<= (others=>'0');
--                  g_data<= "111111";
--                  b_data<= (others=>'0');    
--               elsif ( ( vsync_cnt >= (tVW + tVBP +320 )) and ( vsync_cnt <= (tVW + tVBP + 479))) then
--                  r_data<= (others=>'0');
--                  g_data<= (others=>'0');
--                  b_data<= "11111";   
--               end if;
--            end if; 
--         end if;
--      end if;
--   end process;
	
--	process (clk)is
--		variable gin: integer range 0 to 255;
--	begin
--		if rising_edge(clk) then
--			gin := to_integer(unsigned(GPIO_IN));
--			if gin >= 127 then -- positive
--				GPIO_OUT <= std_logic_vector(to_unsigned(127+(gin-127)/2, GPIO_OUT'length));
--			else --negative
--				GPIO_OUT <= std_logic_vector(to_unsigned(127-(127-gin)/2, GPIO_OUT'length));
--			end if;
--		end if;
--	end process;
	
	process(clk, RSTB)         --출력할 이미지. R,G,B가 화면상에 번갈아 출력
   begin
      if (RSTB='0')then
         r_data<= (others=>'0');
         g_data<= (others=>'0');
         b_data<= (others=>'0');
      elsif(rising_edge(clk)) then
         if ( (vsync_cnt >= (tVW + tVBP)) and (vsync_cnt <= (tVW + tVBP + tW )) ) then
            if ( (hsync_cnt >= (tHW + tHBP +1) ) and ( hsync_cnt <= (tHW + tHBP + tHV)) ) then
               if vsync_cnt= (tVW + tVBP + tW/2) then
						r_data<= (others=>'1');
						g_data<= (others=>'1');
						b_data<= (others=>'1');
					elsif vsync_cnt= tVW + tVBP + tW - TO_INTEGER(divide(TO_UNSIGNED(TO_INTEGER(UNSIGNED(mem(hsync_cnt - tHW - tHBP)))*479, 8), TO_UNSIGNED(255, 8))) then	-- 255 is GPIO_IN
						r_data<= (others=>'0');
						g_data<= (others=>'0');
						b_data<= (others=>'1');
					else
						r_data<= (others=>'0');
						g_data<= (others=>'0');
						b_data<= (others=>'0');
               end if;
				end if; 
         end if;
      end if;
   end process;
	
	data_out<= r_data & g_data & b_data;
   de<=de_i;
	
end Behavioral;