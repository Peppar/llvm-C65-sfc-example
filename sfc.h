//==============================================================================
//
// SFC registers
//
// Oskar Holstensson
//
//==============================================================================
#ifndef _SFC_H
#define _SFC_H

#include "types.h"

typedef volatile uint8_t SFC_REG_8;
typedef volatile uint16_t SFC_REG_16;
typedef struct __attribute__((packed)) _SFC_REG_24 {
  union {
    volatile uint16_t w;
    struct {
      volatile uint8_t l;
      volatile uint8_t m;
    };
  };
  volatile uint8_t h;
} SFC_REG_24;

//==============================================================================
// Bus B control registers
//==============================================================================
typedef volatile struct __attribute__((packed)) _SFC_B {
  SFC_REG_8 INIDISP;
  SFC_REG_8 OBSEL;
  SFC_REG_16 OAMADD;
  SFC_REG_8 OAMDATA;
  SFC_REG_8 BGMODE;
  SFC_REG_8 MOSAIC;
  SFC_REG_8 BG1SC;
  SFC_REG_8 BG2SC;
  SFC_REG_8 BG3SC;
  SFC_REG_8 BG4SC;
  SFC_REG_8 BG12NBA;
  SFC_REG_8 BG34NBA;
  union {
    SFC_REG_8 BG1HOFS;
    SFC_REG_8 M7HOFS;
  };
  union {
    SFC_REG_8 BG1VOFS;
    SFC_REG_8 M7VOFS;
  };
  SFC_REG_8 BG2HOFS;
  SFC_REG_8 BG2VOFS;
  SFC_REG_8 BG3HOFS;
  SFC_REG_8 BG3VOFS;
  SFC_REG_8 BG4HOFS;
  SFC_REG_8 BG4VOFS;
  SFC_REG_8 VMAIN;
  SFC_REG_16 VMADD;
  union {
    SFC_REG_16 VMDATA;
    struct {
      SFC_REG_8 VMDATAL;
      SFC_REG_8 VMDATAH;
    };
  };
  SFC_REG_8 M7SEL;
  SFC_REG_8 M7A;
  SFC_REG_8 M7B;
  SFC_REG_8 M7C;
  SFC_REG_8 M7D;
  SFC_REG_8 M7X;
  SFC_REG_8 M7Y;
  SFC_REG_8 CGADD;
  SFC_REG_8 CGDATA;
  SFC_REG_8 W12SEL;
  SFC_REG_8 W34SEL;
  SFC_REG_8 WOBJSEL;
  SFC_REG_8 WH0;
  SFC_REG_8 WH1;
  SFC_REG_8 WH2;
  SFC_REG_8 WH3;
  SFC_REG_8 WBGLOG;
  SFC_REG_8 WOBJLOG;
  SFC_REG_8 TM;
  SFC_REG_8 TS;
  SFC_REG_8 TMW;
  SFC_REG_8 TSW;
  SFC_REG_8 CGWSEL;
  SFC_REG_8 CGADSUB;
  SFC_REG_8 COLDATA;
  SFC_REG_8 SETINI;
  SFC_REG_24 MPY;
  SFC_REG_8 SLHV;
  SFC_REG_8 OAMDATAREAD;
  SFC_REG_16 VMDATAREAD;
  SFC_REG_8 CGDATAREAD;
  SFC_REG_8 OPHCT;
  SFC_REG_8 OPVCT;
  SFC_REG_8 STAT77;
  SFC_REG_8 STAT78;
  SFC_REG_8 APUIO0;
  SFC_REG_8 APUIO1;
  SFC_REG_8 APUIO2;
  SFC_REG_8 APUIO3;
  SFC_REG_8 Reserved[60];
  SFC_REG_8 WMDATA;
  SFC_REG_24 WMADD;
} SFC_B;

#define INIDISP_BRIGHTNESS     ((unsigned int) 0xF << 0)
#define INIDISP_BRIGHTNESS_MAX ((unsigned int) 0xF << 0)
#define INIDISP_BRIGHTNESS_OFF ((unsigned int) 0x0 << 0)
#define INIDISP_FORCEBLANK     ((unsigned int) 0x1 << 7)

