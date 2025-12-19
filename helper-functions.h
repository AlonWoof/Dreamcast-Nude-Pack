
#include <SADXModLoader.h>



void updateTime();
float getDeltaTime();
int random(int min, int max);

float clampFloat(float target, float min, float max);
float clampFloat01(float target);
float remapRange(float from, float fromMin, float fromMax, float toMin, float toMax);
float getVectorMagnitude(NJS_VECTOR vec);
float lerp(float a, float b, float f);
Float njDistanceP2P(NJS_POINT3* p1, NJS_POINT3* p2);
NJS_VECTOR getPlayerSidePos(taskwk* twp, double dist, int angle_offset);
void fixPartnerCollisions();
bool isIngame();

enum {
	MD_MTN_INIT,
	MD_MTN_SET,
	MD_MTN_CHNG,
	MD_MTN_LOOP,
	MD_MTN_NEXT,
	MD_MTN_STOP,
	MD_MTN_TXEN,
	MD_MTN_POTS,
	MD_MTN_COMB,
	MD_MTN_XSPD,
	MD_MTN_WORK,
	MD_MTN_WKNX,
	MD_MTN_MANU,
	MD_MTN_TRNS,
	MD_MTN_END
};

#define PNUM(twp) twp->counter.b[0]
#define PLNO(twp) twp->counter.b[1]

#define PL_ITEM_NBARRIA              0x1                    /* Normal barrier */
#define PL_ITEM_TBARRIA              0x2                    /* Magnetic barrier */
#define PL_ITEM_KILLED               0x4000                 /* Player was killed */
#define PL_ITEM_MUTEKI               0x8000                 /* Invincibility */

#define IM_MOTIONWK 0x1
#define IM_TASKWK   0x2
#define IM_FORCEWK  0x4
#define IM_ANYWK    0x8

#define SHORT_ANG(ang) ((ang) & 0xFFFF)
#define ROTATEX(m, ang) if (ang != 0) njRotateX(m, SHORT_ANG(ang));
#define ROTATEY(m, ang) if (ang != 0) njRotateY(m, SHORT_ANG(ang));
#define ROTATEZ(m, ang) if (ang != 0) njRotateZ(m, SHORT_ANG(ang));

#define CWK_FLAG_HIT    0x1          /* Currently intersecting another collision */
#define CWK_FLAG_2      0x2          /* ? */
#define CWK_FLAG_4      0x4          /* ? */
#define CWK_FLAG_8      0x8          /* ? */
#define CWK_FLAG_PUSH   0x10         /* Currently being pushed by another collision */
#define CWK_FLAG_DAMAGE 0x20         /* Currently receiving damage */
#define CWK_FLAG_HOMING 0x40         /* Can be added to the target lists */
#define CWK_FLAG_MEM    0x8000       /* The info array was allocated */

#define CI_ATTR_NO_SEND      0x4      /* Do not send information to other collisions */
#define CI_ATTR_NO_RECEIVE   0x8      /* Do not receive information from other collisions */
#define CI_ATTR_IGNORE       0x10     /* Do not run physical collision check */
#define CI_ATTR_POS_ABSOLUTE 0x20     /* The position is no longer relative to the entity */
#define CI_ATTR_ANG_YZX      0x200    /* Use YZX rotation order instead of ZXY */
#define CI_ATTR_DAMAGE       0x400    /* Allow damage */
#define CI_ATTR_2000         0x2000   /* ? */
#define CI_ATTR_NO_PUSH      0x4000   /* Do not get pushed by other collisions */
#define CI_ATTR_ANG_ABSOLUTE 0x8000   /* The angle is no longer relative to the entity */
#define CI_ATTR_40000        0x40000  /* ? */
#define CI_ATTR_80000        0x80000  /* ? */
#define CI_ATTR_100000       0x100000 /* ? */
#define CI_ATTR_200000       0x200000 /* ? */
#define CI_ATTR_400000       0x400000 /* ? */
#define CI_ATTR_800000       0x800000 /* ? */

#define CI_DMG_SET(att, def) (att | (def << 2)) /* Set the attack and defense priorities (0-3) */
#define CI_DMG_HIT    0x10 /* Collision has been hurt */
#define CI_DMG_PLAYER 0x20 /* Can hurt collisions in PLAYER and CHAO list */
#define CI_DMG_ENEMY  0x40 /* Can hurt collisions in ENEMY and ENEMY2 lists */
#define CI_DMG_OBJECT 0x80 /* Can hurt collisions in OBJECT and OBJECT2 lists */
#define CI_DMG_ALL (CI_DMG_PLAYER | CI_DMG_ENEMY | CI_DMG_OBJECT) /* Can hurt all collisions except BULLET/ITEM ones */

