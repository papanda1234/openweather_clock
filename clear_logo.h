#define clear_width 64
#define clear_height 64
static unsigned char clear_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x03, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x06,
   0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x84, 0x30, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x10, 0x86, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x60, 0x80,
   0x00, 0x60, 0x70, 0x00, 0x00, 0x38, 0x00, 0x80, 0x00, 0x10, 0x40, 0x00,
   0x00, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x43, 0x00, 0x00,
   0x00, 0x00, 0x40, 0x00, 0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00,
   0x80, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x3c, 0x00, 0xc0, 0x00, 0x00, 0xf8,
   0xff, 0x01, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x1e, 0x00, 0x07, 0x00, 0x00,
   0x80, 0x03, 0x80, 0x03, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00,
   0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x66, 0x00, 0x00, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x23, 0xc0, 0x01, 0x20, 0x00, 0x00, 0x00, 0x00, 0x33, 0xf0,
   0x07, 0x60, 0x00, 0x00, 0x00, 0x00, 0x31, 0x18, 0x0c, 0x40, 0x00, 0x00,
   0x00, 0x80, 0x11, 0x0c, 0x08, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x11, 0x06,
   0x18, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x11, 0x06, 0x10, 0x80, 0x00, 0x00,
   0x00, 0x80, 0x11, 0x04, 0x10, 0x80, 0xc0, 0x03, 0x00, 0x00, 0x31, 0x0c,
   0x18, 0x80, 0x60, 0x06, 0xe0, 0x00, 0x21, 0x08, 0x18, 0x80, 0x10, 0x0c,
   0x30, 0x03, 0x63, 0x00, 0x0c, 0xc0, 0x10, 0x08, 0x18, 0x03, 0xc3, 0x00,
   0x0c, 0x40, 0x00, 0x08, 0x18, 0x00, 0x82, 0x01, 0x06, 0x60, 0x00, 0x18,
   0x10, 0x00, 0x06, 0x87, 0x03, 0x30, 0x00, 0x18, 0x20, 0x00, 0x0c, 0xfc,
   0x01, 0x18, 0x00, 0x08, 0xc0, 0x00, 0x0c, 0x00, 0x00, 0x1c, 0x18, 0x0e,
   0x00, 0x00, 0x18, 0x00, 0x00, 0x0e, 0xf0, 0x07, 0x00, 0x00, 0x30, 0x00,
   0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xc0, 0x01, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03,
   0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0x0f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00,
   0x18, 0x10, 0x00, 0x00, 0x00, 0x00, 0x16, 0x00, 0x0c, 0x10, 0x00, 0x00,
   0x00, 0x00, 0x11, 0x00, 0x0c, 0x10, 0x00, 0x00, 0x00, 0x80, 0x19, 0x00,
   0x08, 0x08, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x18, 0x08, 0x00, 0x00,
   0x00, 0x80, 0x01, 0x00, 0x30, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
   0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
