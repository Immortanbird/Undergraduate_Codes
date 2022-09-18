		.386
		.model flat,stdcall
		option casemap:none
        include Calculator.inc

		.code
WinMain proc hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
		LOCAL	wc:WNDCLASSEX						;������
        LOCAL	msg:MSG								;��Ϣ
		LOCAL	hWnd:HWND							;�Ի�����

		mov		wc.cbSize,sizeof WNDCLASSEX			                ;WNDCLASSEX�Ĵ�С
        mov		wc.style,CS_BYTEALIGNWINDOW or CS_BYTEALIGNWINDOW   ;���ڷ�� or CS_HREDRAW or CS_VREDRAW 
        mov		wc.lpfnWndProc,OFFSET Calculate		                ;������Ϣ��������ַ
        mov		wc.cbClsExtra,0						                ;�ڴ�����ṹ��ĸ����ֽ����������ڴ�
        mov		wc.cbWndExtra,DLGWINDOWEXTRA		                ;�ڴ���ʵ����ĸ����ֽ���
        mov		eax,hInst
        mov		wc.hInstance,eax					                ;��������������
        mov		wc.hbrBackground,COLOR_BTNFACE+1	                ;������ˢ���
        mov		wc.lpszMenuName,NULL				                ;�˵�����ָ��
        mov		wc.lpszClassName,OFFSET DialogName	                ;������ָ��
        invoke	LoadIcon,hInst,addr IconName		                
        mov		wc.hIcon,eax						                ;ͼ����
        invoke	LoadCursor,NULL,IDC_ARROW
        mov		wc.hCursor,eax						                ;�����
        mov		wc.hIconSm,0						                ;����Сͼ����
        
        invoke	RegisterClassEx,addr wc								;ע�ᴰ����
        invoke	CreateDialogParam,hInst,addr DialogName,0,addr Calculate,0	;�����Ի��򴰿�
        mov     hWnd,eax											;����Ի�����
        invoke	ShowWindow,hWnd,CmdShow
        invoke	UpdateWindow,hWnd									;���´���

		.while	TRUE												;��Ϣѭ��
				invoke	GetMessage,addr msg,0,0,0					;��ȡ��Ϣ
				.break  .if eax == 0
				invoke	TranslateMessage,addr msg					;ת��������Ϣ
				invoke	DispatchMessage,addr msg					;�ַ���Ϣ
		.endw
		mov		eax,msg.wParam 
        ret
WinMain endp

