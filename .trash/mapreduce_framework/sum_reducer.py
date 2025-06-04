#!/usr/bin/env python3
"""
Sum Reducer - Sums values for each key
Input format: key\tvalue
Output format: key\tsum
"""
import sys

def main():
    current_key = None
    current_sum = 0
    
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
            
        parts = line.split('\t')
        if len(parts) != 2:
            continue
            
        key, value = parts[0], int(parts[1])
        
        if current_key == key:
            current_sum += value
        else:
            if current_key:
                print(f"{current_key}\t{current_sum}")
            current_key = key
            current_sum = value
    
    if current_key:
        print(f"{current_key}\t{current_sum}")

if __name__ == "__main__":
    main()
