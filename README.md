# KouchPad
Turn your old Synaptics touchpad into mini sized keyboard 

# How I got this idea ? 
A long time ago I watched UnboxTherapy's video https://www.youtube.com/watch?v=IHYbix6jRfI . Then yesterday (2019/5/3), I got another Syncaptics from broken laptops. first time I just playing around by learning the special mode and display all data (I needed) on my GU280x16G-7000 VFD module. But it's time to create something (may be ?) useful using everything I have.

# How It works ?
It's very easy (as a principle). The touchpad will init with special mode by enabled the 6 bytes data sending. We can have mousestate and x axis, y axis, z axis . Then I create the 4 by 12 table using EAGLE to draw the layout (I had no idea to use other cad / cam software because it's one I can use). After draw the layout I put the characters in specific positions. then print to (near) real scale (by export as highest DPI image. and then import to MSoffice and resize it!). I printed on the A4 size sticker (made from paper) and stick it on the touchpad. and then I press some several positions to make some marks and calculate by simply devide the maximum y value with 4 and maximum x value with 12 (y is for row x is for column).

# For what ?
I made this for the future project. I will make the handheld computer based on raspberry pi (basically for learning pentest).

# Does it actually works ?
Yeah. It's working if I don't touch the edge of the touchpad.

# What to do next ?
I want to do a lots of implementations 

```
- add support for mouse mode and be-able to switch between mouse mode and keyboard mode on the fly
- make a better enclosure.
- use LARGER touchpad. for example this one https://www.ebay.com/itm/SYNAPTICS-T1005G-Touch-Pad-Mouse-Pad-Pointing-device/322830232985 
- after NICE enclosure done. let add some LED (may be WS2812. I had the 4x4 one.
- add support to Alps touchpad (WIP).
```

# What I need if I wanted too ?
BOM is here

```
- STM32F103. Maybe bluepill board, Blackpill or even maple mini clone like mine(I use maple mini STM32F103CBT6).

- synaptics 920 000842 01 touchpad (To match with everything I done. Use this one but you can use larger pad but need to re-finding the positions of all key and resize the keyboard to your touchpad size or you can creat your own layout).

- Sticker paper (I used the A4 size because I already have it.) this for printing the keyboard layout. or you can use other thing but keep in mind. if it's too thick. touchpad won't detect the finger easily.

-some of wires (4 of them, VCC GND DATA CLOCK)

-USB CABLE for device programming / using the HID.

-Yourself and tools

```

# What I need to do after I got every thing ?
First start at solder the wire to the pads 

```
Pads           Desc       STM32Board
T22            VCC 5v     VIN(this one is USB's 5volt on my maple)
T23            GND        GND
T11            Data       Pin 5 (on maple mini)
T10            Clock      Pin 6 (on maple mini)

```
next setup the STM32Duino (you can google it). Don't forget to install ps/2 library and USB composite library.

```
PS/2 library    ->   https://github.com/PaulStoffregen/PS2Keyboard
USB composite library   ->   https://github.com/arpruss/USBComposite_stm32f1
```

after setting things up. use the KBDortholinaer.png file and resize to the 4.2 by 8.2 centimeter. (Sorry I don't use Imperial unit).I resized in Microsoft Office word. and print it on the sticker paper. after that, Cut the paper (only the kbd layout) the edge less (no black line) side toward the bottom.

![alt_text](https://i.imgur.com/VMUL4QD.jpg)

# Thing that never works 
more than 1 key rollover is not supported due to the hardware (touchpad) limitation. /

# WIP implementations 

```
- Mouse emulation using simple algorithm to make relative mvement on absolute mode.(Code now available)
- Add support to Alps touchpad
```
