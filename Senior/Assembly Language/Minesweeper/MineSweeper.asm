        TITLE MineSweeper
        .486
        .model flat,stdcall
        option casemap:none   

        include MineSweeper.inc

printf  PROTO C :ptr sbyte, :VARARG

.code
start:
        invoke GetModuleHandle,NULL			
        mov hInstance,eax
	    invoke WinMain,hInstance,0,0,SW_SHOWDEFAULT
		invoke ExitProcess,eax

RandInt	proc siz :dword                     ;用线性同余法生成随机数，（97a+7）mod siz
        .if     RandSeed == 0
	            invoke  GetTickCount
                mov     RandSeed,eax
        .else
                mov     eax,RandSeed
        .endif
	    mov     ebx,97
	    mul     ebx
	    add     eax,7
        mov     RandSeed,eax
	    mov     edx,0
	    mov     ebx,siz
	    div     ebx
        inc     edx
	    ret
RandInt endp

WinMain proc hInst :DWORD,hPrevInst :DWORD,CmdLine :DWORD,CmdShow:DWORD
        LOCAL wc:WNDCLASSEX						    ;窗口类
        LOCAL msg:MSG							    ;消息
		LOCAL hWnd:HWND							    ;对话框句柄
		
        mov     wc.cbSize,sizeof WNDCLASSEX			;WNDCLASSEX的大小
        mov     wc.style,CS_BYTEALIGNWINDOW or CS_BYTEALIGNWINDOW ;窗口风格 or CS_HREDRAW or CS_VREDRAW 
        mov     wc.lpfnWndProc,OFFSET MineSweeper	;窗口消息处理函数地址
        mov     wc.cbClsExtra,0						;在窗口类结构后的附加字节数，共享内存
        mov     wc.cbWndExtra,DLGWINDOWEXTRA		;在窗口实例后的附加字节数
        mov     eax,hInst
        mov     wc.hInstance,eax					;窗口所属程序句柄
        mov     wc.hbrBackground,COLOR_BTNFACE+1	;背景画刷句柄
        mov     wc.lpszMenuName,NULL				;菜单名称指针
        mov     wc.lpszClassName,OFFSET DialogName	;类名称指针
        invoke  LoadIcon,hInst,addr IconName		;加载Icon
        mov     wc.hIcon,eax						;图标句柄
        invoke  LoadCursor,NULL,IDC_ARROW
        mov     wc.hCursor,eax						;光标句柄
        mov     wc.hIconSm,0						;窗口小图标句柄
        
        invoke  RegisterClassEx,addr wc			    ;注册窗口类
        invoke  CreateDialogParam,hInst,addr DialogName,0,addr MineSweeper,0	;调用对话框窗口
        
        mov     hWnd,eax							;保存对话框句柄     
        invoke  ShowWindow,hWnd,CmdShow			    ;最后一个参数可设置为SW_SHOWNORMAL
        invoke  UpdateWindow,hWnd				    ;更新窗口
        invoke  PlaySound,offset MusicPath,NULL,SOUND_SYNC

StartLoop:										    ;消息循环
		invoke  GetMessage,addr msg,0,0,0		    ;获取消息
		cmp     eax,0
		je      ExitLoop
		invoke  TranslateMessage,addr msg
		invoke  DispatchMessage,addr msg
		jmp     StartLoop
ExitLoop:
		mov     eax,msg.wParam 
        ret
WinMain endp

