# JavaQml
Simple test of interfacing DOtherSide with Java

## Requirements
DOtherSide compiled and installed in your system path

## Compile steps
```
javac -h . DOtherSideJNI.java
mkdir build
cd build
cmake ..
make
cd ..
export LD_LIBRARY_PATH=`pwd`/build
javac Main.java && java Main
```

