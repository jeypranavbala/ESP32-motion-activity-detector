/*
ESP32 Activity Monitoring System
--------------------------------
- MPU6050 accelerometer based motion detection
- Variance-based activity classification
- OLED display visualization
- Sliding window signal processing
- Circular buffer implementation

Author: Jey Pranav Bala
*/

#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// ---------- Hardware Objects ----------
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(128, 64, &Wire);

// ---------- Pin Configuration ----------
#define TOUCH_SENSOR_PIN 33

// ---------- Variance Detection Settings ----------
#define WINDOW_SIZE 20   // Number of samples in sliding window

float accBuffer[WINDOW_SIZE];
int bufferIndex = 0;
bool bufferFull = false;

// ---------- Screen States ----------
enum ScreenState {
  Animation,
  Status
};

ScreenState currentScreenState = Animation;

// ---------- Sitting Detection Timer ----------
unsigned long sittingStartTime = 0;


// =====================================================
// Update circular buffer with new acceleration value
// =====================================================
void updateBuffer(float newValue) {
  accBuffer[bufferIndex] = newValue;
  bufferIndex = (bufferIndex + 1) % WINDOW_SIZE;

  if (bufferIndex == 0) bufferFull = true;
}


// =====================================================
// Calculate variance of values in sliding window
// variance = avg((value - mean)^2)
// =====================================================
float calculateVariance() {
  int size = bufferFull ? WINDOW_SIZE : bufferIndex;
  if (size == 0) return 0;

  float mean = 0;

  // Compute mean
  for (int i = 0; i < size; i++) {
    mean += accBuffer[i];
  }
  mean /= size;

  // Compute variance
  float variance = 0;
  for (int i = 0; i < size; i++) {
    float diff = accBuffer[i] - mean;
    variance += diff * diff;
  }

  return variance / size;
}


// =====================================================
// Setup
// =====================================================
void setup() {
  Serial.begin(115200);  // Optional debugging

  // Initialize MPU6050 sensor
  if (!mpu.begin()) {
    // Serial.println("Sensor initialization failed");
    while (1) delay(10);
  }

  // Serial.println("MPU6050 initialized");

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    // Serial.println("Display initialization failed");
    while (1) delay(10);
  }

  display.display();
  delay(500);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setRotation(0);

  pinMode(TOUCH_SENSOR_PIN, INPUT);
}


// =====================================================
// Main Loop
// =====================================================
void loop() {
  int touchState = digitalRead(TOUCH_SENSOR_PIN);

  if (touchState == HIGH) {
    currentScreenState = Status;
  }

  if (currentScreenState == Animation) {
    displayAnimation();
  }
  else if (currentScreenState == Status) {
    displayStatus();
  }
}


// =====================================================
// Animation Screen
// =====================================================
void displayAnimation() {
  display.clearDisplay();

  int ballSize = 4;
  int ballX = -ballSize;

  while (ballX < display.width()) {
    display.clearDisplay();
    display.fillCircle(ballX, display.height() / 2, ballSize, WHITE);
    display.display();
    ballX++;
    delay(10);
  }

  delay(1000);
}


// =====================================================
// Status Screen (Activity Detection)
// =====================================================
void displayStatus() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Compute total acceleration magnitude
  float total_acceleration = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  // Update sliding window buffer
  updateBuffer(total_acceleration);

  // Compute motion variance
  float motionVariance = calculateVariance();

  // Activity classification based on motion intensity
  String activity;

  if (motionVariance < 0.2) {
    activity = "Sitting";

    if (sittingStartTime == 0) {
      sittingStartTime = millis();
    }
  }
  else if (motionVariance >= 0.2 && motionVariance < 1.5) {
    activity = "Walking";
    sittingStartTime = 0;
  }
  else {
    activity = "Running";
    sittingStartTime = 0;
  }

  // Optional debug output (disabled for production)
  /*
  Serial.print("Total Acc: ");
  Serial.print(total_acceleration);
  Serial.print(" | Variance: ");
  Serial.println(motionVariance);
  */

  // Display activity on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Activity:");
  display.println(activity);
  display.display();

  // Auto return to animation after long sitting
  if (activity == "Sitting" && (millis() - sittingStartTime) > 20000) {
    currentScreenState = Animation;
    sittingStartTime = 0;
  }

  delay(200);  // Sampling interval (5 samples/sec)
}
