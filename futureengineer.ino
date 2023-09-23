#include <Adafruit_BNO055.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>


// BNO055 object
Adafruit_BNO055 bno = Adafruit_BNO055(55);
//TCS3475 object
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);


//Global Variables

// Constants
const int distance1 = 70;
const int leftdistance = 100;
const int turningangle = 280;

// // Steering Constrains
// const int front = 103;
// const int left = 70;
// const int right = 135;




// Pins definition for motor, servo, and ultrasonic sensors
const int servo = 2;
const int m1 = 4;
const int m2 = 5;


bool steering_tracking = true;
int setpoint[13] = {0,265,175,86,8,265,175,86,8,265,175,86,8} ;
int currentSetpoint = 0;

// float filtered_distance(int sensor) {
//     float filter = 0;
//     for (int i = 0; i < 5; i++) {
//         filter += get_distance(sensor);
//     }
//     return filter / 5;
// }
    set_steer(110); // turn straight
    delay(1000);
    set_motor(190); // start moving
}

void loop() {

   

    // Update sensor data
    updateSensorData();
   
    // Print sensor data
    print_sensor_data();
    start_steeringTracking();
    set_heading(currentSetpoint); // (heading, steering tracking flag)

    int i = 1;
    while (i<=12)
    {  
        updateSensorData();
        print_sensor_data();
        set_heading(currentSetpoint);
        if (sensorData.distances[FRONT] < distance1) {
            stop_steeringTracking();
            set_steer(150);
            set_motor(190);
            while(sensorData.angle >= setpoint[i])
            {  
                set_motor(160);
                updateSensorData();
                // Serial.println("****Turning Left*********");
                // print_sensor_data();
                // Serial.print("  Setpoint: ");
                // Serial.print(currentSetpoint);
            }
            updateSensorData();
            currentSetpoint = setpoint[i];
            start_steeringTracking();
            set_heading(currentSetpoint);
            set_motor(190);

            // Serial.print("  Setpoint: ");
            // Serial.print(currentSetpoint);
            i=i+1;
            delay(400);
         }
   
    }
    stop_motor();

   
}
