# POD HD Preset Tool

The POD HD Preset Tool can convert preset, setlist and bundles between different POD HD models without modifying their settings. Optionally, It also can mass change some settings of all presets, setlists, bundles like setting all amps to preamps or changing the microphone.

It supports POD HD 300, POD HD 400, POD HD 500, POD HD Desktop, POD HD Pro.

podhd runs on Windows and macOS. The application is written in ugly code using C++ with the Qt framework and previous, outdated versions are still available in Objective-C using Cocoa as UI framework for Mac OS X as well as the first version in Java/Swing.

## Features:

For the POD HD 500 / POD HD 500X / POD HD Desktop / POD HD Pro / POD HD ProX:
  * Convert presets, bundles and setlists to each other model. It literally "converts" them , i.e. does not modify any Amp/Cab/FX Setting.
  * Edit bundles, presets and setlists:
    * Independently change inputs, impedance, amps, cabs and mics without changing their parameters. For example, change your live setlist to a studio setlist by changing all pre amp models to full amp models with cab without losing your settings.
  * Translate POD HD 300 / POD HD 400 presets to POD HD 500 / POD HD 500X / POD HD Desktop / POD HD Pro / POD HD ProX presets. Click here for more information.

For the POD HD 300 / 400:
  * Translate POD HD 500 / POD HD 500X / POD HD Desktop / POD HD Pro / POD HD ProX presets to POD HD 300 / POD HD 400 presets

## Screenshot:

![podhd convert Main UI](http://www.jzab.de/sites/default/files/images/podhd_convert_qt_mac.png?raw=true "Pod HD Convert Main UI")

## Application Usage:

* On the Top, click on the Tab named after your desired deivce. So, if you own a POD HD Desktop, click on HD Desktop
* Below, click on Browse and specify the directory that contains your (downloaded) Presets, Setlists or Bundles that you want to convert to your device or modify.
* Now choose what you want to do with the files in the chosen directory. The settings are grouped in convert, translate or modify for a better overwiev. Apply everything you desire. For example, if you downloaded a POD HD 500 Preset and want to run in on your POD HD Desktop, checkmark the box Patch HD 500 Presets to Desktop (.h5e -> .hbe).
* On the Bottom, Click Run.
