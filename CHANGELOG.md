# Change log

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

## [0.0.1] - 02.10.2020

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