Calculate proc hWin:DWORD,uMsg:UINT,aParam:DWORD,bParam:DWORD
		.if uMsg == WM_INITDIALOG
   				invoke	GetDlgItem,hWin,ID_EDIT						;��ȡ����ı�����
				mov		hEdit,eax									;�����ı�����
				invoke	LoadIcon,hInstance,addr IconName			;����Icon
				mov		hIcon,eax									;����Icon���
				invoke	SendMessage,hWin,WM_SETICON,ICON_SMALL ,eax
				invoke	SendMessage,hEdit,WM_SETTEXT,0,addr Output	;��ʾ"0."
		.elseif uMsg == WM_CHAR										;��������
				mov eax,aParam
				sub eax,'0'
				add eax,ID_NUM0
				.if		(eax >= ID_NUM0) && (eax <= ID_NUM9)		;����
						invoke	Calculate,hWin,WM_COMMAND,eax,0
				.elseif eax == 961									;ID_BACK
						invoke	Calculate,hWin,WM_COMMAND,ID_BACK,0
				.elseif eax == 1014									;ID_EQU
						invoke	Calculate,hWin,WM_COMMAND,ID_EQU,0
				.elseif eax == 999									;ID_DOT
						invoke	Calculate,hWin,WM_COMMAND,ID_DOT,0
				.elseif eax == 996									;ID_ADD
						invoke	Calculate,hWin,WM_COMMAND,ID_ADD,0
				.elseif eax == 998									;ID_SUB
						invoke	Calculate,hWin,WM_COMMAND,ID_SUB,0
				.elseif	eax == 995									;ID_MUL
						invoke	Calculate,hWin,WM_COMMAND,ID_MUL,0
				.elseif eax == 1000									;ID_DIV
						invoke	Calculate,hWin,WM_COMMAND,ID_DIV,0
				.endif
		.elseif uMsg == WM_COMMAND
				mov		eax,aParam
				.if		eax == ID_CE							;���㰴ťCE
						lea		esi,Output
						mov		BYTE PTR[esi],'0'
						mov		BYTE PTR[esi+1],'.'
						mov		BYTE PTR[esi+2],0
						.if		IsError==1
								invoke	Init
						.endif
						invoke	SendMessage,hEdit,WM_SETTEXT,0,addr Output
				.elseif eax == ID_C								;��ʼ����ťC
						invoke	Calculate,hWin,WM_COMMAND,ID_CE,bParam
						invoke	Init
				.elseif IsError == 1
						ret
				.elseif eax == ID_BACK							;�˸�ťBackspace
						invoke	UnpackNum							
						.if		IsStart == 0
								lea		esi,Output
								.while	BYTE PTR[esi] != 0
										inc		esi
								.endw
								.if		BYTE PTR[esi-1]=='.'
										.if		HasPoint == 1
												mov		HasPoint,0
										.else
												.if		BYTE PTR[esi-3] == '-'
														lea		esi,Output
														mov		BYTE PTR[esi],'0'
														mov		BYTE PTR[esi+1],'.'
														mov		BYTE PTR[esi+2],0
												.else
														mov		BYTE PTR[esi-2],'.'
														mov		BYTE PTR[esi-1],0
												.endif
										.endif
								.else
										mov		BYTE PTR[esi-1],0
								.endif
								lea		esi,Output
								.if		BYTE PTR[esi] == '.'
										mov		BYTE PTR[esi],'0'
										mov		BYTE PTR[esi+1],'.'
										mov		BYTE PTR[esi+2],0
								.endif
								invoke	ShowNum
						.endif
				.elseif (eax >= ID_NUM0) && (eax <= ID_NUM9)	;���ְ�ť
						.if		HasEqual == 1
								invoke	Init
						.endif
						invoke	BtnNum,eax
				.elseif eax == ID_NEG							;�����Ű�ť
						invoke	UnpackNum							
						invoke	StrToFloat,addr Output, addr Number
						finit
						fldz
						fld		Number
						fsub
						fstp	Number
						invoke	FloatToStr2,Number,addr Output
						invoke	ShowNum
				.elseif eax == ID_DOT							;С���㰴ť
						mov		BYTE PTR HasPoint,1
						mov		BYTE PTR IsStart,0
				.elseif (eax >= ID_ADD) && (eax <= ID_DIV)		;˫Ŀ�������ť
						invoke	BtnOperator
				.elseif eax == ID_EQU							;���ڰ�ť
						invoke	BtnEqual
				.endif
		.elseif
				invoke DefWindowProc,hWin,uMsg,aParam,bParam
		.endif
        ret
Calculate endp
;=========================================================================
BtnNum proc USES eax,Num:DWORD
		lea		esi,Output
		mov		eax,Num
		sub		eax,954
		.if		IsStart == 1
				mov		[esi],eax
				inc		esi
				mov		BYTE PTR[esi],'.'
				inc		esi
				mov		BYTE PTR[esi],0
				mov		IsStart,0
		.else
				.while	BYTE PTR[esi] != '.'
						inc esi
				.endw
				.if		HasPoint == 1
						.while BYTE PTR[esi]!=0
							inc esi
						.endw
						mov [esi],ax
						inc esi
						mov BYTE PTR[esi],0
				.else
						.if BYTE PTR[Output]=='0'
							lea esi,Output
							mov [esi],eax
							mov BYTE PTR[esi+1],'.'
							mov BYTE PTR[esi+2],0
						.else
							mov [esi],eax
							inc esi
							mov BYTE PTR[esi],'.'
							inc esi
							mov BYTE PTR[esi],0
						.endif
				.endif
		.endif	
		invoke	ShowNum
		ret	
BtnNum endp
;=========================================================================
BtnOperator proc USES eax
		.if		HasEqual != 1
				invoke GetResult
		.endif
		.if		eax ==	ID_MUL
				mov		Operator,'*'
		.elseif eax == ID_DIV
				mov		Operator,'/'
		.elseif eax == ID_SUB
				mov		Operator,'-'
		.elseif eax == ID_ADD
				mov		Operator,'+'
		.endif
		mov HasEqual,0
		ret
