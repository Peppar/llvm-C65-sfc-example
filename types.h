#ifndef _TYPES_H
#define _TYPES_H

//==============================================================================
// Address space definitions
// ==============================================================================
// We define __near (default) and __far address space attributes to
// distinguish 16-bit from 24-bit addresses.
#define __near __attribute__((address_space(0)))
#define __far __attribute__((address_space(1)))

//==============================================================================
// Type definitions for 8, 16 and 24-bit registers
//==============================================================================

typedef unsigned char uint8_t;
typedef signed char int8_t;

#ifdef c65
typedef unsigned int uint16_t;
typedef signed int int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef unsigned long long uint64_t;
typedef signed long long int64_t;
#else
typedef unsigned short uint16_t;
typedef signed short int16_t;
typedef unsigned int uint32_t;
typedef signed int int32_t;
typedef unsigned long uint64_t;
typedef signed long int64_t;
#endif

#endif
