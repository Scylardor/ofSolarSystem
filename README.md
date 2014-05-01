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
  * special effects like a Star Trek's Borg fleet passing through the solar system, a kind of cutscene using a video of Captain Picard, and real-time geometry drawing Saturn's rings

![Picard](https://github.com/Scylardor/ofSolarSystem/blob/master/bin/data/screen2.jpg?raw=true "Picard screenshot")

How to run it
-------------

This is an OpenFrameworks project.

If you have an OpenFrameworks distribution installed on your computer, just download the repository and drop the bin/ and src/ folders into an OpenFrameworks project using the ofxAssimpModelLoader add-on, compile it with your IDE of choice, and it should run.

This project has been successfully tested and ran on both Linux (Ubuntu 13.04 x86_64) and Windows (Seven x86_64) distributions of OpenFrameworks 0.8.0.

Credits
-------

Most of the celestial objects textures used come from http://planetpixelemporium.com/ .

The star field texture comes from http://paulbourke.net/miscellaneous/starfield/ .

The Borg Cube texture comes from http://ribot02.deviantart.com/art/borg-tech-texture-311444974 .
\section{Modèle 3D}

The USS Enterprise-D 3D model and its textures comes from http://www.trekmeshes.ch/meshes/meshesdetails.php?Name=1701D. The original author is Chris Setterington and the 3DS Max adaptation used by the application has been made by Erik Timmermans.

The "We Are The Borg" sound comes from the movie "Star Trek: First Contact" (1996, Paramount Pictures).

The video used in the Enterprise cutscene is an excerpt of the Star Trek episode "Encounter At Farpoint" (Star Trek: The Next Generation, Season 1, episode 1, 1987).

![Borgs](https://github.com/Scylardor/ofSolarSystem/blob/master/bin/data/borgs.jpg?raw=true "Borgs screenshot")

Bugs
----

Some bugs are currently known :
  * Due to a known Assimp library problem, the Enterprise 3D model can't be loaded on Windows platforms. Consequently, this feature doesn't work on Windows.
  * For an unknown reason, taking a snapshot while or after the Enterprise video has been played makes the application crash (potentially an OpenFrameworks bug). That's why triggering the Enterprise cutscene disables snapshots.


Redistribute
------------

You can do what you want with the source code of this project.
