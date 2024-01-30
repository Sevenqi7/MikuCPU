# 接口一览表

IDU.scala

| signal name | description                                        | type                      |
| ----------- | -------------------------------------------------- | ------------------------- |
| ifu_s1      | 前端取出的指令和对应的PC                           | ValidIO(new PCInstBundle) |
| pred_check  | 分支预测正确性检查                                 | BranchPredictorUpdate     |
| exception   | 异常发生（现在还没做）                             | Bool                      |
| to_issue    | issue_buffer的基本单位。目前包含pc，指令，译码信息 | IssueEntry                |



Scoreboard.scala

| input signal or data    | description                                                  | width |
| ----------------------- | ------------------------------------------------------------ | ----- |
| sb_flush                | 清空记分牌                                                   | Bool  |
| flush_unissued_instr    | 清空未发射的指令                                             | Bool  |
| sb_new_inst | 计数板被传入了一个新的未被分配的指令 | Bool  |
| sb_way                  | 该条指令要发射的分支<br />val alu :: load_store :: branch :: mul_div :: Nil = Enum(4) | 4     |
| sb_rd                   | destination寄存器编号                                        | 5     |
| sb_rj                   | j号通用寄存器编号                                            | 5     |
| sb_rk                   | k号通用寄存器编号                                            | 5     |
| sb_rd_en                | 该指令是否启用destination寄存器                              | Bool  |
| sb_rj_en                | 该指令是否启用j号寄存器                                      | Bool  |
| sb_rk_en                | 该指令是否启用k号寄存器                                      | Bool  |
| sb_inst_time            | 刚发射出去的指令所需要的时钟周期数（待定）                       | 6     |
| sb_commit_en            | 是否提交指令                                     | Bool  |
| sb_commit_way           | 当前提交的指令所在的支路                                     | 4     |
| sb_commit_rd | 当前提交指令的目标寄存器，如果没有则写0 | 5 |

| output signal or data | description                              | width |
| --------------------- | ---------------------------------------- | ----- |
| sb_issue_en           | 该指令是否发射                           | Bool  |
| sb_full               | 计分板存储空位已满，阻塞新decode好的指令 | Bool  |