#define OBSEL_NAMEBASE            ((unsigned int) 0x7 << 0)
#define OBSEL_NAMESEL             ((unsigned int) 0x3 << 3)
#define OBSEL_OBJSIZE             ((unsigned int) 0x7 << 5)
#define OBSEL_OBJSIZE_8x8_16x16   ((unsigned int) 0x0 << 5)
#define OBSEL_OBJSIZE_8x8_32x32   ((unsigned int) 0x1 << 5)
#define OBSEL_OBJSIZE_8x8_64x64   ((unsigned int) 0x2 << 5)
#define OBSEL_OBJSIZE_16x16_32x32 ((unsigned int) 0x3 << 5)
#define OBSEL_OBJSIZE_16x16_64x64 ((unsigned int) 0x4 << 5)
#define OBSEL_OBJSIZE_32x32_64x64 ((unsigned int) 0x5 << 5)
#define OBSEL_OBJSIZE_16x32_32x64 ((unsigned int) 0x6 << 5)
#define OBSEL_OBJSIZE_16x32_32x32 ((unsigned int) 0x7 << 5)

#define OAM_PRIOROT   ((unsigned int) 0x1   << 15)
#define OAM_PRIOROT_0 ((unsigned int) 0x0   << 15)
#define OAM_PRIOROT_N ((unsigned int) 0x1   << 15)
#define OAM_OBJNUM    ((unsigned int) 0x7F  <<  1)
#define OAM_ADD       ((unsigned int) 0x1FF <<  0)

#define BGMODE_MODE          ((unsigned int) 0x7 << 0)
#define BGMODE_MODE1BG3PRIO  ((unsigned int) 0x1 << 3)
#define BGMODE_CHSIZE1       ((unsigned int) 0x1 << 4)
#define BGMODE_CHSIZE1_8x8   ((unsigned int) 0x0 << 4)
#define BGMODE_CHSIZE1_16x16 ((unsigned int) 0x1 << 4)
#define BGMODE_CHSIZE2       ((unsigned int) 0x1 << 5)
#define BGMODE_CHSIZE2_8x8   ((unsigned int) 0x0 << 5)
#define BGMODE_CHSIZE2_16x16 ((unsigned int) 0x1 << 5)
#define BGMODE_CHSIZE3       ((unsigned int) 0x1 << 6)
#define BGMODE_CHSIZE3_8x8   ((unsigned int) 0x0 << 6)
#define BGMODE_CHSIZE3_16x16 ((unsigned int) 0x1 << 6)
#define BGMODE_CHSIZE4       ((unsigned int) 0x1 << 7)
#define BGMODE_CHSIZE4_8x8   ((unsigned int) 0x0 << 7)
#define BGMODE_CHSIZE4_16x16 ((unsigned int) 0x1 << 7)

#define MOSAIC_BG1       ((unsigned int) 0x1 << 0)
#define MOSAIC_BG1_1x1   ((unsigned int) 0x0 << 0)
#define MOSAIC_BG1_16x16 ((unsigned int) 0x1 << 0)
#define MOSAIC_BG2       ((unsigned int) 0x1 << 1)
#define MOSAIC_BG2_1x1   ((unsigned int) 0x0 << 1)
#define MOSAIC_BG2_16x16 ((unsigned int) 0x1 << 1)
#define MOSAIC_BG3       ((unsigned int) 0x1 << 2)
#define MOSAIC_BG3_1x1   ((unsigned int) 0x0 << 2)
#define MOSAIC_BG3_16x16 ((unsigned int) 0x1 << 2)
#define MOSAIC_BG4       ((unsigned int) 0x1 << 3)
#define MOSAIC_BG4_1x1   ((unsigned int) 0x0 << 3)
#define MOSAIC_BG4_16x16 ((unsigned int) 0x1 << 3)

