;===================== Start Ԥ����˵�� Start =====================
;--------------------------- ͷ�ļ����� ---------------------------
		include windows.inc
        include user32.inc
        include kernel32.inc
        include comctl32.inc
        include masm32.inc
        include shell32.inc
        include winmm.inc
        include comdlg32.inc
;--------------------------- ��������� ---------------------------
        includelib user32.lib
        includelib comctl32.lib
        includelib masm32.lib
        includelib winmm.lib
        includelib comdlg32.lib
		includelib msvcrt.lib
;---------------------------- �������� ----------------------------

		ID_ADDA         equ 1001
		ID_ADDB         equ 1002
		ID_Implement    equ 1003
		
		ID_CUSTOM		equ 40003

		ID_CUS_EDIT1    equ 1003
		ID_CUS_EDIT2    equ 1004
		ID_CUS_EDIT3    equ 1005
		ID_CUS_OK       equ 1011
		ID_CUS_CANCEL   equ 1012
		ID_RADAR        equ 1013
		ID_BOMB         equ 1014

;---------------------------- �������� ----------------------------
	
		WinMain				PROTO :DWORD,:DWORD,:DWORD,:DWORD		;����������
        MineSweeper			PROTO :DWORD,:DWORD,:DWORD,:DWORD		;��Ϣ��������
		CreateMap			PROTO :DWORD							;��ͼ���ɳ���
		LayMines			PROTO :DWORD							;����
		RandInt				PROTO :DWORD							;���������
		MapCustom			PROTO :DWORD,:DWORD,:DWORD,:DWORD
		ButtonSubclass		PROTO :DWORD,:DWORD,:DWORD,:DWORD
		ChangeWindowSize	PROTO :DWORD
		RADAR				PROTO :DWORD	
		
;======================= End Ԥ����˵�� End =======================
;===================== Start ���ݶζ��� Start =====================

		.data
		intMsg				byte    "%d",0
		szMsg2				byte    "%s", 0ah, 0
		szMsg3				byte    "������%d�Ű�ť", 0dh, 0ah,0
		szMsg4				byte    "�ð�ťmapֵΪ%d", 0dh, 0ah,0
		szMsg5				byte    "%d", 0dh,0ah,0

		button				db 'button',0
		button1				db  ' ',0
		button_star			db  '*',0
		button2				db  ' ',0
		buttonVoid			db  ' ',0
		button12			db  '��',0

		temMsg				byte  100 dup(0)
		res					dword 1
		tNum				dword 100
		
		szCaption			db	'ɨ��', 0
		szText				db	'��ȵ��˵��ף���', 0
		szWinText			db	'��ϲ������ʤ������', 0

		hInstance			dd	?					;��������
		hWinMineSweeper		dd	?					;ɨ�׶Ի���hWin
		hMenu				dd	?					;�˵����
		hIcon				dd	?					;Icon���
		DialogName			db	"MINESWEEPER",0		;�Ի�������
		CustomDialogName	db	"CUSTOM",0			;�Զ����ͼ�����Ի�������

		MenuName			db	"Menu",0			;�˵�����
		IconName			db	"Icon",0			;Icon����
		
		Map					db 1024 dup(0)			;��������     0:���ף�1������
		clicked				db 1024 dup(0)			;��������

		MapRow				dd	10					;��ͼ����
		MapCol				dd	10					;��ͼ����
		BlockNum			dd  0					;����*����
		SIZE_W				dd	0					;��ͼ����
		SIZE_H				dd	0					;��ͼ�߶�

		MinesNum			dd  10					;������
		RandSeed			dd  0					;���������
		SOUND_SYNC			dd	20009h
		MusicPath			db	"music.wav",0

		digNine				dd		0
		
		remainSecurityNum	dd  0					;ʣ�లȫ������
		remainMinesNum		dd	0					;ʣ������

;======================= End ���ݶζ��� End =======================        