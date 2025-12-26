# BeamNG.drive Autonomous Driving
## BeamNG Setup
### Basic Vehicle Information
In order for basic vehicle data to be viewable by BeamNG-Autodrive, we need to enable the OutGauge UDP protocol and the MotionSim UDP protocol. See [BeamNG Documentation](https://documentation.beamng.com/modding/protocols/) for this.

1. <b>Outgauge UDP.</b> In BeamNG, navigate to 'Options > Other > Outgauge UDP protocol' and set address, port, and the max update rate.
2. <b>MotionSim UDP.</b> In BeamNG, navigate to 'Options > Other > MotionSim UDP protocol' and set address, port, and the max update rate.
>NOTE: You will have to completely restart BeamNG for these settings to take effect.

>NOTE 2: I am developing this using WSL, and 127.0.0.1 in BeamNG will NOT work. In WSL, run `ip addr show eth0` and use the given IP in BeamNG.