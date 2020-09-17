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

	// display.clearDisplay();
	// if(detectShot() == true){
	// 	ammo--;
	// 	if (ammo == 0)
	// 	{
	// 		ammo == 50;
	// 	}
	// 	mainMenu();
	// }
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

//max char length is 21

//Back                              //Go back to the main page (aka ammo counter).
//Muzzle Flash Setup                //Setup the muzzle flash (options for changing the color and turning it off)
//Bat/Volt Warn Setup               //Setup the battery/voltage warning mode or turn it off.
//Info                              //Show info about this project and how much fucking time i put into this (2/09/2020 at 7.48 PM)



display.setCursor(0,0);


switch (pageNum){
	case 0: //not in any pages
		//This code is from Marcus Wynwood (An Epic Guy!)
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


//splashScreen is Done!
//Todo: make the splashScreen a bitmap
void splashScreen() {
#define shortSquareBracket 13
#define longSquareBracket  32

	display.clearDisplay();

		//For the top square bracket

			//for the left of the top square bracket
			display.drawFastVLine(48,0,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(49,0,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(50,0,shortSquareBracket,SSD1306_WHITE);

			//for the middle of the top square bracket
			display.drawFastHLine(48,0,longSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(48,1,longSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(48,2,longSquareBracket,SSD1306_WHITE);

			//for the right of the top square bracket
			display.drawFastVLine(77,0,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(78,0,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(79,0,shortSquareBracket,SSD1306_WHITE);


		//For the right square bracket


			//for the top of the right square bracket
			display.drawFastHLine(83,16,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(83,17,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(83,18,shortSquareBracket,SSD1306_WHITE);

			//for the middle of the right square bracket
			display.drawFastVLine(94,16,longSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(95,16,longSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(96,16,longSquareBracket,SSD1306_WHITE);

			//for the bottom of the right square bracket
			display.drawFastHLine(83,45,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(83,46,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(83,47,shortSquareBracket,SSD1306_WHITE);

		//For the bottom square bracket 


			//for the left of the bottom square bracket
			display.drawFastVLine(48,51,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(49,51,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(50,51,shortSquareBracket,SSD1306_WHITE);

			//for the middle of the bottom square bracket
			display.drawFastHLine(48,61,longSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(48,62,longSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(48,63,longSquareBracket,SSD1306_WHITE);

			//for the right of the bottom square bracket
			display.drawFastVLine(77,51,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(78,51,shortSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(79,51,shortSquareBracket,SSD1306_WHITE);


		//For the left square bracket


			//for the top of the left square bracket
			display.drawFastHLine(32,16,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(32,17,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(32,18,shortSquareBracket,SSD1306_WHITE);

			//for the middle of the left square bracket
			display.drawFastVLine(32,16,longSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(33,16,longSquareBracket,SSD1306_WHITE);
			display.drawFastVLine(34,16,longSquareBracket,SSD1306_WHITE);

			//for the bottom of the left square bracket
			display.drawFastHLine(32,45,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(32,46,shortSquareBracket,SSD1306_WHITE);
			display.drawFastHLine(32,47,shortSquareBracket,SSD1306_WHITE);

 	display.setTextSize(1);
  	display.setTextColor(SSD1306_WHITE);
	display.setCursor(52,28);
	display.println("AFBM");



	display.display();
	delay(2000);
	display.clearDisplay();
	display.display();
}