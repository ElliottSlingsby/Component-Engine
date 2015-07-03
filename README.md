## Solution Folder Structure
**Middleware:** Contains all library includes and licenses.  
**Bin:** Contains all dll files, and is also where the exe will be placed.  
**Asset:** The default path where the Asset Loader loads from.  
**Source:** Contains the files for the main project.  

## Project Folder Structure
**Base:** Contains base classes used for game objects.  
**Component:** Contains derived component classes.  
**Game:** Contains temporary Main and Setup functions. (Eventually will be replaced with a game class)  
**Math:** Contains math based classes like Vectors and Quaternions.  
**Prefab:** Contains derived entity prefabs.  

## Global Singletons
**Asset Loader:** Handles flyweight loading of all images. (Eventually will also handle obj files and maybe sound)  
**Entity Manager:** Handles the instantiation, tracking, and overall lifetime of all entities created.  
**Window:** Handles initializing SDL and OpenGL, controlling the main window, and flipping the buffer.  