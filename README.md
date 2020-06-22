# ShardIllumination
Code for illuminating "shards" of acrylic glass.

## Background
I recently bought a
[tabletop CNC machine](https://www.sainsmart.com/products/sainsmart-genmitsu-cnc-router-3018-pro-diy-kit),
and I am completely in love with it. One of the first projects I attempted after
setting up my CNC was a disk of acrylic glass, engraved with a picture of an
[Oddish](https://bulbapedia.bulbagarden.net/wiki/Oddish_(Pok%C3%A9mon)), Oddishes
being my five-year-old's second favorite thing in the universe. His first favorite?
LEDs. So hey, why not combine the two?

This repo contains several sketches that perform variations on lighting up RGB
LEDs (uniform color, as opposed to individually addressible), with the intent
being that the LEDs lie in a channel inside a base holding a piece of acrylic glass.

This isn't a terribly [novel](https://www.youtube.com/watch?v=kgPghSJhkzU)
[idea](https://www.youtube.com/watch?v=697cEhHvYZk), but I had my own twist to add.
You know that obnoxiously loud person in the office who you can hear three floors down,
even when they're talking at their "normal" volume? It me. So when I saw
[this tweet](https://twitter.com/EffinBirds/status/1271819657608155136) from
[@effinbirds](https://twitter.com/EffinBirds), I knew I needed that image engraved,
mounted, and configured to flash any time my voice exceeded a certain decibel.

When I told my kid about the project, he demanded a (profanity-free) version of his own,
and, as he has taken to shrieking loud enough to break glass (like father, like son),
I configured his variant to only be triggered by high-pitched noises (boy, were my
neighbors thrilled when I was "calibrating" that project).

## Project Variants

The variants provided in this repo are:

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
The base and acrylic shards were designed in
[Easel](https://www.inventables.com/technologies/easel). The project files and G-Code
for the stand can be found in the [shard stand folder](shard%20stand). The images used
in the acrylic shards were not my design, so for those, you're on your own.

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