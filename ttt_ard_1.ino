
#include "Arduino.h"
#include "PCF8574.h"

#define GRID_SIZE 3

struct ledControl {
  int redpin;
  PCF8574 *redpcf;
  bool redard;
  int bluepin;
  PCF8574 *bluepcf;
  bool blueard;
  int buttonpin;
  PCF8574 *buttonpcf;
  bool buttonard;
};

typedef char gridColumn[GRID_SIZE];

bool isButtonPressed(ledControl *led) {
  if( led->buttonard ) {
    return digitalRead(led->buttonpin) == LOW;
  }
  return led->buttonpcf->digitalRead(led->buttonpin) == LOW;
}

void setRedOn(ledControl *led) {
  if( led->redard ) {
    digitalWrite(led->redpin, HIGH);
  } else {
    led->redpcf->digitalWrite(led->redpin, HIGH);
  }
}

void setBlueOn(ledControl *led) {
  if( led->blueard ) {
    digitalWrite(led->bluepin, HIGH);
  } else {
    led->bluepcf->digitalWrite(led->bluepin, HIGH); 
  }
}

void setRedOff(ledControl *led) {
  if( led->redard ) {
    digitalWrite(led->redpin, LOW);
  } else {
    led->redpcf->digitalWrite(led->redpin, LOW);
  }
}

void setBlueOff(ledControl *led) {
  if( led->blueard ) {
    digitalWrite(led->bluepin, LOW);
  } else {
    led->bluepcf->digitalWrite(led->bluepin, LOW); 
  }
}

void setRedOutput(ledControl *led) {
  if( led->redard ) {
    pinMode(led->redpin, OUTPUT);
  } else {
    led->redpcf->pinMode(led->redpin, OUTPUT);
  }  
}

void setBlueOutput(ledControl *led) {
  if( led->blueard ) {
    pinMode(led->bluepin, OUTPUT);
  } else {
    led->bluepcf->pinMode(led->bluepin, OUTPUT);
  }  
}

void setButtonInput(ledControl *led) {
  if( led->buttonard ) {
    pinMode(led->buttonpin, INPUT_PULLUP);
  } else {
    led->buttonpcf->pinMode(led->buttonpin, INPUT_PULLUP);
  }
}

/////////////

ledControl grid[GRID_SIZE][GRID_SIZE];

PCF8574 pcf8574_1(0x20,A1,A0);
PCF8574 pcf8574_2(0x21,A1,A0);
PCF8574 pcf8574_3(0x22,A1,A0);
PCF8574 pcf8574_4(0x23,A1,A0);

//////////////

bool checkForWin(gridColumn game[], int gridSize, int row, int col) {
    char userValue = game[row][col];

    // horizontal check
    int hCount = 0;
    for (int c = 0; c < gridSize; c++) {
        if (game[row][c] == userValue) {
            hCount++;
        }
    }
    if (hCount == gridSize) {
        return true;
    }

    // vertical check
    int vCount = 0;
    for (int r = 0; r < gridSize; r++) {
        if (game[r][col] == userValue) {
            vCount++;
        }
    }
    if (vCount == gridSize) {
        return true;
    }

    // slope == 1
    bool diagonalOne = (row == col);
    // slope == -1
    bool diagonalTwo = (row == (gridSize - 1) - col);

    // diagonal check
    if (diagonalOne) {
        int countOne = 0;
        for (int i = 0; i < gridSize; i++) {
            if (game[i][i] == userValue) {
                countOne++;
            }
        }
        if (countOne == gridSize) {
            return true;
        }
    }

    // diagonal check
    if (diagonalTwo) {
        int countTwo = 0;
        for (int i = 0; i < gridSize; i++) {
            if (game[(gridSize - 1) - i][i] == userValue) {
                countTwo++;
            }
        }
        if (countTwo == gridSize) {
            return true;
        }
    }

    return false;
}

// 2. Comp Input
bool compInput(gridColumn game[], int gridSize, int *row, int *col) {
  for (int r = 0; r < gridSize; r++) {
    for (int c = 0; c < gridSize; c++) {
      if (game[r][c] == '_') {
          *row = r;
          *col = c;
          Serial.print("Computer: ");
          Serial.print(r);
          Serial.print(",");
          Serial.println(c);
          return true;
      }
    }
  }
  return false;
}

bool compRand(gridColumn game[], int gridSize, int *row, int *col) {
  while(true) {
    int r = random(gridSize);    
    int c = random(gridSize);

    if (game[r][c] == '_') { 
      *row = r;
      *col = c;
      Serial.print("Computer: ");
      Serial.print(r);
      Serial.print(",");
      Serial.println(c);
      return true;
    }
  }
}

bool checkDraw(gridColumn game[], int gridSize) {
  int qtyOfBlanks = 0;
  for (int r = 0; r < gridSize; r++) {
    for (int c = 0; c < gridSize; c++) {
      Serial.print("LookinAt: "); Serial.print(r); Serial.print(","); Serial.print(c); Serial.print(" - "); Serial.println(game[r][c]); 
      if( game[r][c] == '_' ) {
        Serial.print("BlankAt: "); Serial.print(r); Serial.print(","); Serial.println(c);
        qtyOfBlanks += 1;
      }
    }
  }

  Serial.print("QuantityOfBlanks: "); Serial.println(qtyOfBlanks);
  if (qtyOfBlanks == 0) {
      return true;
  } else {
      return false;
  }
}

