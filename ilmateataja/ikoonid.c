//Selles failis asuvad ikoonide baidimassiivid.
//Ikoonide joonistamise kohta mõjutusi saadud juhendist lehel http://educ8s.tv/arduino-bitmap-graphics-tutorial/.
#include <avr/pgmspace.h>

const unsigned char cloud_icon []PROGMEM = {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0xff,0xe0,0x0,0x0,
0x0,0x0,0x0,0x3,0xff,0xf8,0x0,0x0,
0x0,0x0,0x0,0x7,0xff,0xfc,0x0,0x0,
0x0,0x0,0x0,0x1f,0xff,0xff,0x0,0x0,
0x0,0x0,0x0,0x3f,0xff,0xff,0x80,0x0,
0x0,0x0,0x0,0x3f,0xff,0xff,0x80,0x0,
0x0,0x0,0x0,0x7f,0xff,0xff,0xc0,0x0,
0x0,0x0,0x1f,0xff,0xff,0xff,0xe0,0x0,
0x0,0x0,0x7f,0xff,0xff,0xff,0xe0,0x0,
0x0,0x0,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x3,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x3,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0x7,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0xf,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0xf,0xff,0xff,0xff,0xff,0xf0,0x0,
0x1,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,
0x7,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,
0xf,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0x80,
0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xf0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x7f,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x3f,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
0x1f,0xff,0xff,0xff,0xff,0xff,0xff,0x80,
0xf,0xff,0xff,0xff,0xff,0xff,0xff,0x0,
0x7,0xff,0xff,0xff,0xff,0xff,0xfe,0x0,
0x3,0xff,0xff,0xff,0xff,0xff,0xfc,0x0,
0x0,0x3f,0xff,0xff,0xff,0xff,0xc0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};


const unsigned char sun_icon []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x6,0x0,0x1,0xc0,0x0,0x30,0x0,0x0,
0x0,0x7,0x0,0x1,0xc0,0x0,0x70,0x0,0x0,
0x0,0x3,0x80,0x0,0x80,0x0,0xe0,0x0,0x0,
0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,
0x0,0x0,0xe0,0x0,0x0,0x3,0x80,0x0,0x0,
0x0,0x0,0x70,0x0,0x0,0x7,0x0,0x0,0x0,
0x0,0x0,0x38,0x0,0x0,0xe,0x0,0x0,0x0,
0x0,0x0,0x10,0xf,0xf8,0x4,0x0,0x0,0x0,
0x0,0x0,0x0,0x3f,0xfe,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0xff,0xff,0x80,0x0,0x0,0x0,
0x0,0x0,0x1,0xff,0xff,0xc0,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x3,0xfe,0xf,0xff,0xff,0xf8,0x3f,0xe0,0x0,
0x7,0xff,0xf,0xff,0xff,0xf8,0x7f,0xf0,0x0,
0x3,0xfe,0xf,0xff,0xff,0xf8,0x3f,0xe0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xf8,0x0,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0x7,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x3,0xff,0xff,0xe0,0x0,0x0,0x0,
0x0,0x0,0x1,0xff,0xff,0xc0,0x0,0x0,0x0,
0x0,0x0,0x0,0xff,0xff,0x80,0x0,0x0,0x0,
0x0,0x0,0x0,0x3f,0xfe,0x0,0x0,0x0,0x0,
0x0,0x0,0x10,0xf,0xf8,0x4,0x0,0x0,0x0,
0x0,0x0,0x38,0x0,0x0,0xe,0x0,0x0,0x0,
0x0,0x0,0x70,0x0,0x0,0x7,0x0,0x0,0x0,
0x0,0x0,0xe0,0x0,0x0,0x3,0x80,0x0,0x0,
0x0,0x1,0xc0,0x0,0x0,0x1,0xc0,0x0,0x0,
0x0,0x3,0x80,0x0,0x80,0x0,0xe0,0x0,0x0,
0x0,0x7,0x0,0x1,0xc0,0x0,0x70,0x0,0x0,
0x0,0x6,0x0,0x1,0xc0,0x0,0x30,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x1,0xc0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x80,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};


