#ifndef PLAYER_LIB_H
#define PLAYER_LIB_H
#include "sys_matrix.h"
#include "z64.h"

struct CollisionPoly;

void Matrix_MultVec3f(z64_xyzf_t* src, z64_xyzf_t* dest);
int32_t BgCheck_AnyLineTest3(z64_col_ctxt_t* colCtx, z64_xyzf_t* posA, z64_xyzf_t* posB, z64_xyzf_t* posResult, struct CollisionPoly** outPoly,
                         int32_t chkWall, int32_t chkFloor, int32_t chkCeil, int32_t chkOneFace, int32_t* bgId);
uint32_t SurfaceType_CanHookshot(z64_col_ctxt_t* colCtx, struct CollisionPoly* poly, int32_t bgId);
Gfx* Gfx_SetupDL(Gfx* gfx, uint32_t i);

#endif
