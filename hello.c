#include "neslib.h"
#include "Utils.h"
#include "vrambuf.h"
//#link "vrambuf.c"

#define NUM_ACTORS 1
#define FLOOR_H 22
#define VIS_SCREEN_x 31
#define VIS_SCREEN_y 28
#define BLOCK 32
// link the pattern table into CHR ROM
//#link "chr_generic.s"

// actor x/y coordinates
byte actor_x[NUM_ACTORS];
byte actor_y[NUM_ACTORS];
// actor x/y velocity
sbyte actor_dx[NUM_ACTORS];
sbyte actor_dy[NUM_ACTORS];

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
  0x1d, 0x37, 0x2b, // sprite palette 3
};

// main function, run after console reset
void main(void) {
  char i; 	// sprite idex
  char x, y;	// world index
  char oam_id;	// sprite ID
  
  for (i=0;i<NUM_ACTORS;++i)
  {
    actor_y[i] = (FLOOR_H-1)*BLOCK;
    actor_x[i] = 0;
    actor_dy[i] = 0;
    actor_dx[i] = 1;
  }

  // write text to name table
  vram_adr(NTADR_A(2, 2));
  vram_write("This is", 7);
  vram_adr(NTADR_A(2,3));
  vram_write("Jefferey Schlueter's", 20);
  vram_adr(NTADR_A(2,4));
  vram_write("first NES game!", 15);
   
  // place static level geometry
  for (x=1; x < VIS_SCREEN_x; x++)
    for (y=FLOOR_H; y < VIS_SCREEN_y; y++)
    {
      vram_adr(NTADR_A(x, y));
      vram_put('\x0C');
    }
  //placing door
  // FIND OUT HOW TO USE THE COMPLETE SPRITE AT ONCE
  vram_adr(NTADR_A(VIS_SCREEN_x-2, FLOOR_H-2)); vram_put('\xc4');
  vram_adr(NTADR_A(VIS_SCREEN_x-2, FLOOR_H-1)); vram_put('\xc5');
  vram_adr(NTADR_A(VIS_SCREEN_x-1, FLOOR_H-2)); vram_put('\xc6');
  vram_adr(NTADR_A(VIS_SCREEN_x-1, FLOOR_H-1)); vram_put('\xc7');
  
  // Clear Sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
  // enable batch updating
  vrambuf_clear();
  set_vram_update(updbuf);
  // enable PPU rendering (turn on screen)
  ppu_on_all();
  // infinite loop
  while (1) 
  {
    oam_id = 0;
    for (i=0; i<NUM_ACTORS; ++i)
    {
      if (actor_x > 0)
      {
        oam_id = oam_spr(actor_x[i], actor_y[i], 0xd9, 3, oam_id);
        oam_id = oam_spr(actor_x[i]+8, actor_y[i], 0xdb, 3, oam_id);
        oam_id = oam_spr(actor_x[i], actor_y[i]+8, 0xdd, 3, oam_id);
        oam_id = oam_spr(actor_x[i]+8, actor_y[i]+8, 0xdf, 3, oam_id);
      }
      else
      {
        oam_id = oam_spr(actor_x[i], actor_y[i], 0xd9, 3, oam_id);
        oam_id = oam_spr(actor_x[i]+8, actor_y[i], 0xdb, 3, oam_id);
        oam_id = oam_spr(actor_x[i], actor_y[i]+8, 0xdd, 3, oam_id);
        oam_id = oam_spr(actor_x[i]+8, actor_y[i]+8, 0xdf, 3, oam_id);
      }
      
      actor_y[i] += actor_dy[i];
      actor_x[i] += actor_dx[i];
      
      //if (actor_x[i] > (VIS_SCREEN_y-1)*BLOCK || actor_x[i] < BLOCK)
      //  actor_dx[i] *= -1;
    }
    
    if (oam_id!=0) oam_hide_rest(oam_id);
    
    vrambuf_flush();
  }
}
