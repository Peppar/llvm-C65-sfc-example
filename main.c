////////////////////////////////////////////////////////////////////////
//
// Example for the clang/llvm 65816 backend
//
// By Oskar Holstensson
//
////////////////////////////////////////////////////////////////////////
#include "sfc.h"

static void InitLoadCG(uint8_t Ch, const uint8_t *Source, uint8_t Dest,
                       uint16_t Count, uint8_t Fixed) {
  SFC_MDMA *MDMA = &SFC_BASE_DMA->MDMA[Ch];

  // Setup color graphics address
  SFC_BASE_B->CGADD = Dest;

  // Setup MDMA
  if (Fixed)
    MDMA->MDMAP = DMAP_MODE_A0 | DMAP_DIRECTION_AB | MDMAP_ADDINC_FIXED;
  else
    MDMA->MDMAP = DMAP_MODE_A0 | DMAP_DIRECTION_AB | MDMAP_ADDINC_INC;
  MDMA->BBAD = 0x22; // CGDATA
  MDMA->ABAD.w = (uint16_t)Source;
  MDMA->ABAD.h = 0x00;
  MDMA->COUNT = Count;
}

static void InitLoadGraphics(uint8_t Ch, const uint8_t *Source, uint16_t Dest,
                             uint16_t Count, uint8_t Fixed) {
  SFC_MDMA *MDMA = &SFC_BASE_DMA->MDMA[Ch];

  // Set video memory addressing mode and address
  SFC_BASE_B->VMAIN = VMAIN_INCAMT_1 | VMAIN_REMAP_NONE | VMAIN_INCMODE_HIGH;
  SFC_BASE_B->VMADD = Dest;

  // Setup MDMA
  if (Fixed)
    MDMA->MDMAP = DMAP_MODE_A0_A1 | DMAP_DIRECTION_AB | MDMAP_ADDINC_FIXED;
  else
    MDMA->MDMAP = DMAP_MODE_A0_A1 | DMAP_DIRECTION_AB | MDMAP_ADDINC_INC;
  MDMA->BBAD = 0x18; // VMDATA
  MDMA->ABAD.w = (uint16_t)Source;
  MDMA->ABAD.h = 0x00;
  MDMA->COUNT = Count;
}

static void WriteSerReg16(volatile SFC_REG_8 *Reg, uint16_t Data) {
  *Reg = (uint8_t)(Data & 0xFF);
  *Reg = (uint8_t)(Data >> 8);
}

static void ResetSfcMemories() {
  const uint8_t Zero = 0;

  // Initialize VRAM and CGRAM to all zeroes
  InitLoadGraphics(0, &Zero, 0x0000, 0x0000, 1);
  InitLoadCG(1, &Zero, 0x00, 0x400, 1);
  SFC_BASE_CTRL->MDMAEN = MDMAEN_DMA0 | MDMAEN_DMA1;
}