#define BGSC_HMIRR ((unsigned int) 0x1  << 0)
#define BGSC_VMIRR ((unsigned int) 0x1  << 1)
#define BGSC_ADD   ((unsigned int) 0x3F << 2)

#define BG12NBA_ADD1 ((unsigned int) 0xF << 0)
#define BG12NBA_ADD2 ((unsigned int) 0xF << 4)
#define BG34NBA_ADD3 ((unsigned int) 0xF << 0)
#define BG34NBA_ADD4 ((unsigned int) 0xF << 4)

#define BGHOFS_HOFS ((unsigned int) 0x3FF  << 0)
#define BGVOFS_VOFS ((unsigned int) 0x3FF  << 0)
#define M7HOFS_HOFS ((unsigned int) 0x1FFF << 0)
#define M7VOFS_VOFS ((unsigned int) 0x1FFF << 0)

#define VMAIN_INCAMT       ((unsigned int) 0x3 << 0)
#define VMAIN_INCAMT_1     ((unsigned int) 0x0 << 0)
#define VMAIN_INCAMT_32    ((unsigned int) 0x1 << 0)
#define VMAIN_INCAMT_128   ((unsigned int) 0x2 << 0)
#define VMAIN_REMAP        ((unsigned int) 0x3 << 2)
#define VMAIN_REMAP_NONE   ((unsigned int) 0x0 << 2)
#define VMAIN_REMAP_1      ((unsigned int) 0x1 << 2)
#define VMAIN_REMAP_2      ((unsigned int) 0x2 << 2)
#define VMAIN_REMAP_3      ((unsigned int) 0x3 << 2)
#define VMAIN_INCMODE      ((unsigned int) 0x1 << 7)
#define VMAIN_INCMODE_LOW  ((unsigned int) 0x0 << 7)
#define VMAIN_INCMODE_HIGH ((unsigned int) 0x1 << 7)

#define M7SEL_VMIRR            ((unsigned int) 0x1 << 0)
#define M7SEL_VMIRR_NONE       ((unsigned int) 0x0 << 0)
#define M7SEL_VMIRR_MIRR       ((unsigned int) 0x1 << 0)
#define M7SEL_HMIRR            ((unsigned int) 0x1 << 1)
#define M7SEL_HMIRR_NONE       ((unsigned int) 0x0 << 1)
#define M7SEL_HMIRR_MIRR       ((unsigned int) 0x1 << 1)
#define M7SEL_EMPTYFILL        ((unsigned int) 0x1 << 6)
#define M7SEL_EMPTYFILL_NONE   ((unsigned int) 0x0 << 6)
#define M7SEL_EMPTYFILL_CHAR0  ((unsigned int) 0x1 << 6)
#define M7SEL_FIELDSIZE        ((unsigned int) 0x1 << 7)
#define M7SEL_FIELDSIZE_NORMAL ((unsigned int) 0x0 << 7)
#define M7SEL_FIELDSIZE_LARGE  ((unsigned int) 0x1 << 7)

#define W12SEL_BG1_WIN1_INV ((unsigned int) 0x1 << 0)
#define W12SEL_BG1_WIN1_EN  ((unsigned int) 0x1 << 1)
#define W12SEL_BG1_WIN2_INV ((unsigned int) 0x1 << 2)
#define W12SEL_BG1_WIN2_EN  ((unsigned int) 0x1 << 3)
#define W12SEL_BG2_WIN1_INV ((unsigned int) 0x1 << 4)
#define W12SEL_BG2_WIN1_EN  ((unsigned int) 0x1 << 5)
#define W12SEL_BG2_WIN2_INV ((unsigned int) 0x1 << 6)
#define W12SEL_BG2_WIN2_EN  ((unsigned int) 0x1 << 7)

