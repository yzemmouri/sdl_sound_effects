#include<stdio.h>
#include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"
# include "SDL2/SDL_mixer.h"
# include "SDL2/SDL_image.h"
#define W_W 1000
#define W_H 800

int sound_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W-60 && b.x <= W_W-10 && b.y >= 10 && b.y <= 50)
         return (1);
   }
   return (0);
}

int play_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-156 && b.x <= W_W/2-156 + 313 && b.y >= W_H/2 && b.y <= W_H/2 + 159)
         return (1);
   }
   return (0);
}

int menu_icon_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= 10 && b.x <= 60 && b.y >= 10 && b.y <= 60)
         return (1);
   }
   return (0);
}

int menu_buttons_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W/2-100 && b.x <= W_W/2+100)
      {
         if (b.y >= (W_H/6*0)+(12*1) && b.y <= (W_H/6*0)+(12*1) + W_H/6)
            return (1);
         if (b.y >= (W_H/6*1)+(12*2) && b.y <= (W_H/6*1)+(12*2) + W_H/6)
            return (2);
         if (b.y >= (W_H/6*2)+(12*3) && b.y <= (W_H/6*2)+(12*3) + W_H/6)
            return (3);
         if (b.y >= (W_H/6*3)+(12*4) && b.y <= (W_H/6*3)+(12*4) + W_H/6)
            return (4);
         if (b.y >= (W_H/6*4)+(12*5) && b.y <= (W_H/6*4)+(12*5) + W_H/6)
            return (5);
      }
   }
   return (0);
}

int close_btn_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.x >= W_W - 55 && b.x <= W_W - 15 && b.y >= 15 && b.y <= 55)
         return (1);
   }
   return (0);
}

int img_player_press(SDL_MouseButtonEvent b)
{
   if(b.button == SDL_BUTTON_LEFT){
      if (b.y >= W_H/2+W_H/6 && b.y <= W_H/2+W_H/6+W_H/2-W_H/4)
      {
         if (b.x >= W_W/5 && b.x <= W_W/5 + W_W/9)
            return (1);
         if (b.x >= W_W-W_W/5-W_W/10 && b.x <= W_W-W_W/5-W_W/10 + W_W/9)
            return (2);
      }
   }
   return (0);
}

