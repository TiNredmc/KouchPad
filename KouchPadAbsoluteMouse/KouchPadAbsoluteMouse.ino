
// include library and config for PS/2 device
#include <ps2.h>
PS2 mouse(6, 5); // mouse pinout (clockT10,dataT11)

#include <USBHID.h>
int IsShift, IsCtrl, IsAlt, IsFn, IsSup, Isrised, Islowed;
volatile int touchmode;
int but = PB8;

void interruptFunction() {
  if (touchmode == 1) {
    touchmode = 0;
    digitalWrite(33, LOW);
  } else {
    touchmode = 1;
    digitalWrite(33, HIGH);
  }
}

void kbd_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
  mouse.write(0xe8);
  mouse.read();  // ack byte
  mouse.write(0x03); // x1  ( x1 * 64  +  x2 * 16  +  x3 * 4  +  x4   == modebyte )
  mouse.read();  // ack byte
  mouse.write(0xe8);
  mouse.read();  // ack byte
  mouse.write(0x00); // x2
  mouse.read();  // ack byte
  mouse.write(0xe8);
  mouse.read();  // ack byte
  mouse.write(0x00); // x3
  mouse.read();  // ack byte
  mouse.write(0xe8);
  mouse.read();  // ack byte
  mouse.write(0x00); // x4
  mouse.read();  // ack byte
  mouse.write(0xf3); // set samplerate 20 (stores mode)
  mouse.read();  // ack byte
  mouse.write(0x14);//equa to 20 in DECIMAL
  mouse.read();  // ack byte
  delayMicroseconds(100);
}


HIDAbsMouse touchpad;

void setup() {
  // put your setup code here, to run once:
  USBHID_begin_with_serial(HID_KEYBOARD_MOUSE);
  Keyboard.begin();
  pinMode(but, INPUT_PULLDOWN);
  pinMode(33, OUTPUT);
  attachInterrupt(but, interruptFunction, RISING);
  kbd_init();
}
// all importatn variables for us:
byte mstat1;
byte mstat2;
byte mxy;
byte mx;
byte my;
byte mz;

unsigned int cx, cy;

