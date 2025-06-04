#!/usr/bin/env python3
"""
Word Count Reducer - Reads sorted key-value pairs from stdin, sums counts
Input format: word\t1
Output format: word\tcount
"""
import sys

def main():
    current_word = None
    current_count = 0
    
    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
            
        # Parse word and count
        parts = line.split('\t')
        if len(parts) != 2:
            continue
            
        word, count = parts[0], int(parts[1])
        
        if current_word == word:
            current_count += count
        else:
            if current_word:
                print(f"{current_word}\t{current_count}")
            current_word = word
            current_count = count
    
    # Output the last word
    if current_word:
        print(f"{current_word}\t{current_count}")

if __name__ == "__main__":
    main()
