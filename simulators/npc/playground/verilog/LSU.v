// import "DPI-C" function void dci_pmem_write(input longint waddr, input longint wdata, input byte wmask);
// import "DPI-C" function void dci_pmem_read(input longint raddr, output longint rdata, input byte rmask);

module LSU(input [63:0] pc, input [63:0] addr, input [4:0] LsuType, input WriteEn, input ReadEn, input [63:0]WriteData, output [63:0] ReadData);

    wire [7:0] mask;
    wire [63:0] lw_result;
    wire [63:0] lh_result;
    wire [63:0] lb_result;
    reg [63:0] data_r;

    wire lw_flag = LsuType[0] && ((mask ^ 8'h0F) == 8'b0);
    wire lh_flag = LsuType[0] && ((mask ^ 8'h03) == 8'b0);
    wire lb_flag = LsuType[0] && ((mask ^ 8'h01) == 8'b0);
    assign mask = ~(8'hFF << LsuType[4:1]);
    assign lw_result = {{32{data_r[31]}}, data_r[31:0]};
    assign lh_result = {{48{data_r[15]}}, data_r[15:0]};
    assign lb_result = {{56{data_r[7]}}, data_r[7:0]};
    assign ReadData = lw_flag     ? lw_result :
                      lh_flag     ? lh_result :
                      lb_flag     ? lb_result : data_r;

        always@(*) begin
            if(WriteEn) begin
                dci_pmem_write(addr, WriteData, mask);
                data_r = 64'h0;
            end
            else if(ReadEn)begin
                dci_pmem_read(addr, data_r, mask);
            end
            else
                data_r = 64'b0;
        end
endmodule