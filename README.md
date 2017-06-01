Anime Media Streamer Renamer (amsrenamer)
================================

amsrenamer is an simple utility to rename given anime releases for easy import into media streamers.

Prerequisites
=============
- GNU/Linux operating system
- GCC
- Make

How to compile
==============
1. Download the source:
``` git clone https://github.com/zaclimon/HorribleSubs-Renamer```
2. Compile the source:
``` make amsrenamer```
3. Profit!

Usage
=====
You can use it to rename separately an HorribleSubs release like so:
```amsrenamer -f "path-to-file.mkv"```
```amsrenamer -f "path-to-file.mp4"```

Or you can use it to rename a directory containing a ton of releases as well like so:
```amsrenamer -d "/path/to/dem/releases"```

License
=======
This program is licensed under the GPL. Because open source. :stuck_out_tongue: