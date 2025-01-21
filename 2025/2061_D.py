def solve():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # Sort both arrays
    a.sort()
    b.sort()
    
    # Create frequency maps
    a_counts = {}
    for x in a:
        a_counts[x] = a_counts.get(x, 0) + 1
    
    # Process each target number in b
    for target in b:
        # If we have the target number directly
        if target in a_counts and a_counts[target] > 0:
            a_counts[target] -= 1
            continue
            
        # Try to find a combination to make this target
        found = False
        curr_nums = sorted(num for num in a_counts if a_counts[num] > 0)
        
        # Use two pointers to find pairs that can sum to target
        left = 0
        while left < len(curr_nums):
            x = curr_nums[left]
            if a_counts[x] == 0:
                left += 1
                continue
                
            # Try combinations starting with this number
            need = target - x
            possible_pairs = []
            
            # Look for numbers that could pair with x
            for y in curr_nums:
                if y >= x and a_counts[y] > (1 if y == x else 0):
                    if abs(x - y) <= 1 and x + y <= target:
                        possible_pairs.append(y)
            
            # Try each possible pair
            for y in possible_pairs:
                if x == y and a_counts[x] < 2:
                    continue
                    
                if x + y == target:
                    a_counts[x] -= 1
                    if y == x:
                        if a_counts[x] > 0:
                            a_counts[x] -= 1
                            found = True
                            break
                    else:
                        a_counts[y] -= 1
                        found = True
                        break
            
            if found:
                break
            left += 1
        
        if not found:
            print("No")
            return
    
    print("Yes")

# Read number of test cases
t = int(input())
for _ in range(t):
    solve()

