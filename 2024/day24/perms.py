from itertools import combinations

def swap_pairs(lst, pairs):
    for a, b in pairs:
        lst[a], lst[b] = lst[b], lst[a]
    return lst

def four_pair_swaps(lst):
    n = len(lst)
    indices = list(range(n))
    
    # Generate all possible pairs of indices
    all_pairs = list(combinations(indices, 2))
    
    # Find all combinations of 4 unique pairs
    four_pair_combinations = list(combinations(all_pairs, 4))
    
    # Filter out invalid cases where indices overlap
    valid_swaps = [pairs for pairs in four_pair_combinations 
                   if len(set(i for pair in pairs for i in pair)) == 8]
    
    # Perform swaps and generate results
    permutations = []
    for swap_set in valid_swaps:
        new_lst = lst[:]
        permutations.append(swap_pairs(new_lst, swap_set))
    
    return permutations

# Example usage
lst = list(range(0, 300))
result = four_pair_swaps(lst)
for r in result:
    print(r)
