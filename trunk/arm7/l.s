#include "../mem.h"

TEXT _main(SB), $-4
/*	MOVW		$Mach0(SB), R13 */
//	ADD		$(KSTACK-4), R13	/* leave 4 bytes for link */

	MOVW		$0, R0			/* start with IME=0 */
	MOVW		$(SFRbase + 0x208), R1	
	MOVW		R0, (R1)

	MOVW		$setR12(SB), R12 	/* static base (SB) */

	MOVW		$(PsrMirq), R1		/* Switch to IRQ mode */
	MOVW		R1, CPSR
	MOVW		$(IWRAMTOP7 - 0x60), R13

	MOVW		$(PsrMsys), R1		/* Switch to System mode */
	MOVW		R1, CPSR
	MOVW		$(IWRAMTOP7 - 0x100), R13

	BL		main(SB)		/* jump to kernel */

TEXT swiDelay(SB), $-4
	SWI	0x030000
	RET
TEXT swiWaitForVBlank(SB), $-4
	SWI	0x050000
	RET
/* fixme will need to figure out more here */
TEXT swiDivMod(SB), $-4
	SWI 0x090000
	RET