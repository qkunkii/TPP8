# Supermarket ORM Application
---
1. **Склонуйте репозиторій:**
   ```cmd
   git clone <посилання_на_ваш_репозиторій>
   cd <назва_папки_проєкту>
   ```

2. **Сконфігуруйте проєкт через CMake:**
   *(Замініть `C:\vcpkg` на реальний шлях до вашого пакетного менеджера)*
   ```cmd
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
   ```

3. **Зберіть проєкт:**
   ```cmd
   cmake --build build --config Debug
   ```

4. **Запустіть застосунок:**
   ```cmd
   .\build\Debug\SupermarketORM.exe
   ```

---
