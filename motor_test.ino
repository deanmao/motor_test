#include <AutoDriver.h>

AutoDriver motor(9, 10);
int direction = 1;

void setup()
{
  motor.configSyncPin(BUSY_PIN, 0);// BUSY pin low during operations;
                                    //  second paramter ignored.
  motor.configStepMode(STEP_FS);   // 0 microsteps per step
  motor.setMaxSpeed(10000);        // 10000 steps/s max
  motor.setFullSpeed(10000);       // microstep below 10000 steps/s
  motor.setAcc(10000);             // accelerate at 10000 steps/s/s
  motor.setDec(10000);
  motor.setSlewRate(SR_530V_us);   // Upping the edge speed increases torque.
  motor.setOCThreshold(OC_2250mA);  // OC threshold 750mA
  motor.setPWMFreq(PWM_DIV_2, PWM_MUL_2); // 31.25kHz PWM freq
  motor.setOCShutdown(OC_SD_DISABLE); // don't shutdown on OC
  motor.setVoltageComp(VS_COMP_DISABLE); // don't compensate for motor V
  motor.setSwitchMode(SW_USER);    // Switch is not hard stop
  motor.setOscMode(INT_16MHZ_OSCOUT_16MHZ); // for motor, we want 16MHz
                                    //  internal osc, 16MHz out. boardB and
                                    //  boardC will be the same in all respects
                                    //  but this, as they will bring in and
                                    //  output the clock to keep them
                                    //  all in phase.
  motor.setAccKVAL(255);           // We'll tinker with these later, if needed.
  motor.setDecKVAL(255);
  motor.setRunKVAL(255);
  motor.setHoldKVAL(20);           // This controls the holding current; keep it low.
  motor.resetDev();
}

void stop() {
  motor.softStop();
  while (motor.busyCheck());
}

void go() {
  if (direction == 1) {
    motor.run(FWD, 200);
  } else {
    motor.run(REV, 200);
  }
}

void loop() {
  go();
  delay(2000);
  direction *= -1;
  stop();
}

