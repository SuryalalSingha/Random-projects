; *************************** snap.asm ***************************
;
section .data
; error messages will be saved here
syntax_error_printf db 'Syntax Error: Found Error In printf', 0, 0Ah ; syntax error msg
dot db '.' ; for the divide fn
section .bss
; buffers for input will be preserved here
smlbuff: resb 1024
bigbuff: resb 5120
section .text 
    global exit
    global str_len
    global str_print
    global str_println
    global int_print
    global int_println
    global clear_all
    global str_input
    global sp_input
    global big_str_input
    global print_lf
    global str_to_int
    global divide 
    global printf
    ;**************** code starts ****************;
        exit:
            ; 
            ; for exiting from the program 
            ; without making any segmentation fault 
            ; 
            mov ebx, 0
            mov eax, 1
            int 0x80 
            ret
            ;
            ; end of function 
            ;
            
        str_len:
            ;
            ; for calculating the size of string 
            ; inside a text section 
            ; for helping me while printing 
            ;
            push ebp 
            mov ebp, esp
            push ebx
            mov eax, [ebp+8]
            mov ebx, eax
            .next_char:
                cmp byte [eax], 0
                jz .endlop
                inc eax
                jmp .next_char
            .endlop:
                sub eax, ebx
                pop ebx
                pop ebp
            ret 4
            ; end of function 
            ;
            
        str_print:
            ;
            ; for printing the raw string that 
            ; prints without '\n'
            ;
            push ebp
            mov ebp, esp 
            push edx
            push ecx
            push ebx
            push eax ; saving the last value of eax
            mov eax, [ebp+8] ; moving the parameter (str ptr)
            push eax ; for saving the str, coz str_len will erase the value in stack and return value in eax so the value in eax also be erased 
            push eax ; for passing argument in str_len
            call str_len ; here eax already 4 added with esp so eax erased 
            mov edx, eax ; moving len for printing. at this time the eax has the returned value (the length of str)
            pop eax ; now getting the str back from stack
            mov ecx, eax ; moving the str ptr
            mov ebx, 1 
            mov eax, 4 
            int 80h ; or 0X80
            pop eax
            pop ebx
            pop edx 
            pop ecx
            pop ebp
            ret 4 ; erase the parameter from stack (adding 4 to esp)
            ; end of function 
            ;
            
        str_println:
            ; the complete printing function 
            ; that can string with '\n'
            ; 
            push ebp 
            mov ebp, esp 
            push eax ; saving the last value of eax (2)
            mov eax, [ebp+8]
            push eax ; for saving the str ptr
            call str_print ; it'll clear the stack no need to pop eax
            xor eax, eax ; clear the whole eax
            mov eax, 0Ah ; mov the newline to eax
            push eax ; move the value in stack (1)
            mov eax, esp ; get the ptr of the value using esp
            push eax ; pushing the eax as parameter to print 
            call str_print ; it'll clear the stack no need to pop eax
            pop eax ; (1)
            pop eax ; (2)
            pop ebp
            ret 4
            ; end of function 
            ;
            ;
        int_print:
            ;
            push ebp 
            mov ebp, esp
            push eax
            push ecx
            push edx
            push esi
            mov eax, [ebp+8]
            mov ecx, 0
            ;
            .dividloop:
                inc ecx
                mov esi, 10
                idiv esi
                add edx, 48
                push edx
                cmp eax, 0
                jnz .dividloop
                ;
            .printloop:
                dec ecx
                mov eax, esp
                call str_print
                pop eax
                xor eax, eax
                cmp ecx, 0
                jnz .printloop
            pop esi
            pop edx 
            pop ecx
            pop eax
            pop ebp
            ret 4
            ;end of function 
            ;
        int_println:
            ; print with '\n'
            push ebp
            mov ebp, esp
            mov eax, [ebp+8]
            push eax
            call int_print
            xor eax, eax 
            mov eax, 0Ah
            push eax
            mov eax, esp
            push eax
            call str_print
            pop eax
            pop eax
            pop ebp 
            ret 4
            ;end of function 
            ;
        clear_all:
            ;
            ; for fun but can be useful 
            ;
            xor eax, eax
            xor ebx, ebx
            xor ecx, ecx
            xor edx, edx
            xor edi, edi
            xor esi, esi
            ret
            ;end of function 
        str_input:
            ;
            push edx 
            push ecx 
            push ebx 
            mov eax, 3
            mov ebx, 0
            mov ecx, smlbuff 
            mov edx, 1024
            int 80h 
            mov eax, smlbuff 
            pop ebx
            pop ecx 
            pop edx 
            ret
            ; end of function (EOF haha)
        sp_input: ; special input 
            ;
            push ebp
            mov ebp, esp
            push edx
            push ecx
            push ebx
            push eax
            mov eax, 3
            mov ebx, 0
            mov ecx, [ebp+12] ; the buffer pointer. push it first 
            mov edx, [ebp+8] ; the length pointer. push it second 
            int 80h
            pop eax
            pop ebx
            pop ecx
            pop edx
            pop ebp
            ret 8
        big_str_input:
            ;
            push edx 
            push ecx 
            push ebx 
            mov eax, 3
            mov ebx, 0
            mov ecx, bigbuff 
            mov edx, 5120
            int 80h 
            mov eax, bigbuff 
            pop ebx
            pop ecx 
            pop edx 
            ret
            ;
            ;
        print_lf: ; printing linefeed or making a new line
            ; it's a function like: void print_lf(void) [no parameter]
            ;
            pusha
            mov eax, 0Ah
            push eax
            mov eax, esp
            push eax
            call str_print
            pop eax
            popa
            ; 
            ;
        str_to_int: ; atoi
            ;
            push ebp 
            mov ebp, esp 
            push ebx
            push ecx
            push edx
            push esi
            ;
            mov eax, [ebp+8]
            push eax
            call str_len ; eax=len
            dec eax ; minus one for avoiding null Terminator
            imul eax, 4
            mov ebx, eax ; ebx = len
            mov eax, [ebp+8]
            
            mov ecx, 1
            .stackLoop:
                push [eax+ebx]
                inc ecx
                sub ebx, 4
                cmp ebx, 0
                jz .atoinextstep 
                jnz .stackLoop 
            .atoinextstep:
            call _initesi_
            .conLoop:
                pop eax
                sub eax, '0'
                mul eax, esi
                div esi, 10
                add edx, eax
                cmp esi, 0
                jnz .conLoop
                jz endofatoi
            endofatoi:
                mov eax, edx
                ; 
                pop esi
                pop edx
                pop ecx
                pop ebx
                pop ebp
            ret 4
        _initesi_: ; used for this module only 
            push eax
            xor eax, eax
            mov eax, 1
            strt:
                mul eax, 10
                loop strt
            mov esi, eax
            push eax
            ret
            ;
        divide: ; suppose 15 ÷ 2 (which is 7.5)
            push ebp
            mov ebp, esp 
            push esi
            push edx
            push eax
            call clear_all ; (clear all registers)
            mov eax, [ebp+12] ; 15
            mov esi, [ebp+8] ; 2
            idiv esi ; eax = 7, edx=1
            push eax ; for calling the print function 
            call str_print ; stack cleared 
            mov eax, edx ; moving the remainder for multiplication and division 
            imul eax, 1000
            idiv eax, esi
            push eax ; pushing for function number 2
            mov edx, dot ; pushing the dot for printing 
            push edx
            call str_print ; stack erased edx so now eax is in the esp
            call str_print ; function number 2
            pop eax
            pop edx
            pop esi
            pop ebp
            ret 8
            ; 
        printf:       ; mimicking the printf from stdio.h of C lang
            ; eax cannot be recovered 
            ; this function is defferent than others in this file
            ;
            push ebp
            mov ebp, esp
            push esi
            push edx
            push ecx
            push ebx
            call clear_all
            mov eax, [ebp+8]
            .srcfirst:
                cmp byte [eax], 0
                jz .endsrc
                cmp [eax], ' ' ; the ASCII space character. maybe 32
                jz .skipspace
                cmp [eax], '%'
                jz .srcletter
                jnz .errorexitprintf
                .skipspace:
                    inc eax
                    jmp .srcfirst 
                .srcletter:
                    inc eax
                    inc ecx
                    cmp [eax], 'd'
                    jz .printdword
                    jnz .errorexitprintf
                    cmp [eax], 's'
                    jz .printsword
                    jnz .errorexitprintf
            .printdword:
                mov esi, ecx*4
                push [ebp+esi]
                call int_print
                inc eax
                jmp .srcfirst
            .printsword:
                mov esi, ecx*4
                push [ebp+esi]
                call str_print
                inc eax
                jmp .srcfirst
            .endsrc:
                call print_lf
                mov eax, [ecx+1]
                jmp .endprintf 
            .errorexitprintf:
                push syntax_error_printf
                call str_println
            .endprintf:
            pop ebx
            pop ecx
            pop edx
            pop esi
            pop ebp
            mul eax, 4
            ret
            ;
            ;
            ;
;
; Written In:
; X86 32bit NASM Linux Based Assembly Language 
;
; **  CAUTION ! **
; this module/header file is not fully complete yet.
; it is filled with lots of code errors. but, you know, 
; working with assembly is not so easy. so I'm just 
; writing the code first with the fresh mind and then
; I'll fix it all. So, for now don't use it.
; The Real AUTHOR: Suryalal Singha
;  Contact:
;    * GitHub: https://github.com/SuryalalSingha
;    * Email: surya.geek.email@gmail.com 
;    * LinkedIn and other: provided in GitHub profile 
; Contributions: This project is fully made by me.
; No Artificial intelligence has been forgotten writing 
; this code. I used AI for only finding bugs and making the doc. 
; 
; Although none has contributed in this project yet.
; I request you to contribute with your better knowledge 
; and help me to make it a successful project.
;
;
; More functions like file management and cli utilities will be added one by one.