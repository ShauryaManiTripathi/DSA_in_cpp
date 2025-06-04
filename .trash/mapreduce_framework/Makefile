# Makefile for Multithreaded MapReduce Framework

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -pthread
TARGET = mapreduce_engine
SOURCES = main.cpp

# Build the main engine
$(TARGET): $(SOURCES) mapreduce.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Make mapper and reducer scripts executable
setup: $(TARGET)
	chmod +x *.py
	mkdir -p test_data output intermediate
	echo "This is a test file with some words." > test_data/file1.txt
	echo "MapReduce is a powerful programming model." > test_data/file2.txt
	echo "Multithreading enables parallel processing." > test_data/file3.txt
	echo "The quick brown fox jumps over the lazy dog." > test_data/file4.txt

# Test word count
test_wordcount: setup
	./$(TARGET) --mapper "python3 wordcount_mapper.py" --reducer "python3 wordcount_reducer.py" \
		--input test_data --output output --mappers 4 --reducers 2 --verbose --merge

# Test line length
test_linelength: setup
	./$(TARGET) --mapper "python3 linelength_mapper.py" --reducer "python3 sum_reducer.py" \
		--input test_data --output output --mappers 2 --reducers 2 --verbose --merge

# Test with threading directory files
test_threading: setup
	@if [ -d "../threading/files" ]; then \
		./$(TARGET) --mapper "python3 wordcount_mapper.py" --reducer "python3 wordcount_reducer.py" \
			--input ../threading/files --output output --mappers 8 --reducers 4 --verbose --merge; \
	else \
		echo "Threading files directory not found, using test_data"; \
		make test_wordcount; \
	fi

# Build C++ mappers and reducers
cpp_mappers: wordcount_mapper.cpp wordcount_reducer.cpp
	$(CXX) $(CXXFLAGS) -o wordcount_mapper_cpp wordcount_mapper.cpp
	$(CXX) $(CXXFLAGS) -o wordcount_reducer_cpp wordcount_reducer.cpp

# Test with C++ mappers/reducers
test_cpp: setup cpp_mappers
	./$(TARGET) --mapper "./wordcount_mapper_cpp" --reducer "./wordcount_reducer_cpp" \
		--input test_data --output output --mappers 4 --reducers 2 --verbose --merge

# Performance comparison between Python and C++
perf_compare: setup cpp_mappers
	@echo "=== Performance Comparison: Python vs C++ ==="
	@echo "Testing with Python mappers/reducers..."
	@time ./$(TARGET) --mapper "python3 wordcount_mapper.py" --reducer "python3 wordcount_reducer.py" \
		--input test_data --output output_py --mappers 4 --reducers 2 --verbose
	@echo ""
	@echo "Testing with C++ mappers/reducers..."
	@time ./$(TARGET) --mapper "./wordcount_mapper_cpp" --reducer "./wordcount_reducer_cpp" \
		--input test_data --output output_cpp --mappers 4 --reducers 2 --verbose

# Interactive demo
demo: setup cpp_mappers
	@echo "=== MAPREDUCE FRAMEWORK DEMO ==="
	@echo "1. Testing Python mappers/reducers..."
	make test_wordcount
	@echo ""
	@echo "2. Testing C++ mappers/reducers..."
	make test_cpp
	@echo ""
	@echo "3. Testing line length analysis..."
	make test_linelength
	@echo ""
	@echo "=== ALL DEMOS COMPLETED ==="

# Performance test
perf_test: setup
	@echo "Generating large test data..."
	@mkdir -p perf_data
	@for i in {1..10}; do \
		head -c 100000 /dev/urandom | tr -dc 'a-zA-Z0-9 \n' > perf_data/large_file_$$i.txt; \
	done
	@echo "Running performance test..."
	time ./$(TARGET) --mapper "python3 wordcount_mapper.py" --reducer "python3 wordcount_reducer.py" \
		--input perf_data --output output --mappers 8 --reducers 4 --verbose --merge

# Clean up
clean:
	rm -f $(TARGET) wordcount_mapper_cpp wordcount_reducer_cpp
	rm -rf output intermediate perf_data output_py output_cpp
	rm -f *.txt

# Show results
show_results:
	@echo "=== OUTPUT FILES ==="
	@ls -la output/ 2>/dev/null || echo "No output directory found"
	@echo ""
	@echo "=== FINAL OUTPUT (first 20 lines) ==="
	@head -20 output/final_output.txt 2>/dev/null || echo "No final output found"

.PHONY: setup test_wordcount test_linelength test_threading perf_test clean show_results cpp_mappers test_cpp perf_compare demo cpp_mappers test_cpp perf_compare demo
