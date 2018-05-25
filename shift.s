;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Bit shift routines for clang/llvm 65816 backend
;;
;; By Oskar Holstensson
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	.text

        .globl  c65_shl8
        .type   c65_shl8,@function
        ;; 8-bit shift left
.quorve:
c65_shl8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <1
        beq 2f
        lda <0
1:
        asla
        dex
        bne 1b
        sta <0
2:
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_shl16
        .type   c65_shl16,@function
        ;; 16-bit shift left
c65_shl16:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <2
        beq 2f
        lda <0
1:
        asla
        dex
        bne 1b
        sta <0
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_shl32
        .type   c65_shl32,@function
        ;; 32-bit shift left
c65_shl32:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <4
        beq 2f
        lda <0
1:
        asla
        rol <2
        dex
        bne 1b
        sta <0
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_shl64
        .type   c65_shl64,@function
        ;; 64-bit shift left
c65_shl64:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <8
        beq 2f
        lda <0
1:
        asla
        rol <2
        rol <4
        rol <6
        dex
        bne 1b
        sta <0
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_lshr8
        .type   c65_lshr8,@function
        ;; 8-bit logical shift right (unsigned)
c65_lshr8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <1
        beq 2f
        lda <0
1:
        lsra
        dex
        bne 1b
        sta <0
2:
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_lshr16
        .type   c65_lshr16,@function
        ;; 16-bit logical shift right (unsigned)
c65_lshr16:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <2
        beq 2f
        lda <0
1:
        lsra
        dex
        bne 1b
        sta <0
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_lshr32
        .type   c65_lshr32,@function
        ;; 32-bit logical shift right (unsigned)
c65_lshr32:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <4
        beq 2f
        lda <2
1:
        lsra
        ror <0
        dex
        bne 1b
        sta <2
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_lshr64
        .type   c65_lshr64,@function
        ;; 64-bit logical shift right (unsigned)
c65_lshr64:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <8
        beq 2f
        lda <6
1:
        lsra
        ror <4
        ror <2
        ror <0
        dex
        bne 1b
        sta <6
2:
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_ashr8
        .type   c65_ashr8,@function
        ;; 8-bit arithmetic shift right (signed)
c65_ashr8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <1
        beq 1f
        lda <0
        bmi _c65_ashr8_neg
_c65_ashr8_pos:
        lsra
        dex
        bne _c65_ashr8_pos
        sta <0
1:
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

_c65_ashr8_neg:
        .index 8
        .accu 8
        sec
        rora
        dex
        bne _c65_ashr8_neg
        sta <0
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_ashr16
        .type   c65_ashr16,@function
        ;; 16-bit arithmetic shift right (signed)
c65_ashr16:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <2
        beq 1f
        lda <0
        bmi _c65_ashr16_neg
_c65_ashr16_pos:
        lsra
        dex
        bne _c65_ashr16_pos
        sta <0
1:
        rep #0x10
        .index 16
        plx
        rts

_c65_ashr16_neg:
        .index 8
        sec
        rora
        dex
        bne _c65_ashr16_neg
        sta <0
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_ashr32
        .type   c65_ashr32,@function
        ;; 32-bit arithmetic shift right (signed)
c65_ashr32:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <4
        beq 1f
        lda <2
        bmi _c65_ashr32_neg
_c65_ashr32_pos:
        lsra
        ror <0
        dex
        bne _c65_ashr32_pos
        sta <2
1:
        rep #0x10
        .index 16
        plx
        rts

_c65_ashr32_neg:
        .index 8
        sec
        rora
        ror <0
        dex
        bne _c65_ashr32_neg
        sta <2
        rep #0x10
        .index 16
        plx
        rts

        .globl  c65_ashr64
        .type   c65_ashr64,@function
        ;; 64-bit arithmetic shift right (signed)
c65_ashr64:
        .index 16
        .accu 16
        phx
        sep #0x10
        .index 8
        ldx <8
        beq 1f
        lda <6
        bmi _c65_ashr64_neg
_c65_ashr64_pos:
        lsra
        ror <4
        ror <2
        ror <0
        dex
        bne _c65_ashr64_pos
        sta <6
1:
        rep #0x10
        .index 16
        plx
        rts

_c65_ashr64_neg:
.index 8
        sec
        rora
        ror <4
        ror <2
        ror <0
        dex
        bne _c65_ashr64_neg
        sta <6
        rep #0x10
        .index 16
        plx
        rts
