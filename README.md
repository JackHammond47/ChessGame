# Overview

This is a simple chess game, playable in the command line. The program is functional, however is missing some full feautures of chess due to time constraints. These include, castling, en-passent, upgrading pawns, and check/check-mate. The game is for 2 users and is played by having each player type the c,y coordinate of the peice they want to move and the x,y of where they want it to move. The program checks if the move is valid, moves the peice and deletes any captured peices. When one king is captured, one player wins.

[Software Demo Video](https://youtu.be/eC4Uq1lQrD4)

# Development Environment

I used C++ with VS code and minGW to compile, build, and run the code. I also used the iostream library for user input and output in the terminal.

# Useful Websites

- [cpluplus.com forum: idea about chess game](https://cplusplus.com/forum/general/235482/)
- [w3 schools tutorial on C++ syntax](https://www.w3schools.com/cpp/cpp_syntax.asp)

# Future Work

- Add check for pawns, if peice in front, block movement and if peice diagonal, allow capture move. Currently players have to manually verify that moves are legal.
- Add special moves such as en-passent, castling, and upgrading pawns.
- Add undo functionality and saving boards.
- Add restricitions for each color only moving every other turn and check restrictions and autmatic game-over for check-mate or stale-mate.