BtnOperator endp
;=========================================================================
BtnEqual proc
		.if (IsStart==1) && (HasEqual==0)
			fstp	Number
			fst		Number
			fld		Number
		.endif
		invoke	GetResult
		mov		HasEqual,1
		ret
BtnEqual endp
;=========================================================================
GetResult proc USES eax
		invoke	UnpackNum
		finit
		.if (IsStart==1) && (HasEqual==0)
		.else
			.if HasEqual != 1
					invoke	StrToFloat,addr Output, addr Operand
			.endif
			fld		Result			
			fld		Operand
			.if	Operator == '.'
				fst		Result
				jmp		Show
			.elseif Operator=='+'
				fadd	ST(1),ST(0)
			.elseif Operator=='-'
				fsub	ST(1),ST(0)
			.elseif Operator=='*'
				fmul	ST(1),ST(0)
			.elseif Operator=='/'
				fldz
				fcomi	ST(0),ST(1)
				jnz		NotZero
				mov		IsError,1
				invoke	SendMessage,hEdit,WM_SETTEXT,0,addr Div0
				ret
NotZero:		fstp	Operand		
				fdiv	ST(1),ST(0)
			.endif
			fstp	Operand
			fst		Result
Show:		mov		IsStart,1
			mov		HasPoint,0
			invoke	FloatToStr2,Result,addr Output
			invoke	ShowNum
		.endif
		ret
GetResult endp
;=========================================================================
PackNum proc USES eax ebx ecx edx
		lea		esi,Output
		mov		eax,0
		.while	BYTE PTR[esi] != '.'
				inc eax
				inc esi
		.endw
		.while  BYTE PTR[esi] != 0
				inc esi
		.endw
		dec		eax
		mov		edx,0
		mov		ecx,3
		div		ecx
		.while	BYTE PTR[esi] != '.'
				mov bx,[esi]
				mov [esi+eax],bx
				dec esi
		.endw
		mov		bx,[esi]
		mov		[esi+eax],bx
		dec		esi
		mov		ecx,0
		.while	eax != 0
				.if	ecx < 3
					mov		bx,[esi]
					mov		[esi+eax],bx
					inc		ecx
				.else
					mov		BYTE PTR[esi+eax],','
					dec		eax
					mov		ecx,1
				.endif
				dec		esi
		.endw
		lea		esi,Output
		.while	BYTE PTR[esi] != 0
				mov bx,[esi]
				inc esi
		.endw
		ret
PackNum endp
;=========================================================================
UnpackNum proc USES ecx
		lea		esi,Output
		mov		ecx,0
		.while	BYTE PTR[esi+ecx] != 0
				.if		BYTE PTR[esi] == ","
						inc ecx
				.endif
				mov		bx,[esi+ecx]
				mov		[esi],bx
				inc		esi
		.endw
		;invoke SendMessage,hEdit,WM_SETTEXT,0,addr Output
		ret
UnpackNum endp
;=========================================================================
ShowNum proc
		invoke	UnpackNum
		lea		esi,Output
		lea		edi,Output
		.while	BYTE PTR[esi] != 0
				inc		esi
		.endw
		.while	(BYTE PTR[edi] != '.') && (edi < esi)
				inc		edi
		.endw
		.if		esi == edi
				mov		BYTE PTR[esi],'.'
				mov		BYTE PTR[esi+1],0
		.endif
		.if		IsPacket == 1
				invoke	PackNum
		.endif
		invoke	SendMessage,hEdit,WM_SETTEXT,0,addr Output
		ret
ShowNum endp
;=========================================================================
Init proc
		mov		IsStart,1			;��ʼ��
		mov		HasPoint,0			;���С����
		mov		HasEqual,0
		fldz
		fst		Number				;������
		fst		Operand
		mov		Operator,'.'		;��������
		mov		IsError,0
		finit						;��ʼ��FPU
		ret 
Init endp
;==========================================================================
start:
		invoke	GetModuleHandle,NULL
		mov		hInstance,eax
		invoke	WinMain,hInstance,0,0,SW_SHOWDEFAULT
		invoke	ExitProcess,eax
		end		start