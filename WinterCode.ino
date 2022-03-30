#define PIXEL_COUNT 192      // Length of the strings in pixels. I am using 3.048 meter long strings that have 60 LEDs per meter. 


#define FRAME_DELAY_MS 15    // Max time in ms for each frame while scrolling. Lower numbers make for faster scrolling (until we run out of speed).
                           // Note that we automatically start speeding up when the buffer starts getting full and then slow down again when it starts getting empty. 

#define COLOR_R 0x59                                          
#define COLOR_G 0x00                                          
#define COLOR_B 0x00

/*------------------- FONT CUT TOP HERE -------------------------------*/


// Font details:
// 1) Each char is fixed 5x7 pixels. 
// 2) Each byte is one column.
// 3) Columns are left to right order, leftmost byte is leftmost column of pixels.
// 4) Each column is 8 bits high.
// 5) Bit #7 is top line of char, Bit #1 is bottom.
// 6) Bit #0 is always 0 so that the RX pin can be used for serial input.
// 7) Include optional space to put between chars (or leave out for chars that should touch each other).

// defines ascii characters 0x20-0x7F (32-127)
// PROGMEM after variable name as per https://www.arduino.cc/en/Reference/PROGMEM

#define ASCII_OFFSET (0x20)     // ASCII code of 1st char in font array

#define ASCII_NONPRINT (0x80)   // ASCII code of char to show for chars not included in the font (could also be a space)

#define FONT_WIDTH 6      

