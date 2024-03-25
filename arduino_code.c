        unsigned long previousMillis = 0;  		 // Variável para armazenar o tempo da última mudança de estado
        unsigned long effectInterval = 500;      // Intervalo desejado em milissegundos
        unsigned long emergencyInterval = 600;

        int leftButtonPin = 13;  // Define leftButtonPin no pino digital 13
        int ledLeftAPin = 10;    // Define ledPin no pino digital 10
        int ledLeftBPin = 11;    // Define ledPin no pino digital 11
        int ledLeftCPin = 12;    // Define ledPin no pino digital 12

        int rightButtonPin = 2;  // Define rightButtonPin no pino digital 2
        int ledRightAPin = 5;    // Define ledPin no pino digital 5
        int ledRightBPin = 4;    // Define ledPin no pino digital 4
        int ledRightCPin = 3;    // Define ledPin no pino digital 3

        int emergencyButtonPin = 8;  // Define emergencyButtonPin no pino digital 8

        int initialLeftButtonState = LOW;       //Define o estado inicial do botao como LOW
        int initialRightButtonState = LOW;      //Define o estado inicial do botao como LOW
        int initialEmergencyButtonState = LOW;  //Define o estado inicial do botao como LOW


        void setup() {
            pinMode(ledLeftAPin, OUTPUT);   // Define ledLeftAPin (pino 10) como saída
            pinMode(ledLeftBPin, OUTPUT);   // Define ledLeftBPin (pino 11) como saída
            pinMode(ledLeftCPin, OUTPUT);   // Define ledLeftCPin (pino 12) como saída

            pinMode(ledRightAPin, OUTPUT);  // Define ledRightAPin (pino 5) como saída
            pinMode(ledRightBPin, OUTPUT);  // Define ledRightBPin (pino 4) como saída
            pinMode(ledRightCPin, OUTPUT);  // Define ledRightCPin (pino 3) como saída

            pinMode(leftButtonPin, INPUT);  // Define leftButtonPin (pino 13) como entrada
            pinMode(rightButtonPin, INPUT); // Define rightButtonPin (pino 2) como entrada

            pinMode(emergencyButtonPin, INPUT); // Define emergencyButtonPin (pino 8) como entrada
        }

        void checkButtons(){
            int currentRightButtonState = digitalRead(rightButtonPin);              //Lê o estado atual do botão
            int currentLeftButtonState = digitalRead(leftButtonPin);                //Lê o estado atual do botão
            int currentEmergencyButtonState = digitalRead(emergencyButtonPin);      //Lê o estado atual do botão


            if(currentRightButtonState != initialRightButtonState){

                while(digitalRead(ledRightCPin)== HIGH){
                    digitalWrite(ledRightAPin, LOW);
                    digitalWrite(ledRightBPin, LOW);
                    digitalWrite(ledRightCPin, LOW);
                    break;
                }

                delay(250);
                dynamicEffect(ledRightAPin);
                dynamicEffect(ledRightBPin);
                dynamicEffect(ledRightCPin);

            }else{ //caso botao esteja LOW/desligado, desliga os leds

                digitalWrite(ledRightAPin,LOW);
                digitalWrite(ledRightBPin,LOW);
                digitalWrite(ledRightCPin,LOW);
            }

            if(currentLeftButtonState != initialLeftButtonState){

                while(digitalRead(ledLeftCPin)== HIGH){
                    digitalWrite(ledLeftAPin, LOW);
                    digitalWrite(ledLeftBPin, LOW);
                    digitalWrite(ledLeftCPin, LOW);
                    break;
                }

                delay(250);
                dynamicEffect(ledLeftAPin);
                dynamicEffect(ledLeftBPin);
                dynamicEffect(ledLeftCPin);

            }else{ //caso botao esteja desligado, desliga os leds

                digitalWrite(ledLeftAPin,LOW);
                digitalWrite(ledLeftBPin,LOW);
                digitalWrite(ledLeftCPin,LOW);
            }

            if(currentEmergencyButtonState != initialEmergencyButtonState){
                while(digitalRead(ledLeftAPin)== HIGH){
                    PORTD &= B1111100;// Define os pinos 2 e 3 no PORTD como LOW
                    PORTB &= B1111100;// Define os pinos 4, 5, 10, 11 e 12 no PORTB como LOW
                    break;
                }

                emergencyEffect();

            }else{

                PORTD &= B1111100;// Define os pinos 2 e 3 no PORTD como LOW
                PORTB &= B1111100;// Define os pinos 4, 5, 10, 11 e 12 no PORTB como LOW
            }
        }

        void dynamicEffect(int ledPin){
            long currentMillis = millis();

            if (currentMillis - previousMillis >= effectInterval) {
                previousMillis = currentMillis;
                digitalWrite(ledPin,HIGH);
                delay(effectInterval);
            }
        }

        void emergencyEffect(){
            long currentMillis = millis();

            if (currentMillis - previousMillis >= emergencyInterval) {
                previousMillis = currentMillis;
                delay(500);
                PORTD |= B1111100;// Define os pinos 2 e 3 no PORTD como LOW
                PORTB |= B1111100;// Define os pinos 4, 5, 10, 11 e 12 no PORTB como LOW
                delay(emergencyInterval);
            }
        }

        void loop() {
            checkButtons();
        }

