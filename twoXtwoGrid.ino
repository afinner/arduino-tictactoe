/*the user input
for a 2x2 grid*/


bool switchedState1;
bool switchedState2;
bool switchedState3;
bool switchedState4;

bool led1 = false;
bool led2 = false;
bool led3 = false;
bool led4 = false;

bool change = false;

bool change1 = false;
bool change2 = false;
bool change3 = false;
bool change4 = false;

bool gameActive = true;
bool playerRed = true;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  for(int pinNumber = 6; pinNumber < 14; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }   
}

void loop() {
  while(gameActive == true) {

    change = false;
    
    if( change == false ) {
      switchedState1 = led1 or (digitalRead(2) == HIGH);
      change1 = (switchedState1 != led1);
      change = change1;
    }

    if( change == false ) {
      switchedState2 = led2 or (digitalRead(3) == HIGH);
      change2 = (switchedState2 != led2);
      change = change2;
    }
    
    if( change == false ) {
      switchedState3 = led3 or (digitalRead(4) == HIGH);
      change3 = (switchedState3 != led3);
      change = change3;
    }
    
    if( change == false ) {
      switchedState4 = led4 or (digitalRead(5) == HIGH);
      change4 = (switchedState4 != led4);
      change = change4;
    }

   if( change == true ) {

    if( change1 == true ) {
        led1 = true;
        if( playerRed == true ) {
          digitalWrite(6, HIGH);
        } else {
          digitalWrite(7, HIGH);
        }
    }
    if( change2 == true ) {
        led2 = true;
        if( playerRed == true ) {
          digitalWrite(8, HIGH);
        } else {
          digitalWrite(9, HIGH);
        }
    }
    if( change3 == true ) {
        led3 = true;
        if( playerRed == true ) {
          digitalWrite(10, HIGH);
        } else {
          digitalWrite(11, HIGH);
        }
    }
    if( change4 == true ) {
        led4 = true;
        if( playerRed == true ) {
          digitalWrite(12, HIGH);
        } else {
          digitalWrite(13, HIGH);
        }
    }
    
    if( led1 and led2 and led3 and led4 ) {
      gameActive == false;
    } 
    
    playerRed = !playerRed;
 
   } else {
    delay(200);
   }
  }
  
}
