
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

  
img_t img ;
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(uint8_t * data, size_t size)
{

  FuzzedDataProvider fdp(data, size);

  if ((img.pixels) == NULL)
  {
    img = img_create(fdp.ConsumeIntegralInRange<unsigned>(0,2000), fdp.ConsumeIntegralInRange<unsigned>(0,2000));
  }

  
  
  auto value = fdp.ConsumeIntegralInRange(0,1000);

  if (value>990)
  {
    if (img.pixels!=NULL)
      img_free(&img);
    
    img = img_create(fdp.ConsumeIntegral<unsigned>(),
		       fdp.ConsumeIntegral<unsigned>());
    
    
  }
  
  auto val = fdp.ConsumeIntegralInRange(0,4);      
  if (val == 0)
  {
    auto vec = fdp.ConsumeBytes<uint8_t> (size);
    uint32_t * ptr = reinterpret_cast<uint32_t*>(vec.data());
    
  }
  else if (val == 1)
  {
    if (img.pixels != NULL){
      img_adjust_brightness(&img,fdp.ConsumeFloatingPoint<float>());
    }
  }
  else if (val == 2)
  {
    if (img.pixels != NULL){
      img_adjust_contrast(&img,fdp.ConsumeFloatingPoint<float>());
    }
    if (img.pixels!=NULL) img_free(&img);
  }
  else if (val == 3)
  {
    if (img.pixels != NULL){
      img_adjust_brightness(&img,fdp.ConsumeFloatingPoint<float>());
    }
  }
  else if (val == 4)
  {
      if (img.pixels != NULL){
	img_sharpen(&img,fdp.ConsumeFloatingPoint<float>(),fdp.ConsumeFloatingPoint<float>());
      }
  }

  return 1;
}
