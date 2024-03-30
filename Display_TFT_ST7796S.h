#ifndef _DISPLAY_TFT_ST7796S_
#define _DISPLAY_TFT_ST7796S_

// Display_TFT_ST7796S
// _DISPLAY_TFT_ST7796S_
// ST7796S

#include "Adafruit_GFX.h"
#include "Arduino.h"
#include "Print.h"
#include <Adafruit_SPITFT.h>
#include <SPI.h>

#define ST7796S_TFTWIDTH 320  ///< ST7796S max TFT width
#define ST7796S_TFTHEIGHT 480 ///< ST7796S max TFT height

#define ST7796S_NOP 0x00     ///< No-op register
#define ST7796S_SWRESET 0x01 ///< Software reset register
#define ST7796S_RDDID 0x04   ///< Read display identification information
#define ST7796S_RDDST 0x09   ///< Read Display Status

#define ST7796S_SLPIN 0x10  ///< Sleep Mode IN
#define ST7796S_SLPOUT 0x11 ///< Sleep Mode Out
#define ST7796S_PTLON 0x12  ///< Partial Mode ON
#define ST7796S_NORON 0x13  ///< Normal Display Mode ON

#define ST7796S_RDMODE 0x0A     ///< Read Display Power Mode
#define ST7796S_RDMADCTL 0x0B   ///< Read Display MADCTL
#define ST7796S_RDPIXFMT 0x0C   ///< Read Display Pixel Format
#define ST7796S_RDIMGFMT 0x0D   ///< Read Display Image Format
#define ST7796S_RDDSM 0x0E      ///< Read Display Signal Mode (No estava)
#define ST7796S_RDSELFDIAG 0x0F ///< Read Display Self-Diagnostic Result

#define ST7796S_INVOFF 0x20   ///< Display Inversion OFF
#define ST7796S_INVON 0x21    ///< Display Inversion ON
#define ST7796S_GAMMASET 0x26 ///< Gamma Set (NO admet ST7796S)
#define ST7796S_DISPOFF 0x28  ///< Display OFF
#define ST7796S_DISPON 0x29   ///< Display ON

#define ST7796S_CASET 0x2A    ///< Column Address Set
// #define ST7796S_PASET 0x2B ///< Page Address Set (CHANGED)
#define ST7796S_RASET 0x2B    ///< Raw Address Set (RASET (2Bh) in ST7796S)
#define ST7796S_RAMWR 0x2C    ///< Memory Write
#define ST7796S_RAMRD 0x2E    ///< Memory Read

#define ST7796S_PTLAR 0x30    ///< Partial Area
#define ST7796S_VSCRDEF 0x33  ///< Vertical Scrolling Definition
#define ST7796_TEOFF 0x34     ///< Tearing Effect Line OFF (NO estava)
#define ST7796_TEON 0x35      ///< Tearing Effect Line ON (NO estava)
#define ST7796S_MADCTL 0x36   ///< Memory Access Control
#define ST7796S_VSCRSADD 0x37 ///< Vertical Scrolling Start Address
// IDMOFF (38h): Idle Mode OFF (NO estava)
// IDMON (39h): Idle mode ON (NO estava)
#define ST7796S_PIXFMT 0x3A   ///< COLMOD: Pixel Format Set
// WRMEMC (3Ch): Write Memory Continue (NO estava)
// RDMEMC (3Eh): Read Memory Continue (NO estava)

// STE (44h): Set Tear Scanline (NO estava)
// GSCAN (45h): Get Scanline (NO estava)

// WRDISBV (51h): Write Display Brightness (NO estava)
// RDDISBV (52h): Read Display Brightness Value (NO estava)
// WRCTRLD (53h): Write CTRL Display (NO estava)
// RDCTRLD (54h): Read CTRL value Display (NO estava)
// WRCABC (55h): Write Adaptive Brightness Control (NO estava)
// RDCABC (56h): Read Content Adaptive Brightness Control (NO estava)
// WRCABCMB (5Eh): Write CABC Minimum Brightness (NO estava)
// RDCABCMB (5Fh): Read CABC Minimum Brightness (NO estava)

// RDFCS (Aah): Read First Checksum (NO estava)
// RDCFCS (Afh): Read Continue Checksum (NO estava)

// IFMODE (B0h): Interface Mode Control (NO estava)
#define ST7796S_FRMCTR1 0xB1 ///< Frame Rate Control (In Normal Mode/Full Colors)
#define ST7796S_FRMCTR2 0xB2 ///< Frame Rate Control (In Idle Mode/8 colors)
#define ST7796S_FRMCTR3 0xB3 ///< Frame Rate control (In Partial Mode/Full Colors)
#define ST7796S_INVCTR 0xB4  ///< Display Inversion Control
// BPC(B5): Blanking Porch Control (NO estava)
#define ST7796S_DFUNCTR 0xB6 ///< Display Function Control
// EM(B7): Entry Mode Set (NO estava)

