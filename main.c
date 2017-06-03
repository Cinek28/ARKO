//#include "transform.h"
#include </usr/include/allegro5/allegro.h>
#include </usr/include/allegro5/allegro_image.h>
#include </usr/include/allegro5/allegro_native_dialog.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800

struct transformation{
    unsigned int srcWidth;
    unsigned int srcHeight;
    unsigned char* src;
    int transposition[2];
    float rotation[2];
}trans;

int main(int argc, char **argv){

    if(argc<2){
        printf("No argument provided. Please specify picture file to process.");
        return 0;
    }
    const char* pictureFile = argv[1];
    printf("Filename: %s\n",argv[1]);

    trans.rotation[0]=30;
    trans.rotation[1]=30;
    trans.transposition[0]=50;
    trans.transposition[1]=50;
    //transform(trans.srcWidth,trans.srcHeight,trans.src,WIDTH,HEIGHT,trans.rotation,trans.transposition);
    ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_BITMAP  *image   = NULL;
   if(!al_init()) {
        printf("%0x\n%0x\n",ALLEGRO_VERSION_INT,al_get_allegro_image_version());
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }

   if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }

   display = al_create_display(WIDTH,HEIGHT);

   if(!display) {
      al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return 0;
   }
   al_get_pixel
   image = al_load_bitmap(pictureFile);
   int i = (&image).w;
   if(!image) {
      al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(display);
      return 0;
   }
   al_draw_bitmap(image,WIDTH/2,HEIGHT/2,0);

   al_flip_display();
   al_rest(2);

   al_destroy_display(display);
   al_destroy_bitmap(image);

   return 0;
}
