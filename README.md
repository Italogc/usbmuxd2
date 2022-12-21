# usbmuxd2

Antes do jailbreak do Palera1n verifique se no seu "diretório local" do seu linux, aonde fica a pasta do palera1n, se tem uma pasta chamada "usbmuxd2"... Se tiver não faça nada, mas, se não tiver, clona este meu repositório no seu linux, abrindo uma nova janela no terminal xfce e executando o seguinte comando:

sudo git clone --recursive https://github.com/Italogc/usbmuxd2

Após o fim do processo verifique se a pasta usbmuxd2 já está presente no seu diretório local, e se positivo, feche o terminal e pode executar o processo do se palera1n quando você quiser numa nova janela de terminal.

Caso eu tenha te ajudado, por favor me ajude também no meu canal do youtube, obrigado!
https://www.youtube.com/channel/UCaxq1mPPv-ya78YXkNnn1oQ

Abaixo a descrição nativa e recomendações dos criadores oficiais do usbmuxd2

## About
A socket daemon to multiplex connections from and to iOS devices over USB and WIFI

## Background
This project is a reimplementation of the original [usbmuxd](https://github.com/libimobiledevice/usbmuxd) daemon by the libimobiledevice project (which in turn is an open source implementation of Apple's own usbmuxd).

usbmuxd stands for "USB multiplexing daemon", however since the introduction of iTunes WIFI sync it also multiplexes connections over WIFI.

When usbmuxd is running it provides a socket interface in /var/run/usbmuxd that is designed to be compatible with the socket interface that is provided on macOS.

The daemon also manages pairing records with iOS devices and the host in /var/lib/lockdown (Linux) or /var/db/lockdown (macOS). Ensure proper permissions are setup for the daemon to access the directory.

## Requirements

Development Package of:
* libusb (USB)
* libplist and libplist++
* libusbmuxd
* libimobiledevice
* avahi-client (WIFI)

Software:
* make
* autoheader
* automake
* autoconf
* libtool
* pkg-config
* clang (This project was developed and tested with clang compiler)

## BUILD
usbmuxd2 is intended to be run on Linux only!\
A compiler with C++17 is required!

This project does *NOT* support Windows!\
This project is not meant to be run on macOS! (You really don't need it on macOS!)


### Actually building
To compile run:

```bash
./autogen.sh
make
```

If debug symbols and extra logging is desired, build with
```bash
./autogen.sh --enable-debug
make
```


### Running on macOS
***This project is not meant to be run on macOS!***  
macOS already ships a usbmuxd which is capable of multiplexing connections through USB and WIFI, you really don't want to run this on macOS!!!!

If you for some reason stil really need to run this, you can get usbmuxd2 in USB-only mode to work on macOS (tested on macOS High Sierra 10.13.6).  
WIFI is not supported on macOS!

**DO NOT TRY TO BUILD USING THE XCODE PROJECT!**  
Follow the same build instructions shown above and these extra steps for running.

For usbmuxd to work on macOS it is neccessary to delete `AppleMobileDevice.kext` as well as to unload Apple's usbmuxd.
Otherwise it is not possible to claim iOS devices over USB.
```bash
#delete kext
sudo rm -rf /System/Library/Extensions/AppleMobileDevice.kext
sudo reboot
#Make sure not to install Xcode extensions after reboot,
#or the kext will be back
#Now unload apple's usbmuxd
sudo launchctl unload /System/Library/LaunchDaemons/com.apple.usbmuxd.plist
```
If you want to reinstall the kext, just open Xcode and install it's extensions.
