/* char is 1 byte
     short int is 2 bytes
        long int is 4 bytes
*/
typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned long int   u32;

typedef signed char        s8;
typedef signed short int   s16;
typedef signed long int    s32;

/* float is 4 bytes
     short  double is 8 bytes
         long double is 12 bytes
*/
typedef  float         f32 ;
typedef  double        f64 ;
typedef  long double   f96 ;


typedef  u8 ERROR_STATUS;

#define NULL             ((void *)0)

#define status_Ok   1U
#define status_NOk  0U

