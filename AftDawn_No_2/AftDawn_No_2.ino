//AftDawn's code//
//Goal: to get a 7 seg display thru 2 4026 IC's to work with a button to decrement

//Goal: not done


const int button = 6;
const int enable = 5;
const int tensSet = 4;
const int onesSet = 3;
const int reset = 2;

int currentNum = 31;


bool Trigger = true;

  
void setup() {
//setting up the pins
  pinMode(button, INPUT);
  pinMode(enable, OUTPUT);
  pinMode(tensSet, OUTPUT);
  pinMode(onesSet, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(reset, LOW);
}

void loop() {
//I love this bit of code, V This bit is apart of my small debounce code that ties in very well with the "make_Num" function so as it will only call it only 
  if(!digitalRead(button) && Trigger){
    currentNum--;
    make_Num(currentNum);
    Trigger = false;
    
    Serial.println("Number State:");
    Serial.println(currentNum);
    delay(50);
  }
  if(digitalRead(button) && !Trigger){
    Serial.println("Running Else Code");
    Trigger = true;
    delay(50);
  }
 if(currentNum <= 0){
  currentNum = 31;
  Serial.println("Running Reset Code");
 }
}

void make_Num(int Number) {
  int tens = 0;
  int ones = 0;
  tens = Number / 10;
  ones = Number % 10;


  delay(1);
  digitalWrite(enable, LOW);
  digitalWrite(reset, HIGH);
  delay(1);
  digitalWrite(reset, LOW);
  int pulseTens = tens;
  while(pulseTens > 0){
    digitalWrite(tensSet, HIGH);
    delay(1);
    digitalWrite(tensSet, LOW);
    delay(1);
    pulseTens--;
  }
  
  int pulseOnes = ones;
  while(pulseOnes > 0){
    digitalWrite(onesSet, HIGH);
    delay(1);
    digitalWrite(onesSet, LOW);
    delay(1);
    pulseOnes--;
  }
  digitalWrite(enable, HIGH);
}

