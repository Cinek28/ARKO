#include "transform.h"
#include </usr/include/allegro5/allegro.h>
#include </usr/include/allegro5/allegro_image.h>
#include </usr/include/allegro5/allegro_native_dialog.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct transformation{
    unsigned int srcWidth;
    unsigned int srcHeight;
    unsigned int dstWidth;
    unsigned int dstHeight;
    unsigned char* src;
    unsigned char* dst;
    int transposition[2];
    float rotation;
}trans;

const float FPS = 60;
const int WIDTH = 600;
const int HEIGHT = 600;
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_Z, KEY_X
};

int main(int argc, char **argv)
{
   if(argc<2){
    printf("No picture selected. Provide picture file: ./Affinite <picture_name>.");
    return 0;
   }
   trans.transposition[0] = 0;
   trans.transposition[1] = 0;
   const char* pictureFile = argv[1];
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *image = NULL;
   ALLEGRO_BITMAP *transformedImage = NULL;
   bool key[4] = { false, false, false, false, false, false };
   bool redraw = true;
   bool doexit = false;

   if(!al_init()) {
      fprintf(stderr, "Failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
      fprintf(stderr, "Failed to initialize the keyboard!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "Failed to create timer!\n");
      return -1;
   }

   display = al_create_display(WIDTH, HEIGHT);
   if(!display) {
      fprintf(stderr, "Failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }


   if(!al_init_image_addon()) {
      fprintf(stderr,"Failed to initialize image addon!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   image = al_load_bitmap(pictureFile);

   if(!image){
      fprintf(stderr,"Failed to load image!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_clear_to_color(al_map_rgb(255, 0, 255));

   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(image);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }

   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));

   al_flip_display();

   al_start_timer(timer);
   transformedImage = al_create_bitmap(WIDTH,HEIGHT);

   trans.srcWidth = al_get_bitmap_width(image);
   trans.srcHeight = al_get_bitmap_height(image);
   trans.dstWidth = WIDTH;
   trans.dstHeight = HEIGHT;
   unsigned int tableSize = trans.srcWidth*trans.srcHeight*4;
   unsigned int pitch = trans.srcWidth*4;
   trans.src = malloc(tableSize);

     ALLEGRO_LOCKED_REGION* locked_bitmap =  al_lock_bitmap(image,ALLEGRO_PIXEL_FORMAT_RGBA_8888,ALLEGRO_LOCK_READONLY);
   unsigned char* locked_image = (unsigned char*)(locked_bitmap->data);

   for (int k = trans.srcHeight*trans.srcWidth*4-4; k >= 0;k=k-4){
            trans.src[k] =*(locked_image)--;
            trans.src[k+3] = *(locked_image)--;
            trans.src[k+2] = *(locked_image)--;
            trans.src[k+1] = *(locked_image)--;
   }
   al_unlock_bitmap(image);
   float rotationTable[2];
   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
         if(key[KEY_UP]) {
            trans.transposition[1] += 10;
         }

         if(key[KEY_DOWN]) {
            trans.transposition[1] -= 10;
         }

         if(key[KEY_LEFT]) {
            trans.transposition[0] -= 10;
         }

         if(key[KEY_RIGHT]) {
            trans.transposition[0] += 10;
         }


         if(key[KEY_Z]) {
            trans.rotation += 5.;
         }

         if(key[KEY_X]) {
            trans.rotation -= 5.;
         }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;

            case ALLEGRO_KEY_Z:
               key[KEY_Z] = true;
               break;

            case ALLEGRO_KEY_X:
               key[KEY_X] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               key[KEY_UP] = false;
               break;

            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;

            case ALLEGRO_KEY_LEFT:
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;

            case ALLEGRO_KEY_Z:
                key[KEY_Z] = false;
                break;

            case ALLEGRO_KEY_X:
                key[KEY_X] = false;
                break;
         }
      }
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         al_clear_to_color(al_map_rgb(0,0,0));
         rotationTable[0] = cosf(trans.rotation*3.1415/180.);
         rotationTable[1] = sinf(trans.rotation*3.1415/180.);
        locked_bitmap = al_lock_bitmap(transformedImage,ALLEGRO_PIXEL_FORMAT_RGBA_8888 , ALLEGRO_LOCK_WRITEONLY);
        trans.dst = (unsigned char*)(locked_bitmap->data);
            for(int i = 0; i < WIDTH*(HEIGHT-1); i++){
                    *(trans.dst)-- = 0;
                    *(trans.dst)-- = 0;
                    *(trans.dst)-- = 0;
                    *(trans.dst)-- = 0;
                }

        transform(trans.src, trans.srcWidth, trans.srcHeight, trans.dst, trans.dstWidth, trans.dstHeight, rotationTable[0],rotationTable[1], trans.transposition[0],trans.transposition[1] );
        al_unlock_bitmap(transformedImage);
         al_draw_bitmap(transformedImage,0,0,0);

         al_flip_display();
      }
   }


   al_unlock_bitmap(transformedImage);
   free(trans.src);
   al_destroy_bitmap(transformedImage);
   al_destroy_bitmap(image);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}


