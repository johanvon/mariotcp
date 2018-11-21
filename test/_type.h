#ifndef ___TYPE_H__
#define ___TYPE_H__

#ifdef  LINUX32
typedef  int                sint32;
typedef  unsigned int       uint32;
typedef  long long          sint64;
typedef  unsigned long long uint64;
#endif

#ifdef  LINUX64
typedef  int                sint32;
typedef  unsigned int       uint32;
typedef  long               sint64;
typedef  unsigned long      uint64;
#endif

typedef  short     	    sint16;
typedef  unsigned short     uint16;
typedef  unsigned char      ubyte;
typedef  char		    sbyte;

#endif  //___TYPE_H__

