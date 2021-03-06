#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/**********************************************************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

Pick one up today in the adafruit shop! ------> http://www.adafruit.com/category/63_98

These displays use I2C or SPI to communicate, 2 to 5 pins are required to interface.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries, with contributions from the open source community.
Scrolling code contributed by Michael Gregg. Dynamic buffer allocation based on work by Andrew Canaday.
BSD license, check license.txt for more information. All text above must be included in any redistribution
**********************************************************************************************************/
#include <JC_Button.h>


#include "src/Display Library/7 Segment/AFBM4026.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

//Todo: Look into I2C as a 2 wire solution instead of using SPI's 5 wire connection, I2C oled code below 

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 22 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
AFBM_4026 sevSeg(30, 31, 32);


// #define OLED_MOSI   9
// #define OLED_CLK   10
// #define OLED_DC    11
// #define OLED_CS    12
// #define OLED_RESET 13
// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


#define selectButton 24
#define	scrollButton 25
#define revButton    26
#define fireButton   27
Button Select(selectButton);
Button Scroll(scrollButton);
Button Rev(revButton);
Button Fire(fireButton);

//All of the global stuff//

#define ammoSensor  A0
byte ammo;
bool oneTimeTrigger = 0;

//TODO: Put this code and all other code into respective library's 
// byte ammoTypes[] = {
// 	06,10,12,18,22,25,35,50
// };

// static String menuItems[] = {
// 	"Back",
// 	"Info"
// };

// String muzzleFlashItems[] = {
// 	"Red",
// 	"Green",
// 	"Blue"
// };


void setup() {
	// Serial.begin(9600);
	// if(!oled.begin(SSD1306_SWITCHCAPVCC)) {
	// 	Serial.println(F("SSD1306 allocation failed"));
	// 	for(;;);
	// }
	Select.begin();
	Scroll.begin();
	pinMode(ammoSensor, INPUT_PULLUP);
	// oled.display();
	delay(2000);
}


void loop() {
	Serial.print ("Select:");
	Serial.print(dectectSelectButton());
	Serial.print ("     ");
	Serial.print ("Scroll:");
	Serial.print(dectectScrollButton());
	Serial.print ("     ");
	Serial.print ("Rev:");
	Serial.print(dectectRevButton());
	Serial.print ("     ");
	Serial.print ("Fire:");
	Serial.print(dectectFireButton());
	// if(ammo > 99) ammo = 99;
	// if(detectShot() && oneTimeTrigger == true){
	// 	ammo--;
	// 	oneTimeTrigger = false;
	// };
	// if(!detectShot() && !oneTimeTrigger){
	// 	oneTimeTrigger = true;
	// }
	// mainScreen();
	for(int i=0; i<99; i++){
		sevSeg.sendNum(i);
	}
	delay(100);
}

// Show the Ammo counter plus any attachments (Flashlight etc)
void mainScreen(){
	oled.clearDisplay();
	oled.setTextColor(SSD1306_WHITE);


	oled.setTextSize(4);
	oled.setCursor(43,36);

	if (ammo < 10)
	{
		oled.print("0");
		oled.print(ammo);
	}
	else
	{
		oled.print(ammo);
	}


	oled.setTextSize(1);
	oled.setCursor(92,57);
	oled.print("RNDS");

	oled.display();

}

const unsigned long heldPress(600);
int dectectSelectButton(){
	if (Select.read() == true){
		if (Select.pressedFor(heldPress) == true){
			return 2;
		}
	return 1;
	}
	else{
		return 0;
	}
}
int dectectScrollButton(){
	if (Scroll.read() == true){
		if (Scroll.pressedFor(heldPress) == true){
			return 2;
		}
	return 1;
	}
	else{
		return 0;
	}
}
int dectectRevButton(){
	if (Rev.read() == true){
		if (Rev.pressedFor(heldPress) == true){
			return 2;
		}
	return 1;
	}
	else{
		return 0;
	}
}
int dectectFireButton(){
	if (Fire.read() == true){
		if (Fire.pressedFor(heldPress) == true){
			return 2;
		}
	return 1;
	}
	else{
		return 0;
	}
}


bool detectShot(){
	if (analogRead(ammoSensor) > 200){
		return true;
	}
	else{
		if (analogRead(ammoSensor) < 100)
		{
			return false;
		}
	}
}


//showMenu is Not Done!
// void showMenu(int selectedItem, int pageNum) {
// display.clearDisplay();
// display.setCursor(0,0);

// switch (pageNum){
// 	case 0: //not in any pages
// 		//This code is from Marcus Wynwood (An Epic Guy!(https://github.com/mwynwood))
// 		for(int i=0; i<menuItems->length(); i++) {
// 			if(selectedItem == i){
// 				display.print("> ");
// 			}
// 			else{
// 			display.print("  ");
// 			}
// 			display.println(menuItems[i]);
// 		}
// 	break;

// 	case 1: //in Muzzle Flash Page 

// 	break;
// }
// display.display();
// }