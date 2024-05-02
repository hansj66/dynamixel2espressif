#ifndef _ARDUINO_STUFF_H_
#define _ARDUINO_STUFF_H_

#include <sys/time.h>
#include <stdint.h>

#define LOW 0
#define HIGH 1


#define pgm_read_byte(addr) (*(const unsigned char *)(addr))

#define pgm_read_word(addr)           \
  ({                                  \
    typeof(addr) _addr = (addr);      \
    *(const unsigned short *)(_addr); \
  })

#define pgm_read_dword(addr)         \
  ({                                 \
    typeof(addr) _addr = (addr);     \
    *(const unsigned long *)(_addr); \
  })

#define pgm_read_float(addr)     \
  ({                             \
    typeof(addr) _addr = (addr); \
    *(const float *)(_addr);     \
  })

#define pgm_read_ptr(addr)       \
  ({                             \
    typeof(addr) _addr = (addr); \
    *(void *const *)(_addr);     \
  })

uint32_t millis();


  #endif