// Creates a looping ticker tape using WS2812B Neopixel strips. 
// You should have 7 LED strips with the "Data In" pin for each connected to the D1-D7 pins on an Arduino Uno. (They also need power and ground connections)
// The Arduino listens for text on its built in serial port at 960bd,n,8,1 and then scrolls it out on the LEDs. It uses a buffer to the scrolling speed can be smoothed out.
// To send the serial data, you can connect the Arduino to a computer via USB and then use the Arduino Serial Monitor. Set the monitor to 9600 and "No Line Ending".
// Type stuff in the top bar and press enter and watch it scroll out on the LEDs. 
// You can also connect other serial devices like a bluetooth HC-05 to the RX pin on the Arduino. 
// For more info see the full article at http://wp.josh.com/Build-a-giant-scrolling-ticker-tape-from-WS2812B-Neopixels-and-an-Arduino-Uno

// Change this to be at least as long as your pixel string (too long will work fine, just will be a little slower)

#define PIXEL_COUNT 60      // Length of the strings in pixels. I am using a 1 meter long strings that have 60 LEDs per meter. 


#define FRAME_DELAY_MS 50    // Max time in ms for each frame while scrolling. Lower numbers make for faster scrolling (until we run out of speed).
                           // Note that we automatically start speeding up when the buffer starts getting full and then slow down again when it starts getting empty. 


// Define the color we will send for on pixels. Each value is a byte 0-255. 

#define COLOR_R 0x40                                          
#define COLOR_G 0x00                                          
#define COLOR_B 0x00     
//#define COLOR_W 0x00     // Uncomment this line if you are using RGBW LED strips

// This defines the end of a message for looping. Send this at the end of a message to make it loop.

#define MESSAGE_TERMINATOR '|'

/*------------------- FONT CUT TOP HERE -------------------------------*/

// This nice 5x7 font from here...
// http://sunge.awardspace.com/glcd-sd/node4.html

// Converted from font to C code with...
// https://github.com/bigjosh/MacroMarquee/blob/master/fontgen/cpp/fontconvert.cpp
// ...but you can also manually create fonts by just typing 1's and 0's if you are patient and you squint. 

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

// The hard part of actually sending data out the strings is below. 

#define RES_NS 500000   // Width of the low gap between bits to cause a frame to latch, from the WS2812B datasheets (recently increased to 50us for newer chips)

// We access the digital pins directly for speed. See https://www.arduino.cc/en/Reference/PortManipulation

#define PIXEL_PORT  PORTD  // Data register of the pins the pixels are connected to
#define PIXEL_DDR   DDRD   // Direction register of the pins the pixels are connected to

// Sends a full 8 bits down all the pins, represening a single color of 1 pixel

/// Assumes interrupts are *off* on entry and returns with them off.

// At 16Mhz, each cycle is 62.5ns. We will aim for...
// T0H 375ns =  6 cycles
// T1H 750ns = 12 cycles
// T1L 375ns =  6 cycles

// Send one bit to each LED string using WS2812B signaling based on the value of the coresponding bit in `bits`
// EX: if bit #3 in `bits` is 1, then a 1 waveform is sent out on digital pin 3. 

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

    // We assume here that whatever called `sendBits()` will take long enough to call it again that we will have some space between the signals.
                                  
    // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is a relatively long 5us)
    
} 


// Just wait long enough without sending any bits to cause the pixels to latch and display the last sent frame
// This is the "RESET" period in the WS2812B datasheets

