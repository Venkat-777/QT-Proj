# Team-2-QT-Project-2D-Graphics-Modeler

Link to the Github Repository: https://github.com/Ericcccccai/Team-2-QT-Project-2D-Graphics-Modeler.git

CS1C 2D Graphics Modeler Project Team 2 QT

Hi, we are the midnight coders. This is a QT program that allow the users to add, remove, and edit different shapes. 

Shapes include Ellipse, Rectangle, Text, Line, Polyline, and Polygon.

The shapes are avliable to add, remove, edit, move, and more. 

Requirements:

********************************
Individual Project Requirements
********************************

2) Provide “contact us” method with team name and logo 

   a) Header File: "mainwindow.h"
   
   b) Source File: "mainwindow.cpp"
   
   c) Line Numbers: Team Name (line 25), Team Logo (line 11)

3) Display all graphic objects (i.e. shapes including text) in rendering window. The shape id will be displayed above each shape identifying it. 
   The rendering area to display shapes must have minimum dimensions of 1000 pixels (horizontal) by 500 pixels (vertical). The coordinate system
   is defined such that the top left corner of the rendering area is located at point (0,0), the bottom right corner at point (1000,500).
   
   a) Header File: "shapeManager.h"
   
   b) Source File: "shapeManager.cpp"
   
   c) Line Number: line 66
   
   * rendering window with specific dimensions is set using fillRect() for each shape before the shape is drawn

4) Your program should read from a shape file that keeps track of all shapes currently being rendered by the 2D modeler. Shapes are identified by
   their type: line, polyline, polygon, rectangle, ellipse, text. Shapes have properties: shape dimensions, pen color, pen width, pen style, pen
   cap style, pen join style, brush color, brush shape. Text has properties: shape dimensions, text string, text color, text alignment, text point
   size, text font family, text font style, text font weight. All shapes must also have a unique ID.
   
   a) Header File: "Parser.h"
   
   b) Source File: "Parser.cpp"
   
   c) Line Numbers: 
        
        - Read from shape file: lines 54, 85
        - Shape Type: 
            i)   Line: line 107
            ii)  Polyline: line 117
            iii) Polygon: line 128
            iv)  Rectangle: line 142
            v)   Ellipse: line 166
            vi)  Text: line 190
                   - Text String: line 572
                   - Text Color: line 586
                   - Text Alignment: line 602
                   - Text Point Size: line 613
                   - Text Font Family: line 623
                   - Text Font Style: line 637
                   - Text Font Weight: line 653	
        - Shape Properties:
            i)    Shape Dimensions:
                   - Line, Polyline, Polygon: lines 110, 120, 131, 332
                   - Rectangle, Ellipse, Text: lines 144, 168, 192, 352
            ii)   Pen Color: line 410
            iii)  Pen Width: line 421
            iv)   Pen Style: line 436
            v)    Pen Cap Style: line 452
            vi)   Pen Join Style: line 468
            vii)  Brush Color: line 511
            viii) Brush Shape: line 527
        - Shape Unique ID: lines 61, 92

5) Your program should be able to move shapes, including text, being rendered. This is accomplished via a move shape form. All changes are visible
   in the rendering area. – administrator only
   
	a) Header File: 
	
	b) Source File: 
   
	c) Line Number: 
   
6) Your program should be able to add and remove shapes, including text, being rendered. This is accomplished via an add/remove shape form. All
changes are visible in the rendering area. – administrator only

   a) Header File: "shapeManager.h"
   
   b) Source File: "shapeManager.cpp"
	
   c) Line Number: lines 38, 54

10) Save all changes between executions

       a) Header File: "Parser.h"
	
       b) Source File: "Parser.cpp"
	
       c) Line Number: line 675


****************************
General Project Requirements
****************************

You must use inheritance, aggregation, exception handlers, a virtual function, and at least two overloaded operators. At least one class should
use templates. At least one class must contain a pointer (a copy constructor needs to be written and tested).

1) Inheritance

   a) Header File: "Rectangle.h"

   b) Source File: "Rectangle.cpp"
	
   c) Line Number: 12 (.h)
	
	  * Rectangle inherits from Shape (same with all other shape classes)

2) Aggregation
   
	a) Header File: "Polyline.h"
   
	b) Source File: "Polyline.cpp"
   
	c) Line Number: 32 (.h)
	
      * Polyline "has-a" Vector<QPoint> points to hold its dimensions

3) Exception Handlers
   
	a) Header File: "shapeManager.h"
   
	b) Source File: "shapeManager.cpp"
   
	c) Line Number: line 48
	
      * use exception handlers to make sure that code doesn't remove a Shape if the size of the vector is 0 (there are no shapes)
   
4) Virtual Function
   
	a) Header File: "shape.h"
   
	b) Source File: "shape.cpp"
   
	c) Line Number: line 342 (.h)
	
      * draw() is a pure virtual method that is defined separately in its derived Shape classes

5) Overloaded Operators
   
	a) Header File: "shape.h"
   
	b) Source File: "shape.cpp"
   
	c) Line Number: lines 323, 337
	
      * == is overloaded to compare the unique ID of two Shape objects, returns true/false
	
      * < is overloaded to compare if one Shape's ID is less than the other's, returns true/false
     
6) Templated Class
				
   a) Header File: "vector.h"
				
   b) Source File: N/A
				
   c) Line Number: lines 10, 88
				
      * vector class and its methods are templated so they can work with different data types

7) Pointer
			
   a) Header File: "shapeManager.h"
				
   b) Source File: "shapeManager.cpp"
				
   c) Line Number: line 23
				
      * shapeManager uses the getShape method to return a pointer to a specific Shape based on the ID passed as a parameter

8) Copy Constructor
				
   a) Header File: "vector.h"
				
   b) Source File: N/A
				
   c) Line Number: line 155
				
      * copy constructor allows all values from one vector to be copied into another as long as it has already been instantiated
