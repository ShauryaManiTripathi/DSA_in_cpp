#!/usr/bin/env python3
"""
Word Count Mapper - Reads lines from stdin, outputs word counts to stdout
Output format: word\t1
"""
import sys
import re

def main():
    for line in sys.stdin:
        # Remove punctuation and convert to lowercase
        line = line.strip().lower()
        words = re.findall(r'\b\w+\b', line)
        
        # Output each word with count 1
        for word in words:
            if word:  # Skip empty words
                print(f"{word}\t1")

if __name__ == "__main__":
    main()
