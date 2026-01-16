# Assigmnent 1
Given the [prompt](./Doc/Assignment_1.md) I have decided to take an approach that I will document ina series of markdown files. 

## Approach

### Obtaining Necissary Dev Tools
- Given my main machine is currently running arch linux as of Jan 2026, installing the IDE with the provided zips will be pointless (not a fan of IDEs anyways). 

- Typically, my preferred approach to embedded development is to use command line interface (CLI) build tools. This lead me to research CLI alternatives to the proposed IDE. This is where the fun comes in as there really isn't a supported CLI toolchain provided by NXP like esp-idf for ESP32, so I have opted to use openOCD for flashing and the standard compilers for, well, compiling.

For any other arch users:
' 
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib arm-none-eabi-gdb
sudo pacman -S openocd
wget https://github.com/ARM-software/CMSIS_5/archive/refs/heads/develop.zip
unzip develop.zip
mkdir -p RTE/CMSIS
cp -r CMSIS_5-develop/CMSIS/Core/Include/* RTE/CMSIS/
rm -rf CMSIS_5-develop develop.zip
'
The main comprimise (if you really want to call it that) is that a [makefile](./Makefile) is now required for projects. 

### Verifiation 
I started with verifying that openOCD worked first. You don't have to, I just did.
To do this I:
1. installed openOCD.
2. Connected the NXP board and checked if it was seen by my machine with lsusb, which it was when I connected to the port on the left (with the ports towards you)
3. Then I checked what openOCD supported with 
   '
   ECE_444/Assignments/Assignment_1 on  main [✘!?]
   at 21:45:29 φ ls /usr/share/openocd/scripts/board/ | grep -i frdm
   
   frdm-kl25z.cfg
   frdm-kl46z.cfg
   nxp_frdm-k64f.cfg
   nxp_frdm-ls1012a.cfg
   '
   Which is alarming since the specific board is not in there, but it looked close enough.
4. For one final check I entered the command
  'ECE_444/Assignments/Assignment_1 on  main [✘!?]
   at 21:47:01 φ openocd -f interface/jlink.cfg -c "transport select swd" -c "adapter speed 1000" -f target/kx.cfg
   
   Open On-Chip Debugger 0.12.0-01004-g9ea7f3d64-dirty (2025-11-12-08:18)
   Licensed under GNU GPL v2
   For bug reports, read
           http://openocd.org/doc/doxygen/bugs.html
   swd
   adapter speed: 1000 kHz
   
   Info : add flash_bank kinetis kx.pflash
   Info : Listening on port 6666 for tcl connections
   Info : Listening on port 4444 for telnet connections
   Info : J-Link OpenSDA 2 compiled Aug  4 2014 13:30:09
   Info : Hardware version: 1.00
   Info : VTarget = 3.300 V
   Info : clock speed 1000 kHz
   Info : SWD DPIDR 0x2ba01477
   Info : [kx.cpu] Cortex-M4 r0p1 processor detected
   Info : [kx.cpu] target has 6 breakpoints, 4 watchpoints
   Info : MDM: Chip is unsecured. Continuing.
   Info : starting gdb server for kx.cpu on 3333
   Info : Listening on port 3333 for gdb connections
   '
   Looks like success to me!
   
### Creating a New Project
Since I don't beleive in IDEs, I cannot rely on a project wizard to give me a project architecture (they usually aren't very good anyways). To create a sensible architecture I executed the command
'
mkdir -p src inc build
'
Though this is probably common knowledge, src is for the source code, inc is for the header files, and build is for all the binarys and junk that goes onto MCU's flash. I also downloaded the framework zip provided on blackboard. I organized the project structure like this:
'
cp K22_Project_Framework_F20/main.c ./src/
cp K22_Project_Framework_F20/ADC.c ./src/
cp K22_Project_Framework_F20/DAC.c ./src/
cp K22_Project_Framework_F20/MCG.c ./src/
cp K22_Project_Framework_F20/TimerInt.c ./src/

# and for the headers
cp K22_Project_Framework_F20/* .h ./inc

# and the device specific files
cp K22_Project_Framework_F20/RTE ./
cp RTE/Device/MK22FN512VLH12/startup_MK22F51212
'
Then my final file structure looked like this:
'
ECE_444/Assignments/Assignment_1 on  main [✘!?]
at 22:28:52 φ tree
 .
├── 󱧼 build
├──  Doc
│   └──  Assignment_1.md
├──  inc
│   ├──  ADC.h
│   ├──  DAC.h
│   ├──  MCG.h
│   └──  TimerInt.h
├──  README_Assignment_1.md
├──  RTE
│   ├──  _Target_1
│   │   └──  RTE_Components.h
│   └──  Device
│       ├──  MK22FN512VLH12
│       │   ├──  fsl_device_registers.h
│       │   ├──  MK22F51212.h
│       │   ├──  MK22F51212_features.h
│       │   ├──  MK22FN512xxx12_flash.scf
│       │   ├──  MK22FN512xxx12_ram.scf
│       │   ├──  startup_MK22F51212.s
│       │   ├──  system_MK22F51212.c
│       │   └──  system_MK22F51212.h
│       └──  MK22FN512xxx12
│           ├──  fsl_device_registers.h
│           ├──  MK22F51212.h
│           ├──  MK22F51212_features.h
│           ├──  MK22FN512xxx12_flash.scf
│           ├──  MK22FN512xxx12_ram.scf
│           ├──  RTE_Device.h
│           ├──  startup_MK22F51212.s
│           ├──  system_MK22F51212.c
│           └──  system_MK22F51212.h
├── 󰣞 src
│   ├──  ADC.c
│   ├──  DAC.c
│   ├──  main.c
│   ├──  MCG.c
│   └──  TimerInt.c
└──  startup_MK22F51212.s
'

