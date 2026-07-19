# Design Patterns in C++

`⚙️ Build Debug: passing`<br>
`🚀 Build Release: passing`<br>
`📄 License: GPLv3`<br>
`📝 Language: C++`<br>
`💻 OS: Windows | Linux`

---
A comprehensive, multi-platform collection of classic **Design Patterns implemented in modern C++**. Developed with the Standard Template Library (STL), this repository serves as a practical, production-ready reference. Each pattern is cleanly decoupled into object-oriented header definitions and paired with standalone execution examples to showcase real-world behavioral, structural, creational, and concurrency strategies.
---

### 🚀 Key Features

* **Decoupled Architecture**: Patterns are cleanly separated into dedicated category directories using header-only structures or clean interfaces.
* **Cross-Platform Compatibility**: Complete native compilation support across both Windows (MSVC/Clang) and Linux (GCC/Clang) environments.
* **Modern C++ Standards**: Implemented utilizing modern C++ design principles, smart pointers, and standard memory management paradigms.
* **Robust Automation Suite**: Features a centralized scripting engine to orchestrate environment paths, compilation workflows, and workspace diagnostics.
* **Isolated Build Environment**: Keeps the root workspace pristine by forcing all CMake cache and temporary artifacts into a dedicated binary directory.

---

## 📂 Project Structure

```text
.
├── behavioral_pattern/ ............. # Behavioral Design Patterns declarations
│   ├── observer.hpp .................... # Observer pattern implementation
│   └── behavioral_pattern.png .......... # Structural architecture diagram
├── concurrecy_pattern/ ............. # Concurrency Design Patterns declarations
│   └── concurrecy_pattern.png .......... # Structural architecture diagram
├── creational_pattern/ ............. # Creational Design Patterns declarations
│   ├── abstract_factory.hpp ............ # Abstract Factory pattern implementation
│   ├── factory_method.hpp .............. # Factory Method pattern implementation
│   ├── prototype.hpp ................... # Prototype pattern implementation
│   ├── singleton.hpp ................... # Singleton pattern implementation
│   └── creational_pattern.png .......... # Structural architecture diagram
├── examples/ ....................... # Target source files and compilation entrypoints
│   ├── example_abstract_factory.cpp .... # Abstract Factory execution example
│   ├── example_factory_method.cpp ...... # Factory Method execution example
│   ├── example_observer.cpp ............ # Observer execution example
│   ├── example_prototype.cpp ........... # Prototype execution example
│   ├── example_singleton.cpp ........... # Singleton execution example
│   └── CMakeLists.txt .................. # Main CMake targets configuration file
├── scripts/ ........................ # Cross-platform automation and orchestration tools
│   ├── build.cmd / build.sh ............. # Main compilation and build scripts
│   ├── clean.cmd / clean.sh ............. # Workspace cleanup scripts
│   ├── env.cmd / env.sh ................. # Shared environment and absolute path maps
│   ├── run.cmd / run.sh ................. # Compiled executable wrappers
│   ├── run_valgrind.sh .................. # Linux memory leak profiling script
│   └── doxygen.cfg ...................... # Doxygen documentation configuration file
├── structural_pattern/ ............. # Structural Design Patterns declarations
│   ├── adapter.hpp ..................... # Adapter pattern implementation
│   └── structural_pattern.png .......... # Structural architecture diagram
├── LICENSE ......................... # Project license file (GPLv3)
└── README.md ....................... # Main project documentation file
```

---

## 🛠️ Automation Scripts

The project provides automation tools inside the `scripts/` directory to standardize your workflow.

| Feature | Windows (`.cmd`) | Linux/macOS (`.sh`) | Description |
| :--- | :--- | :--- | :--- |
| **Orchestration** | `build.cmd` | `build.sh` | Compiles targets, generates CMake artifacts, and builds pattern examples. |
| **Execution** | `run.cmd` | `run.sh` | Iterates and runs the compiled pattern binaries locally. |
| **Cleanup** | `clean.cmd` | `clean.sh` | Deep cleans the workspace, wiping build caches and generated objects. |
| **Environment** | `env.cmd` | `env.sh` | Centralizes absolute paths and local project variables shared across scripts. |
| **Profiling** | *N/A* | `run_valgrind.sh` | Launches compiled executables through **Valgrind** to track memory leaks. |

---

## ⚙️ How to Build and Run

Follow these steps to generate workspace binaries and execute the pattern targets:

1. **Build the project**  
   Run the compilation script from the root folder, passing your preferred build configuration as an argument:
   * **Windows:** `.\scripts\build.cmd debug` (or `release`)
   * **Linux/Unix:** `./scripts/build.sh debug` (or `release`)
   
   > ℹ️ *Note: The script automatically loads `env.cmd`/`env.sh` to resolve absolute paths, switches directory to `build/` to isolate the cache, and triggers CMake directly using the `examples/CMakeLists.txt` file.*

2. **Run the patterns**  
   Execute the automated run scripts to launch the built binaries:
   * **Windows:** `.\scripts\run.cmd`
   * **Linux/Unix:** `./scripts/run.sh` or `./scripts/run_valgrind.sh`
   
   > 🛡️ *Note: On Windows, any temporary linker artifacts (such as `.ilk`, `.exp`, `.lib`) are automatically pruned from the output directory right after the compilation step.*

---

### 🔨 Dynamically Generated Items (After Build/Run)

```text
├── bin/ ....................... # Created after build; contains clean compiled pattern executables
└── build/ ..................... # Created after build; contains temporary intermediate CMake objects
└── log/ ....................... # Created after running run_valgrind.sh; contains Valgrind logs
```

---

## 📄 License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.
