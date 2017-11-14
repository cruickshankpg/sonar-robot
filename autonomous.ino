#include <NewPing.h>
#include <AFMotor.h>
#include <StandardCplusplus.h>
#include <vector>

#define MIN_DISTANCE 30
#define MAX_DISTANCE 200
#define SAMPLE_SIZE 5

AF_DCMotor left_motor(3);
AF_DCMotor rght_motor(4);
NewPing sonar(14, 15, MAX_DISTANCE);
std::vector<int> distances (5);

void turn_right()
{
  left_motor.setSpeed(150);
  rght_motor.setSpeed(100);
  left_motor.run(FORWARD);
  rght_motor.run(BACKWARD);
}

void go_straight()
{
  left_motor.setSpeed(200);
  rght_motor.setSpeed(200);
  left_motor.run(FORWARD);
  rght_motor.run(FORWARD);
}

int scan_surroundings()
{
  int distance;
  int averaged_distance;
  int total = 0;

  if (distances.size() >= SAMPLE_SIZE)
  {
    distances.erase(distances.begin());
  }

  distance = (sonar.ping() / US_ROUNDTRIP_CM);

  //Serial.print("\nPinged distance: ");
  //Serial.print(distance);
  if (distance == 0)
  {
    distance = 2 * MAX_DISTANCE;
  }

  distances.push_back(distance);

  for (int ii : distances)
  {
    total += ii;
  }

  averaged_distance = total / distances.size();

  return(averaged_distance);
  
}

void setup()
{
  left_motor.setSpeed(200);
  rght_motor.setSpeed(200);
  rght_motor.run(RELEASE);
  left_motor.run(RELEASE);
  //Serial.begin(9600);
}

void loop()
{
  int distance = scan_surroundings();
  //Serial.print("\nAveraged distance: ");
  //Serial.print(distance);

  if (distance < MIN_DISTANCE)
  {
    turn_right();
  }
  else if (distance > 80)
  {
    go_straight();
  }
  
  delay(2);
}
