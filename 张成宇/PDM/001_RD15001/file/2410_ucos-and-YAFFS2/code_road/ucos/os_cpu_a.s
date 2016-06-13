	.global  OSRunning
	.global  OSPrioCur
	.global  OSPrioHighRdy
	.global  OSTCBCur
	.global  OSTCBHighRdy
	.global  OSIntNesting
	.global  OSIntExit
	.global  OSTaskSwHook
	.global  HandleIRQ

	.global  OS_CPU_SR_Save 
	.global  OS_CPU_SR_Restore
	.global  OSStartHighRdy
	.global  OSCtxSw
	.global  OSIntCtxSw
	.global  OS_CPU_IRQ_ISR

	.set NO_INT, 0xC0                        /* Mask used to disable interrupts (Both FIR and IRQ)*/
	.set SVC32_MODE, 0x13
	.set FIQ32_MODE, 0x11
	.set IRQ32_MODE, 0x12

	.text
	.code 32

OS_CPU_IRQ_ISR:
	
	STMFD   SP!, {R1-R3}                     /* PUSH WORKING REGISTERS ONTO IRQ STACK */
	MOV     R1, SP                           /* Save   IRQ stack pointer */
	ADD     SP, SP,#12                       /* Adjust IRQ stack pointer */
	SUB     R2, LR,#4                        /* Adjust PC for return address to task */
	MRS     R3, SPSR                         /* Copy SPSR (i.e. interrupted task's CPSR) to R3 */
	MSR     CPSR_c, #(NO_INT | SVC32_MODE)   /* Change to SVC mode */
	
	                                         /* SAVE TASK'S CONTEXT ONTO TASK'S STACK */
	STMFD   SP!, {R2}                        /* Push task's Return PC */
	STMFD   SP!, {LR}                        /* Push task's LR */
	STMFD   SP!, {R4-R12}                    /* Push task's R12-R4 */
	LDMFD   R1!, {R4-R6}                     /* Move task's R1-R3 from IRQ stack to SVC stack */
	STMFD   SP!, {R4-R6}
	STMFD   SP!, {R0}                        /* Push task's R0    onto task's stack */
	STMFD   SP!, {R3}                        /* Push task's CPSR (i.e. IRQ's SPSR) */

	                                         /* HANDLE NESTING COUNTER */
	LDR     R0, =OSIntNesting                /* OSIntNesting++; */
	LDRB    R1, [R0]
	ADD     R1, R1,#1
	STRB    R1, [R0]
	
	CMP     R1, #1                           /* if (OSIntNesting == 1) { */
	BNE     OS_CPU_IRQ_ISR_1
	LDR     R4, =OSTCBCur                    /* OSTCBCur->OSTCBStkPtr = SP; */
	LDR     R5, [R4]
	STR     SP, [R5]                         /* } */
	
OS_CPU_IRQ_ISR_1:

	MSR     CPSR_c, #(NO_INT | IRQ32_MODE)   /* Change to IRQ mode (to use the IRQ stack to handle interrupt) */
	LDR     R0, =HandleIRQ      /* HandleIRQ() */
	MOV     LR, PC
	BX      R0

	MSR     CPSR_c, #(NO_INT | SVC32_MODE)   /* Change to SVC mode */
	LDR     R0, =OSIntExit                   /* OSIntExit() */
	MOV     LR, PC
	BX      R0
	                                         /* RESTORE NEW TASK'S CONTEXT */
	LDMFD   SP!, {R4}                        /* Pop new task's CPSR */
	MSR     SPSR_cxsf, R4
	LDMFD   SP!, {R0-R12,LR,PC}^             /* Pop new task's context */

OS_CPU_SR_Save:

	MRS     R0,CPSR                          /* Set IRQ and FIQ bits in CPSR to disable all interrupts */
	ORR     R1,R0,#NO_INT
	MSR     CPSR_c,R1
	MRS     R1,CPSR                          /* Confirm that CPSR contains the proper interrupt disable flags */
	AND     R1,R1,#NO_INT
	CMP     R1,#NO_INT
	BNE     OS_CPU_SR_Save                   /* Not properly disabled (try again) */
	BX      LR                               /* Disabled, return the original CPSR contents in R0 */

