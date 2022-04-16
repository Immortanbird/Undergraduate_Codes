`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/05/13 13:53:56
// Design Name: 
// Module Name: CLC
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module CLC(input[1:3] X, output[1:6] F);
//���±���С�����ʾ�������ɵ�λ����λ

(* dont_touch = "true" *)
wire X1_n, X2_n, X3_n;
//X1_n,X2_n,X3_n�ֱ�ΪX[1],X[2],X[3]ȡ��
wire X1_nor_X2, X1_nor_X3, X1_nor_X2_n, X2_n_nor_X3, X1_n_nor_X2_n;
//�ֱ��ʾ������м��ź�

not
    (X1_n, X[1]),
    (X2_n, X[2]),
    (X3_n, X[3]);
    
nor 
    (X1_nor_X2, X[1], X[2]),
    (X1_nor_X3, X[1], X[3]),
    (X1_nor_X2_n, X[1], X2_n),
    (X2_n_nor_X3, X2_n, X[3]),
    (X1_n_nor_X2_n, X1_n, X2_n);

nor
    (F[1], X1_n, X2_n),
    (F[2], X1_n, X1_nor_X2, X1_nor_X3, X1_nor_X2_n, X2_n_nor_X3),
    (F[3], X1_nor_X2, X1_n_nor_X2_n, X3_n),
    (F[4], X2_n, X[3]);

not
    (F[5], 1),
    (F[6], X3_n);

endmodule