#define ST7796S_PWCTR1 0xC0 ///< Power Control 1
#define ST7796S_PWCTR2 0xC1 ///< Power Control 2
#define ST7796S_PWCTR3 0xC2 ///< Power Control 3
// #define ST7796S_PWCTR4 0xC3 ///< Power Control 4 (NO admet ST7796S)
// #define ST7796S_PWCTR5 0xC4 ///< Power Control 5 (NO admet ST7796S)
// VCMPCTL(C5h): VCOM Control (NO estava)
#define ST7796S_VMCTR1 0xC5 ///< VCOM Control 1
// VCM Offset (C6h): Vcom Offset Register (NO estava)
#define ST7796S_VMCTR2 0xC7 ///< VCOM Control 2 (NO admet ST7796S)

// NVMADW (D0h): NVM Address/Data Write (NO estava)
// NVMBPROG (D1h): NVM Byte Program (NO estava)
// NVM Status Read(D2h) (NO estava)
// RDID4 (D3h): Read ID4 (NO estava)
// #define ST7796S_RDID1 0xDA ///< Read ID 1 (NO admet ST7796S)
// #define ST7796S_RDID2 0xDB ///< Read ID 2 (NO admet ST7796S)
// #define ST7796S_RDID3 0xDC ///< Read ID 3 (NO admet ST7796S)
// #define ST7796S_RDID4 0xDD ///< Read ID 4 (NO admet ST7796S)

#define ST7796S_GMCTRP1 0xE0 ///< Positive Gamma Correction
#define ST7796S_GMCTRN1 0xE1 ///< Negative Gamma Correction
// DGC1(E2h): Digital Gamma Control 1 (NO estava)
// DGC2 (E3h): Digital Gamma Control 2 (NO estava)
// DOCA (E8h): Display Output Ctrl Adjust (NO estava)

// CSCON (F0h): Command Set Control (NO estava)
// SPI Read Control (FBh) (NO estava)
//#define ST7796S_PWCTR6 0xFC (NO admet ST7796S)

// Color definitions
#define ST7796S_BLACK 0x0000       ///<   0,   0,   0
#define ST7796S_NAVY 0x000F        ///<   0,   0, 123
#define ST7796S_DARKGREEN 0x03E0   ///<   0, 125,   0
#define ST7796S_DARKCYAN 0x03EF    ///<   0, 125, 123
#define ST7796S_MAROON 0x7800      ///< 123,   0,   0
#define ST7796S_PURPLE 0x780F      ///< 123,   0, 123
#define ST7796S_OLIVE 0x7BE0       ///< 123, 125,   0
#define ST7796S_LIGHTGREY 0xC618   ///< 198, 195, 198
#define ST7796S_DARKGREY 0x7BEF    ///< 123, 125, 123
#define ST7796S_BLUE 0x001F        ///<   0,   0, 255
#define ST7796S_GREEN 0x07E0       ///<   0, 255,   0
#define ST7796S_CYAN 0x07FF        ///<   0, 255, 255
#define ST7796S_RED 0xF800         ///< 255,   0,   0
#define ST7796S_MAGENTA 0xF81F     ///< 255,   0, 255
#define ST7796S_YELLOW 0xFFE0      ///< 255, 255,   0
#define ST7796S_WHITE 0xFFFF       ///< 255, 255, 255
#define ST7796S_ORANGE 0xFD20      ///< 255, 165,   0
#define ST7796S_GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define ST7796S_PINK 0xFC18        ///< 255, 130, 198


class Display_ST7796S : public Adafruit_SPITFT {
public:
  Display_ST7796S(int8_t _CS, int8_t _DC, int8_t _MOSI, int8_t _SCLK, int8_t _RST = -1, int8_t _MISO = -1);
  Display_ST7796S(int8_t _CS, int8_t _DC, int8_t _RST = -1);
  #if !defined(ESP8266)
  Display_ST7796S(SPIClass *spiClass, int8_t dc, int8_t cs = -1, int8_t rst = -1);
  #endif // end !ESP8266
  Display_ST7796S(tftBusWidth busWidth, int8_t d0, int8_t wr, int8_t dc, int8_t cs = -1, int8_t rst = -1, int8_t rd = -1);

  void begin(uint32_t freq = 0);
  void setRotation(uint8_t r);
  void invertDisplay(bool i);
  void scrollTo(uint16_t y);
  void setScrollMargins(uint16_t top, uint16_t bottom);

  // Transaction API not used by GFX
  void setAddrWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

  uint8_t readcommand8(uint8_t reg, uint8_t index = 0);
};

#endif // _DISPLAY_TFT_ST7796S_