#define W34SEL_BG3_WIN1_INV ((unsigned int) 0x1 << 0)
#define W34SEL_BG3_WIN1_EN  ((unsigned int) 0x1 << 1)
#define W34SEL_BG3_WIN2_INV ((unsigned int) 0x1 << 2)
#define W34SEL_BG3_WIN2_EN  ((unsigned int) 0x1 << 3)
#define W34SEL_BG4_WIN1_INV ((unsigned int) 0x1 << 4)
#define W34SEL_BG4_WIN1_EN  ((unsigned int) 0x1 << 5)
#define W34SEL_BG4_WIN2_INV ((unsigned int) 0x1 << 6)
#define W34SEL_BG4_WIN2_EN  ((unsigned int) 0x1 << 7)

#define WOBJSEL_OBJ_WIN1_INV   ((unsigned int) 0x1 << 0)
#define WOBJSEL_OBJ_WIN1_EN    ((unsigned int) 0x1 << 1)
#define WOBJSEL_OBJ_WIN2_INV   ((unsigned int) 0x1 << 2)
#define WOBJSEL_OBJ_WIN2_EN    ((unsigned int) 0x1 << 3)
#define WOBJSEL_COLOR_WIN1_INV ((unsigned int) 0x1 << 4)
#define WOBJSEL_COLOR_WIN1_EN  ((unsigned int) 0x1 << 5)
#define WOBJSEL_COLOR_WIN2_INV ((unsigned int) 0x1 << 6)
#define WOBJSEL_COLOR_WIN2_EN  ((unsigned int) 0x1 << 7)

#define WBGLOG_BG1      ((unsigned int) 0x3 << 0)
#define WBGLOG_BG1_OR   ((unsigned int) 0x0 << 0)
#define WBGLOG_BG1_AND  ((unsigned int) 0x1 << 0)
#define WBGLOG_BG1_XOR  ((unsigned int) 0x2 << 0)
#define WBGLOG_BG1_XNOR ((unsigned int) 0x3 << 0)
#define WBGLOG_BG2      ((unsigned int) 0x3 << 2)
#define WBGLOG_BG2_OR   ((unsigned int) 0x0 << 2)
#define WBGLOG_BG2_AND  ((unsigned int) 0x1 << 2)
#define WBGLOG_BG2_XOR  ((unsigned int) 0x2 << 2)
#define WBGLOG_BG2_XNOR ((unsigned int) 0x3 << 2)
#define WBGLOG_BG3      ((unsigned int) 0x3 << 4)
#define WBGLOG_BG3_OR   ((unsigned int) 0x0 << 4)
#define WBGLOG_BG3_AND  ((unsigned int) 0x1 << 4)
#define WBGLOG_BG3_XOR  ((unsigned int) 0x2 << 4)
#define WBGLOG_BG3_XNOR ((unsigned int) 0x3 << 4)
#define WBGLOG_BG4      ((unsigned int) 0x3 << 6)
#define WBGLOG_BG4_OR   ((unsigned int) 0x0 << 6)
#define WBGLOG_BG4_AND  ((unsigned int) 0x1 << 6)
#define WBGLOG_BG4_XOR  ((unsigned int) 0x2 << 6)
#define WBGLOG_BG4_XNOR ((unsigned int) 0x3 << 6)

#define WOBJLOG_OBJ        ((unsigned int) 0x3 << 0)
#define WOBJLOG_OBJ_OR     ((unsigned int) 0x0 << 0)
#define WOBJLOG_OBJ_AND    ((unsigned int) 0x1 << 0)
#define WOBJLOG_OBJ_XOR    ((unsigned int) 0x2 << 0)
#define WOBJLOG_OBJ_XNOR   ((unsigned int) 0x3 << 0)
#define WOBJLOG_COLOR      ((unsigned int) 0x3 << 2)
#define WOBJLOG_COLOR_OR   ((unsigned int) 0x0 << 2)
#define WOBJLOG_COLOR_AND  ((unsigned int) 0x1 << 2)
#define WOBJLOG_COLOR_XOR  ((unsigned int) 0x2 << 2)
#define WOBJLOG_COLOR_XNOR ((unsigned int) 0x3 << 2)

