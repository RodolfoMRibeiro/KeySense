CXX := g++
CXXFLAGS := -Wall -Iinclude

SRCS := src/windows_logger/hook_manager.cpp src/windows_logger/key_input.cpp src/windows_logger/keylogger.cpp src/windows_logger/os_manager.cpp src/windows_logger/windows_info.cpp src/main.cpp
OUT := my_program.exe

build: $(OUT)
$(OUT): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(OUT)

clean:
	rm -f $(OUT)
