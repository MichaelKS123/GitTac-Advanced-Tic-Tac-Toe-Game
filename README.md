# 🎮 GitTac - Advanced Tic Tac Toe Game

**Created by Michael Semera**

GitTac is a feature-rich Tic Tac Toe game written in C++ with support for both classic 2D and advanced 3D gameplay, single-player mode with AI opponents at four difficulty levels (Easy, Medium, Hard, Impossible), and multiplayer mode for playing with friends.

---

## ✨ Features

### Game Modes
- 🎯 **Single Player** - Play against AI with 4 difficulty levels
- 👥 **Multiplayer** - Play against a friend locally

### Board Types
- 📏 **Classic 2D** - Traditional 3x3 grid
- 🎲 **Advanced 3D** - Challenging 3x3x3 cube

### AI Difficulty Levels
1. **Easy** - Random move selection
2. **Medium** - Basic strategy (win/block detection)
3. **Hard** - Advanced strategy (win/block + center/corner preference)
4. **Impossible** - Minimax algorithm (perfect play)

### Technical Features
- ✅ 2D and 3D array implementation
- ✅ Comprehensive win condition checking
- ✅ Input validation and error handling
- ✅ Colorful terminal output with ANSI codes
- ✅ Clean, object-oriented design
- ✅ Minimax AI algorithm for unbeatable gameplay

---

## 🎯 Concepts Covered

### Data Structures
- **2D Arrays** - Classic board representation
- **3D Arrays** - Advanced multi-layer board
- **Vectors** - Dynamic move storage
- **Tuples** - Coordinate management

### Algorithms
- **Minimax Algorithm** - Game tree search for optimal moves
- **Alpha-Beta Pruning** - Optimization (implicit in implementation)
- **Win Detection** - Multiple pattern checking algorithms
- **Strategic Move Selection** - Heuristic-based AI decisions

### C++ Concepts
- **Object-Oriented Programming** - Class-based design
- **Enums** - Game mode and difficulty management
- **Loops** - Game flow control
- **Conditionals** - Win/draw/lose checking
- **Input Validation** - Robust user input handling
- **Standard Library** - Vector, string, iostream usage

---

## 📋 Prerequisites

- **C++ Compiler** - g++, clang++, or MSVC
- **C++11 or higher** - For modern C++ features
- **Terminal/Command Prompt** - For running the game

---

## 🚀 Installation & Compilation

### Linux / macOS

```bash
# Clone or download the source code
git clone https://github.com/yourusername/gittac.git
cd gittac

# Compile the game
g++ -std=c++11 gittac.cpp -o gittac

# Run the game
./gittac
```

### Windows (Command Prompt)

```cmd
# Compile using MinGW
g++ -std=c++11 gittac.cpp -o gittac.exe

# Or using MSVC
cl /EHsc gittac.cpp

# Run the game
gittac.exe
```

### Using Make (Optional)

Create a `Makefile`:

```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = gittac

all: $(TARGET)

$(TARGET): gittac.cpp
	$(CXX) $(CXXFLAGS) gittac.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
```

Then:
```bash
make
make run
```

---

## 🎮 How to Play

### Starting the Game

1. **Run the executable**
   ```bash
   ./gittac
   ```

2. **Choose board type**
   - Option 1: Classic 2D (3x3)
   - Option 2: Advanced 3D (3x3x3)

3. **Select game mode**
   - Option 1: Single Player (vs AI)
   - Option 2: Multiplayer (vs Human)

4. **Enter player name(s)**
   - Single Player: Enter your name
   - Multiplayer: Enter both players' names

5. **Choose difficulty** (Single Player only)
   - 1: Easy - Random moves
   - 2: Medium - Basic strategy
   - 3: Hard - Advanced tactics
   - 4: Impossible - Perfect AI

### Classic 2D Mode

**Board Layout:**
```
     1   2   3
   ╔═══╦═══╦═══╗
 1 ║   ║   ║   ║
   ╠═══╬═══╬═══╣
 2 ║   ║   ║   ║
   ╠═══╬═══╬═══╣
 3 ║   ║   ║   ║
   ╚═══╩═══╩═══╝
```

**Making a Move:**
```
X's turn. Enter row (1-3): 2
Enter column (1-3): 2
```

