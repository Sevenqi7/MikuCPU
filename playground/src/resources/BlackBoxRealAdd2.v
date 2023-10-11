module BlackBoxRealAdd2(
    input  [63:0] in1,
    input  [63:0] in2,
    output [63:0] out
);
  assign out = in1 * in2;
endmodule

