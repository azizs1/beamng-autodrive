# BeamNG.drive Autonomous Driving
## BeamNG Setup
### Basic Vehicle Information
In order for basic vehicle data to be viewable by BeamNG-Autodrive, we need to enable the OutGauge UDP protocol and the MotionSim UDP protocol. See [BeamNG Documentation](https://documentation.beamng.com/modding/protocols/) for this.

1. <b>Outgauge UDP.</b> In BeamNG, navigate to 'Options > Other > Outgauge UDP protocol' and set address, port, and the max update rate.
2. <b>MotionSim UDP.</b> In BeamNG, navigate to 'Options > Other > MotionSim UDP protocol' and set address, port, and the max update rate.
>NOTE: You will have to completely restart BeamNG for these settings to take effect.

>NOTE 2: I am developing this using WSL, and 127.0.0.1 in BeamNG will NOT work. In WSL, run `ip addr show eth0` and use the given IP in BeamNG.

### Camera Streaming
Due to limitations with BeamNG.drive, we cannot have multiple cameras simultaneously streaming (this is only available with BeamNG.tech). As a result, we use OBS to set up an external stream of the application with ffmpeg.
With OBS and ffmpeg installed, follow the steps below to setup OBS:

1. Create a new scene.
2. Add 'Game Capture'.
3. Set the mode to 'Capture specific window' in the dropdown.
4. Set the window to be the BeamNG.drive window.
5. Select the option to ensure the source is visible.
6. Close OBS (it will save automatically).

<span style="color: red;">TODO: Make a config file with IP addresses. cam_url is hardcoded to WSL IP.</span>.