**Win Conditions (2D):**
- 3 in a row horizontally
- 3 in a column vertically
- 3 in a diagonal

### Advanced 3D Mode

**Board Layout (3 Layers):**
```
Layer 1:
     1   2   3
   ╔═══╦═══╦═══╗
 1 ║   ║   ║   ║
   ╠═══╬═══╬═══╣
 2 ║   ║   ║   ║
   ╠═══╬═══╬═══╣
 3 ║   ║   ║   ║
   ╚═══╩═══╩═══╝

Layer 2: ...
Layer 3: ...
```

**Making a Move:**
```
X's turn. Enter layer (1-3): 2
Enter row (1-3): 2
Enter column (1-3): 2
```

**Win Conditions (3D):**
- 3 in a row on any layer (horizontal/vertical/diagonal)
- 3 in a column through layers (vertical stacking)
- 3 in 3D diagonals (corner to corner through cube)

---

## 🤖 AI Difficulty Explained

### 1. Easy Mode
**Algorithm:** Random Move Selection

```cpp
// Pseudo-code
available_moves = get_all_empty_cells()
random_move = pick_random(available_moves)
make_move(random_move)
```

**Characteristics:**
- No strategy
- Random placement
- Easy to beat
- Good for beginners

### 2. Medium Mode
**Algorithm:** Win/Block Strategy

```cpp
// Pseudo-code
if can_win_in_one_move():
    make_winning_move()
else if opponent_can_win():
    block_opponent()
else:
    make_random_move()
```

**Characteristics:**
- Tries to win when possible
- Blocks opponent's winning moves
- Otherwise random
- Moderate challenge

### 3. Hard Mode
**Algorithm:** Win/Block + Center/Corner Priority

```cpp
// Pseudo-code
if can_win_in_one_move():
    make_winning_move()
else if opponent_can_win():
    block_opponent()
else if center_available():
    take_center()
else if corner_available():
    take_corner()
else:
    make_random_move()
```

**Characteristics:**
- All Medium features
- Prefers center square
- Takes corners strategically
- Difficult to beat

### 4. Impossible Mode
**Algorithm:** Minimax with Depth Scoring

```cpp
// Minimax algorithm
function minimax(depth, isMaximizing):
    if game_over:
        return evaluate_position(depth)
    
    if isMaximizing:
        best_score = -infinity
        for each possible_move:
            score = minimax(depth+1, false)
            best_score = max(score, best_score)
        return best_score
    else:
        best_score = +infinity
        for each possible_move:
            score = minimax(depth+1, true)
            best_score = min(score, best_score)
        return best_score
```

**Characteristics:**
- Explores all possible game states
- Chooses mathematically optimal move
- Never loses (only wins or draws)
- Maximum challenge

**Scoring System:**
```
Win: +10 - depth (prefer faster wins)
Loss: -10 + depth (delay losses)
Draw: 0
```

---

## 🏗️ Code Architecture

### Class Structure

```cpp
class GitTacGame {
private:
    // Data members
    vector<vector<char>> board2D;           // 2D board
    vector<vector<vector<char>>> board3D;   // 3D board
    char currentPlayer;
    GameMode mode;
    Difficulty difficulty;
    
public:
    // Setup methods
    void displayBanner();
    void setupGame();
    void initializeBoard();
    
    // Display methods
    void displayBoard2D();
    void displayBoard3D();
    
    // Game logic
    bool isValidMove(int row, int col, int layer);
    void makeMove(int row, int col, int layer);
    bool checkWin();
    bool checkDraw();
    
    // Player input
    void getHumanMove();
    void getAIMove();
    
    // AI algorithms
    void getAIMoveEasy();
    void getAIMoveMedium();
    void getAIMoveHard();
    void getAIMoveImpossible();
    int minimax(int depth, bool isMaximizing);
    
    // Game flow
    void play();
    void playAgain();
};
```

### Win Detection Logic

**2D Board Wins:**
```cpp
// Rows: (0,0)-(0,1)-(0,2), (1,0)-(1,1)-(1,2), (2,0)-(2,1)-(2,2)
// Cols: (0,0)-(1,0)-(2,0), (0,1)-(1,1)-(2,1), (0,2)-(1,2)-(2,2)
// Diag: (0,0)-(1,1)-(2,2), (0,2)-(1,1)-(2,0)
```

