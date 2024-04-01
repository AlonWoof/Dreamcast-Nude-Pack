
#include <SADXModLoader.h>



void updateTime();
float getDeltaTime();
int random(int min, int max);

float clampFloat(float target, float min, float max);
float clampFloat01(float target);
float getVectorMagnitude(NJS_VECTOR vec);
float lerp(float a, float b, float f);
Float njDistanceP2P(NJS_POINT3* p1, NJS_POINT3* p2);
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

