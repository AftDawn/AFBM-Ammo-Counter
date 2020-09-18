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

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

//Todo: Look into I2C as a 2 wire solution instead of using SPI's 5 wire connection, I2C oled code below 
/*
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
*/

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


//All of the global stuff//

const int ammoSenser = A0;
uint8_t ammo;

int ammoTypes[] = {
	06,10,12,18,22,25,35,50
};

static String menuItems[] = {
	"Back",
	"Info"
};

String muzzleFlashItems[] = {
	"Red",
	"Green",
	"Blue"
};


void setup() {
	Serial.begin(9600);
	if(!display.begin(SSD1306_SWITCHCAPVCC)) {
		Serial.println(F("SSD1306 allocation failed"));
		for(;;);
	}
	pinMode(ammoSenser, INPUT_PULLUP);
	display.display();

	ammo = 50;

}


void loop() {
	int i=0;
	while(true) {
		showMenu(i,0);
		i++;
		if(i==menuItems->length()){
			i=0;
		}
		delay(500);
	}
}


void mainMenu(){

	display.clearDisplay();
	display.setTextSize(1);
	display.setCursor(0,0);
	display.println(ammo);
	display.display();
	Serial.print("ammo is at");
	Serial.println(ammo);

}


bool detectShot(){
	if (analogRead(ammoSenser) > 200){
		return 1;
	}
	else{
		if (analogRead(ammoSenser) < 100)
		{
			return 0;
		}
	}
}


//showMenu is Not Done!
void showMenu(int selectedItem, int pageNum) {
display.clearDisplay();
display.setCursor(0,0);

switch (pageNum){
	case 0: //not in any pages
		//This code is from Marcus Wynwood (An Epic Guy!(https://github.com/mwynwood))
		for(int i=0; i<menuItems->length(); i++) {
			if(selectedItem == i){
				display.print("> ");
			}
			else{
			display.print("  ");
			}
			display.println(menuItems[i]);
		}
	break;

	case 1: //in Muzzle Flash Page 

	break;
}
display.display();
}