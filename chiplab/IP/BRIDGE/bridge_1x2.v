/*------------------------------------------------------------------------------
--------------------------------------------------------------------------------
Copyright (c) 2016, Loongson Technology Corporation Limited.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of Loongson Technology Corporation Limited nor the names of 
its contributors may be used to endorse or promote products derived from this 
software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL LOONGSON TECHNOLOGY CORPORATION LIMITED BE LIABLE
TO ANY PARTY FOR DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
--------------------------------------------------------------------------------
------------------------------------------------------------------------------*/

//*************************************************************************
//   > File Name   : bridge_1x2.v
//   > Description : bridge between cpu_ram and data ram, confreg
//   
//     master:    cpu_ram
//                   |  \
//     1 x 2         |   \  
//     bridge:       |    \                    
//                   |     \       
//     slave:      sram  confreg
//
//   > Author      : LOONGSON
//   > Date        : 2017-08-04
//*************************************************************************
`define CONF_ADDR_BASE 32'h1faf_0000
`define CONF_ADDR_MASK 32'h1fff_0000 //for bfaf or 1faf
module bridge_1x2#(                                 
    parameter   BUS_WIDTH  = 32,
    parameter   DATA_WIDTH = 64, 
    parameter   CPU_WIDTH  = 32
)
(
    input                           clk,               // clock 
    input                           resetn,            // reset, active low
    // master : cpu ram
    input                           cpu_ram_ren,       // cpu ram access enable
    input  [DATA_WIDTH/8-1      :0] cpu_ram_wen,       // cpu ram write byte enable
    input  [BUS_WIDTH-1         :0] cpu_ram_raddr,     // cpu ram address
    input  [BUS_WIDTH-1         :0] cpu_ram_waddr,     // cpu ram address
    input  [DATA_WIDTH-1        :0] cpu_ram_wdata,     // cpu ram write data
    output [DATA_WIDTH-1        :0] cpu_ram_rdata,     // cpu ram read data
    // slave : sram 
    output                          sram_ren,          // access sram enable
    output [DATA_WIDTH/8-1      :0] sram_wen,          // write enable 
    output [BUS_WIDTH-1         :0] sram_raddr,        // address
    output [BUS_WIDTH-1         :0] sram_waddr,        // address
    output [DATA_WIDTH-1        :0] sram_wdata,        // data in
    input  [DATA_WIDTH-1        :0] sram_rdata        // data out
    ,
    input                           cpu_rvalid,
    input                           cpu_rready,
    input                           cpu_rlast
    `ifndef RAND_TEST
    // slave : confreg 
    ,
    output                          conf_ren,          // access confreg enable 
    output [DATA_WIDTH/8-1      :0] conf_wen,          // access confreg enable 
    output [BUS_WIDTH-1         :0] conf_raddr,        // address
    output [BUS_WIDTH-1         :0] conf_waddr,        // address
    output [DATA_WIDTH-1        :0] conf_wdata,        // write data
    input  [DATA_WIDTH-1        :0] conf_rdata         // read data
    `endif
);
    wire cpu_one_transfer_end = cpu_rvalid && cpu_rready && cpu_rlast;
    wire read_sel_sram;  // cpu data is from data ram
    wire read_sel_conf;  // cpu data is from confreg

    wire write_sel_sram;  // cpu data is from data ram
    wire write_sel_conf;  // cpu data is from confreg

    assign read_sel_sram = !read_sel_conf;
    assign write_sel_sram = !write_sel_conf;


    // data sram
    assign sram_ren   = cpu_ram_ren & read_sel_sram;
    assign sram_wen   = cpu_ram_wen & {DATA_WIDTH/8{write_sel_sram}};
    assign sram_raddr = cpu_ram_raddr;
    assign sram_waddr = cpu_ram_waddr;
    assign sram_wdata = cpu_ram_wdata;

    // confreg
    `ifndef RAND_TEST
    assign read_sel_conf = (cpu_ram_raddr[31:0] & `CONF_ADDR_MASK) == `CONF_ADDR_BASE;
    assign write_sel_conf = (cpu_ram_waddr & `CONF_ADDR_MASK) == `CONF_ADDR_BASE;
    reg read_sel_sram_r; // reg of sel_dram 
    reg read_sel_conf_r; // reg of sel_conf 
    reg sel_not_change;

    assign conf_ren   = cpu_ram_ren & read_sel_conf;
    assign conf_wen   = cpu_ram_wen & {DATA_WIDTH/8{write_sel_conf}};
    assign conf_raddr = cpu_ram_raddr;
    assign conf_waddr = cpu_ram_waddr;
    assign conf_wdata = cpu_ram_wdata;

    always @ (posedge clk)
    begin
        if (!resetn)
        begin
            read_sel_sram_r <= 1'b0;
            read_sel_conf_r <= 1'b0;
        end
        else if (!sel_not_change||cpu_one_transfer_end)
        begin
            read_sel_sram_r <= read_sel_sram;
            read_sel_conf_r <= read_sel_conf;
        end
    end

    always @ (posedge clk)
    begin
        if (!resetn)
        begin
            sel_not_change <= 1'b0;
        end
        else if(cpu_ram_ren)
        begin
            sel_not_change <= 1'b1;
        end
        else if(cpu_one_transfer_end)
        begin
            sel_not_change <= 1'b0;
        end
    end

    assign cpu_ram_rdata =  {DATA_WIDTH{read_sel_sram_r}} & sram_rdata
                          | {DATA_WIDTH{read_sel_conf_r}} & conf_rdata;
    `else
    assign read_sel_conf  = 1'b0;
    assign write_sel_conf = 1'b0;

    assign cpu_ram_rdata =  sram_rdata;
    `endif


endmodule