#define CI_PUSH_PO_PLAYER 0x1 /* Collision can push a PLAYER or CHAO collision */
#define CI_PUSH_PO_ENEMY  0x2 /* Collision can push a ENEMY or ENEMY2 collision */
#define CI_PUSH_PO_OBJECT 0x4 /* Collision can push a OBJECT or OBJECT2 collision */
#define CI_PUSH_PO_ITEM   0x8 /* Collision can push a ITEM or ITEM2 collision */
#define CI_PUSH_PO_CMN    (CI_PUSH_PO_PLAYER | CI_PUSH_PO_ENEMY | CI_PUSH_PO_OBJECT) /* Collision can push all collisions except ITEM, ITEM2 and BULLET */
#define CI_PUSH_PO_ALL    (CI_PUSH_PO_CMN | CI_PUSH_PO_ITEM) /* Collision can push all collisions except BULLET */

#define CI_PUSH_TH_PLAYER 0x10 /* Collision can't be pushed by a CID_PLAYER or CID_CHAO collision */
#define CI_PUSH_TH_ENEMY  0x20 /* Collision can't be pushed by a CID_ENEMY or CID_ENEMY2 collision */
#define CI_PUSH_TH_OBJECT 0x40 /* Collision can't be pushed by a CID_OBJECT or CID_OBJECT2 collision */
#define CI_PUSH_TH_ITEM   0x80 /* Collision can't be pushed by a CID_ITEM or CID_ITEM2 collision */
#define CI_PUSH_TH_CMN    (CI_PUSH_TH_PLAYER | CI_PUSH_TH_ENEMY | CI_PUSH_TH_OBJECT) /* Collision can't be pushed by all collisions except ITEM, ITEM2 and BULLET */
#define CI_PUSH_TH_ALL    (CI_PUSH_TH_CMN | CI_PUSH_TH_ITEM) /* Collision can't pushed by all collisions except ITEM, ITEM2 and BULLET */

#define PL_FLAG_ONLAND     0x1                              /* On a geometry collision */
#define PL_FLAG_ONCCL      0x2                              /* On a shape collision */
#define PL_FLAG_FLOOR      (PL_FLAG_ONLAND | PL_FLAG_ONCCL) /* On geometry or shape collision */
#define PL_FLAG_DAMAGE	   0x4								/* Hurt */
#define PL_FLAG_COLLIDED   0x8                              /* Touched a collision */
#define PL_FLAG_BALL       0x100                            /* Ball mode */
#define PL_FLAG_LIGHTDASH  0x200                            /* In Light Speed Dash mode */
#define PL_FLAG_ATTACK     0x400                            /* Can hurt other entities */
#define PL_FLAG_HOLD       0x800                            /* Holding mode */
#define PL_FLAG_INPUT      0x1000                           /* Following a guiding path */
#define PL_FLAG_PATH       0x2000                           /* Following a guiding path */
#define PL_FLAG_NOCON      0x4000                           /* Control disabled */
#define PL_FLAG_INVINCIBLE 0x8000                           /* Invincible */

#define HIT_INFO_RIDE 0x1
#define HIT_INFO_RODE 0x2

#define c_colli_hit_info_length 16
#define around_enemy_list_length 657
#define around_ring_list_length 257


#define GET_STAGE(num) ((num) >> 8)  /* Extract stage from GetStageNumber */
#define GET_ACT(num) ((num) & 0xFF)  /* Extract act from GetStageNumber */
#define STAGE_ACT(stage, act) ((stage) << 8 | act) /* Create Stage+Act to compare with GetStageNumber */

/* U.S. keyboard (101 keys). */
enum
{
	PDD_KEYUS_NONE = 0x00,		// 0x00 *
	PDD_KEYUS_ROLLOVER,			// 0x01 *
	PDD_KEYUS_FAIL,				// 0x02
	PDD_KEYUS_UNDEFINED,		// 0x03
	PDD_KEYUS_A,				// 0x04 *
	PDD_KEYUS_B,				// 0x05 *
	PDD_KEYUS_C,				// 0x06 *
	PDD_KEYUS_D,				// 0x07 *
	PDD_KEYUS_E,				// 0x08 *
	PDD_KEYUS_F,				// 0x09 *
	PDD_KEYUS_G,				// 0x0A *
	PDD_KEYUS_H,				// 0x0B *
	PDD_KEYUS_I,				// 0x0C *
	PDD_KEYUS_J,				// 0x0D *
	PDD_KEYUS_K,				// 0x0E *
	PDD_KEYUS_L,				// 0x0F *
	PDD_KEYUS_M,				// 0x10 *
	PDD_KEYUS_N,				// 0x11 *
	PDD_KEYUS_O,				// 0x12 *
	PDD_KEYUS_P,				// 0x13 *
	PDD_KEYUS_Q,				// 0x14 *
	PDD_KEYUS_R,				// 0x15 *
	PDD_KEYUS_S,				// 0x16 *
	PDD_KEYUS_T,				// 0x17 *
	PDD_KEYUS_U,				// 0x18 *
	PDD_KEYUS_V,				// 0x19 *
	PDD_KEYUS_W,				// 0x1A *
	PDD_KEYUS_X,				// 0x1B *
	PDD_KEYUS_Y,				// 0x1C *
	PDD_KEYUS_Z,				// 0x1D *

