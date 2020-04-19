;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Arithmetic routines for clang/llvm 65816 backend
;;
;; By Oskar Holstensson
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        .text

        .globl  memset
memset:
        .index 16
        .accu 16
        phx
        ldy <4
        beq memset_exit
        ldx <0
        sep #0x20
        .accu 8
        lda <2
memset_next:
        sta 0,X
        inx
        dey
        bne memset_next
        rep #0x20
        .accu 16
memset_exit:
        plx
        rts

        .globl  c65_mul8
        ;; 8-bit unsigned multiplication
c65_mul8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        lda #0
_c65_mul8_mult1:
        ldx <0
        beq _c65_mul8_done
        lsr <0
        bcc _c65_mul8_mult2
        clc
        adc <1
_c65_mul8_mult2:
        asl <1
        bra _c65_mul8_mult1
_c65_mul8_done:
        sta <0
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_mul16
        ;; 16-bit unsigned multiplication
c65_mul16:
        .index 16
        .accu 16
        phx
        lda #0
_c65_mul16_mult1:
        ldx <0
        beq _c65_mul16_done
        lsr <0
        bcc _c65_mul16_mult2
        clc
        adc <2
_c65_mul16_mult2:
        asl <2
        bra _c65_mul16_mult1
_c65_mul16_done:
        sta <0
        plx
        rts

        .globl  c65_mul32
        ;; 32-bit unsigned multiplication
c65_mul32:
        .index 16
        .accu 16
        phx
        lda #0
        pha
        pha
_c65_mul32_mult1:
        ldx <0
        bne _c65_mul32_cont
        ldx <2
        beq _c65_mul32_done
_c65_mul32_cont:
        lsr <2
        ror <0
        bcc _c65_mul32_mult2
        clc
        lda 1,S
        adc <4
        sta 1,S
        lda 3,S
        adc <6
        sta 3,S
_c65_mul32_mult2:
        asl <4
        rol <6
        bra _c65_mul32_mult1
_c65_mul32_done:
        pla
        sta <0
        pla
        sta <2
        plx
        rts

        .globl  c65_mul64
        ;; 64-bit unsigned multiplication
c65_mul64:
        .index 16
        .accu 16
        phx
        lda #0
        pha
        pha
        pha
        pha
_c65_mul64_mult1:
        ldx <0
        bne _c65_mul64_cont
        ldx <2
        bne _c65_mul64_cont
        ldx <4
        bne _c65_mul64_cont
        ldx <6
        beq _c65_mul64_done
_c65_mul64_cont:
        lsr <6
        ror <4
        ror <2
        ror <0
        bcc _c65_mul64_mult2
        clc
        lda 1,S
        adc <8
        sta 1,S
        lda 3,S
        adc <10
        sta 3,S
        lda 5,S
        adc <12
        sta 5,S
        lda 7,S
        adc <14
        sta 7,S
_c65_mul64_mult2:
        asl <8
        rol <10
        rol <12
        rol <14
        bra _c65_mul64_mult1
_c65_mul64_done:
        pla
        sta <0
        pla
        sta <2
        pla
        sta <4
        pla
        sta <6
        plx
        rts

        .globl  c65_udiv8
        ;; 8-bit by 8-bit unsigned division
c65_udiv8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <0
        lda <1
        stz <0
        ldy #1
_c65_udiv8_div1:
        asla
        bcs _c65_udiv8_div2
        iny
        cpy #9
        bne _c65_udiv8_div1
_c65_udiv8_div2:
        rora
_c65_udiv8_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_udiv8_div3
        tax
_c65_udiv8_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_udiv8_div4
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_udiv16
        ;; 16-bit by 16-bit unsigned division
c65_udiv16:
        .index 16
        .accu 16
        phx
        ldx <0
        lda <2
        stz <0
        ldy #1
_c65_udiv16_div1:
        asla
        bcs _c65_udiv16_div2
        iny
        cpy #17
        bne _c65_udiv16_div1
_c65_udiv16_div2:
        rora
_c65_udiv16_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_udiv16_div3
        tax
_c65_udiv16_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_udiv16_div4
        plx
        rts

        .globl  c65_udiv32
        ;; 32-bit by 32-bit unsigned division
c65_udiv32:
        .index 16
        .accu 16
        phx
        pei <2
        pei <0
        stz <0
        stz <2
        ldy #1
_c65_udiv32_div1:
        asl <4
        rol <6
        bcs _c65_udiv32_div2
        iny
        cpy #33
        bne _c65_udiv32_div1