int main(int ac, char **av)
{
   SDL_bool continuer = SDL_TRUE;
   SDL_Window* window = NULL;
   SDL_Renderer* render = NULL;
   SDL_Event event;
   SDL_Surface *welcom_sc;
   SDL_Surface *wolf3d;
   SDL_Surface *play;
   SDL_Surface *menu_icon;
   SDL_Surface *icon;
   SDL_Surface *player1;
   SDL_Surface *player2;
   SDL_Surface *menu_sc;
   SDL_Surface *menu_btns;
   int menu_btn_clicked = 0;
   int previous_screen = 1;
   SDL_Surface *options_pupop;
   int options_pupop_showed = 0;
   SDL_Surface *close_btn;
   int player_num = 1;
   int img_player_selected = 1;
   SDL_Surface *img_player1;
   SDL_Surface *img_player2;
   SDL_Surface *selection_img_player;


   double frame_sound = 0;
   double frame_player_x = 0;
   double frame_player_y = 0;
   int screen = 1;
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
   SDL_Rect rect_sound_d = (SDL_Rect){W_W - 60, 10, 50, 50};
   SDL_Texture *tx_icon = SDL_CreateTextureFromSurface(render, icon);
   SDL_FreeSurface(icon);

   player1 = IMG_Load("player1.png");
   if (!player1)
   {
      printf("5%s", SDL_GetError());
      return (1);
   }
   player2 = IMG_Load("player2.png");
   if (!player2)
   {
      printf("5%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_player_s;
   SDL_Rect rect_player_d = (SDL_Rect){W_W/2 - 50, W_H - 170, 100, 150};
   SDL_Texture *tx_player1 = SDL_CreateTextureFromSurface(render, player1);
   SDL_Texture *tx_player2 = SDL_CreateTextureFromSurface(render, player2);
   SDL_FreeSurface(player1);
   SDL_FreeSurface(player2);

   welcom_sc = IMG_Load("welcom_sc.png");
   if (!welcom_sc)
   {
      printf("6%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_welcom_sc_s;
   SDL_Rect rect_welcom_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   SDL_Texture *tx_welcom_sc = SDL_CreateTextureFromSurface(render, welcom_sc);
   SDL_FreeSurface(welcom_sc);

   wolf3d = IMG_Load("wolf3d.png");
   if (!wolf3d)
   {
      printf("7%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_wolf3d_s;
   SDL_Rect rect_wolf3d_d = (SDL_Rect){W_W/2-150, 50, 300, 126};
   SDL_Texture *tx_wolf3d = SDL_CreateTextureFromSurface(render, wolf3d);
   SDL_FreeSurface(wolf3d);

   play = IMG_Load("play.png");
   if (!play)
   {
      printf("8%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_play_s;
   SDL_Rect rect_play_d = (SDL_Rect){W_W/2-150, W_H/2, 300, 160};
   SDL_Texture *tx_play = SDL_CreateTextureFromSurface(render, play);
   SDL_FreeSurface(play);

   menu_icon = IMG_Load("menu_icon.png");
   if (!menu_icon)
   {
      printf("9%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_menu_icon_s;
   SDL_Rect rect_menu_icon_d = (SDL_Rect){10, 10, 50, 50};
   SDL_Texture *tx_menu_icon = SDL_CreateTextureFromSurface(render, menu_icon);
   SDL_FreeSurface(menu_icon);

   menu_sc = IMG_Load("menu_sc.png");
   if (!menu_sc)
   {
      printf("10%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_menu_sc_s;
   SDL_Rect rect_menu_sc_d = (SDL_Rect){0, 0, W_W, W_H};
   SDL_Texture *tx_menu_sc = SDL_CreateTextureFromSurface(render, menu_sc);
   SDL_FreeSurface(menu_sc);

   menu_btns = IMG_Load("menu_buttons.png");
   if (!menu_btns)
   {
      printf("11%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_menu_btns_home_s;
   SDL_Rect rect_menu_btns_home_d = (SDL_Rect){W_W/2 - 100, (W_H/6*0)+(12*1), 200, W_H/6};
   SDL_Rect rect_menu_btns_resume_s;
   SDL_Rect rect_menu_btns_resume_d = (SDL_Rect){W_W/2 - 100, (W_H/6*1)+(12*2), 200, W_H/6};
   SDL_Rect rect_menu_btns_restart_s;
   SDL_Rect rect_menu_btns_restart_d = (SDL_Rect){W_W/2 - 100, (W_H/6*2)+(12*3), 200, W_H/6};
   SDL_Rect rect_menu_btns_options_s;
   SDL_Rect rect_menu_btns_options_d = (SDL_Rect){W_W/2 - 100, (W_H/6*3)+(12*4), 200, W_H/6};
   SDL_Rect rect_menu_btns_exit_s;
   SDL_Rect rect_menu_btns_exit_d = (SDL_Rect){W_W/2 - 100, (W_H/6*4)+(12*5), 200, W_H/6};
   SDL_Texture *tx_menu_btns = SDL_CreateTextureFromSurface(render, menu_btns);
   SDL_FreeSurface(menu_btns);

   options_pupop = IMG_Load("options_pupop.png");
   if (!options_pupop)
   {
      printf("12%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_options_pupop_s;
   SDL_Rect rect_options_pupop_d = (SDL_Rect){25, 25, W_W-50, W_H-50};
   SDL_Texture *tx_options_pupop = SDL_CreateTextureFromSurface(render, options_pupop);
   SDL_FreeSurface(options_pupop);

   close_btn = IMG_Load("close_btn.png");
   if (!close_btn)
   {
      printf("13%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_close_btn_s;
   SDL_Rect rect_close_btn_d = (SDL_Rect){W_W - 55, 15, 40, 40};
   SDL_Texture *tx_close_btn = SDL_CreateTextureFromSurface(render, close_btn);
   SDL_FreeSurface(close_btn);

   img_player1 = IMG_Load("img_player1.png");
   if (!img_player1)
   {
      printf("14%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_img_player1_s;
   SDL_Rect rect_img_player1_d = (SDL_Rect){W_W/5, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   SDL_Texture *tx_img_player1 = SDL_CreateTextureFromSurface(render, img_player1);
   SDL_FreeSurface(img_player1);

   img_player2 = IMG_Load("img_player2.png");
   if (!img_player2)
   {
      printf("15%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_img_player2_s;
   SDL_Rect rect_img_player2_d = (SDL_Rect){W_W-W_W/5-W_W/10, W_H/2+W_H/6, W_W/9, W_H/2 - W_H/4};
   SDL_Texture *tx_img_player2 = SDL_CreateTextureFromSurface(render, img_player2);
   SDL_FreeSurface(img_player2);

   selection_img_player = IMG_Load("selection_img_player.png");
   if (!selection_img_player)
   {
      printf("16%s", SDL_GetError());
      return (1);
   }

   SDL_Rect rect_selection_img_player_s;
   SDL_Rect rect_selection_img_player_d;
   SDL_Texture *tx_selection_img_player = SDL_CreateTextureFromSurface(render, selection_img_player);
   SDL_FreeSurface(selection_img_player);

   Mix_Music *musique;
   musique = Mix_LoadMUS("musique.wav");
   Mix_PlayMusic(musique, -1);

   Mix_AllocateChannels(2);
   Mix_Chunk *son1;
   Mix_Chunk *son2;
   son1 = Mix_LoadWAV("running.wav");
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
            if (sound_press(event.button) && screen == 2 && options_pupop_showed == 0)
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
            if (play_press(event.button) && screen == 1 && options_pupop_showed == 0)
               screen = 2;

            if (menu_icon_press(event.button) && screen != 3 && options_pupop_showed == 0)
            {
               previous_screen = screen;
               screen = 3;
            }
            else if (menu_icon_press(event.button) && screen == 3 && options_pupop_showed == 0)
               screen = previous_screen;
            if (close_btn_press(event.button) && options_pupop_showed == 1)
               options_pupop_showed = 0;
            img_player_selected = img_player_press(event.button);
            if (img_player_selected && options_pupop_showed == 1)
               player_num = img_player_selected;
            menu_btn_clicked = menu_buttons_press(event.button);
            if (menu_btn_clicked && screen == 3 && options_pupop_showed == 0)
            {
               if (menu_btn_clicked == 1)
                  screen = 1;
               if (menu_btn_clicked == 2)
               {
                  
               }
               if (menu_btn_clicked == 3)
               {
                  
               }
               if (menu_btn_clicked == 4)
                  options_pupop_showed = 1;
               if (menu_btn_clicked == 5)
                  continuer = SDL_FALSE;
            }
            break;
         case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
               case SDLK_w:
                  frame_player_x++;
                  if (player_num == 1)
                     frame_player_y = 3;
                  else
                     frame_player_y = 0;
                  Mix_Resume(0);
                  break;
               case SDLK_s:
                  frame_player_x++;
                  if (player_num == 1)
                     frame_player_y = 0;
                  else
                     frame_player_y = 4;
                  Mix_Resume(0);
                  break;
            }
            break;
         case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
               case SDLK_w:
                  Mix_Pause(0);
                  break;
               case SDLK_s:
                  Mix_Pause(0);
                  break;
            }
            break;
      }
      if (frame_player_x > 7)
         frame_player_x = 0;
      if (frame_player_x < 0)
         frame_player_x = 7;


      if (screen == 1)
      {
         SDL_RenderClear(render);
         rect_welcom_sc_s = (SDL_Rect){0, 0, 612, 344};
         rect_wolf3d_s = (SDL_Rect){0, 0, 867, 364};
         rect_play_s = (SDL_Rect){0, 0, 313, 159};
         rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
         SDL_RenderCopyEx(render, tx_welcom_sc, &rect_welcom_sc_s, &rect_welcom_sc_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_wolf3d, &rect_wolf3d_s, &rect_wolf3d_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_play, &rect_play_s, &rect_play_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      }
      if (screen == 2)
      {
         SDL_RenderClear(render);
         rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
         rect_sound_s = (SDL_Rect){752 * frame_sound, 0, 752, 774};
         rect_player_s = (SDL_Rect){100 * frame_player_x, 100 * frame_player_y, 100, 100};
         SDL_RenderCopyEx(render, tx_icon, &rect_sound_s, &rect_sound_d, 0, NULL, SDL_FLIP_NONE);
         if (player_num == 1)
            SDL_RenderCopyEx(render, tx_player1, &rect_player_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
         else
            SDL_RenderCopyEx(render, tx_player2, &rect_player_s, &rect_player_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
      }
      if (screen == 3)
      {
         SDL_RenderClear(render);
         rect_menu_icon_s = (SDL_Rect){0, 0, 673, 696};
         rect_menu_sc_s = (SDL_Rect){0, 0, 800, 600};
         rect_menu_btns_home_s = (SDL_Rect){0, 0, 281, 137};
         rect_menu_btns_resume_s = (SDL_Rect){0, 1*137, 281, 137};
         rect_menu_btns_restart_s = (SDL_Rect){0, 2*137, 281, 137};
         rect_menu_btns_options_s = (SDL_Rect){0, 3*137, 281, 137};
         rect_menu_btns_exit_s = (SDL_Rect){0, 4*137, 281, 137};
         SDL_RenderCopyEx(render, tx_menu_sc, &rect_menu_sc_s, &rect_menu_sc_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_icon, &rect_menu_icon_s, &rect_menu_icon_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_btns, &rect_menu_btns_home_s, &rect_menu_btns_home_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_btns, &rect_menu_btns_resume_s, &rect_menu_btns_resume_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_btns, &rect_menu_btns_restart_s, &rect_menu_btns_restart_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_btns, &rect_menu_btns_options_s, &rect_menu_btns_options_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_menu_btns, &rect_menu_btns_exit_s, &rect_menu_btns_exit_d, 0, NULL, SDL_FLIP_NONE);
      }
      if (options_pupop_showed == 1)
      {
         rect_options_pupop_s = (SDL_Rect){0, 0, 771, 638};
         rect_close_btn_s = (SDL_Rect){0, 0, 300, 300};
         rect_img_player1_s = (SDL_Rect){0, 0, 52, 92};
         SDL_RenderCopyEx(render, tx_options_pupop, &rect_options_pupop_s, &rect_options_pupop_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_close_btn, &rect_close_btn_s, &rect_close_btn_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_img_player1, &rect_img_player1_s, &rect_img_player1_d, 0, NULL, SDL_FLIP_NONE);
         SDL_RenderCopyEx(render, tx_img_player2, &rect_img_player1_s, &rect_img_player2_d, 0, NULL, SDL_FLIP_NONE);
         if (player_num == 1)
            rect_selection_img_player_d = rect_img_player1_d;
         else
            rect_selection_img_player_d = rect_img_player2_d;
         SDL_RenderCopyEx(render, tx_selection_img_player, &rect_img_player1_s, &rect_selection_img_player_d, 0, NULL, SDL_FLIP_NONE);
      }
      SDL_RenderPresent(render);
   }
   Mix_FreeChunk(son1);//Libération du son 1
   Mix_FreeChunk(son2);
   Mix_FreeMusic(musique); //Libération de la musique
   SDL_DestroyTexture(tx_icon);
   SDL_DestroyTexture(tx_player1);
   SDL_DestroyTexture(tx_player2);
   SDL_DestroyRenderer(render);
   SDL_DestroyWindow( window );
   Mix_CloseAudio();
   SDL_Quit();
   return 0;
}