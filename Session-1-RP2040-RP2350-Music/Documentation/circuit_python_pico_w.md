# Circuit Python op de Raspberry Pi Pico W

Download de uf2 circuitpython firmware voor de Pico W  
https://circuitpython.org/board/raspberry_pi_pico_w/

Sluit de usb-kabel aan op de pico-w aan en plug hem,  
**terwijl je het witte bootsel(ect) knopje op de pico-w ingedrukt houdt**,in je laptop/computer.  
Laat het knopje pas los als de usb-kabel in je laptop/computer zit.  

De pico-w staat nu in de modus waarin je sepcifieke firmware kunt installeren.  
Kopiëer in de verkenner/finder het gedownloade uf2 bestand,  
*adafruit-circuitpython-raspberry_pi_pico_w-en_US-10.1.4.uf2 op het moment*,   
naar de drive die is verschenen toen je pico-w inplugde.

Na het kopieren herstart de pico-w en is dan klaar voor gebruik met een IDE.

Bijvoorbeeld de online circuitpython editor: *( let op Edge of Chrome nodig! )*   
https://code.circuitpython.org/

- Klik op de knop **[USB]** (verbindings methode)
- Klik op **[Connect to Device]**  
- Selecteer in de popup je device en klik op **[verbinding maken]**  
- Klik op **[Select Folder]** / **[Select different folder]**  
- en navigeer naar je device **CircuitPy**  
- Klik op **[select folder]** / **[map selecteren]**  
- klik op **[OK]**

Je bent nu verbonden met de pico-w en kunt je code gaan maken.  
## Een klein **Hello World/ Blink** voorbeeld hieronder:

```
import time
import board
import digitalio

print("Hello World, Blink")
# Set up the LED pin
led = digitalio.DigitalInOut(board.LED) # Use 'board.D13' if no built-in LED
led.direction = digitalio.Direction.OUTPUT

while True:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)
```

--- 
## Voorbeeld met Wifi
```
import time
import board
import digitalio
from os import getenv
import ipaddress
import wifi
import socketpool

connectToWifi=True

print("Hello World")
print("My MAC addr:", [hex(i) for i in wifi.radio.mac_address])

# Set up the LED pin
led = digitalio.DigitalInOut(board.LED) # Use 'board.D13' if no built-in LED
led.direction = digitalio.Direction.OUTPUT

if connectToWifi:
    # --------------- WIFI -------------------------------------
    # Get WiFi details, ensure these are setup in settings.toml
    # CIRCUITPY_WIFI_SSID = "iotroam"
    # CIRCUITPY_WIFI_PASSWORD = "password_for_iotroam"
    # ---------------------------------------------------------- 
    ssid = getenv("CIRCUITPY_WIFI_SSID")
    password = getenv("CIRCUITPY_WIFI_PASSWORD")
    if None in [ssid, password]:
        raise RuntimeError("WiFi settings are kept in settings.toml, please add them there. The settings file must contain 'CIRCUITPY_WIFI_SSID', 'CIRCUITPY_WIFI_PASSWORD', at a minimum.")
    print()
    print(" --- Connecting to WiFi")
    try:
        wifi.radio.connect(ssid, password)
    except TypeError:
        print("Could not find WiFi info. Check your settings.toml file!")
        raise
    
    print(" {-} Connected to WiFi")
    pool = socketpool.SocketPool(wifi.radio)
    print(f"Pico IP address is {wifi.radio.ipv4_address}")
else:
    print("Skipping Wifi")
    
#--------------- END WIFI ---------------
print("Blink on Pico")
while True:
    led.value = True
    time.sleep(0.5)
    led.value = False
    time.sleep(0.5)
``` 

## Pico-W Pinout
![PicoW pintpout](https://components101.com/sites/default/files/component_pin/Raspberry%20Pi-Pico-W-pinout.png "pico-w pinout")