# 🎮 Brick Breaker Game

A classic **Brick Breaker** game developed in C++ using SDL2 library with modern graphics, sound effects, and multiple difficulty levels. This project demonstrates advanced game programming concepts including physics simulation, collision detection, event handling, and state management.

![Game Status](https://img.shields.io/badge/Status-Complete-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Windows-blue)
![Language](https://img.shields.io/badge/Language-C++-orange)
![Framework](https://img.shields.io/badge/Framework-SDL2-red)

## 🎯 Features

### Core Gameplay
- **Classic Brick Breaker mechanics** with paddle and ball physics
- **Collision detection** system for ball-paddle and ball-brick interactions
- **Dynamic ball physics** with realistic bounce angles based on paddle position
- **Lives system** with game over functionality
- **Scoring system** with persistent high score tracking

### Game Modes & Difficulty
- **Multiple difficulty levels**: Easy, Medium, Hard
- **Special brick types**: Normal bricks and indestructible special bricks
- **Progressive difficulty** with varying brick layouts

### User Interface & Menus
- **Main Menu** with intuitive navigation
- **Pause Menu** for in-game control
- **High Score Display** with reset functionality
- **Help Section** with game instructions
- **Level Selection Menu**

### Audio & Visual Features
- **Background music** with different tracks for menus and gameplay
- **Sound effects** for ball collisions and game events
- **Custom graphics** for all game elements (ball, paddle, bricks, backgrounds)
- **Smooth animations** and visual feedback

### Technical Features
- **60 FPS gameplay** with precise timing control
- **File I/O** for high score persistence
- **Memory management** with proper resource cleanup
- **Event-driven architecture** for responsive controls
- **Modular code structure** with separate headers

## 🛠️ Technologies Used

### Programming Languages
- **C++** - Core game logic and application development
- **Modern C++ standards** with object-oriented programming principles

### Graphics & Multimedia Libraries
- **SDL2** - Cross-platform multimedia library for graphics rendering
- **SDL2_image** - Image loading and texture management
- **SDL2_ttf** - True Type Font rendering for text display
- **SDL2_mixer** - Audio playback for music and sound effects

### Development Tools
- **Visual Studio 2022** - Integrated Development Environment
- **MSBuild** - Build system and project management
- **Git** - Version control system

### Assets & Resources
- **Custom sprite graphics** for game elements
- **Audio files** (WAV, MP3) for immersive sound experience
- **TTF fonts** for text rendering

## 🎮 How to Play

### Controls
- **Arrow Keys** or **A/D Keys** - Move paddle left/right
- **P Key** - Pause/Resume game
- **Mouse** - Navigate menus
- **ESC Key** - Access pause menu

### Objective
- Break all the **normal bricks** (colored) to win the level
- Avoid letting the ball fall below the paddle
- **Special bricks** (doom-style) are indestructible - avoid them!
- Achieve the highest score possible

### Scoring
- Each normal brick destroyed = **5 points**
- Track your high score across gaming sessions
- Challenge yourself with different difficulty levels

## 🚀 Installation & Setup

### Prerequisites
- **Windows 10/11** operating system
- **Visual Studio 2019/2022** with C++ development tools
- **SDL2 Development Libraries** (included in project)

### Quick Start
1. **Clone the repository**:
   ```bash
   git clone https://github.com/Clear20-22/FOP_Project.git
   cd FOP_Project
   ```

2. **Open the project**:
   - Launch `block/block.sln` in Visual Studio
   - Or open the entire folder in Visual Studio Code

3. **Build and run**:
   - Set configuration to **Debug** or **Release**
   - Set platform to **x64**
   - Press **F5** to build and run

### Dependencies
All required SDL2 libraries and DLLs are included:
- `SDL2.dll` - Core SDL functionality
- `SDL2_image.dll` - Image loading support
- `SDL2_ttf.dll` - Font rendering
- `SDL2_mixer.dll` - Audio playback

## 📁 Project Structure

```
FOP_Project/
├── block/
│   ├── main.cpp              # Main game logic and entry point
│   ├── Macros.h              # Game constants and configuration
│   ├── Menu.h                # Menu system implementation
│   ├── Header.h              # Additional headers
│   ├── block.sln             # Visual Studio solution file
│   ├── block.vcxproj         # Project configuration
│   ├── highscore.txt         # Persistent high score storage
│   ├── *.dll                 # SDL2 runtime libraries
│   ├── *.ttf                 # Font files
│   └── ball_image_sound/     # Game assets
│       ├── *.png             # Sprite graphics
│       ├── *.wav, *.mp3      # Audio files
│       └── background images
├── x64/Debug/                # Compiled executable
└── README.md                 # Project documentation
```

## 🏗️ Architecture & Design

### Code Organization
- **Modular design** with separate headers for different functionalities
- **Function-based approach** with clear separation of concerns
- **Resource management** with proper initialization and cleanup
- **Constants file** for easy game balancing and configuration

### Key Components
1. **Game Loop**: Main update-render cycle with fixed timestep
2. **Physics Engine**: Custom collision detection and ball physics
3. **State Management**: Menu systems and game state transitions
4. **Asset Manager**: Texture and audio resource loading
5. **Input Handler**: Keyboard and mouse event processing

### Performance Optimizations
- **Efficient rendering** with texture reuse
- **Optimized collision detection** for game objects
- **Memory-conscious** resource management
- **Frame rate limiting** for consistent gameplay

## 🎨 Game Assets

### Visual Assets
- **Ball sprites**: Multiple ball designs
- **Paddle graphics**: Custom paddle texture
- **Brick textures**: Various brick types and colors
- **Background images**: Immersive space-themed backgrounds
- **UI elements**: Menu backgrounds and visual effects

### Audio Assets
- **Background music**: Multiple tracks for different game states
- **Sound effects**: Ball hits, brick breaking, game over sounds
- **Audio formats**: WAV for effects, MP3 for music

## 🔧 Technical Implementation

### Physics System
- **Vector-based movement** with velocity calculations
- **Collision response** with realistic bounce angles
- **Boundary detection** for screen edges and game objects
- **Mathematical calculations** for paddle-based ball direction

### Rendering Pipeline
- **SDL2 renderer** for hardware-accelerated graphics
- **Texture management** for efficient sprite rendering
- **Text rendering** with TTF font support
- **Layered rendering** for proper visual hierarchy

### Audio System
- **Multi-channel audio** with SDL2_mixer
- **Background music streaming** with loop support
- **Sound effect triggers** based on game events
- **Audio resource management** with proper cleanup

## 💻 Development Skills Demonstrated

### Programming Concepts
- **Object-Oriented Programming** in C++
- **Memory Management** and resource handling
- **File I/O Operations** for data persistence
- **Event-Driven Programming** for user interaction
- **Mathematical Programming** for physics calculations

### Game Development
- **Game Loop Architecture** with update/render cycles
- **State Management** for different game screens
- **Collision Detection** algorithms
- **Physics Simulation** for realistic ball movement
- **User Interface Design** and navigation systems

### Software Engineering
- **Modular Code Design** with header files
- **Version Control** with Git
- **Project Management** with Visual Studio
- **Documentation** and code organization
- **Cross-platform Library Integration**

## 🚧 Future Enhancements

### Potential Features
- **Power-ups**: Multi-ball, larger paddle, extra lives
- **Level progression**: Multiple levels with increasing difficulty
- **Particle effects**: Visual effects for brick destruction
- **Leaderboard system**: Online score tracking
- **Customizable controls**: Key binding options

### Technical Improvements
- **Cross-platform support**: Linux and macOS compatibility
- **Configuration files**: External game settings
- **Level editor**: Custom level creation tools
- **Performance profiling**: Optimization analysis
- **Unit testing**: Automated testing framework

## 👨‍💻 Developer Information

**Project Type**: Game Development | Academic Project  
**Development Time**: [Your timeframe here]  
**Complexity Level**: Intermediate to Advanced  
**Code Quality**: Production-ready with proper documentation

## 📄 License

This project is part of an academic portfolio and is available for educational purposes. Please respect intellectual property rights for any third-party assets used.

---

## 🌟 LinkedIn Skills Showcase

Based on this project, you can confidently list these skills on your LinkedIn profile:

### Technical Skills
- **C++ Programming**
- **Game Development**
- **SDL2 Framework**
- **Object-Oriented Programming (OOP)**
- **Memory Management**
- **Graphics Programming**
- **Audio Programming**
- **Physics Simulation**
- **Collision Detection**
- **Event-Driven Programming**

### Development Tools
- **Visual Studio**
- **Git Version Control**
- **MSBuild**
- **Debugging & Profiling**
- **Project Management**

### Software Engineering
- **Software Architecture**
- **Code Organization**
- **Documentation**
- **Resource Management**
- **Performance Optimization**
- **Cross-platform Development**

### Game Development Specific
- **Game Loop Design**
- **State Management**
- **User Interface (UI) Development**
- **Asset Management**
- **Real-time Systems**
- **Interactive Application Development**

*This project demonstrates practical application of computer science fundamentals in a real-world gaming context, showcasing both technical proficiency and creative problem-solving abilities.*
