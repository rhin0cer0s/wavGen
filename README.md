# Description
An extremely simple .wav generator based on a r/dailyprogrammer challenge:
[[2016-06-15] Challenge #271 [Intermediate] Making Waves](https://www.reddit.com/r/dailyprogrammer/comments/4o74p3/20160615_challenge_271_intermediate_making_waves/)

It take 2 arguments :
- duration of each note
- a string representing the notes to play

# Usage
```
./wavGen note_duration note_string
note_duration   duration of each note in ms
note_string     a sequence of note/octave pair, __ for a silence
```

For example a simple usage :
```
./wavGen 300 A4B4C4D4E4F4G4__G4F4E4D4C4B4A > test.wav
```
Will produce a little ```.wav``` file.