Sweep proc hWin :DWORD,loc :DWORD
        LOCAL handle:DWORD
        LOCAL row:DWORD
        LOCAL col:DWORD
        LOCAL sum:DWORD

        LOCAL up:DWORD
        LOCAL down:DWORD
        LOCAL left:DWORD
        LOCAL right:DWORD
        LOCAL text:WORD
        
        invoke  GetDlgItem,hWin,loc
        mov     handle,eax
        
        mov     eax,loc
        .if     clicked[eax] == 1               ;the button has already been clicked
                ;invoke  AutoSweep,hWin,loc
                invoke  SendMessage,handle,BM_SETSTATE,TRUE,NULL
                ret
        .endif
        
        invoke  GetWindowText,handle,addr text,4
        ;invoke  printf,addr sdMSG
        ;invoke  printf,addr szMsg2,text

        .if     text == 52385                   ;the button is marked
                ret
        .endif

        invoke  SendMessage,handle,BM_SETSTATE,TRUE,NULL

        sub     remainSecurityNum,1
        .if     remainSecurityNum == 0
                mov     eax,MapRow
                mul     MapCol
                mov     BlockNum,eax
                sub     eax,MinesNum
                mov     remainSecurityNum,eax
                invoke  RtlZeroMemory,addr Map,sizeof Map
                invoke  RtlZeroMemory,addr clicked,sizeof clicked
                invoke  MineSweeper,hWin,WM_CLOSE,eax,0
                invoke  MessageBox, NULL, offset szWinText, offset szCaption, MB_OK  
                invoke  WinMain,hInstance,0,0,SW_SHOWDEFAULT           
                ;invoke  ExitProcess,eax                 
        .endif

        mov     eax,loc
        dec     eax
        mov     ebx,MapCol
        xor     edx,edx
        div     ebx
        mov     row,eax
        mov     col,edx             ;get current button coordinate

        mov     sum,0               ;initialize
        mov     left,0
        mov     right,0
        mov     up,0
        mov     down,0

UP:                                 ;check the block above
        mov     eax,row
        cmp     eax,0
        je      DOWN

        mov     up,1

        mov     ecx,loc
        sub     ecx,MapCol
        .if     Map[ecx] == 1
                inc     sum
        .endif
DOWN:                               ;check the block beneath
        mov     eax,row
        inc     eax
        cmp     eax,MapRow
        je      LEFT

        mov     down,1

        mov     ecx,loc
        add     ecx,MapCol
        .if     Map[ecx] == 1
                inc     sum
        .endif
LEFT:                               ;check the left block
        mov     eax,col
        cmp     eax,0
        je      RIGHT

        mov     left,1

        mov     ecx,loc
        dec     ecx
        .if     Map[ecx] == 1
                inc     sum
        .endif
RIGHT:                              ;check the right block
        mov     eax,col
        inc     eax
        cmp     eax,MapCol
        je      CORNER

        mov     right,1

        mov     ecx,loc
        inc     ecx
        .if     Map[ecx] == 1
                inc     sum
        .endif
CORNER:
        .if     (up == 1) && (left == 1)            ;check the up-left block
                mov     ecx,loc
                sub     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (up == 1) && (right == 1)           ;check the up-right block
                mov     ecx,loc
                sub     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (down == 1) && (left == 1)          ;check the down-left block
                mov     ecx,loc
                add     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (down == 1) && (right == 1)         ;check the down-right block
                mov     ecx,loc
                add     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        
        ;invoke  SendMessage,handle,BM_SETSTATE,TRUE,NULL
        mov     eax,loc
        mov     clicked[eax],1

        .if     sum > 0
                add     sum,48
                invoke  SetWindowText,handle,addr sum
                ret
        .endif
        
        ;the current block has no surrounding mines, sweep its neighbours
        .if     up == 1
                mov     ecx,loc
                sub     ecx,MapCol
                invoke  Sweep,hWin,ecx
                .if     left == 1
                        mov     ecx,loc
                        sub     ecx,MapCol
                        dec     ecx
                        invoke  Sweep,hWin,ecx
                .endif
                .if     right == 1
                        mov     ecx,loc
                        sub     ecx,MapCol
                        inc     ecx
                        invoke  Sweep,hWin,ecx
                .endif
        .endif

        .if     down == 1
                mov     ecx,loc
                add     ecx,MapCol
                invoke  Sweep,hWin,ecx
                .if     left == 1
                        mov     ecx,loc
                        add     ecx,MapCol
                        dec     ecx
                        invoke  Sweep,hWin,ecx
                .endif
                .if     right == 1
                        mov     ecx,loc
                        add     ecx,MapCol
                        inc     ecx
                        invoke  Sweep,hWin,ecx
                .endif
        .endif

        .if     left == 1
                mov     ecx,loc
                dec     ecx
                invoke  Sweep,hWin,ecx
        .endif

        .if     right == 1
                mov     ecx,loc
                inc     ecx
                invoke  Sweep,hWin,ecx
        .endif
   
        ret
