
#include <SADXModLoader.h>



void updateTime();
float getDeltaTime();

float clampFloat(float target, float min, float max);
float clampFloat01(float target);
float getVectorMagnitude(NJS_VECTOR vec);
float lerp(float a, float b, float f);
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

#define PL_FLAG_ONLAND     0x1                              /* On a geometry collision */
#define PL_FLAG_ONCCL      0x2                              /* On a shape collision */
#define PL_FLAG_FLOOR      (PL_FLAG_ONLAND | PL_FLAG_ONCCL) /* On geometry or shape collision */
#define PL_FLAG_DAMAGE     0x4                              /* Player is hurt */
#define PL_FLAG_COLLIDED   0x8                              /* Touched a collision */
#define PL_FLAG_10         0x10                             /* ? */
#define PL_FLAG_20         0x20                             /* ? */
#define PL_FLAG_BALL       0x100                            /* Ball mode */
#define PL_FLAG_LIGHTDASH  0x200                            /* In Light Speed Dash mode */
#define PL_FLAG_ATTACK     0x400                            /* Can hurt other entities */
#define PL_FLAG_HOLD       0x800                            /* Holding mode */
#define PL_FLAG_INPUT      0x1000                           /* Following a guiding path */
#define PL_FLAG_PATH       0x2000                           /* Following a guiding path */
#define PL_FLAG_NOCON      0x4000                           /* Control disabled */

#define PL_EQUIPMENT_CRYSTALRING     0x1                    /* Crystal ring (Sonic) */
#define PL_EQUIPMENT_LIGHTSHOES      0x2                    /* Light speed shoes (Sonic) */
#define PL_EQUIPMENT_ANCIENTLIGHT    0x4                    /* Ancient light (Sonic) */
#define PL_EQUIPMENT_JETANKLET       0x8                    /* Jet Anklet (Tails) */
#define PL_EQUIPMENT_RHYTHMBADGE     0x10                   /* Rhythm Badge (Tails) */
#define PL_EQUIPMENT_FIGHTGLOVES     0x20                   /* Fighting gloves (Knuckles) */
#define PL_EQUIPMENT_SHOVELCLAW      0x40                   /* Shovel Claw (Knuckles) */
#define PL_EQUIPMENT_LONGHAMMER      0x80                   /* Long Hammer (Amy) */
#define PL_EQUIPMENT_WARRIORFEATHER  0x100                  /* Warrior Feather (Amy) */
#define PL_EQUIPMENT_LASERBLASTER    0x200                  /* Laser Blaster (Gamma) */
#define PL_EQUIPMENT_JETBOOSTER      0x400                  /* Jet Booster (Gamma) */
#define PL_EQUIPMENT_POWERROD        0x800                  /* Power Rod (Big) */
#define PL_EQUIPMENT_LIFERING        0x1000                 /* Life Ring (Big) */
#define PL_EQUIPMENT_SUPER           0x8000                 /* Super Sonic */

#define PL_ITEM_NBARRIA              0x1                    /* Normal barrier */
#define PL_ITEM_TBARRIA              0x2                    /* Magnetic barrier */
#define PL_ITEM_KILLED               0x4000                 /* Player was killed */
#define PL_ITEM_MUTEKI               0x8000                 /* Invincibility */

