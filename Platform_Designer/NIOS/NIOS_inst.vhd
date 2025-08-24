	component NIOS is
		port (
			clk_clk             : in  std_logic := 'X'; -- clk
			pio_external_export : out std_logic;        -- export
			reset_reset_n       : in  std_logic := 'X'  -- reset_n
		);
	end component NIOS;

	u0 : component NIOS
		port map (
			clk_clk             => CONNECTED_TO_clk_clk,             --          clk.clk
			pio_external_export => CONNECTED_TO_pio_external_export, -- pio_external.export
			reset_reset_n       => CONNECTED_TO_reset_reset_n        --        reset.reset_n
		);

