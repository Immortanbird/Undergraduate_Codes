		include windows.inc
        include user32.inc
        include kernel32.inc
        include comctl32.inc
        include masm32.inc
        include shell32.inc
        include winmm.inc
        include comdlg32.inc
        includelib user32.lib
        includelib comctl32.lib
        includelib masm32.lib
        includelib winmm.lib
        includelib comdlg32.lib
		includelib msvcrt.lib

		ICON		equ 105
		ID_EDIT		equ 1001

		ID_NUM0		equ 1002
		ID_NUM1		equ 1003
		ID_NUM2		equ 1004
		ID_NUM3		equ 1005
		ID_NUM4		equ 1006
		ID_NUM5		equ 1007
		ID_NUM6		equ 1008
		ID_NUM7		equ 1009
		ID_NUM8		equ 1010
		ID_NUM9		equ 1011

		ID_NEG      equ 1012
		ID_DOT      equ 1013
		
		ID_BACK		equ 1014
		ID_CE		equ 1015
		ID_C		equ	1016

		ID_EQU		equ	1017
		ID_ADD      equ 1018
		ID_SUB      equ 1019
		ID_MUL      equ 1020
		ID_DIV      equ 1021
		
        WinMain PROTO :DWORD, :DWORD, :DWORD,:DWORD		;窗口主程序
        Calculate PROTO :DWORD,:DWORD,:DWORD,:DWORD		;消息处理程序
        PackNum PROTO									;数字分组子程序
        UnpackNum PROTO									;数字不分组子程序
        BtnNum PROTO :DWORD								;数字按键消息处理程序
        ShowNum PROTO									;显示数据子程序
        ShowTextM PROTO									;显示存储信息子程序
		Init PROTO										;初始化计算器子程序
        GetResult PROTO									;计算结果子程序
		BtnOperator PROTO								;双目运算符消息处理程序
		BtnEqual PROTO									;等于消息处理程序

        .data
		hInstance		dd	?					;主程序句柄
		hEdit			dd	?					;输出文本框句柄
		hIcon			dd	?					;Icon句柄
		DialogName		db	"Calculator",0		;对话框名称
		IconName		db	"Icon",0			;Icon名称
		Output			db	"0.",0,30 dup(0)	;输出字符串
		IsStart			db	1					;判断是否运算开始
		HasPoint		db	0					;判断是否存在小数点
		HasEqual		db	0					;判断是否存在等号
		Remember		dq	0.0					;记忆数据
		Number			dq	0.0					;记录临时数据
		Result			dq	0.0					;记录结果
		Operand			dq  0.0					;记录操作数
		IsPacket		db	0					;数字分组
		Operator		db	'.'					;记录运算符
		IsError			db	0					;记录是否出现异常
		Div0			db	"除数不能为零。",0
		FunctionError	db	"函数输入无效。",0
		NumLittle		REAL8	1.0E-12
		Num10			REAL8	10.0			;实数10
		Num100			REAL8	100.0			;实数100