#include "neslib.h"
#include "vrambuf.h"

// tier 1
#include "defines.h"
#include "utilities.h"
// tier 2   
#include "camera.h"
//static struct Camera TheCamera;
#include "player.h"
static struct Player Ghostie;

//#link "vrambuf.c"
// link the pattern table into CHR ROM
//#link "chr_generic.s"


// main function, run after console reset
void main(void) {
  //char x, y;	// world index
  char event;
  
  // write text to name table
  vram_adr(NTADR_A(2, 2));
  vram_write("This is", 7);
  vram_adr(NTADR_A(2,3));
  vram_write("Jefferey Schlueter's", 20);
  vram_adr(NTADR_A(2,4));
  vram_write("first NES game!", 15);

  Background_Draw();
  
  Player_Init(&Ghostie);
  
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
    // EVENTS
    event = pad_poll(0); // controller indexing 0-3
    Player_Events(&Ghostie, event);
    
    // UPDATE
    Player_Update(&Ghostie);
    
    // DRAW
    oam_id = 0;
    Player_Draw(&Ghostie, &oam_id);
    
    if (oam_id!=0) oam_hide_rest(oam_id);
    vrambuf_flush();
    __Ticks += 1;
  }
}