const unsigned char rain []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x2,0x0,
0x0,0x0,0x0,0x0,0x0,0x7,0x0,
0x0,0x0,0x20,0x0,0x0,0x7,0x0,
0x0,0x0,0x70,0x0,0x0,0xf,0x80,
0x0,0x0,0x78,0x0,0x0,0x1d,0x80,
0x0,0x0,0xf8,0x0,0x0,0x39,0x80,
0x0,0x1,0xd8,0x0,0x0,0x71,0x80,
0x0,0x3,0x8c,0x0,0x0,0xe0,0xc0,
0x0,0x7,0x8c,0x0,0x3,0xc0,0xc0,
0x0,0xe,0xc,0x0,0xf,0x0,0xc0,
0x0,0x3c,0xc,0x0,0x3c,0x0,0xc0,
0x0,0xf0,0xc,0x0,0x78,0x0,0xc0,
0x3,0xe0,0xc,0x0,0xe0,0x0,0xc0,
0x7,0x80,0xc,0x1,0xc0,0x0,0xc0,
0xe,0x0,0xc,0x3,0x80,0x0,0xc0,
0x1c,0x0,0xc,0x7,0x0,0x0,0xc0,
0x38,0x0,0xc,0x6,0x0,0x1,0x80,
0x30,0x0,0xc,0xe,0x0,0x1,0x80,
0x70,0x0,0xc,0xc,0x0,0x1,0x80,
0x60,0x0,0x1c,0xc,0x0,0x1,0x80,
0xe0,0x0,0x18,0xc,0x0,0x3,0x80,
0xc0,0x0,0x18,0xc,0x0,0x3,0x0,
0xc0,0x0,0x18,0xc,0x0,0x7,0x0,
0xc0,0x0,0x30,0xe,0x0,0x6,0x0,
0xe0,0x0,0x30,0x6,0x0,0xe,0x0,
0x60,0x0,0x70,0x7,0x0,0x1c,0x0,
0x60,0x0,0xe0,0x3,0x80,0x38,0x0,
0x30,0x0,0xc0,0x1,0xe0,0x70,0x0,
0x38,0x3,0xc0,0x0,0xff,0xe0,0x0,
0x1e,0x7,0x80,0x80,0x3f,0x80,0x0,
0xf,0xfe,0x1,0xc0,0x0,0x0,0x0,
0x1,0xf8,0x1,0xe0,0x0,0x0,0x0,
0x0,0x0,0x3,0xe0,0x0,0x0,0x0,
0x0,0x0,0x7,0x60,0x0,0x0,0x0,
0x0,0x0,0xe,0x60,0x0,0x0,0x0,
0x0,0x0,0x1c,0x30,0x0,0x0,0x0,
0x0,0x0,0x78,0x30,0x0,0x0,0x0,
0x0,0x1,0xf0,0x30,0x0,0x0,0x0,
0x0,0x3,0xc0,0x30,0x0,0x0,0x0,
0x0,0xf,0x0,0x30,0x0,0x0,0x0,
0x0,0x1c,0x0,0x30,0x0,0x0,0x0,
0x0,0x38,0x0,0x30,0x0,0x0,0x0,
0x0,0x70,0x0,0x30,0x0,0x0,0x0,
0x0,0xe0,0x0,0x30,0x0,0x0,0x0,
0x1,0xc0,0x0,0x30,0x0,0x0,0x0,
0x1,0x80,0x0,0x70,0x0,0x0,0x0,
0x3,0x80,0x0,0x60,0x0,0x0,0x0,
0x3,0x0,0x0,0x60,0x0,0x0,0x0,
0x3,0x0,0x0,0x60,0x0,0x0,0x0,
0x3,0x0,0x0,0xe0,0x0,0x0,0x0,
0x3,0x0,0x0,0xc0,0x0,0x0,0x0,
0x3,0x0,0x1,0xc0,0x0,0x0,0x0,
0x3,0x80,0x1,0x80,0x0,0x0,0x0,
0x1,0x80,0x3,0x80,0x0,0x0,0x0,
0x1,0xc0,0x7,0x0,0x0,0x0,0x0,
0x0,0xe0,0xe,0x0,0x0,0x0,0x0,
0x0,0x7c,0x3c,0x0,0x0,0x0,0x0,
0x0,0x3f,0xf8,0x0,0x0,0x0,0x0,
0x0,0x7,0xc0,0x0,0x0,0x0,0x0
};

