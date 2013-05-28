<h1>RaspCar</h1>

RaspCar is an RC-Car - controlled with an Raspberry Pi from the web. It has two ways of working:
- Control the rc-car with an arduino (see: Arduino.ino), it's getting it commands from serial-port. (for example the Raspberry Pi could send the commands) This option is only needed if theres no way accessing the GPIO Pins from the Raspberry Pi (for example the case isn't made for it)
- Control the rc-car directly with the Raspberry Pi (webiopi is recieving the inputs/commands)


Raspcar will need following Components to work:
- http://code.google.com/p/webiopi/
- some kind of webcam daemon, to access the webcam straight from the web (I'm using "motion")

<h4>The original Project was started here: http://www.forum-raspberrypi.de/Thread-projekt-raspcar (german)</h4>
