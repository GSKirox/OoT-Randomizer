.headersize(0x80079200 - 0x00AEF160)

.org 0x8007BEC8
    ; Replaces jal     func_8007B560
    jal     Player_DrawHookshotReticle
