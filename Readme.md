# ♟️ Console Chess Engine (C++)

A console-based chess engine developed completely using object-oriented programming in **C++**.

The goal of this project was to understand how a complete chess game can be designed from scratch without using any external libraries. Every chess piece has its own movement logic, moves are validated according to the rules of chess, and the game maintains the complete board state throughout gameplay.

## Features

- Standard 8×8 chess board
- Legal move generation for all six pieces
- Move validation
- Piece captures
- Turn-based gameplay
- Check detection
- Checkmate detection
- Stalemate detection
- Castling
- Pawn promotion
- Undo last move
- Console-based board display

---

## Project Structure

```
Console Chess Engine/
│
├── include/
│   ├── Board.h
│   ├── Piece.h
│   ├── Pawn.h
│   ├── Knight.h
│   ├── Bishop.h
│   ├── Rook.h
│   ├── Queen.h
│   ├── King.h
│   ├── Position.h
│   ├── Move.h
│   ├── MoveHistory.h
│   ├── MoveValidator.h
│   ├── CheckDetector.h
│   ├── Player.h
│   └── Game.h
│
├── src/
│   ├── Board.cpp
│   ├── Piece.cpp
│   ├── Pawn.cpp
│   ├── Knight.cpp
│   ├── Bishop.cpp
│   ├── Rook.cpp
│   ├── Queen.cpp
│   ├── King.cpp
│   ├── Position.cpp
│   ├── Move.cpp
│   ├── MoveHistory.cpp
│   ├── MoveValidator.cpp
│   ├── CheckDetector.cpp
│   ├── Player.cpp
│   ├── Game.cpp
│   └── main.cpp
│
├── CMakeLists.txt
└── Readme.md
```

## Build

Using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Or compile manually:

```bash
g++ src/*.cpp -Iinclude -o chess
```

## Run

```bash
./chess
```

Windows:

```bash
chess.exe
```
---

## Technologies Used

- C++
- CMake
- Object-Oriented Programming
- STL (Vector, String, etc.)

---

## OOP Concepts Used

This project demonstrates several important software engineering concepts:

- Encapsulation
- Abstraction
- Inheritance
- Runtime Polymorphism (Virtual Functions)
- Composition
- Modular Design
- Single Responsibility Principle
- DRY (Don't Repeat Yourself)

---

## Current Game Rules Supported

| Rule | Status |
|-------|--------|
| Legal piece movement | ✅ |
| Piece capture | ✅ |
| Turn management | ✅ |
| Check detection | ✅ |
| Checkmate | ✅ |
| Stalemate | ✅ |
| Castling | ✅ |
| Pawn promotion | ✅ |
| Undo move | ✅ |
| Move history | ✅ |

---

## Design Overview

The engine is organized into independent modules:

- **Board** manages the game state.
- **Piece** is an abstract base class.
- Every chess piece overrides its own legal move generation.
- **MoveValidator** filters illegal moves and ensures the king is never left in check.
- **CheckDetector** detects check, checkmate, and attacked squares.
- **MoveHistory** stores previous moves for undo functionality.
- **Game** controls the gameplay loop, player turns, and user interaction.

This modular design makes the engine easy to extend and maintain.

---


## Future Improvements

Some features that can be added in the future:

- En passant
- Minimax AI
- Alpha-Beta Pruning
- PGN/FEN support
- GUI using SFML