const unsigned char estonia_icon []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x48,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x1,0x7f,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x2,0x1,0xff,0xfc,0x0,0x0,
0x0,0x0,0x0,0x0,0x1,0xff,0xff,0xfe,0x1c,0xc,
0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0xff,0xfe,
0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xfc,
0x0,0x0,0x0,0x2,0xff,0xff,0xff,0xff,0xff,0xf0,
0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xff,0xe0,
0x0,0x0,0x0,0x2f,0xff,0xff,0xff,0xff,0xff,0xe0,
0x0,0x0,0x0,0xff,0xff,0xff,0xff,0xff,0xff,0xe0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,
0x0,0x8,0x3,0xff,0xff,0xff,0xff,0xff,0xf8,0x0,
0x0,0x3c,0x39,0xff,0xff,0xff,0xff,0xff,0xc0,0x0,
0x0,0x3f,0x1,0xff,0xff,0xff,0xff,0xff,0x80,0x0,
0x3,0x7f,0x3,0xff,0xff,0xff,0xff,0xff,0x80,0x0,
0x0,0x3f,0x81,0xff,0xff,0xff,0xff,0xff,0x0,0x0,
0x0,0x3e,0x1,0xff,0xff,0xff,0xff,0xff,0x80,0x0,
0x0,0x38,0x2,0x3f,0xff,0xff,0xff,0xff,0xc0,0x0,
0x0,0x10,0x0,0x3f,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x0,0x31,0xff,0xff,0xff,0xff,0xff,0xe0,0x0,
0x0,0x13,0x39,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x0,0xff,0x98,0xff,0xff,0xff,0xff,0xff,0xf0,0x0,
0x12,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,0xf0,0x0,
0x13,0xff,0xf0,0x7f,0xff,0xff,0xff,0xff,0xf0,0x0,
0xf,0xff,0xc0,0x7f,0xff,0xff,0xff,0xff,0xfc,0x0,
0xf,0xff,0x80,0x7f,0xbf,0xff,0xff,0xff,0xfe,0x0,
0x1f,0xff,0x0,0x1f,0xf,0xff,0xff,0xff,0xfe,0x0,
0x3f,0xfc,0x0,0x7,0xf,0xff,0xff,0xff,0xfe,0x0,
0xf,0xf8,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0x0,
0x7,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0x0,
0x2,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0x0,
0x2,0x0,0x0,0x0,0x1f,0xff,0xff,0xff,0xff,0x80,
0x6,0x0,0x0,0x0,0x1f,0xdf,0xff,0xff,0xff,0x80,
0x4,0x0,0x0,0x0,0x1f,0x83,0xff,0xff,0xff,0xc0,
0xc,0x0,0x0,0x0,0x3c,0x0,0xff,0xff,0xff,0xc0,
0x8,0x0,0x0,0x0,0x20,0x0,0x7f,0xff,0xff,0xe0,
0x0,0x0,0x0,0x0,0x60,0x0,0x1f,0xff,0xff,0xf0,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0x80,
0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0x80,
0x0,0x0,0x0,0x0,0x0,0x0,0x1,0xff,0xff,0x80,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xff,0xfe,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xfe,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0x9e,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x6,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xc,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};

const unsigned char air_icon []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0xfc,0x0,0x0,
0x0,0x7,0xff,0x0,0x0,
0x0,0x1f,0x87,0xc0,0x0,
0x0,0x3c,0x0,0xf0,0x0,
0x0,0x70,0x0,0x78,0x0,
0x0,0xe0,0xf8,0x1c,0x0,
0x1,0xc3,0xfe,0x1c,0x0,
0x1,0x87,0x8f,0xce,0x0,
0x3,0x8e,0x3,0xc6,0x0,
0x3,0x1c,0x3,0x7,0x0,
0x3,0x18,0xf,0x3,0x0,
0x7,0x38,0x3c,0x3,0x0,
0x6,0x30,0x7c,0x3,0x0,
0x6,0x30,0xf8,0x1,0x0,
0x6,0x30,0x78,0x0,0x80,
0x6,0x30,0x70,0x0,0x0,
0x7,0x0,0x0,0x6,0x0,
0x3,0x0,0x0,0x6,0x0,
0x3,0x0,0x0,0xf,0x0,
0x1,0x80,0x0,0x1f,0x80,
0x1,0xc0,0x0,0x1f,0x80,
0x0,0xc0,0x0,0x3f,0xc0,
0x0,0xf0,0x0,0x3f,0xc0,
0x0,0x78,0x0,0x7f,0xe0,
0x0,0x3e,0x0,0x7f,0xe0,
0x0,0xf,0xfe,0x7f,0xe0,
0x0,0x3,0xfe,0x7f,0xe0,
0x0,0x0,0x0,0x3f,0xc0,
0x0,0x0,0x0,0x1f,0x80,
0x0,0x0,0x0,0xf,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0
};

