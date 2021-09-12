;R0 3 led
;R1 number
;R2 c0 c1 c2

;R0 number
;R1 3 rows
;R2 c0 c1 c2 #11111110B
;R3 3 有三個七段 #3
;R4 input 3 times
;R5 save input number

        ORG 0 ; start address is 0
        SJMP MAIN
        ORG 03H
        SJMP ISR
MAIN:   MOV DPTR, #TABLE ; DPTR point to TABLE
        MOV IE, #10000001B
        MOV SP, #30H
START1: MOV R0, #3
        MOV R2, #11111110B ; LED drive pin
LOOP1:  MOV P0, R2
        ; MOV A, R1 ; move R1 to A
        ; MOVC A, @A+DPTR ; get value from table
        MOV P1, #10010010B ; move value to P1
        CALL SEVEN
        MOV A, R2 ; move R2 to A
        RL A ; rotate A
        MOV R2, A ; move A back to R2
        DJNZ R0, LOOP1; decrement R0 until 0
        SJMP START1 ; jump to start
ISR:    PUSH PSW
        PUSH ACC
        SETB RS0
START2: MOV R4, #3 ; can input 3 times
LOOP2:  MOV R2, #11111110B ; LED drive pin
        MOV R3, #3
LOOP3:  MOV P0, R2
        CJNE R4, #3, KEEP
        MOV A, #10
        SJMP GETNUM
KEEP:   MOV A, R5       
GETNUM: MOVC A, @A+DPTR
        MOV P1, A
        CALL SEVEN
        MOV A, R2
        RL A
        MOV R2, A
        DJNZ R3, LOOP3 ;閃完C0 C1 C2開始掃描
SCAN1:  MOV R0, #1 ;數字1開始
        MOV R1, #3 ;三行
        MOV A, #11110111B
SCAN2:  MOV P2, A
        JNB P2.7, KEYIN
        INC R0
        JNB P2.6, KEYIN
        INC R0
        JNB P2.5, KEYIN
        INC R0
        RR A
        DJNZ R1, SCAN2
        SJMP LOOP2 ;repeat scan
KEYIN:  CALL SEVEN ;debounce
        CJNE R4, #0, CKEYIN
        POP ACC
        POP PSW
        RETI
CKEYIN: MOV A, R0 ;put the number into P1
        MOV R5, A
        MOVC A, @A+DPTR
        ;MOV P0, #11111110B ;C0 C1 C2
        MOV P1, A
        CALL DELAY
        ; MOV A, R2
        ; RL A
        ; MOV R2, A
        DEC R4
        SJMP LOOP2  
DELAY:  SETB RS1
        MOV R7, #4
D1:     MOV R6, #250
D2:     MOV R5, #250
        DJNZ R5, $
        DJNZ R6, D2
        DJNZ R7, D1
        CLR RS1
        RET
SEVEN:  SETB RS1
        MOV R4, #250
        DJNZ R4, $
        CLR RS1
        RET
TABLE:  DB 11000000B; display “0”
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
        END