#define TM_BG1 ((unsigned int) 0x1 << 0)
#define TM_BG2 ((unsigned int) 0x1 << 1)
#define TM_BG3 ((unsigned int) 0x1 << 2)
#define TM_BG4 ((unsigned int) 0x1 << 3)
#define TM_OBJ ((unsigned int) 0x1 << 4)

#define TS_BG1 ((unsigned int) 0x1 << 0)
#define TS_BG2 ((unsigned int) 0x1 << 1)
#define TS_BG3 ((unsigned int) 0x1 << 2)
#define TS_BG4 ((unsigned int) 0x1 << 3)
#define TS_OBJ ((unsigned int) 0x1 << 4)

#define TMW_BG1 ((unsigned int) 0x1 << 0)
#define TMW_BG2 ((unsigned int) 0x1 << 1)
#define TMW_BG3 ((unsigned int) 0x1 << 2)
#define TMW_BG4 ((unsigned int) 0x1 << 3)
#define TMW_OBJ ((unsigned int) 0x1 << 4)

#define TSW_BG1 ((unsigned int) 0x1 << 0)
#define TSW_BG2 ((unsigned int) 0x1 << 1)
#define TSW_BG3 ((unsigned int) 0x1 << 2)
#define TSW_BG4 ((unsigned int) 0x1 << 3)
#define TSW_OBJ ((unsigned int) 0x1 << 4)

#define CGWSEL_DIRECT         ((unsigned int) 0x1 << 0)
#define CGWSEL_ADDSS          ((unsigned int) 0x1 << 1)
#define CGWSEL_NOMATH         ((unsigned int) 0x3 << 4)
#define CGWSEL_NOMATH_NEVER   ((unsigned int) 0x0 << 4)
#define CGWSEL_NOMATH_OUTSIDE ((unsigned int) 0x1 << 4)
#define CGWSEL_NOMATH_INSIDE  ((unsigned int) 0x2 << 4)
#define CGWSEL_NOMATH_ALWAYS  ((unsigned int) 0x3 << 4)
#define CGWSEL_CLIP           ((unsigned int) 0x3 << 6)
#define CGWSEL_CLIP_NEVER     ((unsigned int) 0x0 << 6)
#define CGWSEL_CLIP_OUTSIDE   ((unsigned int) 0x1 << 6)
#define CGWSEL_CLIP_INSIDE    ((unsigned int) 0x2 << 6)
#define CGWSEL_CLIP_ALWAYS    ((unsigned int) 0x3 << 6)

#define CGADSUB_BG1       ((unsigned int) 0x1 << 0)
#define CGADSUB_BG2       ((unsigned int) 0x1 << 1)
#define CGADSUB_BG3       ((unsigned int) 0x1 << 2)
#define CGADSUB_BG4       ((unsigned int) 0x1 << 3)
#define CGADSUB_OBJ       ((unsigned int) 0x1 << 4)
#define CGADSUB_BACKDROP  ((unsigned int) 0x1 << 5)
#define CGADSUB_HALF      ((unsigned int) 0x1 << 6)
#define CGADSUB_ADSUB     ((unsigned int) 0x1 << 7)
#define CGADSUB_ADSUB_ADD ((unsigned int) 0x0 << 7)
#define CGADSUB_ADSUB_SUB ((unsigned int) 0x1 << 7)

#define COLDATA_INTENSITY ((unsigned int) 0x1F << 0)
#define COLDATA_SET_RED   ((unsigned int) 0x1  << 5)
#define COLDATA_SET_GREEN ((unsigned int) 0x1  << 6)
#define COLDATA_SET_BLUE  ((unsigned int) 0x1  << 7)

#define SETINI_SCREENINTERLACE ((unsigned int) 0x1 << 0)
#define SETINI_OBJINTERLACE    ((unsigned int) 0x1 << 1)
#define SETINI_OVERSCAN        ((unsigned int) 0x1 << 2)
#define SETINI_PSEUDOHIRES     ((unsigned int) 0x1 << 3)
#define SETINI_EXTRABG         ((unsigned int) 0x1 << 6)
#define SETINI_EXTERNALSYNC    ((unsigned int) 0x1 << 7)

