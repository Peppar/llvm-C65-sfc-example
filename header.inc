;------------------------------ Header File ---------------------------------
;   This is basically a combo of MarctheMER's and Neviksti's header files
; Perhaps reading their's will also help your understanding of the header,
; but I believe this will be the simplest method of defining your header,
; as Marc's doesn't provide a full explanation, and Neviksti's can be
; a bit more difficult for beginners (using the WLA directives is easier).
;
; bazz
;----------------------------------------------------------------------------

;----------------------------------------------------------------------------
; Credit to bazz at wiki.superfamicom.org for this file:
; https://wiki.superfamicom.org/writing-the-header
;
; Adapted for C example by Oskar Holstensson
;----------------------------------------------------------------------------

.MEMORYMAP
  ;; The slot is $8000 bytes in size. More details on slots later.
  SLOTSIZE $8000

  ;; There's only 1 slot in SNES, there are more in other consoles.
  DEFAULTSLOT 0

  ;; Define's slot 0's starting address.
  SLOT 0 $8000

  ;; Define slot 1 having its origin in the RAM area
  SLOT 1 $0000
.ENDME

.ROMBANKSIZE $8000             ; Every ROM bank is 32 KBytes in size
.ROMBANKS 1                     ; 2 Mbits - Tell WLA we want to use 8 ROM Banks

.SNESHEADER
  ID "SNES"                     ; 1-4 letter string, just leave it as "SNES"

  NAME "SFC C EXAMPLE        "  ; Program Title - can't be over 21 bytes,
  ;    "123456789012345678901"  ; use spaces for unused bytes of the name.

  SLOWROM
  LOROM

  CARTRIDGETYPE $02             ; $00 = ROM only
  ROMSIZE $06                   ; $06 = 512 kbits
  SRAMSIZE $00                  ; No SRAM
  COUNTRY $01                   ; $01 = U.S.  $00 = Japan, that's all I know
  LICENSEECODE $00              ; Just use $00
  VERSION $00                   ; $00 = 1.00, $01 = 1.01, etc.
.ENDSNES

.SNESNATIVEVECTOR               ; Define Native Mode interrupt vector table
  COP EmptyHandler
  BRK EmptyHandler
  ABORT EmptyHandler
  NMI NMIHandler_
  IRQ EmptyHandler
.ENDNATIVEVECTOR

.SNESEMUVECTOR                  ; Define Emulation Mode interrupt vector table
  COP EmptyHandler
  ABORT EmptyHandler
  NMI EmptyHandler
  RESET Start_
  IRQBRK EmptyHandler
.ENDEMUVECTOR

.BANK 0 SLOT 0    ; Defines the ROM bank and the slot it is inserted in memory.
.ORG $0000
.SECTION "EmptyVectors" SEMIFREE

EmptyHandler:
        rti
.ENDS

.EMPTYFILL $00
