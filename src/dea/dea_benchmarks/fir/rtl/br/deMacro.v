`define SAC(ID,SIGNAL,MASK) \
`ifdef ID  \
    {SIGNAL & MASK}\
`else\
    SIGNAL\
`endif

