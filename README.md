# Recording Footswitch

By Michal Lemczyk.

A four-button USB footswitch for controlling recording and playback hands-free
while playing bass guitar.

An Arduino acts as a USB keyboard. Each footswitch sends one
**Ctrl+Shift+Alt+F-key** combination. Nothing normally uses those combinations,
so an [AutoHotkey](https://www.autohotkey.com/) script can bind them to whatever
the recording workflow needs: start a take, stop and save it, throw it away,
or rewind the backing track. Both hands stay on the bass.

![The Arduino box with its two jacks (A/B and C/D) and the two dual footswitches plugged into it](images/footswitch-setup.jpg)

In my build, the four switches are two off-the-shelf dual footswitches (two
switches each, on one stereo cable). They plug into two stereo jacks on a
small aluminium box that holds the Arduino: one jack carries switches A and
B, the other C and D.

![Inside the box: the two stereo jacks wired to the Arduino Micro (the USB keyboard), with its USB cable](images/enclosure-inside.jpg)

## Buttons

| Switch | Arduino pin | Sends | Used for in my setup |
|---|---|---|---|
| A | 9 | Ctrl+Shift+Alt+F12 | Reset: stop Guitar Pro playback and return to bar 1 |
| B | 7 | Ctrl+Shift+Alt+F11 | Start: arm the recorder, then start Guitar Pro playback |
| C | 5 | Ctrl+Shift+Alt+F10 | Stop: end the take, save it, run the post-processing |
| D | 3 | Ctrl+Shift+Alt+F9 | Abort: stop and discard the take |

The sketch only sends keystrokes. What each one does is decided entirely by
the AutoHotkey script on the PC, so the same pedal works with any DAW or
player.

## Parts

| part | used in my build | notes |
|---|---|---|
| Microcontroller | Arduino Micro | Any board with native USB that can act as a USB keyboard (HID): an ATmega32u4 board such as the Leonardo, Micro or Pro Micro. Boards with a separate USB-serial chip, like the Uno or Nano, cannot use the `Keyboard` library |
| Footswitches | 2 dual footswitches, two switches on one 1/4" stereo cable each ([one of them](https://www.amazon.ca/dp/B0BMF6H337); the other model is no longer sold) | Must be **momentary** and normally open. A latching switch would only trigger on every other press |
| Jacks | 2 × 1/4" (6.35 mm) stereo (TRS) panel jacks, non-switched | One per dual footswitch |
| Enclosure | Cast aluminium box, 112 × 60 × 32 mm | The common "1590B" size |
| Cable | USB cable for the board | Power and data both come over USB |

No resistors are needed: the sketch turns on the board's internal pull-ups
(`INPUT_PULLUP`), so a pressed switch reads `LOW`.

## Wiring

Each dual footswitch carries its two switches on the tip and ring of one
stereo cable, with the sleeve as their common return. Each jack is wired:

| jack | tip | ring | sleeve |
|---|---|---|---|
| 1 (switches A, B) | pin 9 (A) | pin 7 (B) | GND |
| 2 (switches C, D) | pin 5 (C) | pin 3 (D) | GND |

If a footswitch's two buttons come out the wrong way round, swap the two pin
numbers in the sketch rather than the wires.

## Software

- Arduino IDE, with these libraries:
  - `Keyboard` (built in)
  - [`Bounce2`](https://github.com/thomasfredericks/Bounce2), from the Library
    Manager. Each switch is debounced with a 25 ms interval (`INTERVAL_MS`).
- Open `Footswitch/Footswitch.ino`, select the board, and upload.

Each press holds the full combination for 50 ms before releasing it, so
Windows reliably registers all four keys. The keys are sent once per press;
holding a switch down does not repeat it.

## Binding the keys in AutoHotkey (v2)

A minimal script to start from:

```autohotkey
#Requires AutoHotkey v2.0

^+!F12:: {   ; switch A
    MsgBox "Reset"
}
^+!F11:: {   ; switch B
    MsgBox "Start"
}
^+!F10:: {   ; switch C
    MsgBox "Stop"
}
^+!F9:: {    ; switch D
    MsgBox "Abort"
}
```

Replace each `MsgBox` with the real action, for example activating the player
window with `WinActivate` and sending `Space` with `Send "{Space}"`, or starting
a recording script with `Run`.

## Changing the keys

To send different combinations, edit the `Keyboard.press(...)` lines in each
button's block. Key names such as `KEY_F9` and `KEY_LEFT_CTRL` are listed in
the Arduino
[Keyboard modifiers reference](https://docs.arduino.cc/language-reference/en/functions/usb/Keyboard/keyboardModifiers/).

## How this was built

I designed and built the hardware and wrote the sketch; it drives the
AutoHotkey script that records my bass covers. This repo, its README and
the parts and wiring tables were put together with
[Claude Code](https://claude.com/claude-code), Anthropic's AI coding agent,
working from my notes, photos and sketch; commits it helped write carry a
`Co-Authored-By: Claude` line.

## Related projects

Part of one personal project: recording bass covers along to Guitar Pro tabs,
scoring them, and matching my rig's tone to the original recordings.

- [Guitar Pro Utilities](https://github.com/mlemczyk/Guitar-Pro-Utilities):
  Python tools for the tabs this footswitch plays along to: parsing, syncing
  backing tracks, embedding audio, MIDI export and difficulty.
- [Bass Guitar Equipment Analysis](https://github.com/mlemczyk/Bass-Guitar-Equipment-Analysis):
  measurements and fitted models of the rig's pedals, made by re-amping test
  signals through each one.

## License

Public domain, under the [Unlicense](LICENSE).
