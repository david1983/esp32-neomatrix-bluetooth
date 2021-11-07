# arduino led control

This small cordova app allow the color selection of a neomatrix controlled by an ESP32.

## how to build the app
clone the repository and plug your phone usb to pc
```
cordova platform add android
npm run build android && cordova run android
```

## how to build the device
simply connect the 3.3v, gnd and data wire from the neomatrix to the microcontroller.
The code uses PIN 15 but you can change it in the neomatrix.ino file.
