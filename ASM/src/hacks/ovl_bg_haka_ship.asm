; Bg_Haka_ship Hacks (Shadow Temple Boat)
.headersize(0x8097B9A0 - 0xD19030)

.org 0x8097BD9C
; Replaces:
;   addiu   a0, s0, 0x0068
;   func_8006385C (Math_StepToF)
    addiu   a0, s0, 0x0000
    jal     fast_boat
