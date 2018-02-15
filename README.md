ofSolarSystem
=============

An interactive 3D solar system simulation using OpenFrameworks

![screenshot](https://github.com/Scylardor/ofSolarSystem/blob/master/bin/data/screen1.jpg?raw=true "Main screenshot")


Synopsis
--------

This is a project made to experiment with [OpenFrameworks](http://openframeworks.cc).

It has some nice features, such as:
  * a multi-viewports mode, allowing up to four cameras at the same time on the screen
  * everything is interactive: you can change scales, rotation, orbit speed and radius of each object
  * special effects like a Star Trek's Borg fleet passing through the solar system, a kind of cutscene using a video of Captain Picard, and real-time geometry drawing Saturn's rings.

![Picard](https://github.com/Scylardor/ofSolarSystem/blob/master/bin/data/screen2.png?raw=true "Picard screenshot")

*Note*: To be able to play the Star Trek video, you need to install a codec to play MP4s. openFrameworks team advises to install the K-Lite Codec Pack, which works well.

How to run it
-------------

This is an OpenFrameworks project.

If you have an OpenFrameworks distribution installed on your computer, just clone the repository in your $(OF_ROOT)/apps/myApps/ folder. It has been compiled using Code::Blocks, so opening the C::B workspace file and build it should be fine, but you also should be able to build it using any IDE. If it really doesn't work, you can generate a new OpenFrameworks project using the ofxAssimpModelLoader add-on, and drop the bin/ and src/ folders of the Git repository into it.

This project has been successfully tested and ran on Ubuntu (13.04/14.04 x86_64), Windows 7 (x86_64) distributions of OpenFrameworks 0.8.0, and openFrameworks 0.9.8 on Windows 10.

Credits
-------

Most of the celestial objects textures used come from http://planetpixelemporium.com/ .

The star field texture comes from http://paulbourke.net/miscellaneous/starfield/ .

The Borg Cube texture comes from http://ribot02.deviantart.com/art/borg-tech-texture-311444974 .

The USS Enterprise-D 3D model and its textures comes from http://www.trekmeshes.ch/meshes/meshesdetails.php?Name=1701D. The original author is Chris Setterington and the 3DS Max adaptation used by the application has been made by Erik Timmermans.

The "We Are The Borg" sound comes from the movie "Star Trek: First Contact" (1996, Paramount Pictures).

The video used in the Enterprise cutscene is an excerpt of the Star Trek episode "Encounter At Farpoint" (Star Trek: The Next Generation, Season 1, episode 1, 1987).

![Borgs](https://github.com/Scylardor/ofSolarSystem/blob/master/bin/data/borgs.jpg?raw=true "Borgs screenshot")

Bugs
----

Some bugs are currently known :
  * Due to a change in the video player API, my code doesn't seem to make good use of it anymore, and the Star Trek video is very buggy, doesn't always start, and when it does, keeps playing forever. This is a known bug I haven't time to investigate.
  * For an unknown reason, taking a snapshot while or after the Enterprise video has been played makes the application crash (potentially an OpenFrameworks bug). That's why triggering the Enterprise cutscene disables snapshots.


Redistribute
------------

You can do what you want with the source code of this project.