#define COLOR(R, G, B) \
  ((uint16_t)(R & 0x1F | (G & 0x1F) << 5 | (B & 0x1F) << 10))

#define CG_RED   ((unsigned int) 0x1F << 0)
#define CG_GREEN ((unsigned int) 0x1F << 5)
#define CG_BLUE  ((unsigned int) 0x1F << 10)

#define OPHCT_HLOC ((unsigned int) 0x1FF << 0)
#define OPVCT_VLOC ((unsigned int) 0x1FF << 0)

#define STAT77_5C77_VERSION       ((unsigned int) 0xF << 0)
#define STAT77_MASTERSLAVE        ((unsigned int) 0x1 << 5)
#define STAT77_MASTERSLAVE_MASTER ((unsigned int) 0x0 << 5)
#define STAT77_MASTERSLAVE_SLAVE  ((unsigned int) 0x1 << 5)
#define STAT77_OBJRANGEOVERFLOW   ((unsigned int) 0x1 << 6)
#define STAT77_OBJTIMEOVERFLOW    ((unsigned int) 0x1 << 7)

#define STAT78_5C78_VERSION   ((unsigned int) 0xF << 0)
#define STAT78_FRAMERATE      ((unsigned int) 0x1 << 4)
#define STAT78_FRAMERATE_60Hz ((unsigned int) 0x0 << 4)
#define STAT78_FRAMERATE_50Hz ((unsigned int) 0x1 << 4)
#define STAT78_LATCH          ((unsigned int) 0x1 << 6)
#define STAT78_INTERLAVE      ((unsigned int) 0x1 << 7)

#define WMADD_ADD ((unsigned int) 0x1FFFF << 0)

#define TILE(C, P, O, H, V) \
  ((uint16_t)(C & 0x3FF | (P & 0x7) << 10 | (O & 0x1) << 13) \
   | (H & 0x1) << 14 | (V & 0x1) << 15)

#define TILE_NUMBER   ((unsigned int) 0x3FF << 0)
#define TILE_PALETTE  ((unsigned int) 0x7 << 10)
#define TILE_PRIORITY ((unsigned int) 0x1 << 13)
#define TILE_HFLIP    ((unsigned int) 0x1 << 14)
#define TILE_VFLIP    ((unsigned int) 0x1 << 15)

//==============================================================================
// Joypad direct read/write registers
//==============================================================================
typedef volatile struct __attribute__((packed)) _SFC_JOY {
  SFC_REG_8 JOYSER0;
  SFC_REG_8 JOYSER1;
} SFC_JOY;

#define JOYSER_CLK   ((unsigned int) 0x1 << 0)
#define JOYSER_DATA1 ((unsigned int) 0x1 << 0)
#define JOYSER_DATA2 ((unsigned int) 0x1 << 1)

//==============================================================================
// Internal CPU control registers
//==============================================================================
typedef volatile struct __attribute__((packed)) _SFC_CTRL {
  SFC_REG_8 NMITIMEN;
  SFC_REG_8 WRIO;
  SFC_REG_8 WRMPYA;
  SFC_REG_8 WRMPYB;
  SFC_REG_16 WRDIV;
  SFC_REG_8 WRDIVB;
  SFC_REG_16 HTIME;
  SFC_REG_16 VTIME;
  SFC_REG_8 MDMAEN;
  SFC_REG_8 HDMAEN;
  SFC_REG_8 MEMSEL;
  SFC_REG_8 Reserved[2];
  SFC_REG_8 RDNMI;
  SFC_REG_8 TIMEUP;
  SFC_REG_8 HVBJOY;
  SFC_REG_8 RDIO;
  SFC_REG_16 RDDIV;
  SFC_REG_16 RDMPY;
  SFC_REG_16 JOY[4];
} SFC_CTRL;

