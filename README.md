# linuxdriver

Reviewing past knowledge, looking forward to new developments

##### To successfully run the above test cases, please note the following points:

 - First, compile the downloaded kernel regardless of the platform. The compilation commands are as follows:
   ```c
     make CROSS_COMPILE=aarch64-linux-gnu- ARCH=arm64 O=build menuconfig
     make CROSS_COMPILE=aarch64-linux-gnu- ARCH=arm64 O=build
   ```
   The above commands target an ARM 64-bit processor. If you want to compile for other platforms, simply change the corresponding variables after "CROSS_COMPILE" and "ARCH".

   O=build:Specifying the output directory: Using O=build allows you to store all files generated during the compilation process (such as compiled object files, configuration files, modules, etc.) in the build directory instead of the default source directory. This helps keep the source directory clean and makes it easier to manage and clean up 
       the compiled files.
- Next, navigate to the corresponding driver module directory. Pay attention to the Makefile file, and modify the KDIR to match the path of your own kernel source code.


## 001_hello_world:
  - 

## 002_character_dev：
  - This module includes the application to test the driver module. So We need to compile the application by cross compiler tools. I give the command below:
     aarch64-linux-gnu-gcc -static file_app.c -o file_app
  - This driver module just create the major device number. It does not create the device node. So we need to create the device node by myself based on the major device number.
     first, check the major device number. Because I use the method of dynamically allocating major device numbers.
        ```bash
           cat /proc/devices/
        ```
        You will see the device name - "CharDevice"
      second, create the device node:
           mknode  /dev/CharDevice c major_device_number 0
      third, you will see a device node in /dev/ folder

  - Execute the file_app to test the driver module.
  -  write the data:
       ./file_app /dev/CharDevice  "abcde"
  - read the data:
        ./file_app /dev/CharDevice 

