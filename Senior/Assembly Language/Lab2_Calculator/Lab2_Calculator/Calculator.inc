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
		
        WinMain PROTO :DWORD, :DWORD, :DWORD,:DWORD		;����������
        Calculate PROTO :DWORD,:DWORD,:DWORD,:DWORD		;��Ϣ��������
        PackNum PROTO									;���ַ����ӳ���
        UnpackNum PROTO									;���ֲ������ӳ���
        BtnNum PROTO :DWORD								;���ְ�����Ϣ��������
        ShowNum PROTO									;��ʾ�����ӳ���
        ShowTextM PROTO									;��ʾ�洢��Ϣ�ӳ���
		Init PROTO										;��ʼ���������ӳ���
        GetResult PROTO									;�������ӳ���
		BtnOperator PROTO								;˫Ŀ�������Ϣ��������
		BtnEqual PROTO									;������Ϣ��������

        .data
		hInstance		dd	?					;��������
		hEdit			dd	?					;����ı�����
		hIcon			dd	?					;Icon���
		DialogName		db	"Calculator",0		;�Ի�������
		IconName		db	"Icon",0			;Icon����
		Output			db	"0.",0,30 dup(0)	;����ַ���
		IsStart			db	1					;�ж��Ƿ����㿪ʼ
		HasPoint		db	0					;�ж��Ƿ����С����
		HasEqual		db	0					;�ж��Ƿ���ڵȺ�
		Remember		dq	0.0					;��������
		Number			dq	0.0					;��¼��ʱ����
		Result			dq	0.0					;��¼���
		Operand			dq  0.0					;��¼������
		IsPacket		db	0					;���ַ���
		Operator		db	'.'					;��¼�����
		IsError			db	0					;��¼�Ƿ�����쳣
		Div0			db	"��������Ϊ�㡣",0
		FunctionError	db	"����������Ч��",0
		NumLittle		REAL8	1.0E-12
		Num10			REAL8	10.0			;ʵ��10
		Num100			REAL8	100.0			;ʵ��100