#define NMITIMEN_AUTOJOY         ((unsigned int) 0x1 << 0)
#define NMITIMEN_AUTOJOY_DISABLE ((unsigned int) 0x0 << 0)
#define NMITIMEN_AUTOJOY_ENABLE  ((unsigned int) 0x1 << 0)
#define NMITIMEN_IRQ             ((unsigned int) 0x3 << 4)
#define NMITIMEN_IRQ_DISABLE     ((unsigned int) 0x0 << 4)
#define NMITIMEN_IRQ_HTRIG       ((unsigned int) 0x1 << 4)
#define NMITIMEN_IRQ_VTRIG       ((unsigned int) 0x2 << 4)
#define NMITIMEN_IRQ_HVTRIG      ((unsigned int) 0x3 << 4)
#define NMITIMEN_VBLANK          ((unsigned int) 0x1 << 7)
#define NMITIMEN_VBLANK_DISABLE  ((unsigned int) 0x0 << 7)
#define NMITIMEN_VBLANK_ENABLE   ((unsigned int) 0x1 << 7)

#define WRIO_B ((unsigned int) 0x1 << 6)
#define WRIO_A ((unsigned int) 0x1 << 7)

#define HTIME_HCMP ((unsigned int) 0x1FF << 0)

#define VTIME_VCMP ((unsigned int) 0x1FF << 0)

#define MDMAEN_DMA0 ((unsigned int) 0x1 << 0)
#define MDMAEN_DMA1 ((unsigned int) 0x1 << 1)
#define MDMAEN_DMA2 ((unsigned int) 0x1 << 2)
#define MDMAEN_DMA3 ((unsigned int) 0x1 << 3)
#define MDMAEN_DMA4 ((unsigned int) 0x1 << 4)
#define MDMAEN_DMA5 ((unsigned int) 0x1 << 5)
#define MDMAEN_DMA6 ((unsigned int) 0x1 << 6)
#define MDMAEN_DMA7 ((unsigned int) 0x1 << 7)

#define HDMAEN_HDMA0 ((unsigned int) 0x1 << 0)
#define HDMAEN_HDMA1 ((unsigned int) 0x1 << 1)
#define HDMAEN_HDMA2 ((unsigned int) 0x1 << 2)
#define HDMAEN_HDMA3 ((unsigned int) 0x1 << 3)
#define HDMAEN_HDMA4 ((unsigned int) 0x1 << 4)
#define HDMAEN_HDMA5 ((unsigned int) 0x1 << 5)
#define HDMAEN_HDMA6 ((unsigned int) 0x1 << 6)
#define HDMAEN_HDMA7 ((unsigned int) 0x1 << 7)

#define MEMSEL_SLOW ((unsigned int) 0x0 << 0) // SlowROM (Default)
#define MEMSEL_FAST ((unsigned int) 0x1 << 0) // FastROM

#define RDNMI_5A22_VERSION ((unsigned int) 0xF << 0)
#define RDNMI_VBLANK_IRQ   ((unsigned int) 0x1 << 7)

#define TIMEUP_IRQ ((unsigned int) 0x1 << 7)

#define HVBJOY_AUTOJOYSTATUS ((unsigned int) 0x1 << 0)
#define HVBJOY_HBLANK        ((unsigned int) 0x1 << 6)
#define HVBJOY_VBLANK        ((unsigned int) 0x1 << 7)

#define RDIO_B ((unsigned int) 0x1 << 6)
#define RDIO_A ((unsigned int) 0x1 << 7)

#define JOY_R      ((unsigned int) 0x1 <<  4)
#define JOY_L      ((unsigned int) 0x1 <<  5)
#define JOY_X      ((unsigned int) 0x1 <<  6)
#define JOY_A      ((unsigned int) 0x1 <<  7)
#define JOY_RIGHT  ((unsigned int) 0x1 <<  8)
#define JOY_LEFT   ((unsigned int) 0x1 <<  9)
#define JOY_DOWN   ((unsigned int) 0x1 << 10)
#define JOY_UP     ((unsigned int) 0x1 << 11)
#define JOY_START  ((unsigned int) 0x1 << 12)
#define JOY_SELECT ((unsigned int) 0x1 << 13)
#define JOY_Y      ((unsigned int) 0x1 << 14)
#define JOY_B      ((unsigned int) 0x1 << 15)

