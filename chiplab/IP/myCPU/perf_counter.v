module perf_counter (
    input      clk              ,
    input      reset            ,

    input      dcache_miss      ,
    input      icache_miss      ,
    input      commit_inst      ,
    input      br_inst          ,
    input      mem_inst         ,
    input      br_pre           ,
    input      br_pre_error     
);

reg[31:0] dcache_miss_counter;
reg[31:0] icache_miss_counter;
reg[31:0] commit_inst_counter;
reg[31:0] br_inst_counter;
reg[31:0] mem_inst_counter;
reg[31:0] br_pre_counter;
reg[31:0] br_pre_error_counter;

always @(posedge clk) begin
    if (reset) begin
        dcache_miss_counter  <= 32'b0;
        icache_miss_counter  <= 32'b0;
        commit_inst_counter  <= 32'b0;
        br_inst_counter      <= 32'b0;
        mem_inst_counter     <= 32'b0;
        br_pre_counter       <= 32'b0;
        br_pre_error_counter <= 32'b0;
    end
    else begin
        if (dcache_miss) begin
            dcache_miss_counter <= dcache_miss_counter + 32'b1;
        end
        if (icache_miss) begin
            icache_miss_counter <= icache_miss_counter + 32'b1;
        end
        if (commit_inst) begin
            commit_inst_counter <= commit_inst_counter + 32'b1;
        end
        if (br_inst) begin
            br_inst_counter <= br_inst_counter + 32'b1;
        end
        if (mem_inst) begin
            mem_inst_counter <= mem_inst_counter + 32'b1;
        end
        if (br_pre) begin
            br_pre_counter <= br_pre_counter + 32'b1;
        end
        if (br_pre_error) begin
            br_pre_error_counter <= br_pre_error_counter + 32'b1;
        end
    end
end

endmodule
