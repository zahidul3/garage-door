# garage-door

A garage door can be *hacked* to be opened by any wireless system. In this case, we will use BLE to control an existing garage door without changing existing functionality. 

We will attach a wireless board to the wall switch that is wired to the garage door unit. A smartphone or any other BLE devices with sufficient authorization will be able to access the garage door.

# Pre-requisites

BLE device

PC to program the BLE device

Solid State Relay

Knowledge of basic circuit theory

# Method

We insert a solid state relay (SSR) in parallel into the wall switch of the garage door. We control the SSR using one of the output pins of the BLE device. We program the BLE device to accept connections from an external device, i.e. smartphone, and drive the output pin based on byte of data written to a characteristic. I am using Silicon Labs BGX devices for faster programming without an IDE. 

FYI, I have hacked my own garage door this way and have been using my iPhone to open my garage door for years. I am obviously using secure connections so others can't hack into my own garage!