Sweep endp

AutoSweep proc hWin:DWORD,loc :DWORD
        LOCAL handle:DWORD
        LOCAL hTemp:DWORD
        LOCAL row:DWORD
        LOCAL col:DWORD
        LOCAL sum:DWORD

        LOCAL up:DWORD
        LOCAL down:DWORD
        LOCAL left:DWORD
        LOCAL right:DWORD
        LOCAL text:DWORD

        invoke  GetDlgItem,hWin,loc
        mov     handle,eax

        mov     eax,loc
        dec     eax
        mov     ebx,MapCol
        xor     edx,edx
        div     ebx
        mov     row,eax
        mov     col,edx             ;get current button coordinate

        mov     sum,0               ;initialize
        mov     left,0
        mov     right,0
        mov     up,0
        mov     down,0

UP:                                 ;check the block above
        mov     eax,row
        cmp     eax,0
        je      DOWN

        mov     up,1

        mov     ecx,loc
        sub     ecx,MapCol
        invoke  GetDlgItem,hWin,ecx
        mov     hTemp,eax

        invoke  GetWindowText,hTemp,addr text,3
        ;movzx     
DOWN:                               ;check the block beneath
        mov     eax,row
        inc     eax
        cmp     eax,MapRow
        je      LEFT

        mov     down,1

        mov     ecx,loc
        add     ecx,MapCol
        .if     Map[ecx] == 1
                inc     sum
        .endif
LEFT:                               ;check the left block
        mov     eax,col
        cmp     eax,0
        je      RIGHT

        mov     left,1

        mov     ecx,loc
        dec     ecx
        .if     Map[ecx] == 1
                inc     sum
        .endif
RIGHT:                              ;check the right block
        mov     eax,col
        inc     eax
        cmp     eax,MapCol
        je      CORNER

        mov     right,1

        mov     ecx,loc
        inc     ecx
        .if     Map[ecx] == 1
                inc     sum
        .endif
CORNER:
        .if     (up == 1) && (left == 1)            ;check the up-left block
                mov     ecx,loc
                sub     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (up == 1) && (right == 1)           ;check the up-right block
                mov     ecx,loc
                sub     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (down == 1) && (left == 1)          ;check the down-left block
                mov     ecx,loc
                add     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        .if     (down == 1) && (right == 1)         ;check the down-right block
                mov     ecx,loc
                add     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        inc     sum
                .endif
        .endif
        
        ;invoke  SendMessage,handle,BM_SETSTATE,TRUE,NULL
        mov     eax,loc
        mov     clicked[eax],1

        .if     sum > 0
                add     sum,48
                invoke  SetWindowText,handle,addr sum
                ret
        .endif
      
      invoke  GetWindowText,handle,addr text,2
      
AutoSweep endp

DigNine proc hWin :DWORD,loc :DWORD
        LOCAL handle:DWORD
        LOCAL row:DWORD
        LOCAL col:DWORD

        LOCAL up:DWORD
        LOCAL down:DWORD
        LOCAL left:DWORD
        LOCAL right:DWORD
    
        invoke  GetDlgItem,hWin,loc
        mov     handle,eax
        
        mov     eax,loc
        dec     eax
        mov     ebx,MapCol
        xor     edx,edx
        div     ebx
        mov     row,eax
        mov     col,edx             ;get current button coordinate

        mov     left,0              ;initialize
        mov     right,0
        mov     up,0
        mov     down,0

        mov     eax,loc             ;check the clicked block
        .if     Map[eax] == 1
                invoke  SetWindowText,handle,addr button12
        .endif
