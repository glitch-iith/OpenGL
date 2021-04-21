# Getting Started!
We're about to write our first ever opengl program! What does it do? It flashes colors generated randomly.

Before getting started with our first program, we need to learn a few things about the external libraries that we're going to use.

## A note on libraries

From the setting up process, you might remember that I've asked you to download a folder named ```Src``` and place it in your C: drive. If you've opened it, you might have noticed the following 2 folders:
1. GLFW
2. GLEW

These are nothing but the external libraries that I've talked about. So, why are they necessary?

1. Since we're programming "Graphics", unlike the c++ programs that you're used to, we require a window in addition to the console/terminal which displays our graphics. GLFW serves that purpose.
2. GLEW is an extension loading library, which helps in determining which openGL extensions are supported by your hardware.

In addition to the above 2 libraries, we also use another library ```opengl32.lib``` which is available by default with your graphics drivers, so we need not worry about configuring that.

## Step 1: Create a visual studio project
1. Open Visual Studio and select ```Create a new project```
2. Select ```Console App``` and click ```Next```
3. Fill the boxes as below:
   - Project name: ```1 Getting Started```
   - Directory: ```C:\Src```
   - Solution name: ```OpenGL```
4. Do not check "Place solution and project in the same directory"
5. Click ```Create```.

If you've succesfully created a project, then your screen should look like this:
![Project Creation](https://raw.githubusercontent.com/sachingodishela/resources/main/1.PNG)

## Step 2: Linking the libraries
This part of the tutorial is very important. Even minor mistakes in linking libraries will lead to build failure. Be mindful for the next few minutes :)

1. Press ```Alt + F7``` to open the property pages of the current project (i.e. 1 Getting Started)

2. In the property window, at the top you'll see 2 dropdowns. One for configuration and other for platform.

3. For configuration, select ```All Configurations``` and for platform, select ```x64```. Click apply.

![c++ general](https://raw.githubusercontent.com/sachingodishela/resources/main/cpp%20general.PNG)

4. In the left pane, navigate to ```Configuration Properties > C/C++ > General```.

5. In the additional include directories, fill this: ```C:\Src\GLFW\include; C:\Src\GLEW\include```

![linker general](https://raw.githubusercontent.com/sachingodishela/resources/main/linker%20general.PNG)

6. In the left pane, navigate to ```Configuration Properties > Linker > General```.

7. In the additional dependencies, add this at the beginning: ```opengl32.lib;glew32.lib;glfw3.lib;``` 

![linker input](https://raw.githubusercontent.com/sachingodishela/resources/main/linker%20input.PNG)

Click apply and close the properties window.
