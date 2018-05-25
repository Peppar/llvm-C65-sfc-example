.include "header.inc"

.ramsection "GlobalData" bank 0 slot 1
;; Z registers
ZR_:            dsb 32
;; Interrupt Z registers
ZRI_:           dsb 32

NewFrame_:      dw

PrevJoy1:       dw
PrevJoy2:       dw
Color:          dw

.ends

.bank 0
.section "MainText"

Start_:
        ;; Initialize the SNES.
        sei                     ; Disable interrupts
        clc
        xce                     ; Enter native mode (clc+xce)
        rep     #$08            ; Disable decimal arithmetic mode
        rep     #$10            ; 16-bit indexing with X and Y
        ldx     #$1FFF
        txs                     ; Set stack top to $1FFF

        jsr Initialize

        stz NewFrame_.w

WaitFrame_:
        cli                     ; Enable interrupts
        wai                     ; Wait for interrupt
        sei                     ; Disable interrupts
        ;; Check if we were woken by an NMI.
        lda NewFrame_.w
        beq WaitFrame_
        ;; Clear the flag.
        stz NewFrame_.w
        cli                     ; Enable interrupts
        jsr Frame
        jmp WaitFrame_

NMIHandler_:
        ;; NMI interrupt handler. Takes care of the "context switching"
        ;; (moving D to 0x20 for the Z registers) and calls NMIHandler.
        phd
        rep #$30
        .accu 16
        .index 16
        pha
        phx
        phy
        ;; Set NewFrame_ to 1 to indicate that an NMI has occurred.
        lda #1
        sta NewFrame_.w
        ;; Interrupt register page at $0020
        lda #ZRI_
        tcd
        jsr NMIHandler
        ply
        plx
        pla
        pld
        rti

.ends