UP:                                 ;check the block above
        mov     eax,row
        cmp     eax,0
        je      DOWN

        mov     up,1

        mov     ecx,loc
        sub     ecx,MapCol
        .if     Map[ecx] == 1
                invoke  GetDlgItem,hWin,ecx
                mov     handle,eax
                invoke  SetWindowText,handle,addr button12
        .endif
DOWN:                               ;check the block beneath
        mov     eax,row
        inc     eax
        cmp     eax,MapRow
        je      LEFT

        mov     down,1

        mov     ecx,loc
        add     ecx,MapCol
        .if     Map[ecx] == 1
                invoke  GetDlgItem,hWin,ecx
                mov     handle,eax
                invoke  SetWindowText,handle,addr button12
        .endif
LEFT:                               ;check the left block
        mov     eax,col
        cmp     eax,0
        je      RIGHT

        mov     left,1

        mov     ecx,loc
        dec     ecx
        .if     Map[ecx] == 1
                invoke  GetDlgItem,hWin,ecx
                mov     handle,eax
                invoke  SetWindowText,handle,addr button12
        .endif
RIGHT:                              ;check the right block
        mov     eax,col
        inc     eax
        cmp     eax,MapCol
        je      CORNER

        mov     right,1

        mov     ecx,loc
        inc     ecx
        .if     Map[ecx] == 1
                invoke  GetDlgItem,hWin,ecx
                mov     handle,eax
                invoke  SetWindowText,handle,addr button12
        .endif
CORNER:
        .if     (up == 1) && (left == 1)            ;check the up-left block
                mov     ecx,loc
                sub     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        invoke  GetDlgItem,hWin,ecx
                        mov     handle,eax
                        invoke  SetWindowText,handle,addr button12
                .endif
        .endif
        .if     (up == 1) && (right == 1)           ;check the up-right block
                mov     ecx,loc
                sub     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        invoke  GetDlgItem,hWin,ecx
                        mov     handle,eax
                        invoke  SetWindowText,handle,addr button12
                .endif
        .endif
        .if     (down == 1) && (left == 1)          ;check the down-left block
                mov     ecx,loc
                add     ecx,MapCol
                dec     ecx
                .if     Map[ecx] == 1
                        invoke  GetDlgItem,hWin,ecx
                        mov     handle,eax
                        invoke  SetWindowText,handle,addr button12
                .endif
        .endif
        .if     (down == 1) && (right == 1)         ;check the down-right block
                mov     ecx,loc
                add     ecx,MapCol
                inc     ecx
                .if     Map[ecx] == 1
                        invoke  GetDlgItem,hWin,ecx
                        mov     handle,eax
                        invoke  SetWindowText,handle,addr button12
                .endif
        .endif
   
        ret
DigNine endp