void show() {
  _delay_us( (RES_NS / 1000UL) + 1);       // Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}


// Must be big enough to hold serial data coming in while we are showing a message on the LEDs
// Also must be big enough to hold a full display worth of data, so BUFFER_SIZE * FONT_WIDTH >= PIXEL_COUNT.

#define BUFFER_SIZE 1000

byte buffer[ BUFFER_SIZE ];

unsigned bufferHead =0;     // Add new chars here
unsigned bufferTail =0;     // So we can discard new bytes if buffer overflows (I think this is better than overwriting, right?)

boolean looping=false;     // Are we currently looping?
unsigned loopStart =0;      // Where the current looped message starts
unsigned nextLoopStart =0; 

// Note that we do not need a loop end  since the loop will always end at the most recently recieved byte

// Add a byte to the end of the buffer. Siliently discards byte if buffer already full. 

void inline appendBuffer( const byte b ) {   
   
   if (b == '\r' || b=='\n' ) {              // Start looping with the most recently entered message?
      
      if (!looping) {                        // If we are already looping, then ignore a new empty message
         loopStart=nextLoopStart;
         nextLoopStart=bufferHead;
         looping=true;    
      }
      
   } else {
      
      unsigned newBufferHead = bufferHead+1;
      if (newBufferHead==BUFFER_SIZE) newBufferHead=0;
      if (newBufferHead!=bufferTail) {
         buffer[ bufferHead ] = b;
         bufferHead=newBufferHead;
         looping=false;    // if we got a new byte then stop current loooping         
      }
   }
   
}

// Set the whole buffer to spaces so it does not look ugly

void initBuffer() {
  for( unsigned i=0; i<BUFFER_SIZE;i++ )  {
    buffer[i]= ' ';
  }
}

void appendStringToBuffer( const char *s ) {

  while (*s) {
    appendBuffer( *s );
    s++;
  }
  
}

// Is there a byte ready to be read from the serial port?

boolean inline serialReady() {
  return (UCSR0A & _BV(RXC0) ) != 0;
  
}

// Read the next pending byte from the serial port (check to make sure one is ready before reading)

byte inline serialRead() {
  return UDR0;
}

// Read any pending serial bytes into the buffer

void inline serialPollRX() {

  if (serialReady()) {
    appendBuffer( serialRead());    
  }

}

// Send a byte of color data out the pins to the LED strings
// If bit `n` in `bits` is 1, then the byte `color` is sent on digital pin `n`. Otherwise the byte 0x00 is sent on that pin. 

// Note WS2812B strips expect the color bits in highest-bit-first order as per datasheet.

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

// Send 3 bytes of color data (R,G,B) for a single pixel down all the connected strings at the same time

// Note that WS2812B strips expect color bytes in G,R,B order as per datasheet. 

static inline void sendCol( byte colBits  ) {  

  sendByte( colBits , COLOR_G );    // WS2812 takes colors in GRB order
  
  serialPollRX();                   // Poll serial port to see if anything new came in. This is the best time to do it when we have some extra time.
  
  sendByte( colBits , COLOR_R );    // WS2812 takes colors in GRB order
  
  serialPollRX();                   // Poll serial port to see if anything new came in. This is the best time to do it when we have some extra time.
  
  sendByte( colBits , COLOR_B );    // WS2812 takes colors in GRB order  
  
  #ifdef COLOR_W 
    sendByte( colBits , COLOR_W );    // White for RGBW strips. Uncomment line above to use these strips. 
  #endif
  
}

// Send a full batch of data out to the LEDs

// Display the bytes from buffer. The byte at pos will is shown at the rightmost position,
// pos-1 in the next rightmost position, etc until all the pixels in the display is filled. 
// col is the starting col to show. col=0 will show the leftmost col of the rightmost positon, 
// col=7 will show the entire rightmost letter. 

// Returns the leftmost byte that was actually displayed (even if just one col)

// (Why do we go backwartds and then forwards? Becuase I am not smart enough to get the math right to treat everything
// as backwards all the time. FIst is make it work, second is make it fast. If this ends up being too slow for big signs
// then we can optimize it.)

boolean updateLEDs( const unsigned pos, const byte col ) {

  // Becuase of the way the LEDs work, we have to send the leftmost pixels first
  // So first we have to figure out where in the buffer that is. For simplicity, we will
  // iteratively back up our way there.
  
  unsigned p = pos;
  unsigned c = col;
    
  for( unsigned x = 0; x < PIXEL_COUNT ; x++ ) {
        
    if (c) {
      
      c--;
      
    } else {
      
      c=FONT_WIDTH-1;
      
      if (p) {
        p--;
      } else {
        p=BUFFER_SIZE-1;
      }
      
    }
        
  }
  
  // OK, now p and c point to the letter can column of the leftmost row of pixels to put on the screen.

  const unsigned leftmostp = p;     // Remember the leftmost for later

  // Now actually output the pixels to the display in left to right order

  for( unsigned x = 0; x < PIXEL_COUNT ; x++ ) {
    
      const byte b = buffer[p];         // get next character to display

      const byte font_index = b -ASCII_OFFSET;     // The letter in the font of the current byte to display
      
      sendCol( pgm_read_byte_near( &fontdata[font_index ][c] ) );    // The column in the font of the current letter (read from PROGMEM)

      c++;

      if (c==FONT_WIDTH) {       // Finished with this letter?

        // Move on to next letter

        c=0;
        p++;

        if (p==BUFFER_SIZE) {
          
          if (looping) {
            p=loopStart;
          } else {
            p=0;        
          }
        }
      }

  }       
  
  // Latch everything we just sent into the pixels so it is actually displayed
  show();

  // Return the leftmost byte that was actually displayed
  return leftmostp;

}


void setup() {

  // Set up serial. We really only use the Ardunio `Serial` class to initialize the port for us, after that we do everything
  // ourselves manually becuase we need to keep interrupts off and the Aurduino stuff is just too slow for our timing requirements. 

  Serial.begin(9600);         // Set up the serial port for recieving

  UCSR0B &= ~ _BV( TXEN0 );   // Disable the serial TX pin (digital pin 1) so we can use it as digital IO for an LED string
                              // Note that you can remove this line if you want to have bidirectional serial communication, 
                              // but then you will loose a string of LEDS and will need to make the font be only 6 pixels tall.
                              
  // initialize LED strip pins
  
  PIXEL_DDR |= 0xff;         // Set all 8 pins to output mode (note that digital pin 0 is controlled by the serial port so this has no effect on it)

  // This blinking signal seems to reset some stuck pixels and leaves all outputs cleanly low
  PIXEL_PORT |= 0xff;       // Set all outputs to 1
  delay( 500);
  PIXEL_PORT &= ~0xff;      // Set all outputs to 0
  delay( 500);
  PIXEL_PORT |= 0xff;       // Set all outputs to 1
  delay( 500);
  PIXEL_PORT &= ~0xff;      // Set all outputs to 0
  delay( 500);


  // Turn off interrupts, forever. For now on we are repsonsible for polling the incoming serial data.
  // We turn off interrupts becuase if they happen durring our WS2812B waveform generation then they will mess up 
  // our timing. We can not just turn them off durring waveform generation and then turn back on when we are done becuase
  // they would be off long enough to drop bytes, so we have to poll. 
  
  cli();

  // Set the buffer to spaces so it does not look ugly. 
  initBuffer(); 

  // Show something on startup so we know it is working
  // (you can delete this branding if you are that kind of person)
  
//  appendStringToBuffer( "SimpleTickertape from JOSH.COM |" );
  appendStringToBuffer( "01234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ" );

}

// Keep track of the the current leftmost displayed spot in the buffer

unsigned displayStart = 0;
byte displayShift = 0;       // How many pixels into the leftmost char are we

void loop() {  

  // Delay so text does not scroll to quickly...
  // Remeber we can not use millis() here since interrupts are permenetly off
  // We also have to manually keep checking the serial RX so that it does not overflow

  for( unsigned i=0;i < FRAME_DELAY_MS ; i++ ) {
    _delay_us(900);   // Pool just often enough that we do not miss any serial bytes at 9600bd (1 byte about 1ms) 
    serialPollRX();    
  }
  
  if (displayStart!=bufferHead) {
    const unsigned lastDisplayByte = updateLEDs( displayStart , displayShift );
    
    displayShift++;
    
    if (displayShift==FONT_WIDTH) {
      displayShift=0;
      displayStart++;
      if (displayStart==BUFFER_SIZE) {
        displayStart=0;
      }
      
    }
    
  } else {    //displayStart==bufferHead so we have shown everything in the buffer, should we loop around?
  
    if (looping) {
      
      displayStart = loopStart;
      
    }    
    
  }
  
  
  return;  
}
