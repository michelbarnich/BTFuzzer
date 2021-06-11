# BTFuzzer
BTFuzzer is a simple Fuzzing tool for Bluetooth Devices. It uses the BlueZ, since it was the first best thing I found online :P
THIS IS A WIP! It's not functional yet!

## Installation
You need to install Bluez, and gcc.
```
sudo apt install bluez gcc
```

## Usage

```
cd ./BTFuzzer/products
./BTFuzzer
```

BTFuzzer will now try to find any Devices near you, and if it finds one (or more), it will show you a little table similar to this one:

```
  ____ _______ ______ _    _ __________________ _____  
 |  _ \__   __|  ____| |  | |___  /___  /  ____|  __ \ 
 | |_) | | |  | |__  | |  | |  / /   / /| |__  | |__) |
 |  _ <  | |  |  __| | |  | | / /   / / |  __| |  _  / 
 | |_) | | |  | |    | |__| |/ /__ / /__| |____| | \ \ 
 |____/  |_|  |_|     \____//_____/_____|______|_|  \_\
                                      by Michel Barnich
[+] Scanning for Bluetooth Devices... 
[+] Found 1 Device(s): 

|-----|--------------------------------|---------------------|
|   1 |         Bose Mini II SoundLink |   2C:41:A1:46:A6:62 | 
|-----|--------------------------------|---------------------|

[i] Please enter Target Device number: 
```

Now you only have to enter the number to the corresponding Device you want to fuzz, and wait till you find a bug :P

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Disclaimer

This Fuzzer is probably not super useful, it doesn't have any intelligent features, nor does it detect if a device actually encountered a bug. This was just a fun project for me to learn a bit of C and coding on Linux in general. Also, sorry for my bad C code, I'm 100% sure it can be done better than this :D