MineSweeper proc hWin:DWORD,uMsg:UINT,aParam:DWORD,bParam:DWORD
        LOCAL pt :POINT 
		LOCAL loc:dword
		LOCAL hWnd:HWND							                ;自定义地图对话框句柄
    
        .if     uMsg == WM_INITDIALOG
                mov     eax,MapRow
                mul     MapCol
                mov     BlockNum,eax
                sub     eax,MinesNum
                mov     remainSecurityNum,eax
                mov     eax,MinesNum
                mov     remainMinesNum,eax

                mov     eax,hWin
                mov     hWinMineSweeper,eax
	            invoke  CreateMap,hWin                          ;创建地图
                invoke  LayMines,hWin                           ;布雷
                invoke  LoadMenu,hInstance,addr MenuName		;加载菜单
				mov     hMenu,eax								;保存菜单句柄
				invoke  SetMenu,hWin,eax
                invoke  ChangeWindowSize,hWin
        .elseif uMsg == WM_CHAR		
 	            mov     eax,aParam

                .if     (eax >= ID_ADDA) && (eax <= ID_Implement)
                        invoke  MineSweeper,hWin,WM_COMMAND,eax,0
                .endif
        .elseif uMsg == WM_COMMAND
                mov     eax,aParam

                .if     eax == ID_RADAR	
                        invoke  printf,addr szMsg3,eax          ;道具雷达
                        invoke  RADAR,hWin
                .elseif eax == ID_BOMB
                        invoke  printf,addr szMsg3,eax          ;道具炸弹
                        mov     digNine,1
                .elseif (eax <= BlockNum) && (eax > 0)          ;button clicked
                        mov     tNum,eax

                        .if     clicked[eax] == 1               ;the button has already been clicked
                                invoke  GetDlgItem,hWin,eax
                                invoke  SendMessage,eax,BM_SETSTATE,TRUE,NULL
                                ret
                        .endif

                        .if     temMsg==161 ;插旗按钮点击无效
                                ret
                        .endif

                        mov     eax,tNum
                        .if     digNine == 1
                                mov     digNine,0
                                invoke  DigNine,hWin,eax
                        .elseif Map[eax] == 1
                                invoke  MessageBox, NULL, offset szText, offset szCaption, MB_OK
                                invoke  RtlZeroMemory,addr Map,sizeof Map;雷区归零
                                invoke  RtlZeroMemory,addr clicked,sizeof clicked;雷区归零
                                invoke  MineSweeper,hWin,WM_CLOSE,eax,0
                                invoke  WinMain,hInstance,0,0,SW_SHOWDEFAULT      
                                ret
                        .else
                                mov     eax,tNum
                                invoke  printf,addr szMsg3,eax
                                mov     eax,tNum
                                invoke  printf,addr szMsg4,Map[eax]
                                invoke  Sweep,hWin,tNum
                        .endif
                .elseif eax == ID_CUSTOM ;自定义地图
                        invoke  printf,addr szMsg3,eax
                        invoke  CreateDialogParam,hInstance,addr CustomDialogName,0,addr MapCustom,0	;调用对话框窗口
                        mov     hWnd,eax							;保存对话框句柄
                        invoke  ShowWindow,hWnd,SW_SHOWNORMAL			;最后一个参数可设置为SW_SHOWNORMAL
                        invoke  UpdateWindow,hWnd				;更新窗口
                .endif
        .elseif uMsg == WM_RBUTTONDOWN;右键点击方块后的处理函数
                mov     eax,aParam
                .if     Map[eax] == 1
                .elseif (eax <= BlockNum) && (eax > 0)
                        mov     loc,eax
                        invoke  printf,addr szMsg3,eax
                        mov     eax,loc
                        invoke  printf,addr szMsg5,Map[eax]
                        invoke  Sweep,loc,hWin
                .endif
        .elseif uMsg == WM_CLOSE
                invoke  EndDialog,hWin,NULL                        
                ;invoke  PostQuitMessage,0						;有主窗口程序时添加
        .else
                invoke  DefWindowProc,hWin,uMsg,aParam,bParam
        .endif
        xor     eax,eax				       
        ret
MineSweeper endp 

ChangeWindowSize proc hWin:DWORD
        mov     eax,20
        mul     MapRow
        add     eax,150
        mov     SIZE_H,eax

        mov     eax,20
        mul     MapCol
        add     eax,65
        mov     SIZE_W,eax
        invoke  SetWindowPos ,hWin,HWND_NOTOPMOST,700,200,SIZE_W,SIZE_H,  SWP_SHOWWINDOW
        ret
ChangeWindowSize endp