//==============================================================================
// MDMA and HDMA channel registers
//==============================================================================
// Per-MDMA registers
typedef volatile struct __attribute__((packed)) _SFC_MDMA {
  SFC_REG_8 MDMAP;
  SFC_REG_8 BBAD;
  SFC_REG_24 ABAD;
  SFC_REG_16 COUNT;
  SFC_REG_8 Reserved[9];
} SFC_MDMA;

// Per-HDMA registers
typedef volatile struct __attribute__((packed)) _SFC_HDMA {
  SFC_REG_8 HDMAP;
  SFC_REG_8 BBAD;
  SFC_REG_24 TABAD;
  SFC_REG_24 DIRAD;
  SFC_REG_16 CURAD;
  SFC_REG_8 NTLR;
  SFC_REG_8 Reserved[5];
} SFC_HDMA;

// (M/H)DMA channel union
typedef volatile union __attribute__((packed)) _SFC_DMA {
  SFC_MDMA MDMA[8];
  SFC_HDMA HDMA[8];
} SFC_DMA;

#define DMAP_MODE             ((unsigned int) 0x7 << 0)
#define DMAP_MODE_A0          ((unsigned int) 0x0 << 0)
#define DMAP_MODE_A0_A1       ((unsigned int) 0x1 << 0)
#define DMAP_MODE_A0_A0       ((unsigned int) 0x2 << 0)
#define DMAP_MODE_A0_A0_A1_A1 ((unsigned int) 0x3 << 0)
#define DMAP_MODE_A0_A1_A2_A3 ((unsigned int) 0x4 << 0)
#define DMAP_MODE_A0_A1_A0_A1 ((unsigned int) 0x5 << 0)

#define DMAP_DIRECTION    ((unsigned int) 0x1 << 7)
#define DMAP_DIRECTION_AB ((unsigned int) 0x0 << 7)
#define DMAP_DIRECTION_BA ((unsigned int) 0x1 << 7)

#define MDMAP_ADDINC       ((unsigned int) 0x3 << 3)
#define MDMAP_ADDINC_INC   ((unsigned int) 0x0 << 3)
#define MDMAP_ADDINC_FIXED ((unsigned int) 0x1 << 3)
#define MDMAP_ADDINC_DEC   ((unsigned int) 0x2 << 3)

#define HDMAP_ADDMODE          ((unsigned int) 0x1 << 6)
#define HDMAP_ADDMODE_DIRECT   ((unsigned int) 0x0 << 6)
#define HDMAP_ADDMODE_INDIRECT ((unsigned int) 0x1 << 6)

#define HDMA_NTLR_LINECOUNT ((unsigned int) 0x7F << 0)
#define HDMA_NTLR_REPEAT    ((unsigned int) 0x1  << 7)

//==============================================================================
// SFC address definitions
//==============================================================================
#define SFC_BASE_B    ((SFC_B *)    0x2100)
#define SFC_BASE_JOY  ((SFC_JOY *)  0x4016)
#define SFC_BASE_CTRL ((SFC_CTRL *) 0x4200)
#define SFC_BASE_DMA  ((SFC_DMA *)  0x4300)

#define OFFSETOF(TYPE, FIELD) ((uint16_t) &((TYPE *)0)->FIELD)

void FarPoke8(uint32_t Addr, uint8_t X);
void FarPoke16(uint32_t Addr, uint16_t X);
uint8_t FarPeek8(uint32_t Addr);
uint16_t FarPeek16(uint32_t Addr);
uint32_t FarPeek32(uint32_t Addr);
uint64_t FarPeek64(uint32_t Addr);
void MemCopy(uint32_t Dest, uint32_t Src, uint16_t Count);

#endif // _SFC_H
