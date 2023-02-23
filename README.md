# Communications Middleware Library

This repo contains a communications library that exposes pub-sub capabilities and an 
example client and server that uses the library to commmunicate.


## Build Instructions

### Prerequisites  
* Host machine must run Ubuntu 22.04 and have a compiler supporting C++17  
* Install the necessary packages:
`sudo apt-get install libzmq3-dev googletest`
* To build gtest/gmock libraries, run the following:


## TODO
* Make publisher threadsafe
* Make subscriber threadsafe
* Test out inproc transport
* Shared context for publishers (and subscribers?)
* Forwarder pattern for subscribers
* Tests:
  * Multiple publishers + Single subscribers
  * Multiple subscribers + single publishers
  * Multiple publishers + consumer


