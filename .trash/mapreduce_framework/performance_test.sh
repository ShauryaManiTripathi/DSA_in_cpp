#!/bin/bash

# Performance test script for MapReduce framework

echo "=== MAPREDUCE FRAMEWORK PERFORMANCE TEST ==="
echo "Comparing single-threaded vs multi-threaded performance"

# Create larger test data
echo "Creating performance test data..."
mkdir -p perf_test_data
for i in {1..10}; do
    cat test_data/*.txt > "perf_test_data/large_file_$i.txt"
done

echo -e "\n=== TEST 1: Single Thread (1 mapper, 1 reducer) ==="
time (echo "1" | timeout 10s ./bin/examples | head -20)

echo -e "\n=== TEST 2: Multi-Thread (4 mappers, 2 reducers) ==="  
time (echo "1" | timeout 10s ./bin/examples | head -20)

echo -e "\n=== TEST 3: Character Frequency - Single Thread ==="
time (echo "4" | timeout 10s ./bin/examples | head -10)

echo -e "\n=== TEST 4: Character Frequency - Multi Thread ==="
time (echo "4" | timeout 10s ./bin/examples | head -10)

echo -e "\n=== Performance test completed ==="
