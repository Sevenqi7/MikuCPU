module simu_top(
    input                       aclk,
    input                       aresetn
);

    // import "DPI-C" context function void dpic_set_mtimer_irq(input int value);
    export "DPI-C" function dpic_set_mtimer_irq;
    reg mtimer_irq;
    function void dpic_set_mtimer_irq(input int value) ;
        mtimer_irq = (value > 0);
    endfunction

    wire [63: 0] pc      ;
    wire [ 3: 0] arid    ;
    wire [31: 0] araddr  ;
    wire [ 7: 0] arlen   ;
    wire [ 2: 0] arsize  ;
    wire [ 1: 0] arburst ;
    wire [ 1: 0] arlock  ;
    wire [ 3: 0] arcache ;
    wire [ 2: 0] arprot  ;
    wire         arvalid ;
    wire         arready ;

    wire [ 3: 0] rid     ;
    wire [63: 0] rdata   ;
    wire [ 1: 0] rresp   ;
    wire         rlast   ;
    wire         rvalid  ;
    wire         rready  ;

    wire [ 3: 0] awid   ;
    wire [31: 0] awaddr ;
    wire [ 7: 0] awlen  ;
    wire [ 2: 0] awsize ;
    wire [ 1: 0] awburst;
    wire [ 1: 0] awlock ;
    wire [ 3: 0] awcache;
    wire [ 2: 0] awprot ;
    wire         awvalid;
    wire         awready;

    wire [ 3: 0] wid    ;
    wire [63: 0] wdata  ;
    wire [ 7: 0] wstrb  ;
    wire         wlast  ;
    wire         wvalid ;
    wire         wready ;

    wire [ 3: 0] bid    ;
    wire [ 1: 0] bresp  ;
    wire         bvalid ;
    wire         bready ;


    npc_core core(
        .pc          (pc          ),   
        .aclk        (aclk        ),
        .aresetn     (aresetn     ), 
        .intrpt      ({mtimer_irq, 7'b0}),

        .arid        (arid        ),
        .araddr      (araddr      ),
        .arlen       (arlen       ),
        .arsize      (arsize      ),
        .arburst     (arburst     ),
        .arlock      (arlock      ),
        .arcache     (arcache     ),
        .arprot      (arprot      ),
        .arvalid     (arvalid     ),
        .arready     (arready     ),
        .rid         (rid         ),
        .rdata       (rdata       ),
        .rresp       (rresp       ),
        .rlast       (rlast       ),
        .rvalid      (rvalid      ),
        .rready      (rready      ),
        .awid        (awid        ),
        .awaddr      (awaddr      ),
        .awlen       (awlen       ),
        .awsize      (awsize      ),
        .awburst     (awburst     ),
        .awlock      (awlock      ),
        .awcache     (awcache     ),
        .awprot      (awprot      ),
        .awvalid     (awvalid     ),
        .awready     (awready     ),
        .wid         (wid         ),
        .wdata       (wdata       ),
        .wstrb       (wstrb       ),
        .wlast       (wlast       ),
        .wvalid      (wvalid      ),
        .wready      (wready      ),
        .bid         (bid         ),
        .bresp       (bresp       ),
        .bvalid      (bvalid      ),
        .bready      (bready      )
    );

    sim_sram sim_sram(
        .pc          (pc          ),
        .aclk        (aclk        ),
        .aresetn     (aresetn     ), 
        .arid        (arid        ),
        .araddr      (araddr      ),
        .arlen       (arlen       ),
        .arsize      (arsize      ),
        .arburst     (arburst     ),
        .arlock      (arlock      ),
        .arcache     (arcache     ),
        .arprot      (arprot      ),
        .arvalid     (arvalid     ),
        .arready     (arready     ),
        .rid         (rid         ),
        .rdata       (rdata       ),
        .rresp       (rresp       ),
        .rlast       (rlast       ),
        .rvalid      (rvalid      ),
        .rready      (rready      ),
        .awid        (awid        ),
        .awaddr      (awaddr      ),
        .awlen       (awlen       ),
        .awsize      (awsize      ),
        .awburst     (awburst     ),
        .awlock      (awlock      ),
        .awcache     (awcache     ),
        .awprot      (awprot      ),
        .awvalid     (awvalid     ),
        .awready     (awready     ),
        .wid         (wid         ),
        .wdata       (wdata       ),
        .wstrb       (wstrb       ),
        .wlast       (wlast       ),
        .wvalid      (wvalid      ),
        .wready      (wready      ),
        .bid         (bid         ),
        .bresp       (bresp       ),
        .bvalid      (bvalid      ),
        .bready      (bready      )
    );

endmodule