void kbd_run() {
  if (mz > 85) {

    if (cx != 0 && cy != 0 ) {

      if (cy > 1 && cy < 710) {
        if (cx > 10 && cx < 400) {
          if (IsCtrl == 1) {
            Keyboard.release(KEY_LEFT_CTRL);  // Left Control
            IsCtrl = 0 ;
          } else if ( IsCtrl == 0 ) {
            Keyboard.press(KEY_LEFT_CTRL);
            IsCtrl = 1 ;
          } delay(100);
        }
        if (cx > 400 && cx < 800) {
          if (IsFn == 1) {
            IsFn = 0 ; //Function
          } else if ( IsFn == 0 ) {
            IsFn = 1 ;
          } delay(100);
        }
        if (cx > 800 && cx < 1200) {
          if (IsSup == 1) {
            Keyboard.release(KEY_LEFT_GUI);  // Supper, Windows, Command
            IsSup = 0 ;
          } else if ( IsSup == 0 ) {
            Keyboard.press(KEY_LEFT_GUI);
            IsSup = 1 ;
          } delay(100);
        }
        if (cx > 1200 && cx < 1600) {
          if (IsAlt == 1) {
            Keyboard.release(KEY_LEFT_ALT);  //Alt
            IsAlt = 0 ;
          } else if ( IsAlt == 0 ) {
            Keyboard.press(KEY_LEFT_ALT);
            IsAlt = 1 ;
          } delay(100);
        }
        if (cx > 1600 && cx < 2000) {
          if (Islowed == 1) {
            Islowed = 0 ; // Lower
          } else if ( Islowed == 0 ) {
            Islowed = 1 ;
          } delay(100);
        }
        if (cx > 2000 && cx < 2800) {
          Keyboard.write(0x20);  //Spacebar
          delay(100);
        }
        if (cx > 2800 && cx < 3200) {
          if (Isrised == 1) {
            Isrised = 0 ; // Riser
          } else if ( Isrised == 0 ) {
            Isrised = 1 ;
          } delay(100);
        }
        if (cx > 3200 && cx < 3600) {
          Keyboard.write(KEY_LEFT_ARROW);  // Left Arrow
          delay(70);
        }
        if (cx > 3600 && cx < 4000) {
          Keyboard.write(KEY_DOWN_ARROW);  // Down Arrow

          delay(70);
        }
        if (cx > 4000 && cx < 4400) {
          Keyboard.write(KEY_UP_ARROW);  // UP Arrow

          delay(70);
        }
        if (cx > 4400 && cx < 4800) {
          Keyboard.write(KEY_RIGHT_ARROW);  // Right Arrow

          delay(70);
        }
      }

      if (cy > 900 && cy < 1900) {
        if (cx > 10 && cx < 400) {
          if (IsShift == 1) {
            Keyboard.release(KEY_LEFT_SHIFT);  //Left Shift
            IsShift = 0 ;
          } else if ( IsShift == 0 ) {
            Keyboard.press(KEY_LEFT_SHIFT);
            IsShift = 1 ;
          } delay(100);
        }
        if (cx > 400 && cx < 800) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F7); //Z and f7
          } else {
            Keyboard.write(0x7A);
          } delay(100);
        }
        if (cx > 800 && cx < 1200) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F8); //X and f8
          } else {
            Keyboard.write(0x78);
          } delay(100);
        }
        if (cx > 1200 && cx < 1600) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F9); //C and f9
          } else {
            Keyboard.write(0x63);
          } delay(100);
        }
        if (cx > 1600 && cx < 2000) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F10); //V and f10
          } else {
            Keyboard.write(0x76);
          } delay(100);
        }
        if (cx > 2000 && cx < 2400) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F11); //B and f11
          } else {
            Keyboard.write(0x62);
          } delay(100);
        }
        if (cx > 2400 && cx < 2800) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F12); //N and f12
          } else {
            Keyboard.write(0x6E);
          } delay(100);
        }
        if (cx > 2800 && cx < 3200) {
          if (Islowed == 1) {
            Keyboard.write(0x7C);/* | */ Islowed = 0; //M and | \\
          } else if (Isrised == 1) {
            Keyboard.write(0x5C);/* \ */ Isrised = 0;
          } else {
            Keyboard.write(0x6D);
          } delay(100);
        }
        if (cx > 3200 && cx < 3600) {
          if (Islowed == 1) {
            Keyboard.write(0x3E);/* > */ Islowed = 0; //< . and ><
          } else if (Isrised == 1) {
            Keyboard.write(0x3C);/* < */ Isrised = 0;
          } else {
            Keyboard.write(0x2C);
          } delay(100);
        }
        if (cx > 3600 && cx < 4000) {
          Keyboard.write(0x2E);  // > .

          delay(100);
        }
        if (cx > 4000 && cx < 4400) {
          Keyboard.write(0x2F);  // ? slash

          delay(100);
        }
        if (cx > 4400 && cx < 4800) {
          Keyboard.write(KEY_RETURN);  // Return A.K.A Enter

          delay(100);
        }
      }

      if (cy > 2000 && cy < 2900) {
        if (cx > 10 && cx < 400) {
          Keyboard.write(KEY_TAB);

          delay(100);
        }
        if (cx > 400 && cx < 800) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F1); //A and f1
          } else {
            Keyboard.write(0x61);
          } delay(100);
        }
        if (cx > 800 && cx < 1200) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F2); //S and f2
          } else {
            Keyboard.write(0x73);
          } delay(100);
        }
        if (cx > 1200 && cx < 1600) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F3); //D and f3
          } else {
            Keyboard.write(0x64);
          } delay(100);
        }
        if (cx > 1600 && cx < 2000) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F4); //F and f4
          } else {
            Keyboard.write(0x66);
          } delay(100);
        }
        if (cx > 2000 && cx < 2400) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F5); //G and f5
          } else {
            Keyboard.write(0x67);
          } delay(100);
        }
        if (cx > 2400 && cx < 2800) {
          if (IsFn == 1) {
            Keyboard.write(KEY_F6); //H and f6
          } else {
            Keyboard.write(0x68);
          } delay(100);
        }
        if (cx > 2800 && cx < 3200) {
          if (Islowed == 1) {
            Keyboard.write(0x5F);/* _ */ Islowed = 0; //J and _ -
          } else if (Isrised == 1) {
            Keyboard.write(0x2D);/* - */ Isrised = 0;
          } else {
            Keyboard.write(0x6A);
          } delay(100);
        }
        if (cx > 3200 && cx < 3600) {
          if (Islowed == 1) {
            Keyboard.write(0x2B);/* + */ Islowed = 0; //K and + =
          } else if (Isrised == 1) {
            Keyboard.write(0x3D);/* = */ Isrised = 0;
          } else {
            Keyboard.write(0x6B);
          } delay(100);
        }
        if (cx > 3600 && cx < 4000) {
          if (Islowed == 1) {
            Keyboard.write(0x7B);/* { */ Islowed = 0; //L and {[
          } else if (Isrised == 1) {
            Keyboard.write(0x5B);/* [ */ Isrised = 0;
          } else {
            Keyboard.write(0x6C);
          } delay(100);
        }
        if (cx > 4000 && cx < 4400) {
          if (Islowed == 1) {
            Keyboard.write(0x7D);/* } */ Islowed = 0;
          } else if (Isrised == 1) {
            Keyboard.write(0x5D);/* ] */ Isrised = 0;
          } else {
            Keyboard.write(0x3B);
          } delay(100);
        }//; and }]
        if (cx > 4400 && cx < 4800) {
          if (Islowed == 1) {
            Keyboard.write(0x7C);/* | */ Islowed = 0; //' and |\\
          } else if (Isrised == 1) {
            Keyboard.write(0x5C);/* \ */ Isrised = 0;
          } else {
            Keyboard.write(0x27);
          } delay(100);
        }
      }

      if (cy > 3000 && cy < 3900) {
        if (cx > 10 && cx < 400) {
          if (Islowed == 1) {
            Keyboard.write(0x7E);/* ~ */ Islowed = 0; // esc and ` ~
          } else if (Isrised == 1) {
            Keyboard.write(0x60);/* ` */ Isrised = 0;
          } else {
            Keyboard.write(KEY_ESC);
          } delay(100);
        }
        if (cx > 400 && cx < 800) {
          if (Islowed == 1) {
            Keyboard.write(0x21);/* ! */ Islowed = 0; // Q and 1 !
          } else if (Isrised == 1) {
            Keyboard.write(0x31);/* 1 */ Isrised = 0;
          } else {
            Keyboard.write(0x71);
          } delay(100);
        }
        if (cx > 800 && cx < 1200) {
          if (Islowed == 1) {
            Keyboard.write(0x40);/* @ */ Islowed = 0; // W and 2 @
          } else if (Isrised == 1) {
            Keyboard.write(0x32);/* 2 */ Isrised = 0;
          } else {
            Keyboard.write(0x77);
          } delay(100);
        }
        if (cx > 1200 && cx < 1600) {
          if (Islowed == 1) {
            Keyboard.write(0x23);/* # */ Islowed = 0; // E and 3 #
          } else if (Isrised == 1) {
            Keyboard.write(0x33);/* 3 */ Isrised = 0;
          } else {
            Keyboard.write(0x65);
          } delay(100);
        }
        if (cx > 1600 && cx < 2000) {
          if (Islowed == 1) {
            Keyboard.write(0x24);/* $ */ Islowed = 0; // R and 4 $
          } else if (Isrised == 1) {
            Keyboard.write(0x34);/* 4 */ Isrised = 0;
          } else {
            Keyboard.write(0x72);
          } delay(100);
        }
        if (cx > 2000 && cx < 2400) {
          if (Islowed == 1) {
            Keyboard.write(0x25);/* % */ Islowed = 0; // T and 5 %
          } else if (Isrised == 1) {
            Keyboard.write(0x35);/* 5 */ Isrised = 0;
          } else {
            Keyboard.write(0x74);
          } delay(100);
        }
        if (cx > 2400 && cx < 2800) {
          if (Islowed == 1) {
            Keyboard.write(0x5E);/* ^ */ Islowed = 0; // Y and 7 &
          } else if (Isrised == 1) {
            Keyboard.write(0x36);/* 6 */ Isrised = 0;
          } else {
            Keyboard.write(0x79);
          } delay(100);
        }
        if (cx > 2800 && cx < 3200) {
          if (Islowed == 1) {
            Keyboard.write(0x26);/* & */ Islowed = 0; // U and 7 &
          } else if (Isrised == 1) {
            Keyboard.write(0x37);/* 7 */ Isrised = 0;
          } else {
            Keyboard.write(0x75);
          } delay(100);
        }
        if (cx > 3200 && cx < 3600) {
          if (Islowed == 1) {
            Keyboard.write(0x2A);/* * */ Islowed = 0; // I and 8 *
          } else if (Isrised == 1) {
            Keyboard.write(0x38);/* 8 */ Isrised = 0;
          } else {
            Keyboard.write(0x69);
          } delay(100);
        }
        if (cx > 3600 && cx < 4000) {
          if (Islowed == 1) {
            Keyboard.write(0x28);/* ( */ Islowed = 0; // O and 9 (
          } else if (Isrised == 1) {
            Keyboard.write(0x39);/* 9 */ Isrised = 0;
          } else {
            Keyboard.write(0x6F);
          } delay(100);
        }
        if (cx > 4000 && cx < 4400) {
          if (Islowed == 1) {
            Keyboard.write(0x29);/* ) */ Islowed = 0; // P and 0 )
          } else if (Isrised == 1) {
            Keyboard.write(0x30);/* 0 */ Isrised = 0;
          } else {
            Keyboard.write(0x70);
          } delay(100);
        }
        if (cx > 4400 && cx < 4800) {
          Keyboard.write(KEY_BACKSPACE);  // Backspace
          Keyboard.releaseAll();
          delay(100);
        }
      }
    }
  }
}
int cxp[4] ;
int cyp[4] ;
int count ;
#define fx(i)  cxp[(count - (i)) & 03]
#define fy(i)  cyp[(count - (i)) & 03]
int dx, dy ;
void mouse_run() {
  if (mz > 100) {
    fx(0) = (((mstat2 & 0x10) << 8) | ((mxy & 0x0F) << 8) | mx ); // 4;  - 1062) * 0.980;
    fy(0) = (((mstat2 & 0x20) << 7) | ((mxy & 0xF0) << 4) | my ); // 4;  - 820) * 0.980;

    if (count >= 2) {
      dx = ((fx(0) - fx(1)) / 2 + (fx(1) - fx(2)) / 2) / 8;
      dy = ((fy(0) - fy(1)) / 2 + (fy(1) - fy(2)) / 2) / 8;
      Mouse.move(dx, -dy, 0);
    }
    count++;

  } else {
    count = 0;
  }
}

void loop() {
  mstat1 = 0;
  mxy = 0;
  mstat2 = 0;
  mx = 0;
  my = 0;

  mouse.write(0xeb);
  mouse.read();// acknowledgement (0xFA)

  mstat1 = mouse.read();
  mxy = mouse.read();
  mz = mouse.read();
  mstat2 = mouse.read();
  mx = mouse.read();
  my = mouse.read();

  if (touchmode == 0) {
    cx = (((mstat2 & 0x10) << 8) | ((mxy & 0x0F) << 8) | mx ) - 1062;
    cy = (((mstat2 & 0x20) << 7) | ((mxy & 0xF0) << 4) | my ) - 820;

    if (cx > 4801) {
      cx = 0 ;
    }
    if (cy > 4086) {
      cy = 0 ;
    }

    kbd_run();
  } else {
    mouse_run();
  }

}
