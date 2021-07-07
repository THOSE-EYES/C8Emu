# Changelog

## Example
```
## [x.y.z] - dd.mm.yyyy

### Added/Removed
* <your_profile> : <some_data>

### Changed
* <your_profile> : <some_data>

### Fixed
* <your_profile> : <some_data>
```
## [Build 6] - 07.06.2021

### Changed
* @THOSE-EYES : Recreated app's file structure from the ground up
* @THOSE-EYES : Moved every class to a corresponding namespace
* @THOSE-EYES : Moved opcode functionality out of the only method and splitted it into a lot of standalone methods
* @THOSE-EYES : Unit tests are rewritten completely

### Added/Removed
* @THOSE-EYES : Deleted unnecessary classes (Memory, Stack) and changed them to C++ STL classes
* @THOSE-EYES : Created unique exceptions for every class
* @THOSE-EYES : Created mock and fake classes for unit testing
* @THOSE-EYES : Added several new sanity checks

### Fixed
* @THOSE-EYES : Fixed loops in the methods for handling 0xFX55 and 0xFX65 opcodes
* @THOSE-EYES : Fixed several sources of app crashes (incorrect operations of getting register's index out of the opcode)

## [Build 5] - 23.02.2021

### Changed
* @THOSE-EYES : Replaced pointers and arrays in the CPU class with unique_ptr and std::deque respectively(C++11 style)

## [Build 4] - 23.02.2021

### Added
* @THOSE-EYES : Added a superclass for windows
* @THOSE-EYES : Added constants for the new window class

### Fixed
* @THOSE-EYES : Fixed errors in the RAM class

## [Build 3] - 17.02.2021

### Changed
* @THOSE-EYES : Replaced old exception system with STD exceptions
* @THOSE-EYES : Replaced the pointer in Stack and Application classes with unique_ptr (C++11 style)

### Fixed
* @THOSE-EYES : Fixed Application class

## [Build 2] - 16.02.2021

### Changed
* @THOSE-EYES : Updated the description
* @THOSE-EYES : Updated the project structure

## [Build 1] - 02.10.2020

### Added/Removed
* @THOSE-EYES : Added comments on algorithms in every source file inside the project
* @THOSE-EYES : CHANGELOG.md and .gitignore were created
* @THOSE-EYES : io.(cpp/h), sound.(cpp/h) and ui.(cpp/h) were removed (no UI or sound will be present in future builds)
* @THOSE-EYES : Added application.(cpp/h)

### Changed
* @THOSE-EYES : Updated README
* @THOSE-EYES : Code from memory.h and memory.cpp was splitted into two parts (ram.(cpp/h) and stack.(cpp/h))
* @THOSE-EYES : Code from main.cpp and io.(cpp/h) was moved to application.(cpp/h)
* @THOSE-EYES : Important defines were moved to global.h
* @THOSE-EYES : Changed internals of classes : CPU, RAM, STACK (some fileds/methods were moved or deleted that caused a lot of changes in other algorithms)

### Fixed
* @THOSE-EYES : Algorithm of the stack now works as it should (the problem caused exceptions when trying to return from subroutines)
* @THOSE-EYES : Fixed codestyle