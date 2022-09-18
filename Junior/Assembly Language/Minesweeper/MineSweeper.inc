;===================== Start 预定义说明 Start =====================
;--------------------------- 头文件声明 ---------------------------
		include windows.inc
        include user32.inc
        include kernel32.inc
        include comctl32.inc
        include masm32.inc
        include shell32.inc
        include winmm.inc
        include comdlg32.inc
;--------------------------- 引入库声明 ---------------------------
        includelib user32.lib
        includelib comctl32.lib
        includelib masm32.lib
        includelib winmm.lib
        includelib comdlg32.lib
		includelib msvcrt.lib
;---------------------------- 常量声明 ----------------------------

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

;---------------------------- 函数声明 ----------------------------
	
		WinMain				PROTO :DWORD,:DWORD,:DWORD,:DWORD		;窗口主程序
        MineSweeper			PROTO :DWORD,:DWORD,:DWORD,:DWORD		;消息处理程序
		CreateMap			PROTO :DWORD							;地图生成程序
		LayMines			PROTO :DWORD							;布雷
		RandInt				PROTO :DWORD							;生成随机数
		MapCustom			PROTO :DWORD,:DWORD,:DWORD,:DWORD
		ButtonSubclass		PROTO :DWORD,:DWORD,:DWORD,:DWORD
		ChangeWindowSize	PROTO :DWORD
		RADAR				PROTO :DWORD	
		
;======================= End 预定义说明 End =======================
;===================== Start 数据段定义 Start =====================

		.data
		intMsg				byte    "%d",0
		szMsg2				byte    "%s", 0ah, 0
		szMsg3				byte    "按下了%d号按钮", 0dh, 0ah,0
		szMsg4				byte    "该按钮map值为%d", 0dh, 0ah,0
		szMsg5				byte    "%d", 0dh,0ah,0

		button				db 'button',0
		button1				db  ' ',0
		button_star			db  '*',0
		button2				db  ' ',0
		buttonVoid			db  ' ',0
		button12			db  '√',0

		temMsg				byte  100 dup(0)
		res					dword 1
		tNum				dword 100
		
		szCaption			db	'扫雷', 0
		szText				db	'你踩到了地雷！！', 0
		szWinText			db	'恭喜你获得了胜利！！', 0

		hInstance			dd	?					;主程序句柄
		hWinMineSweeper		dd	?					;扫雷对话框hWin
		hMenu				dd	?					;菜单句柄
		hIcon				dd	?					;Icon句柄
		DialogName			db	"MINESWEEPER",0		;对话框名称
		CustomDialogName	db	"CUSTOM",0			;自定义地图呼出对话框名称

		MenuName			db	"Menu",0			;菜单名称
		IconName			db	"Icon",0			;Icon名称
		
		Map					db 1024 dup(0)			;地雷数组     0:无雷，1：有雷
		clicked				db 1024 dup(0)			;地雷数组

		MapRow				dd	10					;地图行数
		MapCol				dd	10					;地图列数
		BlockNum			dd  0					;行数*列数
		SIZE_W				dd	0					;地图宽度
		SIZE_H				dd	0					;地图高度

		MinesNum			dd  10					;地雷数
		RandSeed			dd  0					;随机数种子
		SOUND_SYNC			dd	20009h
		MusicPath			db	"music.wav",0

		digNine				dd		0
		
		remainSecurityNum	dd  0					;剩余安全方块数
		remainMinesNum		dd	0					;剩余雷数

;======================= End 数据段定义 End =======================        