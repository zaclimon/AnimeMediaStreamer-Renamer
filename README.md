HorribleSubs Renamer (hsrenamer)
================================

hsrenamer is an simple utility to rename HorribleSubs releases for easy import into media streamers. (Plex)

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
``` make hsrenamer```
3. Profit!

Usage
=====
You can use it to rename separately an HorribleSubs release like so:
```hsrenamer -f "path-to-file.mkv"```

Or you can use it to rename a directory containing a ton of releases as well like so:
```hsrenamer -d "/path/to/dem/releases"```

License
=======
This program is licensed under the GPL. Because open source. :stuck_out_tongue: