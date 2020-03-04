Depedencies:

    * Xeus 0.23.3
    
    * CPPZMQ 4.3.0
    
    * Clasp
    
Building:
    To build xeus-clasp, we need to use CMAKE to generate a make file. Use the command `cmake .`, and when that finishes, `make && make install`. If this works properly, congrats! xeus-clasp is built and installed. After that finishes, you can run your favorite jupyter notebook/lab (e.g. `juptyer lab` in the terminal) and you should see `xclasp` as a kernel option in the landing page.
