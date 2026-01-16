#include "z_player_lib.h"

#include "gfx.h"
#include "rainbow.h"

void SkinMatrix_Vec3fMtxFMultXYZW(MtxF* mf, z64_xyzf_t* src, z64_xyzf_t* xyzDest, float* wDest) {
    xyzDest->x = mf->xw + ((src->x * mf->xx) + (src->y * mf->xy) + (src->z * mf->xz));
    xyzDest->y = mf->yw + ((src->x * mf->yx) + (src->y * mf->yy) + (src->z * mf->yz));
    xyzDest->z = mf->zw + ((src->x * mf->zx) + (src->y * mf->zy) + (src->z * mf->zz));
    *wDest = mf->ww + ((src->x * mf->wx) + (src->y * mf->wy) + (src->z * mf->wz));
}

void Player_DrawHookshotReticle(z64_game_t* play, z64_link_t* this, float arg2) {
    static z64_xyzf_t D_801260C8 = { -500.0f, -100.0f, 0.0f };
    struct CollisionPoly* sp9C;
    int32_t bgId;
    z64_xyzf_t sp8C;
    z64_xyzf_t sp80;
    z64_xyzf_t sp74;
    z64_xyzf_t sp68;
    float sp64;
    float sp60;
    uint32_t gLinkAdultHookshotReticleDL = 0x0602CB48;

    D_801260C8.z = 0.0f;
    Matrix_MultVec3f(&D_801260C8, &sp8C);
    D_801260C8.z = arg2;
    Matrix_MultVec3f(&D_801260C8, &sp80);

    if (BgCheck_AnyLineTest3(&play->col_ctxt, &sp8C, &sp80, &sp74, &sp9C, 1, 1, 1, 1, &bgId)) {
        OPEN_DISPS(play->common.gfx);

        OVERLAY_DISP = Gfx_SetupDL(OVERLAY_DISP, 7);

        SkinMatrix_Vec3fMtxFMultXYZW(&play->viewProjectionMtxF, &sp74, &sp68, &sp64);

        sp60 = (sp64 < 200.0f) ? 0.08f : (sp64 / 200.0f) * 0.08f;

        translate_sys_matrix(sp74.x, sp74.y, sp74.z, 0);
        scale_sys_matrix(sp60, sp60, sp60, 1);

        gSPMatrix(OVERLAY_DISP++, append_sys_matrix(play->common.gfx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(OVERLAY_DISP++, 0x06, play->obj_ctxt.objects[this->common.alloc_index].data);
        // Color the reticle in grey if surface is not hookshotable and in red if so.
        gDPSetPrimColor(OVERLAY_DISP++, 0, 0, 128, 128, 128, 255);
        if (SurfaceType_CanHookshot(&play->col_ctxt, sp9C, bgId)) {
            colorRGBA8_t rainbow_color;
            rainbow_color.color = get_rainbow_color(play->gameplay_frames, 10);
            gDPSetPrimColor(OVERLAY_DISP++, 0, 0, rainbow_color.r, rainbow_color.g, rainbow_color.b, 255);
        }

        gSPDisplayList(OVERLAY_DISP++, gLinkAdultHookshotReticleDL);

        CLOSE_DISPS(play->common.gfx);
    }
}
