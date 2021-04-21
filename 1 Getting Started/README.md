# Getting Started!
We're about to write our first ever opengl program! What does it do? It flashes colors generated randomly.

Before getting started with our first program, we need to learn a few things about the external libraries we're going to use.

## A note on libraries

In the setting up process, you might remember that I've asked you to download a folder named ```Src``` and place it in your C: drive. If you've opened it, you might have noticed the following 2 folders:
1. GLFW
2. GLEW

These are nothing but the external libraries that I've talked about. So, why are they necessary?

1. Since we're programming "Graphics", unlike the c++ programming that you're used to, we require a window in addition to the console/terminal which displays our graphics. GLFW serves that purpose.
2. GLEW is an extension loading library, which helps in determining which openGL extensions are supported by your hardware.

In addition to the above 2 libraries, we also use another library ```opengl32.lib``` which is available by default with your graphics drivers, so we need not worry about configuring that.
