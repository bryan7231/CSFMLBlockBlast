# CMake SFML Block Blast recreation 

Block Blast coded in C++ and SFML (+OpenGL), as simple as that. This project was pretty interesting to work on, and had a lot of nuance to it that I initally did not expect, such as centering the blocks and adding a system to make sure only one block is grabbed at at time. Overall, it was a really enjoyable project and I would encourage others to try as well! It uses some pretty interesting matrix techniques, as well as a simple shader for Gaussian blur on the game over screen. The score is calculated exponentially based on number of rows cleared, as well as given multiplicative increases if both rows and columns are completed. The game is pretty unbalanced as the random rotations makes it pretty hard to play a long time.  

## How to Use

Clone the repo, either build and run through cmake, or just run the executable that should be in the folder. It probably only works on Windows, sorry Mac and Linux people. Left click to drag and drop blocks, space to restart if you lose. 

## More Reading

Here are some useful resources if you want to learn more about CMake:

- [Official CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/)
- [How to Use CMake Without the Agonizing Pain - Part 1](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-1.html)
- [How to Use CMake Without the Agonizing Pain - Part 2](https://alexreinking.com/blog/how-to-use-cmake-without-the-agonizing-pain-part-2.html)
- [Better CMake YouTube series by Jefferon Amstutz](https://www.youtube.com/playlist?list=PL8i3OhJb4FNV10aIZ8oF0AA46HgA2ed8g)

Documation to SFML:
- [SFML Documentation](https://www.sfml-dev.org/tutorials/3.0/)

## License

The source code is dual licensed under Public Domain and MIT 