static void ResetSfcRegisters() {
  SFC_BASE_B->INIDISP = INIDISP_FORCEBLANK | INIDISP_BRIGHTNESS_MAX;
  SFC_BASE_B->OBSEL = OBSEL_OBJSIZE_8x8_16x16;
  SFC_BASE_B->OAMADD = 0x0000;
  SFC_BASE_B->BGMODE =
      BGMODE_CHSIZE1_8x8 | BGMODE_CHSIZE2_8x8
    | BGMODE_CHSIZE3_8x8 | BGMODE_CHSIZE4_8x8;
  SFC_BASE_B->MOSAIC =
      MOSAIC_BG1_1x1 | MOSAIC_BG2_1x1
    | MOSAIC_BG3_1x1 | MOSAIC_BG4_1x1;
  SFC_BASE_B->BG1SC = 0;
  SFC_BASE_B->BG2SC = 0;
  SFC_BASE_B->BG3SC = 0;
  SFC_BASE_B->BG4SC = 0;
  SFC_BASE_B->BG12NBA = 0;
  SFC_BASE_B->BG34NBA = 0;

  SFC_BASE_B->BG1HOFS = 0;
  SFC_BASE_B->BG1HOFS = 0;
  SFC_BASE_B->BG1VOFS = 0;
  SFC_BASE_B->BG1VOFS = 0;
  SFC_BASE_B->BG2HOFS = 0;
  SFC_BASE_B->BG2HOFS = 0;
  SFC_BASE_B->BG2VOFS = 0;
  SFC_BASE_B->BG2VOFS = 0;
  SFC_BASE_B->BG3HOFS = 0;
  SFC_BASE_B->BG3HOFS = 0;
  SFC_BASE_B->BG3VOFS = 0;
  SFC_BASE_B->BG4HOFS = 0;
  SFC_BASE_B->BG4HOFS = 0;
  SFC_BASE_B->BG4VOFS = 0;
  SFC_BASE_B->BG4VOFS = 0;

  SFC_BASE_B->VMAIN = VMAIN_INCAMT_1 | VMAIN_REMAP_NONE
    | VMAIN_INCMODE_HIGH;
  SFC_BASE_B->VMADD = 0x0000;

  SFC_BASE_B->M7SEL =
      M7SEL_VMIRR_NONE | M7SEL_HMIRR_NONE
    | M7SEL_EMPTYFILL_NONE | M7SEL_FIELDSIZE_NORMAL;
  SFC_BASE_B->M7A = 0;
  SFC_BASE_B->M7B = 0;
  SFC_BASE_B->M7C = 0;
  SFC_BASE_B->M7D = 0;
  SFC_BASE_B->M7X = 0;
  SFC_BASE_B->M7Y = 0;

  SFC_BASE_B->W12SEL = 0;
  SFC_BASE_B->W34SEL = 0;
  SFC_BASE_B->WOBJSEL = 0;
  SFC_BASE_B->WH0 = 0;
  SFC_BASE_B->WH1 = 0;
  SFC_BASE_B->WH2 = 0;
  SFC_BASE_B->WH3 = 0;
  SFC_BASE_B->WBGLOG = 0;
  SFC_BASE_B->WOBJLOG = 0;
  SFC_BASE_B->TM = 0;
  SFC_BASE_B->TS = 0;
  SFC_BASE_B->TMW = 0;
  SFC_BASE_B->TSW = 0;
  SFC_BASE_B->CGWSEL = CGWSEL_NOMATH_NEVER | CGWSEL_CLIP_NEVER;
  SFC_BASE_B->CGADSUB = 0;
  SFC_BASE_B->SETINI = 0;

  SFC_BASE_B->STAT77 = STAT77_MASTERSLAVE_MASTER;

  SFC_BASE_CTRL->NMITIMEN = 0;
  SFC_BASE_CTRL->WRIO = 0xFF;
  SFC_BASE_CTRL->MDMAEN = 0;
  SFC_BASE_CTRL->HDMAEN = 0;
  SFC_BASE_CTRL->MEMSEL = MEMSEL_FAST;
  SFC_BASE_CTRL->RDNMI;
}

// Global variables
//
// For now, these need to be defined in main.asm.
extern volatile uint16_t PrevJoy1;
extern volatile uint16_t PrevJoy2;
extern volatile uint16_t Color;

// Initialize
//
// Initialization routine called after reset.
void Initialize() {
  ResetSfcMemories();
  ResetSfcRegisters();

  // Force blank screen display.
  SFC_BASE_B->INIDISP = INIDISP_FORCEBLANK | INIDISP_BRIGHTNESS_OFF;

  // Set initial color to white.
  Color = 0x7FFF;

  // Write green to color data.
  WriteSerReg16(&SFC_BASE_B->CGDATA, Color);

  // Turn on screen display.
  SFC_BASE_B->INIDISP = INIDISP_BRIGHTNESS_MAX;

  // Enable NMI at VBLANK, IRQ and auto joypad read.
  SFC_BASE_CTRL->NMITIMEN = NMITIMEN_VBLANK_ENABLE
    | NMITIMEN_IRQ_VTRIG | NMITIMEN_AUTOJOY_ENABLE;
}

// NMIHandler
//
// Interrupt routine called at the beginning of the VBLANK phase.
// Do not perform any heavy computation here, leave that to Frame.
void NMIHandler() {
  // Write to address 0x00.
  SFC_BASE_B->CGADD = 0x00;

  // Write the color to the color data.
  WriteSerReg16(&SFC_BASE_B->CGDATA, Color);
}

// Frame
//
// Called at most once every frame. If this function runs for too long,
// the following frame will not trigger a call to this function.
// VBlank will be called as usual, preempting this function for the duration
// of the interrupt.
void Frame() {
  while (SFC_BASE_CTRL->HVBJOY & HVBJOY_AUTOJOYSTATUS)
    /* no-op */ ;

  uint16_t Joy1 = SFC_BASE_CTRL->JOY[0];
  uint16_t Joy2 = SFC_BASE_CTRL->JOY[1];
  uint16_t Joy1Diff = Joy1 & ~PrevJoy1;
  uint16_t Joy2Diff = Joy2 & ~PrevJoy2;
  PrevJoy1 = Joy1;
  PrevJoy2 = Joy2;

  // The buttons change the background color.
  if(Joy1Diff & JOY_B) {
    Color = 0x03FF;
  }
  if(Joy1Diff & JOY_A) {
    Color = 0x001F;
  }
  if(Joy1Diff & JOY_Y) {
    Color = 0x03E0;
  }
  if(Joy1Diff & JOY_X) {
    Color = 0x7C00;
  }
}
