int BUTTON1 = 5;
int BUTTON2 = 10;
int BUTTON3 = 4;
int BUTTON4 = 11;

int LED1 = 7;
int LED2 = 8;
int LED3 = 6;
int LED4 = 9;

int lastBUTTON1State = LOW;
int lastBUTTON2State = LOW;
int lastBUTTON3State = LOW;
int lastBUTTON4State = LOW;

int currentBUTTON1State = LOW;
int currentBUTTON2State = LOW;
int currentBUTTON3State = LOW;
int currentBUTTON4State = LOW;

int LED1State = LOW;
int LED2State = LOW;
int LED3State = LOW;
int LED4State = LOW;

int state = 1;
int inputState = 2;
int outputChar = 0;

String left = "";
String right = "";
char oper = ' ';
const char operators[5] = "*/+-";
String binary = "";
String output = "";

void setup() {
    pinMode(BUTTON1, INPUT);
    pinMode(BUTTON2, INPUT);
    pinMode(BUTTON3, INPUT);
    pinMode(BUTTON4, INPUT);

    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
}

void loop() {
    currentBUTTON1State = digitalRead(BUTTON1);
    currentBUTTON2State = digitalRead(BUTTON2);
    currentBUTTON3State = digitalRead(BUTTON3);
    currentBUTTON4State = digitalRead(BUTTON4);

    if(lastBUTTON1State != currentBUTTON1State) {
        LED1State = !LED1State;
    }
    if(lastBUTTON2State != currentBUTTON2State) {
        LED2State = !LED2State;
    }
    if(lastBUTTON3State != currentBUTTON3State) {
        LED3State = !LED3State;
    }
    if(lastBUTTON4State != currentBUTTON4State) {
        LED4State = !LED4State;
    }

    writeLEDs();

    lastBUTTON1State = currentBUTTON1State;
    lastBUTTON2State = currentBUTTON2State;
    lastBUTTON3State = currentBUTTON3State;
    lastBUTTON4State = currentBUTTON4State;

    binary = String(LED1State) + String(LED2State) + String(LED3State) + String(LED4State);
    int decimal = toDecimal(binary);

    if(state == 1) {
        if(decimal == 1) {
            state = inputState;
        } else if(decimal == 2) {
            if(inputState < 4) {
                inputState += 1;
                state = inputState;
            } else if(inputState == 4) {
                state = 5;
            }
        }
    } else if(state == 2) {
        left += String(decimal);
        state = 1;
    } else if(state == 3) {
        oper = operators[decimal - 1];
        state = 1;
    } else if(state == 4) {
        right += String(decimal);
        state = 1;
    } else if(state == 5) {
        if(output == "") {
            int leftInt = left.toInt();
            int rightInt = right.toInt();
            int result = 0;
            if(oper == '*') result = leftInt * rightInt;
            else if(oper == '/') result = rightInt != 0 ? leftInt / rightInt : 0;
            else if(oper == '+') result = leftInt + rightInt;
            else if(oper == '-') result = leftInt - rightInt;
            output = String(result);
        }

        if(outputChar >= output.length()) {
            state = 1;
            inputState = 2;
            outputChar = 0;
            left = "";
            right = "";
            oper = ' ';
            binary = "";
            output = "";
        } else {
            int digit = output[outputChar] - '0';
            String bin = toBinary(digit);
            LED1State = bin[0] - '0';
            LED2State = bin[1] - '0';
            LED3State = bin[2] - '0';
            LED4State = bin[3] - '0';
            writeLEDs();
            delay(1000);
            outputChar++;
        }
    }

    delay(50);
}

void writeLEDs() {
    digitalWrite(LED1, LED1State);
    digitalWrite(LED2, LED2State);
    digitalWrite(LED3, LED3State);
    digitalWrite(LED4, LED4State);
}

int toDecimal(String binary) {
    int decimal = 0;
    for(int i = 0; i < 4; i++) {
        if(binary[i] == '1') {
            decimal += pow(2, 3 - i);
        }
    }
    return decimal;
}

String toBinary(const int decimal) {
    String res = "";
    for (int i = 3; i >= 0; i--) {
        res += ((decimal >> i) & 1) + '0';
    }
    return res;
}
