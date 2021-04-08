![IMG_1181](https://user-images.githubusercontent.com/5492064/114078551-14a7bf00-9877-11eb-9409-335b2b34aa36.JPG)

# hotPlastiGun

a less portable 3d pen/handheld plastic extruder. used mostly spare 3d printing parts and an arduino ~~uno~~ ~~promicro~~ ~~mega~~ whatever you want. my working version uses a promicro but i fried a few boards along the way

parts list:
- arduino (doesnt matter much which)
- 4.7k resistor
- e3d v6 hotend set:
  - 100k ntc thermistor
  - 12v/40w heater core
  - heatsink
  - heatblock
  - choice of nozzle
  - all metal throat (highly advise against ptfe liner)
- drv8825 stepper driver
- random spare stepper motor i had(17HS4401 on the sticker)
- bowden tube, i suggest a length equal to the length of thermistor/heater cables, but is to prefrence
- extruder gear
- bowden extruder mount/plate for mounting to stepper motor, i used a remix of https://www.thingiverse.com/thing:275593
- random mosfet, provided it can handle 12v@4A or so, Vgs(thr)<5.1

![IMG_1180](https://user-images.githubusercontent.com/5492064/114078420-e924d480-9876-11eb-8c16-473d2cd48752.JPG)
![IMG_1182](https://user-images.githubusercontent.com/5492064/114078568-1ec9bd80-9877-11eb-8ca8-5c8ca1fd6673.JPG)
![IMG_1183](https://user-images.githubusercontent.com/5492064/114078578-22f5db00-9877-11eb-8963-b655fec8f60d.JPG)
