Documentation
====
[Wiki](https://github.com/GrandTheftGentoo/GTG_Qt/wiki)

Check out the new Doxygen docs. See INSTALL for doc generation instructions

Compiling
=========
In order to build this, you will need Qt5 installed in your system or the Qt SDK >= 5.0
```
$ git clone https://github.com/GrandTheftGentoo/GTG_Qt
$ cd game/src
$ mkdir build
$ cd build
$ <see below>
$ make
$ cd ../..
$ ./gtg
```

Step 5:
If you are using system's Qt5, run
```
$ cmake ..
```
If you are using Qt's SDK, run
```
$ cmake .. -DCMAKE_PREFIX_PATH=/<QTSDK-PATH>/<VERSION>/<YOUR-COMPILER>/cmake
```

To build the editor:
```
$ cd editor
$ qmake
$ make
$ ./editor
```

If you are using Qt's SDK, run this first:
```
$ export PATH="$PATH:/<QTSDK-PATH>/<VERSION>/<YOUR-COMPILER>/bin"
```

Communication
=============
* #GTG @ irc.p2p-irc.net
* [Website](http://gtg.installgentoo.com)
