# WebAssembly Introduction

WebAssembly is an assembly language for a conceptual machine. WebAssembly is a way to run programming languages other than JavaScript on web pages.


## Setup your dev environment 
### If you want to skip the following emscripten dev setup see Docker option for compilation below

Install emsdk: https://emscripten.org/docs/getting_started/downloads.html

Remember to run this command at emsdk ROOT dir for each session (terminal)

```source ./emsdk_env.sh --build=Release```

## Compile the code

```emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]'  -o mult.js  mult.c```

- WASM=1 tells Emscripten to give us a Wasm file instead of an asm.js file
- EXTRA_EXPORTED_RUNTIME_METHODS tells compiler we want to use ccall and cwrap
- 03 means optimize aggressively
- After running the command you should end up with a JavaScript file called mult.js and a WebAssembly file called mult.wasm (Wasm module contains compiled C code).

## Docker option for compilation 
Yes, I'm a fan of Docker.  So if you want to get this demo up and running quickly without the trouble of setting up yet another SDK use Docker.  If you have Docker installed you are good! If not, install Docker (one time cost).  

Use the following  image (from emscripten) to produce the js and wasm files  

```docker run --rm -v $(pwd):/src trzeci/emscripten emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' mult.c -o mult.js```

You can then test the js and wasm files on your laptop or desktop as shown below.

## Test it

Now that you have created WASM and js files, it is time to test calling the C function from a web page.  Load, initialize and run your module by using the generated JavaScript file. Once you load the js file, you will have a Module global to use. 

There are two ways to call the native function
- ccall() calls a compiled C function with specified parameters and returns the result
- cwrap() “wraps” a compiled C function and returns a JavaScript function you can call normally
so cwrap is more useful if you plan to call a compiled function multiple times

cwrap--create a JavaScript native function that takes care of converting parameters to something C-friendly and invoking the wrapped function. cwrap takes the function name, return type and argument types as arguments in that order:  

There are two example web pages for testing using ccall and cwrap: testccall.html and testcwrap.html

On a Mac you can use the following to serve up both these pages. Look at Chrome's Browser Console to see output.  

```python -m SimpleHTTPServer 8000```

For other platforms, fire up your favorite web server and then test using your favorite browser.
