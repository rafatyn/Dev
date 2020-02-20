

create_clock -period 20 [get_ports CLOCK_50]

create_clock -period 37.037 [get_ports CLOCK_27[0]]

create_clock -period 20 [get_ports SD_CLK]

derive_pll_clocks

derive_clock_uncertainty
