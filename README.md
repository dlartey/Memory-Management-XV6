# Memory-Management-XV6
Simple memory management program in C for the XV6 OS

This is my implementation of malloc in XV6 which works on XV6: See the project here https://github.com/mit-pdos/xv6-riscv 

To run this program please clone the XV6 github above and run these commands on Ubuntu/Linux
```
sudo apt-get update -y
sudo apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu -y

git clone https://github.com/mit-pdos/xv6-riscv
cd xv6-riscv

make qemu
```
![image](https://user-images.githubusercontent.com/58071586/160236859-198dfb79-3907-4ac8-80cc-bd3ec4906e13.png)

Then make sure that the memory_management.c and memory_management.h files are in the user directory of xv6-riscv,i.e in:
```
xv6-riscv/user directory
```

Then locate the makefile in 
```
xv6-riscv directory
```
and add $U/_memory_management\ to UPROGS
![image](https://user-images.githubusercontent.com/58071586/160236820-178fefb2-af44-465d-a0ee-23dfe16d4944.png)

Now you can run
```
make qemu
memory_management  
```
To test the program
