# Improvements

  - Integration
    - Kobo UI sometimes draws over the terminal. 
    - Kobo sleeps and turns off bluetooth and wifi after a timeout.
      - efbpad should either find a way to kill & restart Kobo UI, or leave it alive and coexist.
    - Secure NiLuJe's authless ssh config, maybe with key auth.

  - Features
    - Add a statusbar (battery, brightness, font, orietation, onscreen keyboard, etc).
      - For an onscreen keyboard several others have already done the heavy lifting. (inkvt, koreader)
    - fbpad.sh should pick the keyboard event device by filtering instead of always trying /dev/input/event3
    - Replace the logo. Right now it is an old gnome-terminal logo desaturated.

  - fbpad
    - Would it perform better to refresh rectangles on the screen instead of always asking for a full refresh?
    - Restore or remove all the hotkey/multiplexing features from fbpad.
      We already get most or all of that functionality from tmux. 

  - kbreader
    - After fbpad exits, we need to type a char for our `kbreader | fbpad` pipe to term
inate (by SIGPIPE)
    - There is no end to how much better the keyboard interpreter could be.
      - Different locales? Compose key? Numpad? Unicode? 
