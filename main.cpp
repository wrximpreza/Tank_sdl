#include <iostream>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#undef main
#define _

typedef struct
{
  int x, y;
  short life;
  char *name;
} Tank;
typedef struct
{
  int x, y;
} TankImg;
typedef struct {
    Tank tank;

    TankImg stars[100];

    //Images
    SDL_Texture *tankSurface;
    SDL_Renderer *renderer;
} GameTank;

int processEvents(SDL_Window *window, GameTank *game)
{
  SDL_Event event;
  int done = 0;

  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_WINDOWEVENT_CLOSE:
      {
        if(window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          done = 1;
        }
      }
      break;
      case SDL_KEYDOWN:
      {
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            done = 1;
          break;
        }
      }
      break;
      case SDL_QUIT:
        //quit out of the game
        done = 1;
      break;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if(state[SDL_SCANCODE_LEFT])
  {
    game->tank.x -= 10;
  }
  if(state[SDL_SCANCODE_RIGHT])
  {
    game->tank.x += 10;
  }
  if(state[SDL_SCANCODE_UP])
  {
    game->tank.y -= 10;
  }
  if(state[SDL_SCANCODE_DOWN])
  {
    game->tank.y += 10;
  }

  return done;
}

void doRender(SDL_Renderer *renderer, GameTank *game)
{
  //set the drawing color to blue
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  //Clear the screen (to blue)
  SDL_RenderClear(renderer);

  //set the drawing color to white
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  SDL_Rect rect = { game->tank.x, game->tank.y, 200, 200 };
  SDL_RenderFillRect(renderer, &rect);

  //We are done drawing, "present" or show to the screen what we've drawn
  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  SDL_Window *window = NULL;                    // Declare a window
  SDL_Renderer *renderer = NULL;                // Declare a renderer
  SDL_Surface *tankSurface = NULL;

  SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

  GameTank game;
  game.tank.x = 220;
  game.tank.y = 140;

  //Create an application window with the following settings:
  window = SDL_CreateWindow("Game Window",                     // window title
                            SDL_WINDOWPOS_UNDEFINED,           // initial x position
                            SDL_WINDOWPOS_UNDEFINED,           // initial y position
                            640,                               // width, in pixels
                            480,                               // height, in pixels
                            0                                  // flags
                            );
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  game.renderer = renderer;


  tankSurface = IMG_Load("tank.png");
  if(tankSurface == NULL)
  {
    printf("Cannot find tank.png!\n\n");
    SDL_Quit();
    exit(1);
  }

  game.tankSurface = SDL_CreateTextureFromSurface(game.renderer, tankSurface);
  SDL_FreeSurface(tankSurface);

  // The window is open: enter program loop (see SDL_PollEvent)
  int done = 0;

  //Event loop
  while(!done)
  {
    //Check for events
    done = processEvents(window, &game);

    //Render display
    doRender(renderer, &game);

    //don't burn up the CPU
    SDL_Delay(10);
  }


  // Close and destroy the window
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  // Clean up
  SDL_Quit();
  return 0;
}
