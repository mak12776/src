
    ;   db  1
    ;   dw  2
    ;   dd  4
    ;   dq  8
    ;   resb
    ;   resw
    ;   resd
    ;   resq

end:
    dd      0

start_index:
    dd      0

start:
    cmp     [eax], ' '
    jeq     l0

    cmp     [eax], '\t'
    jeq     l0


    cmp     [eax], 'a'
    jge

    cmp     [eax], 'z'
    jge


l0:
    inc     eax
    cmp     [eax], [end]
    jeq
