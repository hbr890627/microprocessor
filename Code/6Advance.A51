            ORG 00H ;code start from 00H
            SJMP MAIN ;jump to MAIN
            ORG 03H ;vector address for INT0
            SJMP INT0_ISR ;jump to INT0_ISR
			ORG 13H
			SJMP INT1_ISR 
MAIN:       MOV IE, #10000101B ;enable EA and EX0
            MOV SP, #30H ;stack start from #30H
            MOV A, #00000000B ;set ACC as 0000000B
			SETB PX1
LOOP:       MOV P1, A ;P1 = A (LED output)
            CALL DELAY ;call delay function
            CPL A ;reverse A
            SJMP LOOP ;infinite loop 36
INT0_ISR:   PUSH PSW ;push PSW into stack
            PUSH ACC ;push ACC into stack
            SETB RS0 ;switch to RB1
            MOV A, #11110000B ;set ACC as 11111110B
            MOV R0, #24 ;loop counter = 24
ROTATE_L: 	MOV P1, A ;P1 = A (LED output)
            CALL DELAY ;call delay function
            RL A ;rotate left
            DJNZ R0, ROTATE_L ;loop until R0 is 0
            POP ACC ;pop out ACC from stack
            POP PSW ;pop out PSW from stack
            RETI ;return from ISR
INT1_ISR:	PUSH PSW
			PUSH ACC
			SETB RS1
			MOV A, #11111110B
			MOV R0, #16
			SJMP ROTATE_L
DELAY:      MOV R7, #200
D1:         MOV R6, #250
            DJNZ R6, $
            DJNZ R7, D1
            RET ;return
			END;end the code