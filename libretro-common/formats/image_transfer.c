#include <stdint.h>
#include <string.h>
#include <errno.h>

#ifdef HAVE_RPNG
#include <formats/rpng.h>
#endif
#ifdef HAVE_RJPEG
#include <formats/rjpeg.h>
#endif

#include <formats/image.h>

void image_transfer_free(void *data, enum image_type_enum type)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         rpng_nbio_load_image_free((rpng_t*)data);
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }
}

void *image_transfer_new(enum image_type_enum type)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         return rpng_alloc();
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }

   return NULL;
}

bool image_transfer_start(void *data, enum image_type_enum type)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         if (!rpng_nbio_load_image_argb_start((rpng_t*)data))
            return false;
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }

   return true;
}

void image_transfer_set_buffer_ptr(
      void *data,
      enum image_type_enum type,
      void *ptr)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         rpng_set_buf_ptr((rpng_t*)data, (uint8_t*)ptr);
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }
}

int image_transfer_process(
      void *data,
      enum image_type_enum type,
      uint32_t **buf,
      unsigned *width, unsigned *height)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         if (!rpng_is_valid((rpng_t*)data))
            return IMAGE_PROCESS_ERROR;

         return rpng_nbio_load_image_argb_process(
               (rpng_t*)data,
               buf,
               width, height);
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }

   return 0;
}

bool image_transfer_iterate(void *data, enum image_type_enum type)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         if (!rpng_nbio_load_image_argb_iterate((rpng_t*)data))
            return false;
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
#endif
         break;
   }

   return true;
}
