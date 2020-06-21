# ShardIllumination
Code for illuminating "shards" of acrylic glass.

This project contains several sketches that perform variations on lighting up RGB
LEDs (uniform color, as opposed to individually addressible). The variants provided
are:

- [DemoIllumination](DemoIllumination/DemoIllumination.ino), which cycles through a
  palette of nine colors in sequence
- [MappingTest](MappingTest/MappingTest.ino), for trying out a continuous color
  palette
- [MicCalibrate](MicCalibrate/MicCalibrate.ino), for calibrating the input coming
  from a microphone input
- [IndoorVoice](IndoorVoice/IndoorVoice.ino): illuminates the shard based on an
  analog signal from a microphone
- [TooShrill](TooShrill/TooShrill.ino): the most complex variant, where the illumination
  color and intensity is a function of an amplified microphone signal, sent through a
  high-pass filter

## Circuit Diagram
![Circuit for TooShrill sketch](TooShrill.png)

This is the most complex variant of this project, with a USB boost converter powering
the circuit mainly because I wanted USB power but didn't want to use the mini USB port
in the Arduino Nano.

## Parts List
Coming soon!

### Design Files

## Installation
Several of these sketches rely on a common utility file. In order to include it, you'll
either need to add [`illumination_utils.h`](libraries/illumination_utils.h) to the sketch
folders and then change the `#include` line to use quotes instead of angle-brackets, or
move / symlink the header to a folder within your Arduino "libraries" folder.

## Operation
These are simple example sketches that are widely adaptable to a variety of
microcontrollers and LED setups. As a consequence, while these sketches were runnable
for me given the hardware specified in each sketch, you'll likely have to lightly adapt
these sketches to serve your exact use-case. Even when replicating my exact circuit,
you'll need to upload and run [MicCalibrate](MicCalibrate/MicCalibrate.ino) and view the
output on the serial plotter in order to choose the signal levels for your color mappings.

Once you've tweaked the parameters to your liking, you should be good to upload an
illumination sketch to your microcontroller. None of these sketches involve physical
input, as they either display hard-coded animations
([DemoIllumination](DemoIllumination/DemoIllumination.ino),
[MappingTest](MappingTest/MappingTest.ino)) or are controlled by the input from an analog
input pin, [IndoorVoice](IndoorVoice/IndoorVoice.ino),
[TooShrill](TooShrill/TooShrill.ino)).

So once you've uploaded the code, you can power your circuit via USB or whatever power
system you'd like, and the code should just work.

## Demos
Coming soon!