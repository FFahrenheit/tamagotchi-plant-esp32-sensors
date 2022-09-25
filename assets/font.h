// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Arimo_Regular_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xDB,0x60,0x36,0xC0, // '!'
	0xC6,0xC6,0xC6,0xC6,0xC6, // '"'
	0x04,0x20,0x10,0x80,0xC2,0x02,0x18,0x08,0x61,0xFF,0xE1,0x84,0x06,0x10,0x10,0xC0,0x43,0x01,0x08,0x3F,0xFC,0x30,0x80,0x86,0x02,0x18,0x08,0x40,0x21,0x00, // '#'
	0x02,0x00,0x08,0x01,0xFC,0x0F,0xF8,0x72,0x71,0x88,0xC6,0x20,0x1C,0x80,0x3E,0x00,0x7E,0x00,0x3E,0x00,0x9C,0x02,0x38,0x08,0x6E,0x23,0x98,0x8C,0x3F,0xE0,0x7F,0x00,0x20,0x00,0x80, // '$'
	0x38,0x02,0x06,0xC0,0x60,0xC6,0x0C,0x0C,0x60,0xC0,0xC6,0x18,0x0C,0x63,0x00,0xC6,0x30,0x0C,0x66,0x38,0x6C,0x46,0xC3,0x8C,0xC6,0x01,0x8C,0x60,0x18,0xC6,0x03,0x0C,0x60,0x60,0xC6,0x06,0x0C,0x60,0xC0,0x6C,0x08,0x03,0x80, // '%'
	0x07,0x80,0x0D,0xC0,0x18,0x60,0x18,0x60,0x18,0x60,0x18,0xC0,0x1B,0x80,0x1E,0x00,0x3C,0x18,0x66,0x18,0xC3,0x18,0xC3,0x30,0xC1,0xB0,0xC0,0xE0,0xE0,0xE0,0x7F,0xBE,0x3F,0x1E, // '&'
	0xDB,0x64, // '''
	0x0C,0x0C,0x18,0x30,0x30,0x60,0x60,0x60,0x60,0x60,0xE0,0xE0,0x60,0x60,0x60,0x60,0x60,0x30,0x30,0x18,0x0C,0x0C, // '('
	0x60,0x60,0x30,0x18,0x18,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x1C,0x18,0x18,0x30,0x60,0x60, // ')'
	0x08,0x02,0x00,0x81,0xAC,0x3E,0x07,0x03,0x40,0xD8,0x22,0x00, // '*'
	0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x7F,0xFB,0xFF,0xC0,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00, // '+'
	0xEE,0xE6,0x44, // ','
	0xFD,0xF8, // '-'
	0xEE,0xE0, // '.'
	0x06,0x06,0x0C,0x0C,0x0C,0x18,0x18,0x18,0x18,0x30,0x30,0x30,0x60,0x60,0x60,0xC0,0xC0, // '/'
	0x1F,0x03,0xF8,0x60,0xC6,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0xE6,0x0C,0x61,0xC3,0xF8,0x1F,0x00, // '0'
	0x1C,0x07,0x81,0xB0,0x66,0x08,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x07,0xFE,0xFF,0xC0, // '1'
	0x1F,0x03,0xFC,0x60,0xCE,0x0C,0x00,0xE0,0x0C,0x00,0xC0,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0x60,0x0F,0xFE,0xFF,0xE0, // '2'
	0x1F,0x07,0xFC,0x60,0xCE,0x0C,0x00,0xE0,0x0C,0x01,0xC0,0xF0,0x0F,0x80,0x0C,0x00,0xE0,0x06,0xC0,0x6C,0x0E,0xE0,0xC7,0xFC,0x1F,0x00, // '3'
	0x01,0x80,0x38,0x07,0x80,0x58,0x0D,0x81,0x98,0x19,0x83,0x18,0x61,0x86,0x18,0xC1,0x8F,0xFE,0xFF,0xE0,0x18,0x01,0x80,0x18,0x01,0x80, // '4'
	0x7F,0xC7,0xFC,0x60,0x06,0x00,0x60,0x06,0x00,0x7F,0x0F,0xFC,0xE0,0xC0,0x0E,0x00,0x60,0x06,0x00,0x6C,0x0E,0xE0,0xC7,0xF8,0x1F,0x00, // '5'
	0x0F,0x03,0xFC,0x30,0xC6,0x0C,0x60,0x0E,0x00,0xCF,0x0D,0xFC,0xE0,0xCE,0x0E,0xE0,0x6E,0x06,0x60,0x66,0x0E,0x70,0xC3,0xFC,0x1F,0x00, // '6'
	0xFF,0xEF,0xFE,0x00,0xC0,0x0C,0x01,0x80,0x18,0x03,0x00,0x30,0x06,0x00,0x60,0x0C,0x00,0xC0,0x0C,0x01,0xC0,0x1C,0x01,0x80,0x18,0x00, // '7'
	0x1F,0x07,0xFC,0x60,0xCE,0x0E,0xE0,0xE6,0x0C,0x71,0xC3,0xF0,0x3F,0x86,0x0C,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0x60,0xC7,0xFC,0x1F,0x00, // '8'
	0x1F,0x07,0xF8,0x61,0xCE,0x0C,0xC0,0xEC,0x06,0xC0,0x6E,0x0E,0x60,0xE7,0xF6,0x1E,0x60,0x0E,0x00,0xC6,0x0C,0x61,0xC7,0xF8,0x1E,0x00, // '9'
	0xEE,0xE0,0x00,0x00,0x00,0xEE,0xE0, // ':'
	0xEE,0xE0,0x00,0x00,0x00,0xEE,0xE6,0x44, // ';'
	0x00,0x10,0x03,0x80,0xF0,0x1E,0x03,0xC0,0x78,0x03,0x00,0x1E,0x00,0x3C,0x00,0x78,0x00,0xF0,0x00,0xE0,0x01,0x00, // '<'
	0xFF,0xF7,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xDF,0xFE, // '='
	0x80,0x07,0x00,0x0F,0x00,0x1E,0x00,0x3C,0x00,0x78,0x00,0xC0,0x1E,0x03,0xC0,0x78,0x0F,0x01,0xE0,0x08,0x00,0x00, // '>'
	0x1F,0x07,0xFC,0x60,0xEE,0x06,0xC0,0x60,0x06,0x00,0xE0,0x1C,0x03,0x80,0x70,0x0E,0x00,0xC0,0x00,0x00,0x00,0x0C,0x00,0xC0,0x0C,0x00, // '?'
	0x00,0xFC,0x00,0x3F,0xFC,0x03,0x00,0x70,0x30,0x01,0xC3,0x0F,0x36,0x31,0xFD,0x91,0x8C,0x38,0xD8,0xC0,0xC6,0xC6,0x06,0x36,0x60,0x31,0xB3,0x03,0x0D,0x98,0x18,0x6C,0xC0,0xC2,0x63,0x0E,0x33,0x1F,0xBF,0x0C,0x78,0xF0,0x60,0x00,0x01,0xC0,0x18,0x07,0xFF,0xC0,0x07,0xF0,0x00, // '@'
	0x03,0x80,0x03,0x80,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x0C,0x60,0x0C,0x60,0x0C,0x70,0x18,0x30,0x18,0x30,0x3F,0xF8,0x3F,0xF8,0x30,0x18,0x70,0x0C,0x60,0x0C,0x60,0x0C,0xE0,0x0E, // 'A'
	0xFF,0x83,0xFF,0x8C,0x07,0x30,0x1C,0xC0,0x33,0x01,0xCC,0x0E,0x3F,0xF0,0xFF,0xE3,0x01,0xCC,0x03,0x30,0x0E,0xC0,0x3B,0x00,0xEC,0x07,0x3F,0xF8,0xFF,0xC0, // 'B'
	0x07,0xE0,0x1F,0xF8,0x38,0x1C,0x70,0x0E,0x60,0x04,0x60,0x00,0xE0,0x00,0xE0,0x00,0xC0,0x00,0xE0,0x00,0xE0,0x00,0x60,0x00,0x60,0x04,0x70,0x0E,0x38,0x1C,0x1F,0xF8,0x07,0xE0, // 'C'
	0xFF,0x81,0xFF,0xC3,0x01,0xC6,0x01,0xCC,0x01,0x98,0x03,0xB0,0x07,0x60,0x06,0xC0,0x0D,0x80,0x1B,0x00,0x76,0x00,0xCC,0x01,0x98,0x07,0x30,0x1C,0x7F,0xF0,0xFF,0x80, // 'D'
	0xFF,0xF3,0xFF,0xCC,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x3F,0xFC,0xFF,0xF3,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x3F,0xFE,0xFF,0xF8, // 'E'
	0xFF,0xF7,0xFF,0xB0,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xFF,0xF7,0xFF,0xB0,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x00, // 'F'
	0x07,0xF0,0x0F,0xFE,0x0E,0x07,0x8E,0x00,0xC6,0x00,0x63,0x00,0x03,0x80,0x01,0xC0,0x00,0xE0,0x00,0x70,0x3F,0xB8,0x1F,0xCC,0x00,0x66,0x00,0x33,0x80,0x18,0xF0,0x3C,0x3F,0xFC,0x07,0xF0,0x00, // 'G'
	0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xBF,0xFE,0xFF,0xFB,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x18, // 'H'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xC0, // 'I'
	0x07,0xC0,0xF8,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x6E,0x0C,0xC1,0x9C,0x71,0xFC,0x1F,0x00, // 'J'
	0xC0,0x31,0x80,0xC3,0x03,0x06,0x0C,0x0C,0x38,0x18,0xE0,0x33,0x80,0x6E,0x00,0xFE,0x01,0xCE,0x03,0x0C,0x06,0x0C,0x0C,0x1C,0x18,0x1C,0x30,0x1C,0x60,0x18,0xC0,0x18, // 'K'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x07,0xFE,0xFF,0xC0, // 'L'
	0xE0,0x0E,0xE0,0x0E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xD8,0x36,0xD8,0x36,0xC8,0x36,0xCC,0x66,0xCC,0x66,0xC4,0x66,0xC6,0xC6,0xC6,0xC6,0xC2,0x86,0xC3,0x86,0xC3,0x86,0xC1,0x06, // 'M'
	0xE0,0x1B,0x80,0x6F,0x01,0xBE,0x06,0xD8,0x1B,0x30,0x6C,0xC1,0xB1,0x86,0xC7,0x1B,0x0C,0x6C,0x19,0xB0,0x66,0xC0,0xDB,0x03,0xEC,0x07,0xB0,0x0E,0xC0,0x38, // 'N'
	0x07,0xF0,0x07,0xFF,0x03,0x80,0xE1,0xC0,0x1C,0x60,0x03,0x18,0x00,0xCE,0x00,0x3B,0x00,0x0E,0xC0,0x01,0xB0,0x00,0xEE,0x00,0x39,0x80,0x0C,0x60,0x03,0x1C,0x01,0xC3,0x80,0xE0,0x7F,0xF0,0x07,0xF0,0x00, // 'O'
	0xFF,0xC3,0xFF,0x8C,0x07,0x30,0x0C,0xC0,0x3B,0x00,0xEC,0x03,0xB0,0x0C,0xC0,0x73,0xFF,0x8F,0xF8,0x30,0x00,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00,0xC0,0x00, // 'P'
	0x07,0xF0,0x07,0xFF,0x03,0x80,0xE1,0xC0,0x1C,0x60,0x03,0x18,0x00,0xCE,0x00,0x3B,0x00,0x0E,0xC0,0x01,0xB0,0x00,0xEE,0x00,0x39,0x80,0x0C,0x60,0x03,0x1C,0x01,0xC3,0x80,0xE0,0x7F,0xF0,0x07,0xF0,0x00,0x30,0x00,0x0E,0x00,0x01,0x80,0x00,0x7E,0x00,0x07,0x80, // 'Q'
	0xFF,0xC1,0xFF,0xE3,0x00,0xE6,0x00,0xCC,0x01,0x98,0x03,0x30,0x06,0x60,0x1C,0xFF,0xF1,0xFF,0x03,0x03,0x06,0x07,0x0C,0x06,0x18,0x0E,0x30,0x0C,0x60,0x1C,0xC0,0x1C, // 'R'
	0x0F,0xE0,0x7F,0xE1,0xC0,0xE3,0x00,0xC6,0x00,0x0C,0x00,0x1E,0x00,0x1F,0xC0,0x0F,0xF0,0x01,0xF0,0x00,0x70,0x00,0x60,0x00,0xDC,0x03,0x9C,0x06,0x1F,0xF8,0x0F,0xE0, // 'S'
	0xFF,0xF7,0xFF,0x81,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00, // 'T'
	0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x80,0xE7,0x07,0x0F,0xF8,0x0F,0x80, // 'U'
	0xE0,0x0E,0x60,0x0C,0x60,0x0C,0x70,0x1C,0x30,0x18,0x30,0x18,0x38,0x38,0x18,0x30,0x18,0x30,0x0C,0x60,0x0C,0x60,0x0C,0x60,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x03,0x80,0x03,0x80, // 'V'
	0xE0,0x38,0x0E,0x60,0x38,0x0E,0x60,0x38,0x0C,0x60,0x6C,0x0C,0x70,0x6C,0x1C,0x30,0x6C,0x18,0x30,0x6C,0x18,0x38,0xC6,0x38,0x18,0xC6,0x30,0x18,0xC6,0x30,0x18,0x82,0x30,0x1D,0x83,0x70,0x0D,0x83,0x60,0x0D,0x83,0x60,0x0D,0x01,0x60,0x07,0x01,0xC0,0x07,0x01,0xC0, // 'W'
	0xE0,0x38,0xC0,0x60,0xC1,0x81,0xC7,0x01,0x8C,0x01,0xB0,0x03,0x60,0x03,0x80,0x07,0x00,0x1F,0x00,0x36,0x00,0xC6,0x03,0x8E,0x06,0x0C,0x1C,0x0C,0x70,0x1C,0xC0,0x18, // 'X'
	0xC0,0x0D,0xC0,0x39,0xC0,0xE1,0x81,0x83,0x87,0x03,0x0C,0x03,0x30,0x07,0xE0,0x07,0x80,0x06,0x00,0x0C,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00, // 'Y'
	0x7F,0xF9,0xFF,0xE0,0x03,0x00,0x18,0x00,0xC0,0x07,0x00,0x18,0x00,0xC0,0x06,0x00,0x38,0x01,0xC0,0x06,0x00,0x30,0x01,0xC0,0x0E,0x00,0x3F,0xFE,0xFF,0xF8, // 'Z'
	0xFB,0xEC,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xFB,0xE0, // '['
	0xC0,0xC0,0x60,0x60,0x60,0x30,0x30,0x30,0x10,0x18,0x18,0x18,0x0C,0x0C,0x0C,0x06,0x06, // '\'
	0xFB,0xE1,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0xFB,0xE0, // ']'
	0x06,0x00,0x78,0x06,0x40,0x33,0x03,0x0C,0x18,0x61,0x81,0x8C,0x0C,0xC0,0x30, // '^'
	0xFF,0xFB,0xFF,0xE0, // '_'
	0xE1,0xC1,0x02, // '`'
	0x1F,0x03,0xFC,0x18,0x30,0xC1,0x80,0x0C,0x0F,0xE1,0xFB,0x1C,0x18,0xC0,0xC6,0x0E,0x30,0x70,0xFD,0xC3,0xC7,0x00, // 'a'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xCF,0x0F,0xFC,0xE0,0xCC,0x0E,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x0E,0xE0,0xCF,0xFC,0xCF,0x00, // 'b'
	0x1F,0x07,0xF1,0x87,0x70,0x6C,0x01,0x80,0x30,0x06,0x00,0xC0,0x1C,0x19,0x83,0x1F,0xC1,0xF0, // 'c'
	0x00,0x60,0x06,0x00,0x60,0x06,0x1E,0x67,0xFE,0x60,0xEE,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6E,0x06,0x60,0xE7,0xFE,0x1E,0x60, // 'd'
	0x1F,0x03,0xFC,0x60,0xCE,0x0E,0xC0,0x6F,0xFE,0xFF,0xEC,0x00,0xC0,0x0E,0x04,0x60,0xC3,0xFC,0x1F,0x00, // 'e'
	0x1E,0x3E,0x30,0x30,0xFE,0xFE,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30, // 'f'
	0x1E,0x67,0xFE,0x60,0xEE,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6E,0x06,0x60,0xE7,0xFE,0x3E,0x60,0x06,0x00,0x66,0x0E,0x7F,0xC1,0xF8, // 'g'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0xF9,0xFF,0xB8,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xC0, // 'h'
	0xD8,0x0D,0xB6,0xDB,0x6D,0xB6,0xC0, // 'i'
	0x18,0x60,0x00,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0xFB,0xC0, // 'j'
	0xC0,0x18,0x03,0x00,0x60,0x0C,0x19,0x86,0x31,0x86,0x70,0xDC,0x1F,0x03,0xE0,0x76,0x0C,0xE1,0x8C,0x30,0xC6,0x1C,0xC1,0xC0, // 'k'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xC0, // 'l'
	0xDF,0x1E,0x7F,0xBF,0xB8,0x70,0xD8,0x30,0x6C,0x18,0x36,0x0C,0x1B,0x06,0x0D,0x83,0x06,0xC1,0x83,0x60,0xC1,0xB0,0x60,0xD8,0x30,0x6C,0x18,0x30, // 'm'
	0xCF,0x9F,0xFB,0x83,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0C, // 'n'
	0x1F,0x07,0xFC,0x60,0xCE,0x0E,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6E,0x0E,0x60,0xC3,0xF8,0x1F,0x00, // 'o'
	0xCF,0x0F,0xFC,0xE0,0xCC,0x0E,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x0E,0xE0,0xCF,0xFC,0xCF,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00, // 'p'
	0x1F,0x67,0xFE,0x60,0xEE,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6E,0x06,0x60,0xE7,0xFE,0x1E,0x60,0x06,0x00,0x60,0x06,0x00,0x60,0x06, // 'q'
	0xDD,0xFB,0x86,0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0x0C,0x00, // 'r'
	0x3F,0x0F,0xF3,0x03,0x60,0x0E,0x00,0xF8,0x07,0xC0,0x1E,0x00,0xC8,0x1B,0x03,0x3F,0xC3,0xF0, // 's'
	0x10,0x30,0x30,0xFE,0xFE,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3E,0x1E, // 't'
	0xC0,0xD8,0x1B,0x03,0x60,0x6C,0x0D,0x81,0xB0,0x36,0x06,0xC0,0xD8,0x1B,0x07,0x7F,0xE7,0xCC, // 'u'
	0xC0,0x66,0x0C,0x60,0xC6,0x0C,0x31,0x83,0x18,0x31,0x83,0x38,0x1B,0x01,0xB0,0x1B,0x00,0xE0,0x0E,0x00, // 'v'
	0xC1,0xC1,0xB0,0x70,0x66,0x14,0x31,0x85,0x8C,0x63,0x63,0x18,0xD8,0xC3,0x22,0x60,0xC8,0x98,0x36,0x36,0x0D,0x8D,0x01,0x41,0xC0,0x70,0x70,0x1C,0x1C,0x00, // 'w'
	0x60,0xC7,0x1C,0x31,0x81,0xB0,0x1B,0x00,0xE0,0x0E,0x00,0xE0,0x1B,0x03,0x38,0x31,0x86,0x0C,0x60,0xC0, // 'x'
	0xE0,0x33,0x03,0x18,0x18,0xE0,0xC3,0x0C,0x18,0x60,0x63,0x03,0x30,0x19,0x80,0x68,0x03,0xC0,0x0E,0x00,0x60,0x03,0x00,0x30,0x01,0x80,0x78,0x03,0x80,0x00, // 'y'
	0xFF,0xDF,0xF8,0x0E,0x01,0x80,0x60,0x1C,0x07,0x00,0xC0,0x38,0x0E,0x01,0x80,0x7F,0xEF,0xFC, // 'z'
	0x0F,0x0F,0x86,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x18,0x38,0x1E,0x03,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0xF0,0x78, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0x80, // '|'
	0xF0,0x7C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x06,0x01,0xC1,0xC1,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x0F,0x87,0x80 // '}'
};
const GFXglyph Arimo_Regular_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   8,    0,    0 }, // ' '
	  {     1,   3,  17,   9,    3,  -17 }, // '!'
	  {     8,   8,   5,  10,    1,  -17 }, // '"'
	  {    13,  14,  17,  14,    0,  -17 }, // '#'
	  {    43,  14,  20,  14,    0,  -18 }, // '$'
	  {    78,  20,  17,  22,    1,  -17 }, // '%'
	  {   121,  16,  17,  17,    1,  -17 }, // '&'
	  {   155,   3,   5,   6,    1,  -17 }, // '''
	  {   157,   8,  22,   9,    1,  -17 }, // '('
	  {   179,   8,  22,   9,    0,  -17 }, // ')'
	  {   201,  10,   9,  10,    0,  -17 }, // '*'
	  {   213,  13,  12,  15,    1,  -14 }, // '+'
	  {   233,   4,   6,   8,    2,   -3 }, // ','
	  {   236,   7,   2,   9,    1,   -7 }, // '-'
	  {   238,   4,   3,   8,    2,   -3 }, // '.'
	  {   240,   8,  17,   8,    0,  -17 }, // '/'
	  {   257,  12,  17,  14,    1,  -17 }, // '0'
	  {   283,  11,  17,  14,    2,  -17 }, // '1'
	  {   307,  12,  17,  14,    1,  -17 }, // '2'
	  {   333,  12,  17,  14,    1,  -17 }, // '3'
	  {   359,  12,  17,  14,    1,  -17 }, // '4'
	  {   385,  12,  17,  14,    1,  -17 }, // '5'
	  {   411,  12,  17,  14,    1,  -17 }, // '6'
	  {   437,  12,  17,  14,    1,  -17 }, // '7'
	  {   463,  12,  17,  14,    1,  -17 }, // '8'
	  {   489,  12,  17,  14,    1,  -17 }, // '9'
	  {   515,   4,  13,   8,    2,  -13 }, // ':'
	  {   522,   4,  16,   8,    2,  -13 }, // ';'
	  {   530,  13,  13,  15,    1,  -14 }, // '<'
	  {   552,  13,   8,  15,    1,  -12 }, // '='
	  {   565,  13,  13,  15,    1,  -14 }, // '>'
	  {   587,  12,  17,  14,    1,  -17 }, // '?'
	  {   613,  21,  20,  25,    2,  -17 }, // '@'
	  {   666,  16,  17,  16,    0,  -17 }, // 'A'
	  {   700,  14,  17,  17,    2,  -17 }, // 'B'
	  {   730,  16,  17,  18,    1,  -17 }, // 'C'
	  {   764,  15,  17,  18,    2,  -17 }, // 'D'
	  {   796,  14,  17,  17,    2,  -17 }, // 'E'
	  {   826,  13,  17,  16,    2,  -17 }, // 'F'
	  {   854,  17,  17,  20,    1,  -17 }, // 'G'
	  {   891,  14,  17,  18,    2,  -17 }, // 'H'
	  {   921,   3,  17,   7,    2,  -17 }, // 'I'
	  {   928,  11,  17,  13,    0,  -17 }, // 'J'
	  {   952,  15,  17,  17,    2,  -17 }, // 'K'
	  {   984,  11,  17,  14,    2,  -17 }, // 'L'
	  {  1008,  16,  17,  20,    2,  -17 }, // 'M'
	  {  1042,  14,  17,  18,    2,  -17 }, // 'N'
	  {  1072,  18,  17,  20,    1,  -17 }, // 'O'
	  {  1111,  14,  17,  17,    2,  -17 }, // 'P'
	  {  1141,  18,  22,  20,    1,  -17 }, // 'Q'
	  {  1191,  15,  17,  18,    2,  -17 }, // 'R'
	  {  1223,  15,  17,  17,    1,  -17 }, // 'S'
	  {  1255,  13,  17,  15,    1,  -17 }, // 'T'
	  {  1283,  14,  17,  18,    2,  -17 }, // 'U'
	  {  1313,  16,  17,  16,    0,  -17 }, // 'V'
	  {  1347,  24,  17,  24,    0,  -17 }, // 'W'
	  {  1398,  15,  17,  16,    1,  -17 }, // 'X'
	  {  1430,  15,  17,  17,    1,  -17 }, // 'Y'
	  {  1462,  14,  17,  16,    1,  -17 }, // 'Z'
	  {  1492,   6,  22,   8,    2,  -17 }, // '['
	  {  1509,   8,  17,   8,    0,  -17 }, // '\'
	  {  1526,   6,  22,   8,    0,  -17 }, // ']'
	  {  1543,  13,   9,  13,    0,  -17 }, // '^'
	  {  1558,  14,   2,  14,    0,    3 }, // '_'
	  {  1562,   6,   4,   9,    1,  -18 }, // '`'
	  {  1565,  13,  13,  14,    1,  -13 }, // 'a'
	  {  1587,  12,  17,  15,    2,  -17 }, // 'b'
	  {  1613,  11,  13,  13,    1,  -13 }, // 'c'
	  {  1631,  12,  17,  15,    1,  -17 }, // 'd'
	  {  1657,  12,  13,  14,    1,  -13 }, // 'e'
	  {  1677,   8,  17,   8,    0,  -17 }, // 'f'
	  {  1694,  12,  18,  15,    1,  -13 }, // 'g'
	  {  1721,  11,  17,  15,    2,  -17 }, // 'h'
	  {  1745,   3,  17,   6,    2,  -17 }, // 'i'
	  {  1752,   6,  22,   7,   -1,  -17 }, // 'j'
	  {  1769,  11,  17,  13,    2,  -17 }, // 'k'
	  {  1793,   3,  17,   7,    2,  -17 }, // 'l'
	  {  1800,  17,  13,  21,    2,  -13 }, // 'm'
	  {  1828,  11,  13,  15,    2,  -13 }, // 'n'
	  {  1846,  12,  13,  14,    1,  -13 }, // 'o'
	  {  1866,  12,  18,  15,    2,  -13 }, // 'p'
	  {  1893,  12,  18,  15,    1,  -13 }, // 'q'
	  {  1920,   7,  13,   9,    2,  -13 }, // 'r'
	  {  1932,  11,  13,  13,    1,  -13 }, // 's'
	  {  1950,   8,  16,   8,    0,  -16 }, // 't'
	  {  1966,  11,  13,  15,    2,  -13 }, // 'u'
	  {  1984,  12,  13,  12,    0,  -13 }, // 'v'
	  {  2004,  18,  13,  18,    0,  -13 }, // 'w'
	  {  2034,  12,  13,  12,    0,  -13 }, // 'x'
	  {  2054,  13,  18,  13,    0,  -13 }, // 'y'
	  {  2084,  11,  13,  13,    1,  -13 }, // 'z'
	  {  2102,   9,  22,   9,    0,  -17 }, // '{'
	  {  2127,   3,  22,   7,    2,  -17 }, // '|'
	  {  2136,   9,  22,   9,    0,  -17 } // '}'
};
const GFXfont Arimo_Regular_24 PROGMEM = {
(uint8_t  *)Arimo_Regular_24Bitmaps,(GFXglyph *)Arimo_Regular_24Glyphs,0x20, 0x7E, 28};