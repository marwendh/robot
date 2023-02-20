void loop() {
  // Set motor directions to rotate the robot in place
  digitalWrite(motor1Dir, HIGH);
  digitalWrite(motor2Dir, LOW);

  // Reset encoder values and robot position
  encoder1Value = 0;
  encoder2Value = 0;
  x = 0.0;
  y = 0.0;
  theta = 0.0;

  // Calculate target angle and distance to rotate
  float targetTheta = 90.0; // degrees
  float distanceToRotate = (wheelbase * PI / 4.0) / distancePerTick; // encoder ticks

  // Rotate the robot until the target angle is reached
  while (theta < targetTheta) {
    // Calculate motor speeds using proportional control
    float error = targetTheta - theta;
    int motor1Speed = turnSpeed + kp * error;
    int motor2Speed = turnSpeed - kp * error;
    motor1Speed = constrain(motor1Speed, 0, maxSpeed);
    motor2Speed = constrain(motor2Speed, 0, maxSpeed);
    analogWrite(motor1PWM, motor1Speed);
    analogWrite(motor2PWM, motor2Speed);

    // Calculate distance traveled and change in orientation
    float distanceTraveled = (encoder1Value + encoder2Value) / 2.0 * distancePerTick;
    float dtheta = (encoder2Value - encoder1Value) * distancePerTick / wheelbase * 180.0 / PI;

    // Update robot position and orientation
    x += distanceTraveled * cos((theta + dtheta / 2.0) * PI / 180.0);
    y += distanceTraveled * sin((theta + dtheta / 2.0) * PI / 180.0);
    theta += dtheta;

    // Reset encoder values
    encoder1Value = 0;
    encoder2Value = 0;
  }

  // Stop the robot and delay to allow it to settle
  analogWrite(motor1PWM, 0);
  analogWrite(motor2PWM, 0);
  delay(1000);
}

