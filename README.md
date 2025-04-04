# Wave Sim

Based on 2d wave simulation principle by [ How to write a Height-Field Water Simulator with 100 lines of code by Ten Minute Physics](https://www.youtube.com/watch?v=hswBi5wcqAA).

The ultimate goal is multithreading and OpenMP support with ability to simulate various patterns in an effort to study the effectiveness of shoreline protection mechanisms.


### Roadmap:
- ~~Implement a renderer~~ DONE
- ~~Implement fluid simulation~~ DONE
- Add local multithreading support.
- Add ability to generate a live plot of waves on a point
- Add more shoreline protection structures
- Add OpenMP support.

### Dependencies
- SDL2
- Python 3
- matplotlib
- numpy

### Building:
- `cd build`
- `cmake ..`
- `make`
- `./wavesim`