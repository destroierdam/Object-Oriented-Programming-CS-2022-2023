# Демонстрационен акаунт и репо
https://github.com/destroierdam-demo/

# Git, GitHub
GUI: 

Sourcetree: https://www.sourcetreeapp.com/

# Unit Testing
https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2022

# Статичен анализ на кода
## Настройка на Visual Studio
От инсталатора: Desktop Development with C++
От Visual Studio:
### clang-tidy, clang-format
Extensions -> Manage Extensions -> Online -> Visual Studio Marketplace

Install Clang Powertools 2022

### cppcheck
https://github.com/VioletGiraffe/cppcheck-vs-addin/releases -> CppcheckPlugin.vsix

https://cppcheck.sourceforge.io/

## Нов проект
main.cpp и .clang-tidy файлове

.clang-tidy съдържание
```
---
Checks: "*,
        -abseil-*,
        -altera-*,
        -android-*,
        -fuchsia-*,
        -zircon-*,
        -llvm*,
        -modernize-use-trailing-return-type,
        -modernize-use-default-member-init,
        -readability-static-accessed-through-instance,
        -readability-avoid-const-params-in-decls
"
```

### Clang Powertools настройки
Clang Powertools менюто -> Settings -> Tidy -> Use checks from Tidyfile

### cppcheck settings
Tools -> cppcheck settings 

cppcheck: start analysis when file is saved -> yes

enable inconclusive checks

```
--enable=all
```
### Visual Studio
project -> properties
Configuration Properties -> C/C++ -> General -> warning level 4
                                  -> Language -> Conformance mode: (/permissive-)

___

C++ Weekly with Jason Turner:
https://leanpub.com/u/jason_turner

https://www.youtube.com/watch?v=q7Gv4J3FyYE

https://github.com/lefticus/cpp_weekly/issues/175

#### optional

Clang for Windows

https://github.com/llvm/llvm-project/releases/tag/llvmorg-16.0.0
