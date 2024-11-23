# efbpad

A prototype terminal that was once seen working on a Kobo Clara BW.
Type with a bluetooth keyboard.

This is a very immature project, see the long [TODO.md](TODO.md)

<p align="center">
  <img alt="Wide" src="./images/efbpad_1.jpeg" width="45%">
  <img alt="Detail" src="./images/efbpad_2.jpeg" width="45%">
</p>

## Usage

 - Run `make eink` to produce a package.
   This requires a cross-compiling environment.
   NiLuJe's `koxtoolchain` kobo env is the path of least resistance.
 - Install kfmon, nickelmenu, and [NiLuJe's Kobo utilities.](https://www.mobileread.com/forums/showthread.php?t=254214)
 - Merge the contents of `./root/mnt/onboard/` with the kobo's
   `/mnt/onboard`, or put the produced `KoboRoot.tgz` in `/mnt/onboard/.kobo`

kfmon should create an efbpad entry for the launch script, `efbpad.sh`
efbpad will only start if a bluetooth keyboard is paired and connected at
`/dev/input/event3`.
It will close out when the keyboard is disconnected.

For uninstallation, efbpad only creates these files and directories:
 - `/mnt/onboard/.adds/efbpad`
 - `/mnt/onboard/fonts/tf`
 - `/mnt/onboard/efbpad.png` 
 - `/mnt/onboard/.adds/kfmon/config/efbpad.ini`

## Project Structure, Credits
Others ran so that efbpad could crawl.
This project is just other people's work threaded together.

Broadly there are 4 components:
 - `efbpad.sh`: Startup/shutdown script, "created" by just paring down
   KOReader's `koreader.sh`. 
 - `fbpad`: A framebuffer terminal emulator.
    Here there are patches calls to NiLuJe's FBInk library to execute
    screen refreshes.
    Notably, this isn't the first time someone has done this
    (see fbpad-eink).
 - `kbreader`: Under proper conditions keyboards appear in linux as
    event devices.
    When you start `fbpad` it's waiting for chars from stdin.
    `kbreader` acts as the interpreter to translate keystrokes into
    char strings. It writes its translations to stdout.
    Thus we can get `fbpad` to listen to the keyboard by running a
    piped command as so:
    `kbreader /dev/input/event3 | fbpad the_shell_cmd`.
    `kbreader` is spiritually identical to inkvt's onscreen keyboard,
    except it interprets key events rather than soft-keyboard touches.
  - When fbreader is started it tries to attach to a tmux session (or
    it creates one if it doesn't exist). It's using the one from
    NiLuJe's misc Kobo utilities package.

The included font `regular.tf` was produced using fbpad_mkfn:

```
$ ./mkfn -h 48 -w 24 DejaVuSansMono.ttf:42 > regular.tf
```
