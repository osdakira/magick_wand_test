#include <stdio.h>
#include <stdlib.h>
#include <wand/MagickWand.h>

int main(int argc,char **argv)
{
#define ThrowWandException(wand)                                        \
  {                                                                     \
    char                                                                \
      *description;                                                     \
                                                                        \
    ExceptionType                                                       \
      severity;                                                         \
                                                                        \
    description=MagickGetException(wand,&severity);                     \
    (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
    description=(char *) MagickRelinquishMemory(description);           \
    exit(-1);                                                           \
  }

  MagickBooleanType
    status;

  MagickWand
    *magick_wand;

  if (argc != 2)
    {
      (void) fprintf(stdout,"Usage: %s image \n",argv[0]);
      exit(0);
    }
  /*
    Read an image.
  */
  MagickWandGenesis();
  magick_wand=NewMagickWand();
  status=MagickReadImage(magick_wand,argv[1]);
  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  /*
    Turn the images into a thumbnail sequence.
  */
  MagickResetIterator(magick_wand);
  while (MagickNextImage(magick_wand) != MagickFalse)
    printf("%c\n", MagickGetFilename(magick_wand));
  /*
    Write the image then destroy it.
  */
  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  return(0);
}
