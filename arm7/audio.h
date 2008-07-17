/* 
 * Sound Channel
 */
#define SCHANREG	((SChanReg *)(SFRZERO + 0x400))
typedef struct SChanReg SChanReg;
struct SChanReg {
	union {
		struct {
			uchar vol;
			uchar pad1;
			uchar pan;
			uchar pad2;
		};
		ulong ctl;
	} cr;

	ulong	src;
	ushort	tmr;
	ushort	rpt;
	ulong	wlen; /* in words of 4 bytes */

	uchar	pad3[16];
};

/* SCHANREG->cr.ctl bits */
enum {
	NSChannels	= 16,	/* number of channels */

	SCrepeat	= 1<<27,
	SC1shot		= 1<<28,
	
	SCpcm8bit	= 0<<29,
	SCpcm16bit	= 1<<29,
	SCadpcm		= 2<<29,
	SCpsg		= 3<<29,

	SCena		= 1<<31,

	Minvol		= 0x00,
	Maxvol		= 0x7f,
};

/* usage: SCHANREG->tmr = SCHAN_BASE / hz */
#define SCHAN_BASE	(-0x1000000)

/* 
 * Master sound
 */
#define SNDREG	((SndReg *)(SFRZERO + 0x500))
typedef struct SndReg SndReg;
struct SndReg {
	union {
		uchar mvol;
		ushort ctl;
	} cr;

	ushort pad1;
	ulong bias;
	ushort s508;
	ushort s510;
	ushort s514;
	ushort s518;
	ushort s51c;
};

enum {
	Sndena		= 1<<15,
};

// not sure on the following

#define SOUND_BIAS 	(SNDREG->bias)
#define SOUND508	(SNDREG->s508)
#define SOUND510	(SNDREG->s510)
#define SOUND514	(SNDREG->s514)
#define SOUND518	(SNDREG->s518)
#define SOUND51C	(SNDREG->s51c)

void vblankaudio(void);

void startrecording(uchar *buffer, int length);
int stoprecording(void);
