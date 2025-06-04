#!/usr/bin/env python3
"""
Line Length Mapper - Outputs line lengths
Output format: length\t1
"""
import sys

def main():
    for line in sys.stdin:
        length = len(line.strip())
        if length > 0:
            print(f"{length}\t1")

if __name__ == "__main__":
    main()
