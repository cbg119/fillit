# fillit
This repository holds 42 Silicon Valley's "fillit" project. This project was done in conjunction with @NotHawthorne

The goal of this project is to take in a given list of tetrominos, then attempt to fit them in the smallest square possible.
We accomplish this by storing each tetromino as a 2d int array of offsets, then, using recursive backtracking when needed,
place them along the playing board.