const byte fontdata[][FONT_WIDTH] PROGMEM = {

    { // ASCII 0x20 (' ')
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x21 ('!')
       0b00000000,
       0b00000000,
       0b11111010,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x22 ('"')
       0b00000000,
       0b11100000,
       0b00000000,
       0b11100000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x23 ('#')
       0b00101000,
       0b11111110,
       0b00101000,
       0b11111110,
       0b00101000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x24 ('$')
       0b00100100,
       0b01010100,
       0b11111110,
       0b01010100,
       0b01001000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x25 ('%')
       0b11000100,
       0b11001000,
       0b00010000,
       0b00100110,
       0b01000110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x26 ('&')
       0b01101100,
       0b10010010,
       0b10101010,
       0b01000100,
       0b00001010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x27 (''')
       0b00000000,
       0b10100000,
       0b11000000,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x28 ('(')
       0b00000000,
       0b00111000,
       0b01000100,
       0b10000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x29 (')')
       0b00000000,
       0b10000010,
       0b01000100,
       0b00111000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2A ('*')
       0b00010000,
       0b01010100,
       0b00111000,
       0b01010100,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2B ('+')
       0b00010000,
       0b00010000,
       0b01111100,
       0b00010000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2C (',')
       0b00000000,
       0b00001010,
       0b00001100,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2D ('-')
       0b00010000,
       0b00010000,
       0b00010000,
       0b00010000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2E ('.')
       0b00000000,
       0b00000110,
       0b00000110,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x2F ('/')
       0b00000100,
       0b00001000,
       0b00010000,
       0b00100000,
       0b01000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x30 ('0')
       0b01111100,
       0b10001010,
       0b10010010,
       0b10100010,
       0b01111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x31 ('1')
       0b00000000,
       0b01000010,
       0b11111110,
       0b00000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x32 ('2')
       0b01000010,
       0b10000110,
       0b10001010,
       0b10010010,
       0b01100010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x33 ('3')
       0b10000100,
       0b10000010,
       0b10100010,
       0b11010010,
       0b10001100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x34 ('4')
       0b00011000,
       0b00101000,
       0b01001000,
       0b11111110,
       0b00001000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x35 ('5')
       0b11100100,
       0b10100010,
       0b10100010,
       0b10100010,
       0b10011100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x36 ('6')
       0b00111100,
       0b01010010,
       0b10010010,
       0b10010010,
       0b00001100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x37 ('7')
       0b10000000,
       0b10001110,
       0b10010000,
       0b10100000,
       0b11000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x38 ('8')
       0b01101100,
       0b10010010,
       0b10010010,
       0b10010010,
       0b01101100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x39 ('9')
       0b01100000,
       0b10010010,
       0b10010010,
       0b10010100,
       0b01111000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3A (':')
       0b00000000,
       0b01101100,
       0b01101100,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3B (';')
       0b00000000,
       0b01101010,
       0b01101100,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3C ('<')
       0b00000000,
       0b00010000,
       0b00101000,
       0b01000100,
       0b10000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3D ('=')
       0b00101000,
       0b00101000,
       0b00101000,
       0b00101000,
       0b00101000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3E ('>')
       0b10000010,
       0b01000100,
       0b00101000,
       0b00010000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x3F ('?')
       0b01000000,
       0b10000000,
       0b10001010,
       0b10010000,
       0b01100000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x40 ('@')
       0b01001100,
       0b10010010,
       0b10011110,
       0b10000010,
       0b01111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x41 ('A')
       0b01111110,
       0b10001000,
       0b10001000,
       0b10001000,
       0b01111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x42 ('B')
       0b11111110,
       0b10010010,
       0b10010010,
       0b10010010,
       0b01101100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x43 ('C')
       0b01111100,
       0b10000010,
       0b10000010,
       0b10000010,
       0b01000100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x44 ('D')
       0b11111110,
       0b10000010,
       0b10000010,
       0b01000100,
       0b00111000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x45 ('E')
       0b11111110,
       0b10010010,
       0b10010010,
       0b10010010,
       0b10000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x46 ('F')
       0b11111110,
       0b10010000,
       0b10010000,
       0b10000000,
       0b10000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x47 ('G')
       0b01111100,
       0b10000010,
       0b10000010,
       0b10001010,
       0b01001100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x48 ('H')
       0b11111110,
       0b00010000,
       0b00010000,
       0b00010000,
       0b11111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x49 ('I')
       0b00000000,
       0b10000010,
       0b11111110,
       0b10000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4A ('J')
       0b00000100,
       0b00000010,
       0b10000010,
       0b11111100,
       0b10000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4B ('K')
       0b11111110,
       0b00010000,
       0b00101000,
       0b01000100,
       0b10000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4C ('L')
       0b11111110,
       0b00000010,
       0b00000010,
       0b00000010,
       0b00000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4D ('M')
       0b11111110,
       0b01000000,
       0b00100000,
       0b01000000,
       0b11111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4E ('N')
       0b11111110,
       0b00100000,
       0b00010000,
       0b00001000,
       0b11111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x4F ('O')
       0b01111100,
       0b10000010,
       0b10000010,
       0b10000010,
       0b01111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x50 ('P')
       0b11111110,
       0b10010000,
       0b10010000,
       0b10010000,
       0b01100000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x51 ('Q')
       0b01111100,
       0b10000010,
       0b10001010,
       0b10000100,
       0b01111010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x52 ('R')
       0b11111110,
       0b10010000,
       0b10011000,
       0b10010100,
       0b01100010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x53 ('S')
       0b01100010,
       0b10010010,
       0b10010010,
       0b10010010,
       0b10001100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x54 ('T')
       0b10000000,
       0b10000000,
       0b11111110,
       0b10000000,
       0b10000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x55 ('U')
       0b11111100,
       0b00000010,
       0b00000010,
       0b00000010,
       0b11111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x56 ('V')
       0b11111000,
       0b00000100,
       0b00000010,
       0b00000100,
       0b11111000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x57 ('W')
       0b11111110,
       0b00000100,
       0b00011000,
       0b00000100,
       0b11111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x58 ('X')
       0b11000110,
       0b00101000,
       0b00010000,
       0b00101000,
       0b11000110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x59 ('Y')
       0b11000000,
       0b00100000,
       0b00011110,
       0b00100000,
       0b11000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5A ('Z')
       0b10000110,
       0b10001010,
       0b10010010,
       0b10100010,
       0b11000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5B ('[')
       0b00000000,
       0b00000000,
       0b11111110,
       0b10000010,
       0b10000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5C ('\')
       0b01000000,
       0b00100000,
       0b00010000,
       0b00001000,
       0b00000100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5D (']')
       0b10000010,
       0b10000010,
       0b11111110,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5E ('^')
       0b00100000,
       0b01000000,
       0b10000000,
       0b01000000,
       0b00100000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x5F ('_')
       0b00000010,
       0b00000010,
       0b00000010,
       0b00000010,
       0b00000010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x60 ('`')
       0b00000000,
       0b10000000,
       0b01000000,
       0b00100000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x61 ('a')
       0b00000100,
       0b00101010,
       0b00101010,
       0b00101010,
       0b00011110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x62 ('b')
       0b11111110,
       0b00010010,
       0b00100010,
       0b00100010,
       0b00011100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x63 ('c')
       0b00011100,
       0b00100010,
       0b00100010,
       0b00100010,
       0b00000100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x64 ('d')
       0b00011100,
       0b00100010,
       0b00100010,
       0b00010010,
       0b11111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x65 ('e')
       0b00011100,
       0b00101010,
       0b00101010,
       0b00101010,
       0b00011000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x66 ('f')
       0b00010000,
       0b01111110,
       0b10010000,
       0b10000000,
       0b01000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x67 ('g')
       0b00010000,
       0b00101000,
       0b00101010,
       0b00101010,
       0b00111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x68 ('h')
       0b11111110,
       0b00010000,
       0b00100000,
       0b00100000,
       0b00011110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x69 ('i')
       0b00000000,
       0b00100010,
       0b10111110,
       0b00000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6A ('j')
       0b00000100,
       0b00000010,
       0b00100010,
       0b10111100,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6B ('k')
       0b00000000,
       0b11111110,
       0b00001000,
       0b00010100,
       0b00100010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6C ('l')
       0b00000000,
       0b10000010,
       0b11111110,
       0b00000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6D ('m')
       0b00111110,
       0b00100000,
       0b00011000,
       0b00100000,
       0b00011110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6E ('n')
       0b00111110,
       0b00010000,
       0b00100000,
       0b00100000,
       0b00011110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x6F ('o')
       0b00011100,
       0b00100010,
       0b00100010,
       0b00100010,
       0b00011100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x70 ('p')
       0b00111110,
       0b00101000,
       0b00101000,
       0b00101000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x71 ('q')
       0b00010000,
       0b00101000,
       0b00101000,
       0b00011000,
       0b00111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x72 ('r')
       0b00111110,
       0b00010000,
       0b00100000,
       0b00100000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x73 ('s')
       0b00010010,
       0b00101010,
       0b00101010,
       0b00101010,
       0b00000100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x74 ('t')
       0b00100000,
       0b11111100,
       0b00100010,
       0b00000010,
       0b00000100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x75 ('u')
       0b00111100,
       0b00000010,
       0b00000010,
       0b00000100,
       0b00111110,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x76 ('v')
       0b00111000,
       0b00000100,
       0b00000010,
       0b00000100,
       0b00111000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x77 ('w')
       0b00111100,
       0b00000010,
       0b00001100,
       0b00000010,
       0b00111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x78 ('x')
       0b00100010,
       0b00010100,
       0b00001000,
       0b00010100,
       0b00100010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x79 ('y')
       0b00110000,
       0b00001010,
       0b00001010,
       0b00001010,
       0b00111100,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7A ('z')
       0b00100010,
       0b00100110,
       0b00101010,
       0b00110010,
       0b00100010,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7B ('{')
       0b00000000,
       0b00010000,
       0b01101100,
       0b10000010,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7C ('|')
       0b00000000,
       0b00000000,
       0b11111110,
       0b00000000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7D ('}')
       0b00000000,
       0b10000010,
       0b01101100,
       0b00010000,
       0b00000000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7E ('~')
       0b00010000,
       0b00010000,
       0b01010100,
       0b00111000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x7F
       0b00010000,
       0b00111000,
       0b01010100,
       0b00010000,
       0b00010000,
       0b00000000,  // Interchar space
    },
    { // ASCII 0x80 (box)
       0b11111110,    
       0b10000010,
       0b10000010,
       0b10000010,
       0b11111111,
       0b00000000,  // Interchar space
    },
    
};



/*------------------- FONT CUT BOTTOM HERE -------------------------------*/

#define RES_NS 500000   // Width of the low gap between bits to cause a frame to latch, from the WS2812B datasheets (recently increased to 50us for newer chips)

#define PIXEL_PORT  PORTD  // Data register of the pins the pixels are connected to
#define PIXEL_DDR   DDRD   // Direction register of the pins the pixels are connected to



static void inline sendBits( const byte bits ) { 
                
    __asm__ __volatile__ (
                              
      "out %[port], %[onBits] \n\t"                 // Both 0 and 1 waveforms start with signal going high

      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "out %[port], %[bits]   \n\t"                 // (1 cycles) - Any pins that have a `0` in `bits` will now go low forming a `0` signal 
                                                    // ==========
                                                    // (6 cycles) - T0H = 375ns
      

      "nop \n\t "                                   // (1 cycles) - Any pins that had a `1` in `bits` are still high here.
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "nop \n\t "                                   // (1 cycles) 
      "out %[port], __zero_reg__ \n\t"              // (1 cycles) - Now all pins that were sending a `1` now go low. 
                                                    // ==========
                                                    // (6 cycles) - T0H = 375ns

          
      ::                                            // No outputs
      [port]    "I" (_SFR_IO_ADDR(PIXEL_PORT)),
      [bits]   "d" (bits),
      [onBits]   "d" (0xff)
      
    );
}





void show() {
  
  _delay_us( (RES_NS / 1000UL) + 1);       // Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}


// Must be big enough to hold serial data coming in while we are showing a message on the LEDs

#define BUFFER_SIZE 1000

byte buffer[ BUFFER_SIZE ];

volatile unsigned int buffer_len = 0;      // Number of bytes currently in buffer

// Add a byte to the end of the buffer. Siliently discards byte if buffer already full. 

void inline appendToBuffer( const byte b ) {

  if ( buffer_len < BUFFER_SIZE ) {
    buffer[ buffer_len++ ] = b;
  }
  
}


void inline appendStringToBuffer( const char *s ) {

  while (*s) {
    appendToBuffer( *s );
    s++;
  }


// Check if a byte is available from the serial port. If so, read it and add it to the buffer. 

  if (UCSR0A & _BV(RXC0) ) {      // If there is a byte ready in the recieve buffer
    appendToBuffer( UDR0 );       // Read it and add to our buffer. Note reading the byte clears the RXC0 flag
  }
  
}



static inline void sendByte( const byte bits , byte color ) {

    sendBits( (color & 0b10000000) ? bits : 0x00 );
    sendBits( (color & 0b01000000) ? bits : 0x00 );
    sendBits( (color & 0b00100000) ? bits : 0x00 );    
    sendBits( (color & 0b00010000) ? bits : 0x00 );
    sendBits( (color & 0b00001000) ? bits : 0x00 );
    sendBits( (color & 0b00000100) ? bits : 0x00 );
    sendBits( (color & 0b00000010) ? bits : 0x00 );    
    sendBits( (color & 0b00000001) ? bits : 0x00 );
  
}



static inline void sendCol( byte colBits  ) {  

  sendByte( colBits , COLOR_G );    // WS2812 takes colors in GRB order
  
  
  
  sendByte( colBits , COLOR_R );    // WS2812 takes colors in GRB order
  
  
  
  sendByte( colBits , COLOR_B );    // WS2812 takes colors in GRB order  
 
}

// Send a full batch of data out to the LEDs

// s points to an array of bytes that should be displayed. len is the number of bytes in that array to display. 

// shift will shift the display `shift` columns to the left. By shifting through we can smooth scroll it across the width of the char. 
// when shift=0 that means start at col 0, which means send the full char width of the first char.

// Returns true if there is more left in the buffer that did not fit on the display.

 byte updateLEDs( const byte *s , unsigned int len , byte shift ) {
 
  unsigned int pixel_count = PIXEL_COUNT;  // How many pixels left to fill on the display?

  byte font_col =0;     // What column of the current font char are we currently on? 

  while (len && pixel_count) {

    if (shift) {

      // Use up all the shift columns without actually sending them to the display
      shift--;
      
    } else {

      byte font_index = (*s) -ASCII_OFFSET;     // The letter in the font of the current byte to display
      
      sendCol( pgm_read_byte_near( &fontdata[font_index ][font_col] ) );    // The column in the font of the current letter (read from PROGMEM)
      pixel_count--;

    }

    font_col++;

    if (font_col==FONT_WIDTH) {       // Finished with this letter?

      // Move on to next letter

      font_col=0;       
      
      s++;
      len--;

    }

  }
       

  // If the display is longer than the string, fill any remaining pixels with blanks

  while (pixel_count--) {
    sendCol(  0  );    // All pixels in column off               
  }
    
  // Latch everything we just sent into the pixels so it is actually displayed
  show();

  return len>0;     // If len>0 then we ran out of pixels before we ran out of message to display
}




void setup() {

  Serial.begin(9600);         // Set up the serial port for recieving

  UCSR0B &= ~ _BV( TXEN0 );   // Disable the serial TX pin (digital pin 1) so we can use it as digital IO for an LED string
                              // Note that you can remove this line if you want to have bidirectional serial communication, 
                              // but then you will loose a string of LEDS and will need to make the font be only 6 pixels tall.
                              
  // initialize LED strip pins
  
  PIXEL_DDR |= 0xff;         // Set all 8 pins to output mode (note that digital pin 0 is controlled by the serial port so this has no effect on it)

  // This blinking signal seems to reset some stuck pixels and leaves all outputs cleanly low
  PIXEL_PORT |= 0xff;       // Set all outputs to 1
  delay( 100);
  PIXEL_PORT &= ~0xff;      // Set all outputs to 0
  delay( 100);
  PIXEL_PORT |= 0xff;       // Set all outputs to 1
  delay( 100);
  PIXEL_PORT &= ~0xff;      // Set all outputs to 0
  delay( 100);


  cli();

 // Show something on startup so we know it is working
 
  appendStringToBuffer( "  .....   booting up  .....    " );

}


// Shift keeps track of how many columns shifted over the display currently is. By shifting one column at a 
// time, we can smoothly scroll text across the display.
byte shift = 0;



void loop() {

  
  for( unsigned int i=0;i < FRAME_DELAY_MS ; i++ ) {
     _delay_us(900);   // Pool just often enough that we do not miss any serial bytes at 9600bd (1 byte about 1ms) 
    

    appendStringToBuffer( "...looping...text" );
    
  }


  // Send out the signals to the LED

  byte more_flag = updateLEDs( buffer , buffer_len , shift );

  if (more_flag) {

    // If there is more of the buffer to display, then we shift over one column before the next update to smooth scroll forward

    shift++;

    // If shifting gets us to the end of the current char, then we move everything forward by one char

    if (shift== FONT_WIDTH) {

      shift = 0 ;

      buffer_len--;

    
      
      for( unsigned int i =0; i < buffer_len ; i++ ) {
          
          buffer[i] = buffer[i+1];
           
      }
      
    }
    
  }
  

}