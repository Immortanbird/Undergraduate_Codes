		.386
		.model flat,stdcall
		option casemap:none

		include		windows.inc
		include		kernel32.inc
		includelib	kernel32.lib
		include		user32.inc
		includelib	user32.lib
		include		msvcrt.inc
		includelib	msvcrt.lib

printf	PROTO C :ptr sbyte, :VARARG	
scanf	PROTO C :ptr sbyte, :VARARG
strlen	PROTO C :ptr sbyte, :VARARG
sprintf PROTO C :ptr sbyte, :VARARG
strcmp	PROTO C :ptr sbyte, :VARARG
strcat	PROTO C :ptr sbyte, :VARARG

		.data                           
		hProg		dd		?
		hWind		dd		?
		hEdit1		HWND	?
		hEdit2		HWND	?
		file1_path	byte 256 dup(?)
		file2_path	byte 256 dup(?)
		differs		byte 2048 dup(0)
		differ_num	dd		?
		buffer1		byte 2048 dup(0)
		buffer2		byte 2048 dup(0)

		winClassName	db		'文件比较',0
		winCaptionName	db		'文件比较',0
		edit			byte	'edit', 0
		button			byte	'button', 0
		showbutton		byte	'确认', 0
		SameContent		db		'文件内容相同', 0
		DiffContent		db		'行数: %d', 0AH,0
		szBoxTitle		db		'比较结果', 0

		.code
ReadLine proc fp :HANDLE,buffer :ptr byte
		LOCAL len :dword
		LOCAL chr :byte

		mov		esi,buffer
		mov		edi,0

L1: 
		invoke	ReadFile,fp,addr chr,1,addr len,NULL
		cmp		len,0
		je		L2
		cmp		chr,10
		je		L2
		mov		al, chr
		mov		byte ptr [esi],al
		inc		esi
		inc		edi
		jmp		L1
L2:
		mov		byte ptr [esi],0
		mov		eax,edi
		ret
ReadLine endp

CompareFile proc fpath1:ptr byte, fpath2:ptr byte
		LOCAL fp1 :HANDLE
		LOCAL fp2 :HANDLE
		LOCAL lp1 :dword
		LOCAL lp2 :dword
		LOCAL index_line :dword
		LOCAL buffer_differ[1024] :byte

		invoke	CreateFile, fpath1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
		mov		fp1,eax
		invoke	CreateFile, fpath2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
		mov		fp2,eax
		mov		differ_num,0
		mov		index_line,0
		mov		esi,offset differs
		mov		byte ptr[esi],0
L0:
		inc		index_line
		invoke	ReadLine,fp1,offset buffer1
		mov		lp1,eax
		invoke	ReadLine,fp2,offset buffer2
		mov		lp2,eax
L1:
		cmp		lp1,0
		jne		L3
		cmp		lp2,0
		jne		L2
		jmp		ENDFUNC
L2:
		invoke	sprintf, addr buffer_differ, offset DiffContent, index_line
		invoke	strcat, offset differs, addr buffer_differ
		inc		differ_num
		jmp		L0
L3:
		cmp		lp2,0
		jne		L4
		invoke	sprintf, addr buffer_differ, offset DiffContent, index_line
		invoke	strcat, offset differs, addr buffer_differ
		inc		differ_num
		jmp		L0
L4:
		invoke	strcmp, offset buffer1, offset buffer2
		cmp		eax, 0
		je		L0
		invoke	sprintf, addr buffer_differ, offset DiffContent, index_line
		invoke	strcat, offset differs, addr buffer_differ
		inc		differ_num
		jmp		L0
ENDFUNC:
		ret 
CompareFile endp

WinProc proc uses ebx edi esi, hWnd, uMsg, wParam, lParam
		LOCAL structps: PAINTSTRUCT
		LOCAL hDc

		mov		eax,uMsg

		.if		eax == WM_PAINT
				invoke	BeginPaint,hWnd,addr structps
				mov		hDc, eax
				invoke	EndPaint,hWnd,addr structps
		.elseif eax == WM_CLOSE
				invoke	DestroyWindow,hWind
				invoke	PostQuitMessage,NULL
				ret
		.elseif eax == WM_CREATE
				invoke	CreateWindowEx, NULL, OFFSET button, OFFSET showbutton, WS_CHILD OR  WS_VISIBLE, 120, 100, 150, 25, hWnd, 15, hProg, NULL    
				invoke	CreateWindowEx, WS_EX_CLIENTEDGE, OFFSET edit, NULL, WS_CHILD OR  WS_VISIBLE OR WS_BORDER OR	ES_LEFT	OR ES_AUTOHSCROLL, 10, 10, 350, 35, hWnd, 1, hProg, NULL
				mov		hEdit1,eax
				invoke	CreateWindowEx, WS_EX_CLIENTEDGE, OFFSET edit, NULL, WS_CHILD OR  WS_VISIBLE	OR WS_BORDER OR	ES_LEFT	OR ES_AUTOHSCROLL, 10, 50, 350, 35, hWnd, 2, hProg,	NULL 
				mov		hEdit2,eax
		.elseif	eax == WM_COMMAND
				mov		eax,wParam
				.if		eax == 15
						invoke	GetWindowText,hEdit1,offset file1_path,512
						invoke	GetWindowText,hEdit2,offset file2_path,512
						invoke	CompareFile,offset file1_path,offset file2_path
						.if		differ_num == 0
								invoke	MessageBox, hWnd, offset SameContent, offset szBoxTitle, MB_OK + MB_ICONQUESTION
						.else
								invoke	MessageBox, hWnd, offset differs, offset szBoxTitle, MB_OK + MB_ICONQUESTION
						.endif
				.endif
		.else
				invoke	DefWindowProc,hWnd,uMsg,wParam,lParam
				ret
		.endif

		ret
WinProc endp

WinMain proc
		LOCAL structWndClass: WNDCLASSEX
		LOCAL msg: MSG

		invoke	GetModuleHandle, NULL
		mov		hProg,eax
		invoke	RtlZeroMemory, addr structWndClass, sizeof structWndClass
		invoke	LoadCursor, 0, IDC_ARROW
		mov		structWndClass.hCursor, eax
		mov		eax,hProg
		mov		structWndClass.hInstance, eax
		mov		structWndClass.cbSize, sizeof WNDCLASSEX
		mov		structWndClass.style,CS_HREDRAW or CS_VREDRAW
		mov		structWndClass.lpfnWndProc,offset WinProc
		mov		structWndClass.hbrBackground,COLOR_WINDOW + 1
		mov		structWndClass.lpszClassName,offset winClassName
		invoke	RegisterClassEx, addr structWndClass
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, offset winClassName, offset winCaptionName, WS_OVERLAPPEDWINDOW, 200, 200, 400, 200, NULL, NULL, hProg, NULL
		mov		hWind,eax
		invoke	ShowWindow,hWind,SW_SHOWNORMAL
		invoke	UpdateWindow,hWind
		
		.while	TRUE
				invoke GetMessage,addr msg,NULL,0,0
				invoke TranslateMessage,addr msg
				invoke DispatchMessage,addr msg
		.endw
		ret
WinMain endp

start:                          
        invoke	WinMain
		invoke	ExitProcess,NULL
		end start