
//////////////////////
// Library Includes //
//////////////////////
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

/////////////////////
// Hardware Hookup //
/////////////////////
// R0, G0, B0, R1, G1, B1 should be connected to pins
// 2, 3, 4, 5, 6, and 7 respectively. Their pins aren't defined,
// because they're controlled directly in the library. These pins
// can be moved (somewhat):

// CLK be on PORTB!
// CLK can be moved but must remain on PORTB(8, 9, 10, 11, 12, 13)
#define CLK 11
#define LAT 10
#define OE  9

#define A   A0
#define B   A1
#define C   A2
#define D   A3 // Comment this line out if you're using a 32x16

////////////////////////////////////////////////
/////   Instantiate RGBmatrixPanel Class   /////
////////////////////////////////////////////////

/* ========== For 32x32 LED panels: ========== */
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false); // 32x32

int8_t cursorX = 0;  // Cursor x position, initialize left
int8_t cursorY = 0;  // Cursor y position, initialize top

void setup()
{
  matrix.begin();       // Initialize the matrix.
//  blankEasel(); // Blank screen
//  loadBitmap();
  Serial.begin(9600);   // Start serial

  //print_text("Hi");

  //matrix.drawRect(1, 1, 30, 30, matrix.Color333(1, 0 ,0));
  
}

void print_text( char *inputString )
{
  char c;
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  // matrix.setCursor(cursorX, cursorY);

  
  while (*inputString)
  {
      c = *inputString;
      if (c == '\n')   // CTRL+ENTER = newline / linefeed
      {
        cursorY += 8; // Increase another line
        cursorX = 0;  // Back to beginning
        matrix.setCursor(cursorX, cursorY); // Update cursor
      }
      else if (c == '\r') // ENTER
      {
        cursorY += 8; // Increase another line
        matrix.setCursor(cursorX, cursorY); // Update cursor
      }
      else // Otherwise it's a printable character
      {
        matrix.print(c); // Print char
        cursorX += 6; // Update our cursor
        if (cursorX >= (matrix.width() - 6))
        { // If x is to far to the right, go down a line:
          cursorX = 0;
          cursorY += 8;
        }
      }

      inputString++;
  }
}


void loop()
{
   static int corner_pos=0;
   int        side_length;
   char c;
   static int dir=1;

   side_length = 32 - corner_pos*2;

   // erase current rectangle
   matrix.drawRect(corner_pos, corner_pos, side_length, side_length, matrix.Color333(0, 0 ,0));
   //Serial.print("Erasing ");
   //Serial.print(corner_pos);
   //Serial.print(",");
   //Serial.println(side_length);

   // move in/out by one   
   
   if (dir==1)
   {
      corner_pos++;
      if (corner_pos == 16)
      {
        dir = -1;
        corner_pos = 15;
      }
   }
   else
   {
      corner_pos--;
      if (corner_pos < 0)
      {
        dir = 1;
        corner_pos = 0;
      }
   }
   
   side_length = 32 - corner_pos*2;
   
   // and draw new rectangle
   matrix.drawRect(corner_pos, corner_pos, side_length, side_length, matrix.Color333(1, 0 ,0));
   //Serial.print("Drawing ");
   //Serial.print(corner_pos);
   //Serial.print(",");
   //Serial.println(side_length);

   //while (!Serial.available());
   //c = Serial.read();
   delay(50);
   
}
