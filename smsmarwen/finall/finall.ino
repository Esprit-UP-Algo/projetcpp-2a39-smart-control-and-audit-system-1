#include <SoftwareSerial.h>

SoftwareSerial SIM900A(10, 11);

bool messageSent = true;  // Set to true initially to allow the first message

void setup() {
  Serial.begin(9600);
  SIM900A.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String rx_str = Serial.readStringUntil('\n');  // Read a line from the Serial Monitor

    Serial.print("Received: ");
    Serial.println(rx_str);

    sendMessage(rx_str);
    messageSent = true;  // Set the flag to true after sending the message
  }

  if (SIM900A.available() > 0) {
    char c = SIM900A.read();
    Serial.write(c);  // Print received GSM module data to Serial Monitor
  }
}

void sendMessage(const String &message) {
  if (messageSent) {  // Check if a message has already been sent
    SIM900A.println("AT+CMGF=1");  // Set SMS text mode
    delay(1000);
    printResponse();

    SIM900A.print("AT+CMGS=\"+21653273182\"\r");  // Replace with the desired phone number
    delay(1000);
    printResponse();

    SIM900A.print(message);
    delay(100);

    SIM900A.write(26);  // Send Ctrl+Z to indicate the end of the message
    delay(1000);
    printResponse();

    // messageSent = true;  // No need to set messageSent here
  }
}

void printResponse() {
  while (SIM900A.available()) {
    char c = SIM900A.read();
    Serial.write(c);
  }
}
