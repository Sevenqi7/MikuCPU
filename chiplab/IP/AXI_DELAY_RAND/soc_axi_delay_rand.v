//+FHDR-----------------------------------------------------------------
// (C) Copyright Loongson Technology Corporation Limited. All rights reserved
// Loongson Confidential Proprietary
//-FHDR-----------------------------------------------------------------
module soc_axi_delay_rand#(
    parameter   BUS_WIDTH  = 32,
    parameter   DATA_WIDTH = 64, 
    parameter   CPU_WIDTH  = 32
)
(
    input  wire         enable_delay,
    input  wire [22:0]  random_seed ,
    // group s
    output wire [BUS_WIDTH-1    :0] s_araddr    ,
    output wire [1              :0] s_arburst   ,
    output wire [3              :0] s_arcache   ,
    output wire [3              :0] s_arid      ,
    output wire [3              :0] s_arlen     ,
    output wire [1              :0] s_arlock    ,
    output wire [2              :0] s_arprot    ,
    input  wire                     s_arready   ,
    output wire [2              :0] s_arsize    ,
    output wire                     s_arvalid   ,
    output wire [BUS_WIDTH-1    :0] s_awaddr    ,
    output wire [1              :0] s_awburst   ,
    output wire [3              :0] s_awcache   ,
    output wire [3              :0] s_awid      ,
    output wire [3              :0] s_awlen     ,
    output wire [1              :0] s_awlock    ,
    output wire [2              :0] s_awprot    ,
    input  wire                     s_awready   ,
    output wire [2              :0] s_awsize    ,
    output wire                     s_awvalid   ,
    input  wire [3              :0] s_bid       ,
    output wire                     s_bready    ,
    input  wire [1              :0] s_bresp     ,
    input  wire                     s_bvalid    ,
    input  wire                     aclk        ,
    input  wire                     aresetn     ,
    input  wire [DATA_WIDTH-1   :0] s_rdata     ,
    input  wire [3              :0] s_rid       ,
    input  wire                     s_rlast     ,
    output wire                     s_rready    ,
    input  wire [1              :0] s_rresp     ,
    input  wire                     s_rvalid    ,
    output wire [DATA_WIDTH-1   :0] s_wdata     ,
    output wire [3              :0] s_wid       ,
    output wire                     s_wlast     ,
    input  wire                     s_wready    ,
    output wire [DATA_WIDTH/8-1 :0] s_wstrb     ,
    output wire                     s_wvalid    ,
    // group m
    input  wire [BUS_WIDTH-1    :0] m_araddr    ,
    input  wire [1              :0] m_arburst   ,
    input  wire [3              :0] m_arcache   ,
    input  wire [3              :0] m_arid      ,
    input  wire [3              :0] m_arlen     ,
    input  wire [1              :0] m_arlock    ,
    input  wire [2              :0] m_arprot    ,
    output wire                     m_arready   ,
    input  wire [2              :0] m_arsize    ,
    input  wire                     m_arvalid   ,
    input  wire [BUS_WIDTH-1    :0] m_awaddr    ,
    input  wire [1              :0] m_awburst   ,
    input  wire [3              :0] m_awcache   ,
    input  wire [3              :0] m_awid      ,
    input  wire [3              :0] m_awlen     ,
    input  wire [1              :0] m_awlock    ,
    input  wire [2              :0] m_awprot    ,
    output wire                     m_awready   ,
    input  wire [2              :0] m_awsize    ,
    input  wire                     m_awvalid   ,
    output wire [3              :0] m_bid       ,
    input  wire                     m_bready    ,
    output wire [1              :0] m_bresp     ,
    output wire                     m_bvalid    ,
    output wire [DATA_WIDTH-1   :0] m_rdata     ,
    output wire [3              :0] m_rid       ,
    output wire                     m_rlast     ,
    input  wire                     m_rready    ,
    output wire [1              :0] m_rresp     ,
    output wire                     m_rvalid    ,
    input  wire [DATA_WIDTH-1   :0] m_wdata     ,
    input  wire [3              :0] m_wid       ,
    input  wire                     m_wlast     ,
    output wire                     m_wready    ,
    input  wire [DATA_WIDTH/8-1 :0] m_wstrb     ,
    input  wire                     m_wvalid     
);
wire        mask_ar         ;
reg         mask_ar_disable ;
wire        mask_ar_ok      ;
wire        mask_ar_raw     ;
wire        mask_aw         ;
reg         mask_aw_disable ;
wire        mask_aw_ok      ;
wire        mask_aw_raw     ;
wire        mask_b          ;
wire        mask_b_raw      ;
reg         mask_no_delay   ;
wire        mask_r          ;
wire        mask_r_raw      ;
reg  [22:0] mask_random     ;
wire [22:0] mask_random_next;
wire        mask_reset      ;
reg         mask_short_delay;
wire        mask_w          ;
reg         mask_w_disable  ;
wire        mask_w_ok       ;
wire        mask_w_raw      ;
// group s
assign s_araddr               = m_araddr ;
assign s_arburst              = m_arburst;
assign s_arcache              = m_arcache;
assign s_arid                 = m_arid   ;
assign s_arlen                = m_arlen  ;
assign s_arlock               = m_arlock ;
assign s_arprot               = m_arprot ;
assign s_arsize               = m_arsize ;
assign s_arvalid              = m_arvalid && (mask_ar || !enable_delay);
assign s_awaddr               = m_awaddr ;
assign s_awburst              = m_awburst;
assign s_awcache              = m_awcache;
assign s_awid                 = m_awid   ;
assign s_awlen                = m_awlen  ;
assign s_awlock               = m_awlock ;
assign s_awprot               = m_awprot ;
assign s_awsize               = m_awsize ;
assign s_awvalid              = m_awvalid && (mask_aw || !enable_delay);
assign s_bready               = m_bready  && (mask_b  || !enable_delay);
assign s_rready               = m_rready  && (mask_r  || !enable_delay);
assign s_wdata                = m_wdata;
assign s_wid                  = m_wid  ;
assign s_wlast                = m_wlast;
assign s_wstrb                = m_wstrb;
assign s_wvalid               = m_wvalid  && (mask_w  || !enable_delay);
// group m
assign m_arready              = s_arready && (mask_ar || !enable_delay);
assign m_awready              = s_awready && (mask_aw || !enable_delay);
assign m_bid                  = s_bid  ;
assign m_bresp                = s_bresp;
assign m_bvalid               = s_bvalid && (mask_b || !enable_delay);
assign m_rdata                = s_rdata;
assign m_rid                  = s_rid  ;
assign m_rlast                = s_rlast;
assign m_rresp                = s_rresp;
assign m_rvalid               = s_rvalid && (mask_r || !enable_delay);
assign m_wready               = s_wready && (mask_w || !enable_delay);
// group mask
assign mask_ar                = mask_ar_raw || mask_ar_disable;
assign mask_ar_ok             = s_arvalid && s_arready;
assign mask_ar_raw            = mask_random[0];
assign mask_aw                = mask_aw_raw || mask_aw_disable;
assign mask_aw_ok             = s_awvalid && s_awready;
assign mask_aw_raw            = mask_random[1];
assign mask_b                 = mask_b_raw;
assign mask_b_raw             = mask_random[2];
assign mask_r                 = mask_r_raw;
assign mask_r_raw             = mask_random[3];
assign mask_random_next[22:1] = mask_random[21:0];
assign mask_random_next[   0] = mask_random[22] ^ mask_random[17];
assign mask_reset             = !aresetn;
assign mask_w                 = mask_w_raw || mask_w_disable;
assign mask_w_ok              = s_wvalid && s_wready;
assign mask_w_raw             = mask_random[4];
always@(posedge aclk)
begin
    if(mask_reset)
    begin
        mask_ar_disable<=1'h0;
    end
    else
    if(mask_ar_ok)
    begin
        mask_ar_disable<=1'h0;
    end
    else
    if(s_arvalid)
    begin
        mask_ar_disable<=1'h1;
    end
end
always@(posedge aclk)
begin
    if(mask_reset)
    begin
        mask_aw_disable<=1'h0;
    end
    else
    if(mask_aw_ok)
    begin
        mask_aw_disable<=1'h0;
    end
    else
    if(s_awvalid)
    begin
        mask_aw_disable<=1'h1;
    end
end
always@(posedge aclk)
begin
    if(mask_reset)
    begin
        mask_no_delay<=mask_random[15:0] == 16'h00ff;
        //mask_random<=23'h5500ff;
        mask_random<=random_seed;
        mask_short_delay<=mask_random[7:0] == 8'hff;
    end
    else
    begin
        mask_random<=mask_random_next;
    end
end
always@(posedge aclk)
begin
    if(mask_reset)
    begin
        mask_w_disable<=1'h0;
    end
    else
    if(mask_w_ok)
    begin
        mask_w_disable<=1'h0;
    end
    else
    if(s_wvalid)
    begin
        mask_w_disable<=1'h1;
    end
end
endmodule // soc_axi_delay_rand
