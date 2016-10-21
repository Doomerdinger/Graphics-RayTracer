# Graphics-RayTracer
A ray tracer I made in advanced computer graphics. Updates made after.

The ray tracer takes in an .obj file, uses a raytracing technique to render the scene, and then outputs the result to a file.

It is a command line program. It takes 2 or 4 arguments.
The first two arguments are ObjectName.obj and OutputFileName.obj which specify the input obj file and the name for the rendered png file.
The second two (optional, though you must have both) are the xres and yres, singifying the resolution of the output image in x and y.
  If x and y are not provided, the program uses a defualt resolution (1000x1000 or 500x500 depending on the version).
YOU WILL WANT TO RUN THIS ON A RELEASE BUILD OR IT WILL BE SLOW.
  
Typical .obj files will not work, this application requires a camera object and light objects in the obj file as well. There are examples provided.

Some of the code I was provided uses fopen, which is marked as unsafe. You'll have to add a preprocessor definition in visual studio (it will tell you).
Additionally, this project does not use precompiled headers, so if you use visual studio you will have to disable those.

Files used but not created by me are marked with a comment at the top. 
Source for theose files is Dr. Micah Taylor at Rose-Hulman Institute of technology.