OS_CPU_SR_Restore:
	MSR     CPSR_c,R0
	BX      LR


OSStartHighRdy:
	
	LDR     R0, =OSTaskSwHook                /* OSTaskSwHook(); */
	MOV     LR, PC
	BX      R0

	MSR     CPSR_cxsf, #0xD3                 /* Switch to SVC mode with IRQ and FIQ disabled */

	LDR     R4, =OSRunning                   /* OSRunning = TRUE; */
	MOV     R5, #1
	STRB    R5, [R4]
	                                         /* SWITCH TO HIGHEST PRIORITY TASK */
	LDR     R4, =OSTCBHighRdy                /* Get highest priority task TCB address */
	LDR     R4, [R4]                         /* get stack pointer */
	LDR     SP, [R4]                         /* switch to the new stack */
	
	LDR     R4,  [SP], #4                    /* pop new task's CPSR */
	MSR     SPSR_cxsf,R4
	LDMFD   SP!, {R0-R12,LR,PC}^             /* pop new task's context */


OSCtxSw:
	                                         /* SAVE CURRENT TASK'S CONTEXT */
	STMFD   SP!, {LR}                        /* Push return address */
	STMFD   SP!, {LR}
	STMFD   SP!, {R0-R12}                    /* Push registers */
	MRS     R4,  CPSR                        /* Push current CPSR */
	TST     LR, #1                           /* See if called from Thumb mode */
	ORRNE   R4,  R4, #0x20                   /* If yes, Set the T-bit */
	STMFD   SP!, {R4}
	
	LDR     R4, =OSTCBCur                    /* OSTCBCur->OSTCBStkPtr = SP; */
	LDR     R5, [R4]
	STR     SP, [R5]

	LDR     R0, =OSTaskSwHook                /* OSTaskSwHook(); */
	MOV     LR, PC
	BX      R0
	
	LDR     R4, =OSPrioCur                   /* OSPrioCur = OSPrioHighRdy; */
	LDR     R5, =OSPrioHighRdy
	LDRB    R6, [R5]
	STRB    R6, [R4]
	
	LDR     R4, =OSTCBCur                    /* OSTCBCur  = OSTCBHighRdy; */
	LDR     R6, =OSTCBHighRdy
	LDR     R6, [R6]
	STR     R6, [R4]
	
	LDR     SP, [R6]                         /* SP = OSTCBHighRdy->OSTCBStkPtr; */
	
	                                         /* RESTORE NEW TASK'S CONTEXT */
	LDMFD   SP!, {R4}                        /* Pop new task's CPSR */
	MSR     SPSR_cxsf, R4
	
	LDMFD   SP!, {R0-R12,LR,PC}^             /* Pop new task's context */


OSIntCtxSw:

	LDR     R0, =OSTaskSwHook                /* OSTaskSwHook(); */
	MOV     LR, PC
	BX      R0

	LDR     R4, =OSPrioCur                   /* OSPrioCur = OSPrioHighRdy; */
	LDR     R5, =OSPrioHighRdy
	LDRB    R6, [R5]
	STRB    R6, [R4]

	LDR     R4, =OSTCBCur                    /* OSTCBCur  = OSTCBHighRdy; */
	LDR     R6, =OSTCBHighRdy
	LDR     R6, [R6]
	STR     R6, [R4]

	LDR     SP, [R6]                         /* SP = OSTCBHighRdy->OSTCBStkPtr; */
	                                         /* RESTORE NEW TASK'S CONTEXT */
	LDMFD   SP!, {R4}                        /* Pop new task's CPSR */
	MSR     SPSR_cxsf, R4
	LDMFD   SP!, {R0-R12,LR,PC}^             /* Pop new task's context */
	.end

