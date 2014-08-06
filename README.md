```
  ██████╗██████╗ ██████╗     ███╗   ███╗███████╗████████╗██████╗ ██╗ ██████╗███████╗
 ██╔════╝██╔══██╗██╔══██╗    ████╗ ████║██╔════╝╚══██╔══╝██╔══██╗██║██╔════╝██╔════╝
 ██║     ██████╔╝██████╔╝    ██╔████╔██║█████╗     ██║   ██████╔╝██║██║     ███████╗
 ██║     ██╔═══╝ ██╔═══╝     ██║╚██╔╝██║██╔══╝     ██║   ██╔══██╗██║██║     ╚════██║
 ╚██████╗██║     ██║         ██║ ╚═╝ ██║███████╗   ██║   ██║  ██║██║╚██████╗███████║
  ╚═════╝╚═╝     ╚═╝         ╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚═╝ ╚═════╝╚══════╝
```
C++ Metrics Library which migrate from Java Metrics
---------------------------------------------------

Draft 0.0.1:    Support Meter & UniformReservoir

How to Build 
---------------
*Use "typhoon-blade" to build this library*

1. Install typhoon-blade (http://code.google.com/p/typhoon-blade/)
2. cd repository directory
3. blade build .
4. Target library is "build64_release/CPPMetrics/libcppmetrics.a"

How to Use
------------
1. Add the libcppmetrics.a library to your library
2. Initialize the "MetricsRegistry"
3. Register a CSV reporter
4. Add Metrics

Needed ThirdParty
-----------------
- Boost
- glog
- gflags


