# WebAssembly Introduction

What happens if I want to use applications written in other languages such as C or C++ in a web browser? For example, a game developed in C++ such as https://www.funkykarts.rocks/demo.html. Well, you could try and rewrite the code in Javascript but you may not be able to meet the performance or functional considerations. WebAssembly provides a way of taking code in languages other than JavaScript and run them in the browser.

WebAssembly has been described as machine language for a conceptual machine.  In short, it is  faster as the browser downloads the WebAssembly which is a small jump to the target machine assembly code. Let's step back for a bit. If a web page requires Javascript, the browser downloads the file, parses into an Abstract Syntax Tree, then into bytecode, then it gets compiled and optimized during execution while memory need to be managed by the garbage collector. With WebAssembly, the browser fetches a smaller file (WebAssembly is more compact than Javascript), the code is more like machine code (because it is compiled ahead of time and does not need to be optimized during execution) and no execution cycles are spent on memory management (as this is done by the developer when coding). 

Is WebAssembly ready for prime time right now? The basics are there and there is more to come. For example, exceptions are not defined, no direct access to DOM (you have to go though Javascript) and SIMD support is coming (running tasks in parallel).  Check out current browser support here https://caniuse.com/#search=webassembly   There was also a recent announcment called WASI which is an interesting initiative to run WebAssembly outside a browser environment.

This is a example of calling a simple C function from Javscript.  The C function returns the multiplication of two numbers (I know pretty simple).  The output appears in the browser console. So no need to understand HTML.

So how do I compile code form a language such as C to WebAssembly? I found the emscripten toolset to be an easy option.  

## Compile by first setting up your development environment 
#### If you want to skip the following emscripten SDK development setup see Docker option for compilation below

Install emsdk: https://emscripten.org/docs/getting_started/downloads.html

Remember to run this command at emsdk ROOT dir for each session (terminal)

```source ./emsdk_env.sh --build=Release```

#### Compile the code

```emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]'  -o mult.js  mult.c -g```

- WASM=1 tells Emscripten to give us a Wasm file instead of an asm.js file
- EXTRA_EXPORTED_RUNTIME_METHODS tells compiler we want to use ccall and cwrap
- 03 means optimize aggressively
- g option produces a textual representation of the wasm binary format. Remember the basic unit in WebAssembly is a module.  Look for the s-expressions in the text version (s-expressions are a format for representing trees). So, a module is essentially a tree of nodes. Search for the func declaration of mult.  There should be two i32 parameters and an i32 result (32-bit integers) and the i32.mult instruction.

After running the command you should end up with a JavaScript file called mult.js and a WebAssembly file called mult.wasm (Wasm module contains compiled C code).

## Or Compile by using Docker  
Yes, I'm a fan of Docker.  So if you want to get this demo up and running quickly without the trouble of setting up yet another SDK use Docker.  If you have Docker installed you are good! If not, install Docker (one time cost).  

Use the following  image (from emscripten) to produce the js and wasm files  

```docker run --rm -v $(pwd):/src trzeci/emscripten emcc -O3 -s WASM=1 -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap", "ccall"]' mult.c -o mult.js -g```

You can then test the js and wasm files on your laptop or desktop as shown below.

## Test it

So once you have a WebAssembly module (wasm file) and your js glue code file (produced by emscripten), you can then load it from your Javascript.  It is time to test calling the C function from a web page.  Load, initialize and run your module by using the generated JavaScript file. Once you load the js file, you will have a Module global to use. 

There are two ways to call the native function
- ccall() calls a compiled C function with specified parameters and returns the result
- cwrap() “wraps” a compiled C function and returns a JavaScript function you can call normally
so cwrap is more useful if you plan to call a compiled function multiple times

cwrap--create a JavaScript native function that takes care of converting parameters to something C-friendly and invoking the wrapped function. cwrap takes the function name, return type and argument types as arguments in that order:  

There are two example web pages for testing using ccall and cwrap: testccall.html and testcwrap.html

On a Mac you can use the following to serve up both these pages. Look at Chrome's Browser Console to see output.  

```python -m SimpleHTTPServer 8000```

For other platforms, fire up your favorite web server and then test using your favorite browser.
