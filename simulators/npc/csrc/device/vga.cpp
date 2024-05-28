#include <verilator.h>
#include <npc.h>

#include <memory.h>
#include <device.h>
#include <SDL2/SDL.h>

#define SCREEN_W    400
#define SCREEN_H    300
// #define VGA_SCREEN_W SCREEN_W 
// #define VGA_SCREEN_H SCREEN_H

#define VGA_SCREEN_W (SCREEN_W * 2)
#define VGA_SCREEN_H (SCREEN_H * 2)

uint32_t *vgactl_port_base = NULL;
void *vmem = NULL;

static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL; 

static uint32_t screen_width()
{
    return SCREEN_W;
}

static uint32_t screen_height()
{
    return SCREEN_H;
}

static uint32_t screen_size() {
  return screen_width() * screen_height() * sizeof(uint32_t);
}

static void init_screen()
{
    SDL_Window *window = NULL;
    char title[128] = "riscv64-NPC";
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(
        VGA_SCREEN_W,
        VGA_SCREEN_H,
        0, &window, &renderer
    );
    SDL_SetWindowTitle(window, title);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STATIC, SCREEN_W, SCREEN_H);
}

static inline void update_screen() {
    // Log("reach");
    SDL_UpdateTexture(texture, NULL, vmem, SCREEN_W * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void vga_update_screen()
{
    if(vgactl_port_base[1])
    {
        update_screen();
        vgactl_port_base[1] = 0;
    }
}

void init_vga()
{
    vgactl_port_base = (uint32_t *)malloc(8);
    vgactl_port_base[0] = (screen_width() << 16) | screen_height();
    vmem = malloc(VGA_SCREEN_W * VGA_SCREEN_H *sizeof(uint32_t));
    assert(vgactl_port_base);
    assert(vmem);
    init_screen();
    memset(vmem, 0, VGA_SCREEN_W * VGA_SCREEN_H *sizeof(uint32_t));
}