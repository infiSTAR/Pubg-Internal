EXTERN  DrawLineCall : QWORD;
EXTERN  DrawRectCall : QWORD;
EXTERN  DrawCall : QWORD;
EXTERN  g_SpoofBack: QWORD;
EXTERN  CurrentRsp  : QWORD
EXTERN  EngineDrawHook : QWORD


.CODE

HookFunc PROC
mov qword ptr [CurrentRsp],rsp
jmp EngineDrawHook 
HookFunc ENDP

Asm_CopyMemory PROC
push rdi
push rsi
push r8
sub rsp,18h
mov rdi,rcx
mov rsi,rdx
mov rcx,r8
rep movs byte ptr [rdi],byte ptr [rsi]
mov eax,1h
jmp Return1
xor eax,eax
Return1:
add rsp,18h
pop r8
pop rsi
pop rdi
ret
Asm_CopyMemory ENDP

Asm_ZeroMemory PROC
push rdi
push rsi
sub rsp,18h
mov rdi,rcx
xor rax,rax
mov rcx,rdx
rep stos byte ptr [rdi]
mov rax,1h
add rsp,18h
pop rsi
pop rdi
ret
Asm_ZeroMemory ENDP


_SpoofCall PROC
push rbp
push rsi
push rdi
push r14
push r15
sub rsp, 120H
mov rax, g_SpoofBack
push rax
mov r15,rcx
lea rdi, [rsp+28h]
lea rsi, [rsp+180h]
mov ecx,40h
rep movsb
mov rcx,r15
mov rax, [rsp+178h]
jmp rax
_SpoofCall endp


Fn_DrawLine PROC
var_B8          = dword ptr -0B8h
var_B4          = dword ptr -0B4h
var_B0          = dword ptr -0B0h
var_AC          = dword ptr -0ACh
var_A8          = qword ptr -0A8h
var_98          = byte ptr -98h
var_70          = xmmword ptr -70h
var_48          = dword ptr -48h
var_8           = byte ptr -8
arg_20          = dword ptr  28h
arg_28          = qword ptr  30h
arg_30          = dword ptr  38h

mov     rax, rsp
push    rbx
sub     rsp, 0D0h
mov     [rsp+0D8h+var_A8], 0FFFFFFFFFFFFFFFEh
movaps  xmmword ptr [rax-18h], xmm6
movaps  xmmword ptr [rax-28h], xmm7
movaps  xmmword ptr [rax-38h], xmm8
movaps  xmm6, xmm3
movaps  xmm7, xmm2
movaps  xmm8, xmm1
mov     rbx, rcx
movss   [rsp+0D8h+var_B8], xmm6
movss   xmm0, [rsp+0D8h+arg_20]
movss   [rsp+0D8h+var_B4], xmm0
movss   [rsp+0D8h+var_B0], xmm8
movss   [rsp+0D8h+var_AC], xmm7
lea     r8, [rsp+0D8h+var_B8]
lea     rdx, [rsp+0D8h+var_B0]
lea     rcx, [rsp+0D8h+var_98]
call qword ptr [DrawLineCall]
nop
mov     rax, [rsp+0D8h+arg_28]
movups  xmm0, xmmword ptr [rax]
movdqu  [rsp+0D8h+var_70], xmm0
movss   xmm1, [rsp+0D8h+arg_30]
movss   [rsp+0D8h+var_48], xmm1
lea     rdx, [rsp+0D8h+var_98]
mov		rcx,[rbx+288h]
call qword ptr [DrawCall]
nop
lea     r11, [rsp+0D8h+var_8]
movaps  xmm6, xmmword ptr [r11-10h]
movaps  xmm7, xmmword ptr [r11-20h]
movaps  xmm8, xmmword ptr [r11-30h]
mov     rsp, r11
pop     rbx
ret
Fn_DrawLine ENDP


Fn_DrawRect PROC
mov rax, rsp
push rdi
sub rsp, 0F0h
mov qword ptr [rsp+40h], 0FFFFFFFFFFFFFFFEh
mov qword ptr [rax+08h], rbx
movaps xmmword ptr [rax-18h], xmm6
movaps xmmword ptr [rax-28h],xmm7
movaps xmm6,xmm3
movaps xmm7,xmm2
mov rdi,rdx
mov rbx,rcx
movss xmm0,dword ptr [rsp+120h]
movss dword ptr [rsp+30h],xmm0
movss xmm1,dword ptr [rsp+128h]
movss dword ptr [rsp+34h],xmm1
movss dword ptr [rsp+38h],xmm7
movss dword ptr [rsp+3Ch],xmm6
mov qword ptr [rsp+20h],rdi
lea r9,qword ptr [rsp+30h]
lea rdx,qword ptr [rsp+38h]
lea rcx,qword ptr [rsp+50h]
call qword ptr [DrawRectCall]
mov dword ptr [rsp+64h],2h
lea rdx,qword ptr [rsp+50h]
mov rcx,[rbx+288h]
call qword ptr [DrawCall]
lea r11,qword ptr [rsp+0F0h]
mov rbx,qword ptr [r11+10h]
movaps xmm6,xmmword ptr [r11-10h]
movaps xmm7,xmmword ptr [r11-20h]
mov rsp,r11
pop rdi
ret
Fn_DrawRect ENDP

END