Render-Magic
============

This project is simple enough to compile, requiring the OpenGL, glut and glu libraries. As long as the libraries are present, just run the makefile included in the project directory. 

When run, the program has 2 windows that that pop up. The left window is the viewport where the scene with geometry will appear, and the other is the menu with several different buttons to control different aspects of changing the scene.

Controls:
  Adding Geometry:
  
    Enter add mode by pressing 'o' (already in add mode by default)
    1 to add cube
    2 to add sphere
    3 to add cylinder
    
  Selecting Geometry:
  
    When a new object is added, that object becomes the currently selected object
    Enter select mode by pressing 'o'
    1-0: select objects 1-10
    
  Transforming Geometry:
  
    Make sure Object transformation is toggled on in the menu (top row, second from left)
    Select desired transform from menu as well
      'a' & 'd': translate/rotate/scale along x axis
      'w' & 's': translate/rotate/scale along z axis
      'q' & 'e': translate/rotate/scale along y axis
      
  Translate Lights:
  
    select desired light from menu
    toggle light translation on (top row, second from right)
    same controls as geometry transformations
    
  Toggle lights:
  
    select desired light
    click on toggle light button
    
  Toggle grid:
  
    click toggle grid button
    
  Change Color:
  
    click within the color slider or the bottom black/white slider to change the objects color
    
  Pressing ESC will exit the program
