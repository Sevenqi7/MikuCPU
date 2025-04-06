module CLINT (
    input  wire clock,            
    input  wire reset,        
    input  wire [15:0] addr,    
    input  wire [31:0] wdata,   
    input  wire wen,            
    input  wire ren,            
    output reg  [31:0] rdata,   
    output reg  mtimer_irq   
);

  reg [31:0] msip;
  reg [63:0] mtime;
  reg [63:0] mtimecmp;

  // 复位逻辑
  always @(posedge clock) begin
    if (reset) begin
      mtime <= 64'd0;
      mtimecmp <= 64'hFFFFFFFFFFFFFFFF;
    end else begin
      mtime <= mtime + 1;
    end
  end

  always @(posedge clock) begin
    mtimer_irq <= (mtime >= mtimecmp);
  end

  always @(*) begin
    case (addr & 16'hFFFC)
      32'h0:    rdata = msip;
      32'hBFF8: rdata = mtime[31:0];      
      32'hBFFC: rdata = mtime[63:32];     
      32'h4000: rdata = mtimecmp[31:0];   
      32'h4004: rdata = mtimecmp[63:32];  
      default:     rdata = 32'h0;
    endcase
  end

  always @(posedge clock) begin
    if (wen) begin
      case (addr & 16'hFFFC)
        32'h0: msip <= {31'b0, wdata[0]};
        32'hBFF8: mtime[31:0] <= wdata;
        32'hBFFC: mtime[63:32] <= wdata;
        32'h4000: mtimecmp[31:0]  <= wdata;  // 写低 32 位
        32'h4004: mtimecmp[63:32] <= wdata;  // 写高 32 位
      endcase
    end
  end

endmodule
