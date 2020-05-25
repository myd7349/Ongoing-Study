cmake_minimum_required(VERSION 3.8)

project(MemoryMappedFileDemo CXX)

add_executable(Reader
    "Reader.cpp"
	"../File.cpp"
	"../MemoryMappedFile.cpp"
	)

add_executable(Writer
    "Writer.cpp"
	"../File.cpp"
	"../MemoryMappedFile.cpp"
	)