_c65_udiv32_div2:
        ror <6
        ror <4
_c65_udiv32_div4:
        sec
        lda 1,S
        sbc <4
        tax
        lda 3,S
        sbc <6
        bcc _c65_udiv32_div3
        sta 3,S
        txa
        sta 1,S
_c65_udiv32_div3:
        rol <0
        rol <2
        lsr <6
        ror <4
        dey
        bne _c65_udiv32_div4
        pla
        pla
        plx
        rts

        .globl  c65_udiv64
        ;; 64-bit by 64-bit unsigned division
c65_udiv64:
        .index 16
        .accu 16
        phx
        pha
        pha
        pei <6
        pei <4
        pei <2
        pei <0
        stz <0
        stz <2
        stz <4
        stz <6
        ldy #1
_c65_udiv64_div1:
        asl <8
        rol <10
        rol <12
        rol <14
        bcs _c65_udiv64_div2
        iny
        cpy #65
        bne _c65_udiv64_div1
_c65_udiv64_div2:
        ror <14
        ror <12
        ror <10
        ror <8
_c65_udiv64_div4:
        sec
        lda 1,S
        sbc <8
        tax
        lda 3,S
        sbc <10
        sta 9,S
        lda 5,S
        sbc <12
        sta 11,S
        lda 7,S
        sbc <14
        bcc _c65_udiv64_div3
        sta 7,S
        lda 11,S
        sta 5,S
        lda 9,S
        sta 3,S
        txa
        sta 1,S
_c65_udiv64_div3:
        rol <0
        rol <2
        rol <4
        rol <6
        lsr <14
        ror <12
        ror <10
        ror <8
        dey
        bne _c65_udiv64_div4
        pla
        pla
        pla
        pla
        pla
        pla
        plx
        rts

        .globl  c65_urem8
        ;; 8-bit by 8-bit unsigned remainder
c65_urem8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <0
        lda <1
        stz <0
        ldy #1
_c65_urem8_div1:
        asla
        bcs _c65_urem8_div2
        iny
        cpy #9
        bne _c65_urem8_div1
_c65_urem8_div2:
        rora
_c65_urem8_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_urem8_div3
        tax
_c65_urem8_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_urem8_div4
        stx <0
        rep #0x30
        .index 16
        .accu 16
        plx
        rts

        .globl  c65_urem16
        ;; 16-bit by 16-bit unsigned division and remainder
c65_urem16:
        .index 16
        .accu 16
        phx
        ldx <0
        lda <2
        stz <0
        ldy #1
_c65_urem16_div1:
        asla
        bcs _c65_urem16_div2
        iny
        cpy #17
        bne _c65_urem16_div1
_c65_urem16_div2:
        rora
_c65_urem16_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_urem16_div3
        tax
_c65_urem16_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_urem16_div4
        stx <0
        plx
        rts

        .globl  c65_urem32
        ;; 32-bit by 32-bit unsigned division and remainder
c65_urem32:
        .index 16
        .accu 16
        phx
        pei <2
        pei <0
        stz <0
        stz <2
        ldy #1
_c65_urem32_div1:
        asl <4
        rol <6
        bcs _c65_urem32_div2
        iny
        cpy #33
        bne _c65_urem32_div1
_c65_urem32_div2:
        ror <6
        ror <4
_c65_urem32_div4:
        sec
        lda 1,S
        sbc <4
        tax
        lda 3,S
        sbc <6
        bcc _c65_urem32_div3
        sta 3,S
        txa
        sta 1,S
_c65_urem32_div3:
        rol <0
        rol <2
        lsr <6
        ror <4
        dey
        bne _c65_urem32_div4
        pla
        sta <0
        pla
        sta <2
        plx
        rts

        .globl  c65_urem64
        ;; 64-bit by 64-bit unsigned division and remainder
c65_urem64:
        .index 16
        .accu 16
        phx
        pha
        pha
        pei <6
        pei <4
        pei <2
        pei <0
        stz <0
        stz <2
        stz <4
        stz <6
        ldy #1
_c65_urem64_div1:
        asl <8
        rol <10
        rol <12
        rol <14
        bcs _c65_urem64_div2
        iny
        cpy #65
        bne _c65_urem64_div1
_c65_urem64_div2:
        ror <14
        ror <12
        ror <10
        ror <8
