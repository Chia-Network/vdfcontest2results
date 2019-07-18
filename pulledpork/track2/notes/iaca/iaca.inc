
%macro IACA_START 0
    mov ebx, 111
    db 0x64, 0x67, 0x90
%endmacro

%macro IACA_END 0
    mov ebx, 222
    db 0x64, 0x67, 0x90
%endmacro

%macro GLOBAL_FUNC 1
    global %1:function
%1:
%endmacro

