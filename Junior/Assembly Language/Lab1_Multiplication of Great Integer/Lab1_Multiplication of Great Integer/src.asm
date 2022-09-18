		.386
		.model flat, stdcall
		option casemap:none

		includelib msvcrt.lib

printf	PROTO C :ptr sbyte, :VARARG	
scanf	PROTO C :ptr sbyte, :VARARG
strlen	PROTO C :ptr sbyte, :VARARG

		.data
		format		byte "%s",0
		input_str1	byte 200 dup(0)
		input_str2	byte 200 dup(0)
		output_str	byte 200 dup(0)
		input_num1	dword 200 dup(0)
		input_num2	dword 200 dup(0)
		output_num	dword 200 dup(0)

		input_len1	dword 0
		input_len2	dword 0
		output_len	dword 0

		radix		dword 10

		.code
stoi proc stdcall str_in :ptr byte, num_out :ptr dword, len :dword
		mov		ecx,len
		mov		esi,str_in

@@:
		movzx	eax,byte ptr [esi]
		sub		eax,30h
		push	eax
		inc		esi
		loop	@B
  
		mov		ecx,len
		mov		esi,num_out
@@:
		pop		eax
		mov		dword ptr [esi],eax
		add		esi,4
		loop	@B

		ret
stoi endp

itos proc stdcall str_out :ptr byte, num_in :ptr dword, len :dword
		mov		ecx,len
		mov		esi,num_in
@@:
		mov		eax,dword ptr [esi]
		add		esi,4
		push	eax
		loop	@B

		mov		ecx,len
		mov		esi,str_out
@@:
		pop		eax
		add		eax,30h
		mov		byte ptr [esi],al
		inc		esi
		loop	@B

		ret
itos endp

Multiply proc far C 
		mov		ecx,input_len1
		xor		edi,edi
L1:
		xor		esi,esi

L2:
		mov		eax,dword ptr input_num1[edi*4]
		mul		input_num2[esi*4]

		mov		ebx,esi
		add		ebx,edi
		add		eax,output_num[ebx*4]

		mov		ebx,10
		div		ebx

		mov		ebx,esi
		add		ebx,edi

		mov		output_num[ebx*4],edx
		add		output_num[ebx*4+4],eax

		inc		esi
		mov		ebx,input_len2
		cmp		esi,ebx
		jb		L2

		inc		edi
		loop	L1

		mov		eax,input_len1
		add		eax,input_len2

		.if		output_num[eax*4-4] == 0
				sub		eax,1
				.if		output_num[0] == 0
						mov		eax,1
				.endif
		.endif

		mov		output_len,eax
		ret
Multiply endp

.code
main proc
		invoke	scanf,offset format,offset input_str1
		invoke	strlen,offset input_str1
		mov		input_len1,eax
		invoke	stoi,offset input_str1,offset input_num1,eax

		invoke	scanf,offset format,offset input_str2
		invoke	strlen,offset input_str2
		mov		input_len2,eax
		invoke	stoi,offset input_str2,offset input_num2,eax

		invoke	Multiply
		mov		eax,output_len
		invoke	itos,offset output_str,offset output_num,eax

		invoke	printf,offset format,offset output_str

		ret
main endp
end main