
-- VHDL Instantiation Created from source file TFT_LCD.vhd -- 17:05:50 05/20/2015
--
-- Notes: 
-- 1) This instantiation template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the instantiated module
-- 2) To use this template to instantiate this entity, cut-and-paste and then edit

	COMPONENT TFT_LCD
	PORT(
		CLK : IN std_logic;
		RSTB : IN std_logic;          
		data_out : OUT std_logic_vector(15 downto 0);
		de : OUT std_logic
		);
	END COMPONENT;

	Inst_TFT_LCD: TFT_LCD PORT MAP(
		CLK => ,
		RSTB => ,
		data_out => ,
		de => 
	);