	PDD_KEYUS_1,				// 0x1E *
	PDD_KEYUS_2,				// 0x1F *
	PDD_KEYUS_3,				// 0x20 *
	PDD_KEYUS_4,				// 0x21 *
	PDD_KEYUS_5,				// 0x22 *
	PDD_KEYUS_6,				// 0x23 *
	PDD_KEYUS_7,				// 0x24 *
	PDD_KEYUS_8,				// 0x25 *
	PDD_KEYUS_9,				// 0x26 *
	PDD_KEYUS_0,				// 0x27 *

	PDD_KEYUS_RETURN,			// 0x28 *
	PDD_KEYUS_ESC,				// 0x29 *
	PDD_KEYUS_BACKSPACE,		// 0x2A *
	PDD_KEYUS_TAB,				// 0x2B *
	PDD_KEYUS_SPACE,			// 0x2C *
	PDD_KEYUS_MINUS,			// 0x2D *
	PDD_KEYUS_PLUS,				// 0x2E *
	PDD_KEYUS_LBRACKET,			// 0x2F *
	PDD_KEYUS_RBRACKET,			// 0x30 *
	PDD_KEYUS_BSLASH,			// 0x31 *
	PDD_KEYUS_UNUSED0,			// 0x32
	PDD_KEYUS_SEMICOLON,		// 0x33 *
	PDD_KEYUS_QUOTE,			// 0x34 *
	PDD_KEYUS_TILDA,			// 0x35 *
	PDD_KEYUS_COMMA,			// 0x36 *
	PDD_KEYUS_PERIOD,			// 0x37 *
	PDD_KEYUS_FSLASH,			// 0x38 *
	PDD_KEYUS_CAPSLOCK,			// 0x39 *

	PDD_KEYUS_F1,				// 0x3A *
	PDD_KEYUS_F2,				// 0x3B *
	PDD_KEYUS_F3,				// 0x3C *
	PDD_KEYUS_F4,				// 0x3D *
	PDD_KEYUS_F5,				// 0x3E *
	PDD_KEYUS_F6,				// 0x3F *
	PDD_KEYUS_F7,				// 0x40 *
	PDD_KEYUS_F8,				// 0x41 *
	PDD_KEYUS_F9,				// 0x42 *
	PDD_KEYUS_F10,				// 0x43 *
	PDD_KEYUS_F11,				// 0x44 *
	PDD_KEYUS_F12,				// 0x45 *

	PDD_KEYUS_PRINT,			// 0x46 *
	PDD_KEYUS_SCRLOCK,			// 0x47 *
	PDD_KEYUS_PAUSE,			// 0x48 *

	PDD_KEYUS_INSERT,			// 0x49 *
	PDD_KEYUS_HOME,				// 0x4A *
	PDD_KEYUS_PGUP,				// 0x4B *
	PDD_KEYUS_DEL,				// 0x4C *
	PDD_KEYUS_END,				// 0x4D *
	PDD_KEYUS_PGDN,				// 0x4E *

	PDD_KEYUS_RIGHT,			// 0x4F *
	PDD_KEYUS_LEFT,				// 0x50 *
	PDD_KEYUS_DOWN,				// 0x51 *
	PDD_KEYUS_UP,				// 0x52 *

	PDD_KEYUS_PAD_NUMLOCK,		// 0x53 *
	PDD_KEYUS_PAD_DIVIDE,		// 0x54 *
	PDD_KEYUS_PAD_MULT,			// 0x55 *
	PDD_KEYUS_PAD_MINUS,		// 0x56 *
	PDD_KEYUS_PAD_PLUS,			// 0x57 *
	PDD_KEYUS_PAD_ENTER,		// 0x58 *
	PDD_KEYUS_PAD_END,			// 0x59 *
	PDD_KEYUS_PAD_DOWN,			// 0x5A *
	PDD_KEYUS_PAD_PGDN,			// 0x5B *
	PDD_KEYUS_PAD_LEFT,			// 0x5C *
	PDD_KEYUS_PAD_5,			// 0x5D *
	PDD_KEYUS_PAD_RIGHT,		// 0x5E *
	PDD_KEYUS_PAD_HOME,			// 0x5F *
	PDD_KEYUS_PAD_UP,			// 0x60 *
	PDD_KEYUS_PAD_PGUP,			// 0x61 *
	PDD_KEYUS_PAD_INSERT,		// 0x62 *
	PDD_KEYUS_PAD_DEL,			// 0x63 *

