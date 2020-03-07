`xeus-clasp` is a Jupyter kernel for [clasp](https://github.com/clasp-developers/clasp) based on the native implementation of the Jupyter protocol [xeus](https://github.com/jupyter-xeus/xeus)

## Usage

Launch Jupyter lab or notebook with `jupyter lab` or `jupyter notebook` and launch a new xclasp notebook by selection the **xclasp** kernel.

## Installing

### Depedencies:
    
Xeus-clasp depends on:

    * cmake

    * Xeus 0.23.3
    
    * CPPZMQ 4.3.0
    
    * Clasp
    
    * Jupyter
    
To install the dependencies in bash, try running
```bash
conda install cmake xeus cppzmq jupyterlab -c conda-forge
```
You will also need clasp, which can be built by following the build instructions on Clasp's [wiki](https://github.com/clasp-developers/clasp/wiki/Build-Instructions)
    
    
## Building

Once the dependencies have been installed, we can build `xeus-clasp`. We need to use `cmake` to generate a make file. In the `xeus-clasp` directory, use the command `cmake .`, and when that finishes, `make && make install`. If this works properly, congrats! xeus-clasp is built and installed. After that finishes, you can run your favorite jupyter notebook/lab (e.g. `juptyer lab` in the terminal) and you should see `xclasp` as a kernel option in the landing page.

## Installing the kernel.json file

The xeus-clasp/src/kernel.json needs to be installed so that jupyterlab can find it.
On macOS we put it at ~/Library/Jupyter/kernels/xclasp/kernel.json.

Currently all paths are hard-coded - this needs to be figured out so that it's portable.



## Questions

Clasp has an IRC channel on Freenode called #clasp. If you have questions, problems, suggestions, or generally would like to just hang out with us devs, come and stop by!