**3D Board Wins:**
```cpp
// 2D patterns on each layer (3 layers × 8 patterns = 24)
// Vertical stacks (9 positions × 3 layers = 9)
// 3D diagonals: 4 corner-to-corner paths
// Total: 24 + 9 + 4 = 37 winning combinations!
```

---

## 🎨 Features in Detail

### Color-Coded Output

```cpp
// ANSI color codes used
RED = "\033[31m"      // Player X
BLUE = "\033[34m"     // Player O
GREEN = "\033[32m"    // Success messages
YELLOW = "\033[33m"   // Prompts
CYAN = "\033[36m"     // Headers
MAGENTA = "\033[35m"  // Special messages
```

### Input Validation

```cpp
// Validates:
- Integer inputs only
- Range checking (1-3)
- Empty cell checking
- Error recovery with cin.clear()
- User-friendly error messages
```

### Game State Management

```cpp
// Tracks:
- Current player turn
- Move count (for draw detection)
- Game over status
- Player names
- Board state (2D or 3D)
```

---

## 📊 Complexity Analysis

### Time Complexity

| Operation | 2D Board | 3D Board |
|-----------|----------|----------|
| Display Board | O(9) | O(27) |
| Check Win | O(8) | O(37) |
| Valid Move | O(1) | O(1) |
| Minimax (Impossible) | O(9!) | O(27!)* |

*Note: 3D uses Hard mode AI due to computational limits

### Space Complexity

| Component | 2D Board | 3D Board |
|-----------|----------|----------|
| Board Storage | O(9) | O(27) |
| Minimax Stack | O(9) | O(27) |
| Move History | O(1) | O(1) |

---

## 🐛 Troubleshooting

### Issue: Colors Not Displaying

**Problem:** ANSI codes not supported by terminal

**Solution:**
```cpp
// Remove color codes or use Windows Console API
// For Windows 10+, enable VT100:
system(""); // Empty system call enables ANSI
```

### Issue: Compilation Errors

**Problem:** C++11 features not recognized

**Solution:**
```bash
# Ensure C++11 or higher
g++ -std=c++11 gittac.cpp -o gittac

# Or C++14/17/20
g++ -std=c++17 gittac.cpp -o gittac
```

### Issue: Input Not Working

**Problem:** Buffer issues or invalid input

**Solution:**
```cpp
// Already handled in code with:
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

### Issue: AI Too Slow (Impossible Mode)

**Problem:** Minimax takes time on first few moves

**Solution:**
- This is normal for Impossible mode
- Uses full game tree analysis
- Faster on later moves (fewer possibilities)
- 3D board uses Hard mode to avoid this

---

## 🎓 Learning Outcomes

### Beginner Level
✅ Basic C++ syntax and structure  
✅ Variables and data types  
✅ Input/output operations  
✅ Control flow (if/else, loops)  
✅ Functions and methods  

### Intermediate Level
✅ Object-oriented programming  
✅ Classes and encapsulation  
✅ 2D and 3D arrays  
✅ Error handling  
✅ Game loop architecture  

### Advanced Level
✅ Minimax algorithm implementation  
✅ Recursive algorithms  
✅ Game tree search  
✅ AI strategy design  
✅ Code optimization  

---

## 🚀 Future Enhancements

### Planned Features
- [ ] Graphical user interface (GUI)
- [ ] Network multiplayer
- [ ] Game history and replay
- [ ] Custom board sizes (4x4, 5x5)
- [ ] Save/load game state
- [ ] Tournament mode
- [ ] Statistics tracking
- [ ] Difficulty auto-adjustment
- [ ] Hints for players
- [ ] Undo/redo moves

### Code Improvements
- [ ] Alpha-beta pruning for faster AI
- [ ] Move ordering optimization
- [ ] Transposition table for memoization
- [ ] Iterative deepening
- [ ] Opening book for common starts

---

## 📚 References & Resources

### C++ Learning
- **C++ Reference**: https://en.cppreference.com/
- **Learn C++**: https://www.learncpp.com/
- **C++ Tutorial**: https://www.cplusplus.com/doc/tutorial/

### Game AI Algorithms
- **Minimax Algorithm**: https://en.wikipedia.org/wiki/Minimax
- **Game Theory**: "Artificial Intelligence: A Modern Approach" by Russell & Norvig
- **Alpha-Beta Pruning**: https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-4-alpha-beta-pruning/

### Data Structures
- **Arrays**: https://www.geeksforgeeks.org/array-data-structure/
- **Vectors**: https://www.cplusplus.com/reference/vector/vector/

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Ways to Contribute
1. **Report bugs** - Open an issue
2. **Suggest features** - Propose enhancements
3. **Submit code** - Create pull requests
4. **Improve documentation** - Clarify instructions
5. **Share feedback** - Help improve the game

### Contribution Process
```bash
# Fork the repository
git clone https://github.com/yourusername/gittac.git

