docker build env -t os

docker run --rm -it -v %cd%:/root/env os

D:\w64\bin\gdb.exe
target remote localhost:1234
file "C:/various_shit/os/bin/kernel.bin"