ButtonSubclass proc hWin:DWORD,uMsg:UINT,aParam:DWORD,bParam:DWORD
        mov eax,uMsg
        .if     uMsg == WM_RBUTTONDOWN              ;右键点击方块后的处理函数
                invoke  SendMessage, hWin, BM_GETSTATE,NULL,NULL
                .if     eax != 0
                        ret
                .endif
                invoke  GetWindowText,hWin,addr temMsg,3
                .if     temMsg == 161                 ;插旗按钮点击无效
                        invoke SetWindowText,hWin, addr buttonVoid;
                .else
                        invoke SetWindowText,hWin, addr button12;
                .endif
        .else
                invoke  GetWindowLong,hWin,GWL_USERDATA
                invoke  CallWindowProc,eax,hWin,uMsg,aParam,bParam
        .endif
        ret
ButtonSubclass endp

RADAR proc hWin :DWORD
        LOCAL x:dword
        LOCAL y:dword
        LOCAL tx:dword
        LOCAL ty:dword
        LOCAL mineID:dword
 
        mov     x,0
        mov     y,0
        mov     mineID,1

L1:
        mov     eax,mineID
        .if     Map[eax] == 1
                invoke  GetDlgItem,hWin,eax
                invoke  GetWindowText,eax,addr temMsg,3

                .if     temMsg != 161
                        mov     eax,mineID
                        invoke  GetDlgItem,hWin,eax
                        invoke  SetWindowText,eax,addr button_star
                .endif
        .endif

        inc     mineID
        mov     eax,mineID
        cmp     eax ,BlockNum
        jz      LS
        jmp     L1
LS:
        invoke  Sleep,1000
        mov     mineID,1
L2:
        mov     eax,mineID
        .if     Map[eax] == 1
                invoke  GetDlgItem,hWin,eax
                invoke  GetWindowText,eax,addr temMsg,3
                .if     temMsg!=161
                        mov eax,mineID
                        invoke  GetDlgItem,hWin,eax
                        invoke  SetWindowText,eax,addr button2
                .endif
        .endif

        inc     mineID
        mov     eax,mineID
        cmp     eax ,BlockNum
        jz      L3
        jmp     L2
L3:        
        ret
RADAR endp