// Tic-tac-toe
void setup() {
  // Initialize your grid, buttons, and LEDs here
  grid[0][0] = {P7, &pcf8574_1, false, P6, &pcf8574_1, false, P2, &pcf8574_1, true};
  grid[0][1] = {P5, &pcf8574_1, false, P4, &pcf8574_1, false, P3, &pcf8574_1, true};
  grid[0][2] = {P3, &pcf8574_1, false, P2, &pcf8574_1, false, P4, &pcf8574_1, true};
  grid[1][0] = {P1, &pcf8574_1, false, P0, &pcf8574_1, false, P5, &pcf8574_1, true};
  grid[1][1] = {P7, &pcf8574_2, false, P6, &pcf8574_2, false, P6, &pcf8574_1, true};
  grid[1][2] = {P5, &pcf8574_2, false, P4, &pcf8574_2, false, P7, &pcf8574_1, true};
  grid[2][0] = {P3, &pcf8574_2, false, P2, &pcf8574_2, false, 8, &pcf8574_1, true};
  grid[2][1] = {P1, &pcf8574_2, false, P0, &pcf8574_2, false, 9, &pcf8574_1, true};
  grid[2][2] = {13, &pcf8574_1, true, 12, &pcf8574_1, true, 10, &pcf8574_1, true};
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);

  for(int i = 0; i < GRID_SIZE; i++ ) {
    for(int j = 0; j < GRID_SIZE; j++ ) {
      ledControl *led = &grid[i][j];
      setRedOutput(led);
      setBlueOutput(led);
      setButtonInput(led);
    }
  }

  if (pcf8574_1.begin()){
    Serial.println("OK1");
  }else{
    Serial.println("KO1");
  }

  if (pcf8574_2.begin()){
    Serial.println("OK2");
  }else{
    Serial.println("KO2");
  }
  
  if (pcf8574_3.begin()){
    Serial.println("OK3");
  }else{
    Serial.println("KO3");
  }

  if (pcf8574_4.begin()){
    Serial.println("OK4");
  }else{
    Serial.println("KO4");
  }

  for(int i = 0; i < GRID_SIZE; i++ ) {
    for(int j = 0; j < GRID_SIZE; j++ ) {
      ledControl *led = &grid[i][j];
      setRedOff(led);
      setBlueOff(led);
    }
  }
}

void clearGame(gridColumn game[], int gridSize ) {
  for(int i = 0; i < gridSize; i++ ) {
    for(int j = 0; j < gridSize; j++ ) {
      game[i][j] = '_';
    }
  }
}

void displayGrid(gridColumn game[], int gridSize) {
  for(int i = 0; i < gridSize; i++ ) {
    for(int j = 0; j < gridSize; j++ ) {
      if( game[i][j] == 'X' ) {
        setRedOn(&grid[i][j]);
        continue;
      }
      if( game[i][j] == 'O' ) {
        setBlueOn(&grid[i][j]);
        continue;
      }
      setRedOff(&grid[i][j]);
      setBlueOff(&grid[i][j]);
    }
  }  
}

bool userInput(gridColumn game[], int gridSize, int *row, int *col) {
  for( int r=0; r<gridSize; r++) {
    for( int c=0; c<gridSize; c++ ) {
      ledControl *led = &grid[r][c];
      if( (game[r][c] == '_') && isButtonPressed(led) ) {
        *row = r;
        *col = c;
        Serial.print("User: ");
        Serial.print(r);
        Serial.print(",");
        Serial.println(c);
        return true;
      }
    }
  }
  delay(100);
  return false;
}

char game[GRID_SIZE][GRID_SIZE] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
char blank[GRID_SIZE][GRID_SIZE] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}};
int gridSize = GRID_SIZE;

void loop() {

  clearGame(game, gridSize);
  clearGame(blank, gridSize);
  
  while (true) {
    displayGrid(game, gridSize);

    // Prompt user to input move
    int row, col;
    bool userPress = userInput(game, gridSize, &row, &col);

    // Check the user move
    if( userPress && game[row][col] == '_' ) {
      game[row][col] = 'X';    
      displayGrid(game, gridSize);
      
      if (checkForWin(game, gridSize, row, col)) {
        Serial.println("Game is Over - you won");
        break;
      }
      if (checkDraw(game, gridSize)) {
        Serial.println("Game is Over - draw");
        break;
      }

      delay(800);
      
      // Request computer move
      // bool compMoved = compInput(game, gridSize, &row, &col);
      bool compMoved = compRand(game, gridSize, &row, &col);

      if( compMoved == true) {
        game[row][col] = 'O';
        displayGrid(game, gridSize);
  
        // Check the computer move
        if (checkForWin(game, gridSize, row, col)) {
          Serial.println("Game is Over - you lost");
          break;
        }
        if (checkDraw(game, gridSize)) {
          Serial.println("Game is Over - draw");
          break;
        }
      } else {
        Serial.println("Error: Game is Over - computer could not find a move !");
        break;        
      }        
    }
  }

  for( int i=0; i<5; i++ ) {
    delay(1000);
    displayGrid(blank, gridSize);
    delay(1000);
    displayGrid(game, gridSize);
  }
}
