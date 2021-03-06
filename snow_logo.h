#define snow_width 64
#define snow_height 64
static unsigned char snow_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x38, 0x03, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x0e, 0x01, 0x60, 0x01,
   0xb0, 0x00, 0x02, 0x00, 0x87, 0x01, 0x08, 0x00, 0x10, 0x80, 0x05, 0x80,
   0x81, 0x01, 0x00, 0x03, 0x08, 0x40, 0x00, 0xc0, 0x80, 0x01, 0xb0, 0x01,
   0x88, 0x00, 0x02, 0x60, 0x00, 0x01, 0x00, 0x00, 0x90, 0x60, 0x03, 0x20,
   0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x81, 0x31, 0x00, 0x03, 0x00, 0x00,
   0x00, 0xa0, 0x80, 0xff, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x0b, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
   0x01, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0x18, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x03, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00,
   0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0xc0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x0c, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
   0x00, 0x03, 0x30, 0x00, 0x00, 0x00, 0x03, 0x08, 0x04, 0x06, 0x30, 0x00,
   0x00, 0x80, 0x01, 0x18, 0x1a, 0x04, 0x22, 0x00, 0x00, 0xc0, 0x00, 0x2c,
   0x1a, 0x0c, 0x20, 0x00, 0x00, 0xc0, 0x00, 0x2c, 0x12, 0x08, 0x31, 0x00,
   0x00, 0x40, 0x00, 0x2c, 0x16, 0x08, 0x1d, 0x00, 0x00, 0x40, 0x00, 0x38,
   0x1e, 0x18, 0x02, 0x00, 0x00, 0xc2, 0x00, 0x38, 0x10, 0x18, 0x00, 0x00,
   0x00, 0xc0, 0x00, 0x10, 0x00, 0x18, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00,
   0x00, 0x18, 0x00, 0x00, 0xc0, 0x81, 0x01, 0x00, 0x00, 0x18, 0xe0, 0x01,
   0x00, 0x02, 0x01, 0x00, 0x00, 0x08, 0x00, 0x03, 0x40, 0x02, 0x03, 0x00,
   0x00, 0x0c, 0x10, 0x02, 0x00, 0x01, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x02,
   0xc0, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x08, 0x20, 0x00,
   0xe0, 0x01, 0xd8, 0x00, 0x00, 0x08, 0x60, 0xc0, 0x7f, 0x00, 0x30, 0x00,
   0x00, 0x08, 0x80, 0xc3, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x3e,
   0x78, 0x00, 0x00, 0x08, 0x80, 0x0f, 0xc0, 0x0f, 0xf0, 0x7f, 0x00, 0x0c,
   0x00, 0x08, 0x60, 0x00, 0x00, 0xff, 0x01, 0x06, 0x00, 0x30, 0x32, 0x00,
   0x00, 0x80, 0xff, 0x03, 0x00, 0xe0, 0x1f, 0x00, 0x00, 0x00, 0x86, 0x03,
   0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x02, 0x00,
   0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00,
   0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x04, 0x30, 0x00, 0x80, 0x01, 0x00,
   0x00, 0x00, 0x06, 0x88, 0x80, 0x84, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00,
   0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x80, 0x01, 0x00,
   0x00, 0x80, 0x01, 0x44, 0x00, 0x00, 0x01, 0x00, 0x00, 0xc0, 0x00, 0x34,
   0x00, 0x00, 0x03, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
   0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x1c, 0x00, 0x00,
   0x00, 0x00, 0x78, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x01,
   0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
