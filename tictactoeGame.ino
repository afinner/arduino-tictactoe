
struct pins {
  int red;
  int blue;
  int button;
};

struct ledData {
  bool ledOn;
  pins ledPins;
};

const int rows = 1;
const int cols = 4;
ledData grid[rows][cols];

// setup led pin grid
void setup() {  
  for( int i=0; i<rows; i++) {
    for( int j=0; j<cols; j++ ) {
      pins pinX;
      int ledCounter = (i*cols) + j;
      pinX.red = (ledCounter*2)+6;
      pinX.blue = (ledCounter*2)+7;
      pinX.button = ledCounter+2;

      ledData ledX;
      ledX.ledOn = false;
      ledX.ledPins = pinX;

      grid[i][j] = ledX;

      pinMode(ledX.ledPins.button, INPUT);
      pinMode(ledX.ledPins.red, OUTPUT);
      digitalWrite(ledX.ledPins.red, LOW);
      pinMode(ledX.ledPins.blue, OUTPUT);
      digitalWrite(ledX.ledPins.blue, LOW);    
    };
  };
}

void loop() {
  bool playerRed = true;
  bool gameActive = true;
  
  while(gameActive == true) {
    // check for a move
    bool moved = false;
    for( int i=0; i<rows; i++) {
      for( int j=0; j<cols; j++ ) {
        ledData *led = &grid[i][j];
        moved = (led->ledOn == false) && (digitalRead(led->ledPins.button) == HIGH); 
        if (moved == true) {
          led->ledOn = true;
          if( playerRed == true ) {
            digitalWrite(led->ledPins.red, HIGH);
          } else {
            digitalWrite(led->ledPins.blue, HIGH);
          }
          playerRed = !playerRed;
          break;
        }
      }
      if( moved == true ) break;
    }

    if (moved == true) {   
      // check for end of game
      bool allLedsOn = true;
      for( int i=0; i<rows; i++) {
        for( int j=0; j<cols; j++ ) {
          if(grid[i][j].ledOn == false){
            allLedsOn = false;
            break;
          }
        }
        if (allLedsOn == false) break;
      }
      if(allLedsOn == true) {
        gameActive = false;   
      }
    } else {
      delay(200);
    }   
  }   
}