_c65_urem64_div4:
        sec
        lda 1,S
        sbc <8
        tax
        lda 3,S
        sbc <10
        sta 9,S
        lda 5,S
        sbc <12
        sta 11,S
        lda 7,S
        sbc <14
        bcc _c65_urem64_div3
        sta 7,S
        lda 11,S
        sta 5,S
        lda 9,S
        sta 3,S
        txa
        sta 1,S
_c65_urem64_div3:
        rol <0
        rol <2
        rol <4
        rol <6
        lsr <14
        ror <12
        ror <10
        ror <8
        dey
        bne _c65_urem64_div4
        pla
        sta <0
        pla
        sta <2
        pla
        sta <4
        pla
        sta <6
        pla
        pla
        plx
        rts

        .globl  c65_udivrem8
        ;; 8-bit by 8-bit unsigned division
c65_udivrem8:
        .index 16
        .accu 16
        phx
        sep #0x30
        .index 8
        .accu 8
        ldx <0
        lda <1
        stz <0
        ldy #1
_c65_udivrem8_div1:
        asla
        bcs _c65_udivrem8_div2
        iny
        cpy #9
        bne _c65_udivrem8_div1
_c65_udivrem8_div2:
        rora
_c65_udivrem8_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_udivrem8_div3
        tax
_c65_udivrem8_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_udivrem8_div4
        txa
        sta (<2)
        rep #0x30
        .index 16
        .accu 16
        plx
        rts


        .globl  c65_udivrem16
        ;; 16-bit by 16-bit unsigned division and remainder
c65_udivrem16:
        .index 16
        .accu 16
        phx
        ldx <0
        lda <2
        stz <0
        ldy #1
_c65_udivrem16_div1:
        asla
        bcs _c65_udivrem16_div2
        iny
        cpy #17
        bne _c65_udivrem16_div1
_c65_udivrem16_div2:
        rora
_c65_udivrem16_div4:
        pha
        txa
        sec
        sbc 1,S
        bcc _c65_udivrem16_div3
        tax
_c65_udivrem16_div3:
        rol <0
        pla
        lsra
        dey
        bne _c65_udivrem16_div4
        txa
        sta (<4)
        plx
        rts

        .globl  c65_udivrem32
        ;; 32-bit by 32-bit unsigned division
c65_udivrem32:
        .index 16
        .accu 16
        phx
        pei <2
        pei <0
        stz <0
        stz <2
        ldy #1
_c65_udivrem32_div1:
        asl <4
        rol <6
        bcs _c65_udivrem32_div2
        iny
        cpy #33
        bne _c65_udivrem32_div1
_c65_udivrem32_div2:
        ror <6
        ror <4
_c65_udivrem32_div4:
        sec
        lda 1,S
        sbc <4
        tax
        lda 3,S
        sbc <6
        bcc _c65_udivrem32_div3
        sta 3,S
        txa
        sta 1,S
_c65_udivrem32_div3:
        rol <0
        rol <2
        lsr <6
        ror <4
        dey
        bne _c65_udivrem32_div4
        ;; Remainder is returned indirectly
        lda <8
        tax
        pla
        sta 0,X
        pla
        sta 2,X
        plx
        rts

        .globl  c65_udivrem64
        ;; 64-bit by 64-bit unsigned division and remainder
c65_udivrem64:
        .index 16
        .accu 16
        phx
        pha
        pha
        pei <6
        pei <4
        pei <2
        pei <0
        stz <0
        stz <2
        stz <4
        stz <6
        ldy #1
_c65_udivrem64_div1:
        asl <8
        rol <10
        rol <12
        rol <14
        bcs _c65_udivrem64_div2
        iny
        cpy #65
        bne _c65_udivrem64_div1
_c65_udivrem64_div2:
        ror <14
        ror <12
        ror <10
        ror <8
_c65_udivrem64_div4:
        sec
        lda 1,S
        sbc <8
        tax
        lda 3,S
        sbc <10
        sta 9,S
        lda 5,S
        sbc <12
        sta 11,S
        lda 7,S
        sbc <14
        bcc _c65_udivrem64_div3
        sta 7,S
        lda 11,S
        sta 5,S
        lda 9,S
        sta 3,S
        txa
        sta 1,S
_c65_udivrem64_div3:
        rol <0
        rol <2
        rol <4
        rol <6
        lsr <14
        ror <12
        ror <10
        ror <8
        dey
        bne _c65_udivrem64_div4
        lda 17,S
        tax
        pla
        sta 0,X
        pla
        sta 2,X
        pla
        sta 4,X
        pla
        sta 6,X
        pla
        pla
        plx
        rts
