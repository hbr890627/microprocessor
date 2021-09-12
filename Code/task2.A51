;R0 有三顆7段
;R1 查表用
;R2 控制C0 C1 C2 P0腳位
;R3 掃描用 有三行

;R4 儲存數字
;R5 儲存數字
;R6 儲存數字

ORG 0
SJMP MAIN
ORG 03H
SJMP ISR

    MAIN:
    MOV DPTR, #TABLE
    MOV IE, #10000001B 
    MOV SP, #30H

    START:
    MOV R0, #3 ;三顆7段
    MOV R2, #11111110B ;從C0開始

    LOOP:
    MOV P0, R2
    MOV P1, #10010010B ;顯示5
    CALL DEBOUNCE
    MOV A, R2
    RL A
    MOV R2, A
    DJNZ R0, LOOP
    SJMP START

    SCAN: 
    MOV R1, #1 ;數字1開始
    MOV R3, #3 ;有三行
    MOV A, #11110111B
    SCAN1:
    MOV P2, A
    JNB P2.7, KEYIN
    INC R1
    JNB P2.6, KEYIN
    INC R1
    JNB P2.5, KEYIN
    INC R1
    RR A
    DJNZ R3, SCAN1
    RET

    KEYIN:
    CALL DELAY
    MOV A, R1 ;儲存數字
    CJNE R4, #11, N1
    MOV R4, A
    SJMP SCAN
    N1:
    CJNE R5, #11, N2
    MOV R5, A
    N2:
    MOV R6, A
    SJMP SCAN


    DEBOUNCE:
    MOV R7, #250
    DJNZ R7, $
    RET

    DELAY:
    PUSH ACC
    PUSH PSW
    SETB RS1
    MOV R7, #4
    D1:    
    MOV R6, #250
    D2:     
    MOV R5, #250
    DJNZ R5, $
    DJNZ R6, D2
    DJNZ R7, D1
    POP PSW
    POP ACC
    RET

    ISR: ;POP到3個七段
    PUSH PSW
    PUSH ACC
    SETB RS0
    MOV R4, #11
    MOV R5, #11
    MOV R6, #11
    STARTI:
    MOV R0, #3 ;三顆7段
    MOV R2, #11111110B ;從C0開始
    KEEP:
    MOV A, R4
    MOVC A, @A+DPTR
    MOV P1, A
    MOV P0, R2 ;C0
    CALL DEBOUNCE
    MOV A, R2
    RL A
    MOV R2, A

    MOV A, R5
    MOVC A, @A+DPTR
    MOV P1, A
    MOV P0, R2 ;C1
    CALL DEBOUNCE
    MOV A, R2
    RL A
    MOV R2, A

    MOV A, R6
    MOVC A, @A+DPTR
    MOV P1, A
    MOV P0, R2 ;C2
    CALL DEBOUNCE

    CALL SCAN
    ; DJNZ R0, KEEP
    SJMP STARTI

    POP ACC
    POP PSW
    RETI


    TABLE: 
    DB 11000000B; display “0”
    DB 11111001B; display “1”
    DB 10100100B; display “2”
    DB 10110000B; display “3”
    DB 10011001B; display “4”
    DB 10010010B; display “5”
    DB 10000010B; display “6”
    DB 11111000B; display “7”
    DB 10000000B; display “8”
    DB 10010000B; display “9”
    DB 10111111B; display “-”
    DB 11111111B; display “ ”
    END

