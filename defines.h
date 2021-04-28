// World stuff
#define NUM_ACTORS 1
#define FLOOR_H 22
#define FLOOR_PIXEL_H ((FLOOR_H-1)*32)
#define VIS_SCREEN_x 31
#define VIS_SCREEN_y 28
#define BLOCK 32
#define FRAMES_PER_ANIM 9
// 
#define ScreenPixelWidth 256
#define ScreenPixelHeight 240
// Sprite drawing
#define FLIPHORZ 0x40
#define FLIPVERT 0x80

#define SPR1 0x00
#define SPR2 0x01
#define SPR3 0x02
#define SPR4 0x03

// Steal Jason's perfectly nice palette
/*{pal:"nes",layout:"nes"}*/ // <- thank-you, DemetriusR!
const char PALETTE[32] =
{
  0x03, // screen color
  0x24, 0x16, 0x20, 0x0, // background palette 0
  0x1c, 0x20, 0x2c, 0x0, // background palette 1
  0x00, 0x1a, 0x20, 0x0, // background palette 2
  0x15, 0x23, 0x14, 0x0, // background palette 3
  0x23, 0x31, 0x41, 0x0, // sprite palette 0
  0x00, 0x37, 0x25, 0x0, // sprite palette 1
  0x36, 0x21, 0x19, 0x0, // sprite palette 2
  0x1d, 0x37, 0x2b,      // sprite palette 3
};

static unsigned long __Ticks = 1;	// Ticks since init
static char oam_id;			// sprite ID

