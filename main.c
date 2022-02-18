#include<stdio.h>
#include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/SDL_image.h"
#define W_W 600
#define W_H 400

int sound_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-40 && b.x <= W_W && b.y >= 0 && b.y <= 40)
         return (1);
   }
   return (0);
}

// int play_audio_on_key_down(e) {
//   if (e.keyCode == 38) {
//     clickSound.play();
//   }
// }

// int pauseAudio_on_key_up(e) {
//   if (e.keyCode == 38) {
//     clickSound.pause();
//   }
// }
// document.onkeydown = play_audioOnKeyDown;
// document.onkeyup = pauseAudioOnKeyUp;

int main(int ac, char **av)
{
   SDL_bool continuer = SDL_TRUE;
   SDL_Window* window = NULL;
   SDL_Renderer* render = NULL;
   SDL_Event event;
   SDL_Surface *icon;
   SDL_Surface *player;
   double frame_sound = 0;
   double frame_player_x = 0;
   double frame_player_y = 0;
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
      printf("1%s", SDL_GetError());
      return (1);
   }

   window = SDL_CreateWindow("sound effects", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_W, W_H, SDL_WINDOW_SHOWN);
   if (!window)
   {
      printf("2%s", SDL_GetError());
      return (1);
   }

   render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   if (!render)
   {
      printf("2%s", SDL_GetError());
      return (1);
   }

   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) //Initialisation de l'API Mixer
   {
      printf("3%s", Mix_GetError());
      return (1);
   }

   Mix_VolumeMusic(MIX_MAX_VOLUME/4);

   icon = IMG_Load("sound.png");
   if (!icon)
   {
      printf("4%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_sound_s;
   SDL_Rect rect_sound_d = (SDL_Rect){W_W - 40, 0, 40, 40};
   SDL_Texture *tx_icon = SDL_CreateTextureFromSurface(render, icon);
   SDL_FreeSurface(icon);

   player = IMG_Load("player.png");
   if (!player)
   {
      printf("5%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_player_s;
   SDL_Rect rect_player_d = (SDL_Rect){W_W/2 - 50, W_H - 170, 100, 150};
   SDL_Texture *tx_player = SDL_CreateTextureFromSurface(render, player);
   SDL_FreeSurface(player);

   Mix_Music *musique;
   musique = Mix_LoadMUS("musique.wav");
   Mix_PlayMusic(musique, -1);

   Mix_AllocateChannels(2);
   Mix_Chunk *son1;
   Mix_Chunk *son2;
   son1 = Mix_LoadWAV("footsteps.wav");
   son2 = Mix_LoadWAV("meow.wav");
   Mix_VolumeChunk(son1, MIX_MAX_VOLUME); //Mettre un volume pour ce wav
   Mix_VolumeChunk(son2, MIX_MAX_VOLUME);

   Mix_PlayChannel(0, son1, -1);//Joue le son1 1 sur le canal 1 ; le joue une fois (0 + 1)
   Mix_Pause(0);
   while(continuer)
   {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
         case SDL_QUIT:
            continuer = SDL_FALSE;
            break;
         case SDL_MOUSEBUTTONDOWN:
            if (sound_press(event.button))
            {
               if(Mix_PausedMusic() == 1) //Si la musique est en pause
               {
                  frame_sound = 0;
                  Mix_ResumeMusic(); //Reprendre la musique
               }
               else
               {
                  frame_sound = 1;
                  Mix_PauseMusic(); //Mettre en pause la musique
               }
            }
            break;
         case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
               case SDLK_w:
                  frame_player_x++;
                  frame_player_y = 3;
                  Mix_Resume(0);
                  break;
               case SDLK_s:
                  frame_player_x++;
                  frame_player_y = 0;
                  Mix_Resume(0);
                  break;
            }
            break;
         case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
               case SDLK_w:
                  frame_player_x++;
                  frame_player_y = 3;
                  Mix_Pause(0);
                  break;
               case SDLK_s:
                  frame_player_x++;
                  frame_player_y = 0;
                  Mix_Pause(0);
                  break;
            }
            break;
      }
      if (frame_player_x > 11)
         frame_player_x = 0;
      if (frame_player_x < 0)
         frame_player_x = 11;

      rect_sound_s = (SDL_Rect){119 * frame_sound, 0, 119, 119};
      rect_player_s = (SDL_Rect){95 * frame_player_x, 158 * frame_player_y, 95, 158};
      SDL_RenderClear(render);
      SDL_RenderCopyEx(render, tx_icon, &rect_sound_s, &rect_sound_d, 0, NULL, SDL_FLIP_NONE);
      SDL_RenderCopyEx(render, tx_player, &rect_player_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
      SDL_RenderPresent(render);
   }
   Mix_FreeChunk(son1);//Libération du son 1
   Mix_FreeChunk(son2);
   Mix_FreeMusic(musique); //Libération de la musique
   SDL_DestroyTexture(tx_icon);
   SDL_DestroyTexture(tx_player);
   SDL_DestroyRenderer(render);
   SDL_DestroyWindow( window );
   Mix_CloseAudio();
   SDL_Quit();
   return 0;
}