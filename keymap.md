
# Keymap

## Layers

### Alpha

```
    w f p b      j l u y
→ a r s t g      m n e i o ⇚
  z x c d v      k h , . /
          ↲      ˽ 
```

- Colmak-DH with sticky thumb shift.
- Pinkies for tab and backspace, use muscle memory.
- Home row MODS GASC-CSAG + bilateral combinations via [achordion.h](https://github.com/getreuer/qmk-keymap)
- Double shift for CAPSWORD
- Combos: 
    - `x + c = q`
    - `, + . = ESC`
- Comments `/` and uncomment `CTRL + /`

### Symbol

```
    @ ⸬ ' ●      ● } ) ]             
→ ? \ : _ ●      ● { ( [ " ⇚ 
  ● % | & ●      ● # $ ~ /          
          ↲      ˽ □
```

- Coding: Brackets, `; :`  and `' "` (string/char).
- LaTeX: `\`.
- Enter often follows open brackets. 
- Left top row hard to press due to left thumb hold, put brackets which txt editor mostly auto-completes and rare `£`.
- Bigrams ; + enter and open bracket + enter
- H sounds like HashTag
- Do not want a space to follow any of these charachters as right thumb must move.

### Math

```
    4 5 6 ●      ● ^ < >
→ . 1 2 3 ●      ● = ; - ' ⇚      
  ● 7 8 9 ●      ● + ! * /
        □        ˽ 0
```


- Numpad style numbers with most common numbers on home row.
- Home row MODS GASC-CSAG + bilateral combinations via `achordion.h` on left hand only for `ctrl + +` etc. Note we need basic keycodes on right hand, this is why some non-numerics sneak in.
- Put numbers with math symbols.
- Space follows equals so use left thumb for this layer.
- `_ =` are common keys.
- `0.` and '1.` are the most common decimal point locations.
- Trigram `/**` for comment blocks therfore, make `/*` an inward roll across layers.
- Additional `.` for decimal point.
- Reason that `&&` and `||` as logical operators are more comon than bitwise math op and therfore symbols.
- `><` muscle memory + roll for brackets and avoid `->` sfb.
- Avoid SFB of kind `?=`. Had to have one choices are `<`, `>`, `+`, `!` decided + was least common.
- Need `!` for `!=` bigram.
- Underline (`_`) is under the line (`-`)! 

### Navigation