MapCustom proc hWin :DWORD,uMsg :UINT,aParam :DWORD,bParam :DWORD
        .if     uMsg == WM_INITDIALOG
                invoke  wsprintf,addr temMsg,addr intMsg,MapRow;对话框中预显示当前行数、列数、雷数
                invoke  GetDlgItem,hWin,ID_CUS_EDIT1
                invoke  SendMessage,eax,WM_SETTEXT,0,addr temMsg

                invoke  wsprintf,addr temMsg,addr intMsg,MapCol
                invoke  GetDlgItem,hWin,ID_CUS_EDIT2
                invoke  SendMessage,eax,WM_SETTEXT,0,addr temMsg
            
                invoke  wsprintf,addr temMsg,addr intMsg,MinesNum
                invoke  GetDlgItem,hWin,ID_CUS_EDIT3
                invoke  SendMessage,eax,WM_SETTEXT,0,addr temMsg
        .elseif uMsg == WM_CHAR
                mov     eax,aParam
                .if     (eax >= ID_CUS_OK) && (eax <= ID_CUS_CANCEL)
                        invoke  MapCustom,hWin,WM_COMMAND,eax,0
                .endif
        .elseif uMsg == WM_COMMAND
                mov     eax,aParam
                .if     eax == ID_CUS_CANCEL	;取消键关闭窗口
                        invoke  MapCustom,hWin,WM_CLOSE,eax,0
                .elseif eax == ID_CUS_OK	;确定键改变地图
                        invoke  GetDlgItemText,hWin,ID_CUS_EDIT1,addr temMsg,10;将输入数据存储回三个全局变量
                        invoke  ustr2dw ,addr temMsg

                        mov     tNum,eax            ;对于输入的边界控制 边数0~15 雷数1~max
                        .if     tNum >= 25
                                mov     tNum,25
                        .elseif tNum <= 1
                                mov     tNum,1
                        .endif
                        mov     eax,tNum
                        mov     MapRow,eax

                        invoke  GetDlgItemText,hWin,ID_CUS_EDIT2,addr temMsg,10
                        invoke  ustr2dw ,addr temMsg

                        mov tNum,eax
                        .if     tNum >= 25
                                mov     tNum,25
                        .elseif  tNum <= 1
                                mov     tNum,1
                        .endif
                        mov     eax,tNum
                        mov     MapCol,eax

                        mul     MapRow
                        mov     BlockNum,eax

                        invoke  GetDlgItemText,hWin,ID_CUS_EDIT3,addr temMsg,10
                        invoke  ustr2dw ,addr temMsg

                        mov     tNum,eax
                        mov     ebx,BlockNum
                        .if     tNum >= ebx
                                mov     tNum,ebx
                        .elseif tNum <= 1
                                mov     tNum,1
                        .endif
                        mov     eax,tNum
                        mov     MinesNum,eax

                        invoke RtlZeroMemory,addr Map,sizeof Map                ;雷区归零
                        invoke RtlZeroMemory,addr clicked,sizeof clicked        ;雷区归零
                        invoke MapCustom,hWin,WM_CLOSE,eax,0
                        invoke MineSweeper,hWinMineSweeper,WM_CLOSE,eax,0
                        invoke WinMain,hInstance,0,0,SW_SHOWDEFAULT
                .endif

        .elseif uMsg == WM_CLOSE
                invoke  EndDialog,hWin,NULL                        
        .else
                invoke  DefWindowProc,hWin,uMsg,aParam,bParam
        .endif
  
        xor     eax,eax				       
        ret
MapCustom endp

LayMines proc hWin :DWORD;布雷
        LOCAL mNum:dword
        LOCAL rand:dword

        mov mNum,0
    
L1:
        ;调用随机数生成器
        mov     rand,-1
        .while  (rand==-1||Map[edx]==1)
                invoke  RandInt ,BlockNum
                mov     rand,edx     
        .endw  
        mov     Map[edx],1
        invoke  GetDlgItem,hWin,rand
        invoke  SetWindowText,eax,addr button2  ;开发阶段生成雷之后直接显示

        inc     mNum
        mov     eax,mNum
        cmp     MinesNum ,eax
        jz      L2                              ;布雷已达数量则跳出循环
        jmp     L1
L2:
        ret
LayMines endp

CreateMap proc hWin :DWORD
        LOCAL x:dword
        LOCAL y:dword
        LOCAL tx:dword
        LOCAL ty:dword
        LOCAL mineID:dword

        mov     x,0
        mov     y,0
        mov     mineID,1
        
L1:
        mov     ebx,20
        mov     eax,x
        mul     ebx
        mov     tx,eax
        mov     eax,y
        mul     ebx
        mov     ty,eax
        
        ;地图整体偏移
        add     tx,16
        add     ty,0
        mov     edx,mineID
        invoke  CreateWindowEx,NULL,offset button,offset button1,\
                                WS_CHILD or WS_VISIBLE,tx,ty,20,20,\ 
                                hWin,mineID,hInstance,NULL  ;该按钮的句柄是mineID

        invoke  GetDlgItem,hWin,mineID 
        mov     tNum,eax
        invoke  SetWindowLong,tNum,GWL_WNDPROC,addr ButtonSubclass
        invoke  SetWindowLong,tNum,GWL_USERDATA,eax

        inc     x
        inc     mineID
        mov     eax,x
        cmp     eax ,MapCol
        jz      L2
        jmp     L1
L2:
        mov     x,0
        inc     y
        mov     eax,y
        cmp     eax ,MapRow
        jz      L3
        jmp     L1
L3:
        ret
CreateMap endp
        ret
        end start