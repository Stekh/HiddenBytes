# HiddenBytes  
-----------------------------  
HiddenBytes is a simple GUI application made to showcase a few select steganography algorithms.  
Currently it only supports .bmp and .wav files for simplicity's sake.  

## Dependencies
-----------------------------  
Currently, he only dependency is Qt6.  

## Installation
-----------------------------
For windows, you can get the newest version in the *Releases* tab.  
For other operating systems, you'll need to compile it yourself.  

## Compilation
-----------------------------
Get the source code:
```
git clone https://github.com/Stekh/HiddenBytes.git
cd HiddenBytes
```

Then run:
```
cmake -B cmake-build-debug/ && cmake --build cmake-build-debug/ && cmake-build-debug/HiddenBytes
```