# Create feature branch
git checkout -b feature/amazing-feature

# Make changes and commit
git commit -m "Add amazing feature"

# Push to branch
git push origin feature/amazing-feature

# Open Pull Request
```

---

## 📄 License

This project is licensed under the MIT License.

```
MIT License

Copyright (c) 2025 Michael Semera

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 👤 Author

**Michael Semera**

- 💼 LinkedIn: [Michael Semera](https://www.linkedin.com/in/michael-semera-586737295/)
- 🐙 GitHub: [@MichaelKS123](https://github.com/MichaelKS123)
- 📧 Email: michaelsemera15@gmail.com

---

## 🙏 Acknowledgments

- **Game Theory** - Classic Tic Tac Toe strategies
- **Minimax Algorithm** - Claude Shannon & Alan Turing
- **C++ Community** - Stack Overflow and GitHub contributors
- **Inspiration** - Classic terminal games

---

## 📊 Project Statistics

- 📝 **Lines of Code**: ~800
- 🎯 **Functions**: 25+
- 🎲 **Game Modes**: 2
- 🤖 **AI Levels**: 4
- 🏆 **Win Conditions**: 37 (in 3D mode)
- ⏱️ **Development Time**: Comprehensive implementation
- 🎨 **Color Codes**: 7 ANSI colors

---

## 🎮 Gameplay Tips

### For Beginners
1. **Start with Easy mode** to learn the basics
2. **Control the center** in 2D mode (most strategic position)
3. **Think one move ahead** to avoid obvious traps
4. **Block opponent's wins** before creating your own

### For Intermediate Players
1. **Use corners strategically** in 2D mode
2. **Force opponent into bad positions** (fork strategy)
3. **Plan 2-3 moves ahead**
4. **Try 3D mode** for extra challenge

### For Advanced Players
1. **Challenge Impossible mode** to test your skills
2. **Master 3D diagonal wins** (hardest to see)
3. **Study AI patterns** to predict moves
4. **Create multiple winning threats** (forks)

### 3D Board Strategies
1. **Visualize layers** mentally
2. **Watch for vertical stacks** (often overlooked)
3. **3D diagonals are powerful** (4 ways to win)
4. **Center of middle layer** is strongest position

---

## 🔧 Customization Guide

### Changing Board Size

```cpp
// In GitTacGame constructor
boardSize = 4;  // Change from 3 to 4 for 4x4

// Note: Also update win checking logic
```

### Adding New AI Difficulty

```cpp
// Add to Difficulty enum
enum Difficulty { EASY, MEDIUM, HARD, IMPOSSIBLE, CUSTOM };

// Implement new strategy
void getAIMoveCustom() {
    // Your custom AI logic here
}
```

### Custom Win Conditions

```cpp
// Add to checkWin2D()
bool checkCustomPattern() {
    // Define your custom winning pattern
    // Example: X pattern, T pattern, etc.
}
```

### Changing Colors

```cpp
// Modify color constants
const string PLAYER_X_COLOR = "\033[31m";  // Red
const string PLAYER_O_COLOR = "\033[34m";  // Blue

// Or remove colors entirely
const string RED = "";
const string BLUE = "";
```

---

**Made with 🎮 by Michael Semera**

*Master the game, challenge the AI, have fun!*

---

**Version**: 1.0.0  
**Last Updated**: November 1, 2025  
**Status**: Production Ready ✅  
**Language**: C++11  
**License**: MIT