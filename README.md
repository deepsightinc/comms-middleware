# Communications Middleware Library

This repo contains a communications library that exposes pub-sub capabilities and an 
example client and server that uses the library to communicate.


## Build Instructions

### Prerequisites  
* Host machine must run Ubuntu 22.04 and have a compiler supporting C++17  
* Install the necessary packages:
`sudo apt-get install googletest`
  * Download and install ZMQ package here:
  https://mirrorcache-us.opensuse.org/repositories/network:/messaging:/zeromq:/release-draft/Debian_11/amd64/libzmq3-dev_4.3.4-0_amd64.deb: 
* To build gtest/gmock libraries, run the following:  
````
cd /usr/src/googletest
sudo cmake .
sudo cmake --build . --target install
````

### Building
* Navigate to the root directory of the repository and run the following commands:
````
cmake -S . -B build/
cd build
cmake --build .
````

## TODO
* ~~Make publisher threadsafe~~ 
* ~~Make subscriber threadsafe~~
* Test out inproc transport (defer for later)
* ~~Compile-time topic generation~~
* ~~Proper topic filtering~~
* Protobuf payloads
* ~~Shared context for publishers (and subscribers?)~~
* Forwarder pattern for publishers (defer for later)
* ~~Fake for test~~
* ~~Complete server and client example~~
* ~~Test compilation with aarch64 compiler~~
* ~~Test on Kria~~
* Tests to add:
  * ~~Multiple publishers + Single subscribers~~
  * ~~Multiple subscribers + single publishers~~