	// Numeric Keypad definitions
	PDD_KEYUS_PAD_1 = 0x59,		// 0x59 *
	PDD_KEYUS_PAD_2,			// 0x5A *
	PDD_KEYUS_PAD_3,			// 0x5B *
	PDD_KEYUS_PAD_4,			// 0x5C *
	//	PDD_KEYUS_PAD_5,			// 0x5D * Same as above definition
	PDD_KEYUS_PAD_6 = 0x5E,		// 0x5E *
	PDD_KEYUS_PAD_7,			// 0x5F *
	PDD_KEYUS_PAD_8,			// 0x60 *
	PDD_KEYUS_PAD_9,			// 0x61 *
	PDD_KEYUS_PAD_0,			// 0x62 *
	PDD_KEYUS_PAD_PERIOD,		// 0x63 *

	PDD_KEYUS_UNUSED1,			// 0x64

	PDD_KEYUS_S3				// 0x65 *
};

/* Japanese keyboard (88 keys). */
enum
{
	PDD_KEYJ_NONE = 0x00,
	PDD_KEYJ_ROLLOVER,
	PDD_KEYJ_FAIL,
	PDD_KEYJ_UNDEFINED,
	PDD_KEYJ_A,
	PDD_KEYJ_B,
	PDD_KEYJ_C,
	PDD_KEYJ_D,
	PDD_KEYJ_E,
	PDD_KEYJ_F,
	PDD_KEYJ_G,
	PDD_KEYJ_H,
	PDD_KEYJ_I,
	PDD_KEYJ_J,
	PDD_KEYJ_K,
	PDD_KEYJ_L,
	PDD_KEYJ_M,
	PDD_KEYJ_N,
	PDD_KEYJ_O,
	PDD_KEYJ_P,
	PDD_KEYJ_Q,
	PDD_KEYJ_R,
	PDD_KEYJ_S,
	PDD_KEYJ_T,
	PDD_KEYJ_U,
	PDD_KEYJ_V,
	PDD_KEYJ_W,
	PDD_KEYJ_X,
	PDD_KEYJ_Y,
	PDD_KEYJ_Z,

	PDD_KEYJ_1,
	PDD_KEYJ_2,
	PDD_KEYJ_3,
	PDD_KEYJ_4,
	PDD_KEYJ_5,
	PDD_KEYJ_6,
	PDD_KEYJ_7,
	PDD_KEYJ_8,
	PDD_KEYJ_9,
	PDD_KEYJ_0,

	PDD_KEYJ_RETURN,
	PDD_KEYJ_ESC,
	PDD_KEYJ_BACKSPACE,
	PDD_KEYJ_TAB,
	PDD_KEYJ_SPACE,
	PDD_KEYJ_MINUS,
	PDD_KEYJ_POWER,
	PDD_KEYJ_AT,
	PDD_KEYJ_LBRACKET,
	PDD_UNUSED0,
	PDD_KEYJ_RBRACKET,
	PDD_KEYJ_SEMICOLON,
	PDD_KEYJ_COLON,
	PDD_KEYJ_KAKU,
	PDD_KEYJ_COMMA,
	PDD_KEYJ_PERIOD,
	PDD_KEYJ_FSLASH,
	PDD_KEYJ_CAPSLOCK,

	PDD_KEYJ_F1,
	PDD_KEYJ_F2,
	PDD_KEYJ_F3,
	PDD_KEYJ_F4,
	PDD_KEYJ_F5,
	PDD_KEYJ_F6,
	PDD_KEYJ_F7,
	PDD_KEYJ_F8,
	PDD_KEYJ_F9,
	PDD_KEYJ_F10,
	PDD_KEYJ_F11,
	PDD_KEYJ_F12,

	PDD_KEYJ_PRINT,
	PDD_KEYJ_SCRLOCK,
	PDD_KEYJ_PAUSE,

	PDD_KEYJ_INSERT,
	PDD_KEYJ_HOME,
	PDD_KEYJ_PGUP,
	PDD_KEYJ_DEL,
	PDD_KEYJ_END,
	PDD_KEYJ_PGDN,

	PDD_KEYJ_RIGHT,
	PDD_KEYJ_LEFT,
	PDD_KEYJ_DOWN,
	PDD_KEYJ_UP,

	PDD_KEYJ_APP = 0x65,
	PDD_KEYJ_BSLASH = 0x87,
	PDD_KEYJ_KANA,
	PDD_KEYJ_OR,
	PDD_KEYJ_HENKAN,
	PDD_KEYJ_MUHENKAN
};
