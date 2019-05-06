# Using Absolute mode as virtual relative mode on Synaptics touchpad.

# This code is the implementation of mouse mode using absolute mode of touchpad. So we don't need to reset the touchpad and re-init into the relative (normal PS/2) mode

```
List of implementations to be done.

- Fixing the jiggling effect --Need help
- Add the gesture recognition 
  - one finger tap to click is missing. may be using millis(); to detect short present of (more than zero) value of X and Y       axis (and disabe mouse movement when short tap occur)
  - need to use the millis(); to recognize how long does W detect 2 fingure
    - short hold == righ click 
    - long hold == move Y axis (mouse wheel)
  - three fingures is for middle click 
  - Palm detection. to prevent from moving cursor accidently
  
```
