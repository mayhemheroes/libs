
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_U64_T uint64_t
#include "buffer.h"

#define BUFFER_IMPLEMENTATION
#include "buffer.h"

#define HASHTABLE_U32 uint32_t
#define HASHTABLE_U64 uint32_t
#include "hashtable.h"

#define HASHTABLE_IMPLEMENTATION
#include "hashtable.h"

#define IMG_IMPLEMENTATION
#include "img.h"

#define DIR_IMPLEMENTATION
#include "dir.h"


#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(uint8_t * data, size_t size)
{

  FuzzedDataProvider fdp(data, size);

  auto select = fdp.ConsumeIntegralInRange(0, 2);
  /*
   *  Testing Images api 
    */

  if (select == 0)   // Images
  {
    auto val = fdp.ConsumeIntegralInRange(0, 4);
    if (val == 0)
    {
      auto vec = fdp.ConsumeBytes<uint8_t> (size);
      uint32_t * ptr = reinterpret_cast<uint32_t*>(vec.data());
      if (ptr != NULL)
      {
       img_t img = img_from_abgr32(ptr, fdp.ConsumeIntegralInRange<unsigned>(0,2000), fdp.ConsumeIntegralInRange<unsigned>(0,2000));
      if (img.pixels!=NULL) img_free(&img);
      }
    }
    else if (val == 1)
    {
      img_t img = img_create(fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1, fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1);
      if (img.pixels != NULL){
          img_adjust_brightness(&img,fdp.ConsumeFloatingPoint<float>());
      }
      if (img.pixels!=NULL) img_free(&img);
    }
    else if (val == 2)
    {
      img_t img = img_create(fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1, fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1);
      if (img.pixels != NULL){
          img_adjust_contrast(&img,fdp.ConsumeFloatingPoint<float>());
      }
      if (img.pixels!=NULL) img_free(&img);
    }
    else if (val == 3)
    {
      img_t img = img_create(fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1, fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1);
      if (img.pixels != NULL){
          img_adjust_brightness(&img,fdp.ConsumeFloatingPoint<float>());
      }
      if (img.pixels!=NULL) img_free(&img);
    }
    else if (val == 4)
    {
      img_t img = img_create(fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1, fdp.ConsumeIntegralInRange<unsigned>(0,2000)+1);
      if (img.pixels != NULL){
          img_sharpen(&img,fdp.ConsumeFloatingPoint<float>(),fdp.ConsumeFloatingPoint<float>());
      }
      if (img.pixels!=NULL) img_free(&img);
    }
  }
  /*
   *  Testing Buffers api 
    */

  else if (select == 1)   // Buffers
  {
    auto val = fdp.ConsumeIntegralInRange(0, 1);
    if (val == 0)
    {
      buffer_t * buf = buffer_create();  
      std::string str = fdp.ConsumeRemainingBytesAsString();
      buffer_write_char( buf, str.c_str(), str.size() );
      if (buf != NULL) buffer_destroy(buf);
    }
    else if (val == 1)
    {
      buffer_t * buf = buffer_load(fdp.ConsumeRemainingBytesAsString().c_str());
      if (buf != NULL) buffer_destroy(buf);
    }
  }
  /*
   *  Testing Dir api 
    */

  else if (select == 2)   // Dir
  {
    auto val = fdp.ConsumeIntegralInRange(0, 0);
    if (val == 0)
    {
      std::string str = fdp.ConsumeRemainingBytesAsString();
      dir_t* dir = dir_open(str.c_str());
      if (dir != NULL) dir_close(dir);
    }
  }
  return 1;
}
