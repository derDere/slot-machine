# slot-machine

![Screenshot](https://raw.githubusercontent.com/derDere/slot-machine/readme/Screenshot%202023-01-05%20225317.png)

This is a simple ncursesw based slot machine game for your linux terminal.
It saves your current coins (you can go in dept the bank says thank you 😉) and it saves your max to scoring purposes.
You can also use different profiles if you wan't to show it to you friend.

This started of as a training task for an intern. It was a very simple codewars task and we started talking about what you could actualy do to advance this small little program. Colors, animations, ascii art, and so on. And to me this was sounding like fun and I also have a fable for terminal applications so I just made it. Its kinda fun so I decided to share it with all of you.

## Usage

```
slot-machine [options]
```

### Options
```
-p <profile>      Changes to another profile.
-r                Resets the current profile.
```

### Key bindings
```
SPACE       leaver down
c           insert coin
h           show/hide help
q           quit
```

## Installation
Be sure your terminal is able to display all used emojis. (You may have to change to an advanced font! I suggest nerdfonts.com)
Easy clone make install xD. Here are the commands.

```
git clone https://github.com/derDere/slot-machine.git
cd slot-machine
sudo make install
```
(Be sure to install all dependencies necessaire to build the application. the compiler will tell you. most important is ncursesw. The installation is different depending on your distro and package manager.)

## Deinstallation

```
cd slot-machine
sudo make uninstall
```
