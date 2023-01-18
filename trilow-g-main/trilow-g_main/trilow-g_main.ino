// Final Arduino code for Lunar Project

// Variable Initializations
enum Operation {
  ETHERNET,
  RIGID_PENETROMETER,
  TIP_EXTENDING_DEVICE,
  FLUIDIZATION
};

enum Operation operation;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  switch (operation) {
    case ETHERNET:
      Serial.println("ethernet");
      operation = RIGID_PENETROMETER;
      break;
    case RIGID_PENETROMETER:
      Serial.println("rp");
      operation = TIP_EXTENDING_DEVICE;
      break;
    case TIP_EXTENDING_DEVICE:
      Serial.println("ted");
      operation = FLUIDIZATION;
      break;
    case FLUIDIZATION:
      Serial.println("fluidization");
      operation = ETHERNET;
      break;
  }
}
