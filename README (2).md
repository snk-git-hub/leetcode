# Take / Not Take Pattern - Recursion Tree

Let me draw the recursion tree for the **Take/Not Take** pattern using a simple example.

## Example: Subsets of [1, 2, 3]

```
                                    f(0, [])
                                       |
                    +-----------------+------------------+
                    |                                    |
                 TAKE 1                              NOT TAKE 1
                    |                                    |
                 f(1, [1])                            f(1, [])
                    |                                    |
          +---------+---------+                +---------+---------+
          |                   |                |                   |
       TAKE 2            NOT TAKE 2         TAKE 2            NOT TAKE 2
          |                   |                |                   |
      f(2, [1,2])         f(2, [1])        f(2, [2])           f(2, [])
          |                   |                |                   |
     +----+----+         +----+----+      +----+----+         +----+----+
     |         |         |         |      |         |         |         |
   TAKE 3  NOT TAKE 3  TAKE 3  NOT TAKE 3  TAKE 3  NOT TAKE 3  TAKE 3  NOT TAKE 3
     |         |         |         |      |         |         |         |
f(3,[1,2,3]) f(3,[1,2]) f(3,[1,3]) f(3,[1]) f(3,[2,3]) f(3,[2]) f(3,[3]) f(3,[])
     |         |         |         |      |         |         |         |
   LEAF     LEAF      LEAF      LEAF    LEAF      LEAF      LEAF      LEAF
  [1,2,3]   [1,2]     [1,3]     [1]    [2,3]     [2]       [3]       []
```

## Visual Representation with Arrows

```
                                 idx=0, current=[]
                                        |
                        +---------------+---------------+
                        |                               |
                     Take 1                         Not Take 1
                        ↓                               ↓
                 idx=1, [1]                      idx=1, []
                        |                               |
              +---------+---------+           +---------+---------+
              |                   |           |                   |
           Take 2            Not Take 2    Take 2            Not Take 2
              ↓                   ↓           ↓                   ↓
         idx=2, [1,2]        idx=2, [1]   idx=2, [2]        idx=2, []
              |                   |           |                   |
         +----+----+         +----+----+  +----+----+        +----+----+
         |         |         |         |  |         |        |         |
      Take 3   Not Take   Take 3   Not   Take 3  Not      Take 3   Not
         ↓         ↓         ↓      Take    ↓     Take       ↓      Take
    idx=3      idx=3     idx=3       ↓   idx=3     ↓      idx=3      ↓
    [1,2,3]    [1,2]     [1,3]    idx=3  [2,3]  idx=3     [3]     idx=3
                                   [1]            [2]               []
                                   
    BASE CASES (idx == 3) - Add to result
```

## Detailed Step-by-Step Tree

```
Level 0:  Start with index 0, array [1,2,3], current subset []

Level 1:  Two choices for element at index 0 (which is 1)
          ├─ Take 1:  current = [1],     move to index 1
          └─ Skip 1:  current = [],      move to index 1

Level 2:  Four nodes, each has two choices for element at index 1 (which is 2)
          ├─ [1] → Take 2:  [1,2],   move to index 2
          ├─ [1] → Skip 2:  [1],     move to index 2
          ├─ [] → Take 2:   [2],     move to index 2
          └─ [] → Skip 2:   [],      move to index 2

Level 3:  Eight nodes, each has two choices for element at index 2 (which is 3)
          ├─ [1,2] → Take 3:  [1,2,3],  move to index 3 ✓
          ├─ [1,2] → Skip 3:  [1,2],    move to index 3 ✓
          ├─ [1] → Take 3:    [1,3],    move to index 3 ✓
          ├─ [1] → Skip 3:    [1],      move to index 3 ✓
          ├─ [2] → Take 3:    [2,3],    move to index 3 ✓
          ├─ [2] → Skip 3:    [2],      move to index 3 ✓
          ├─ [] → Take 3:     [3],      move to index 3 ✓
          └─ [] → Skip 3:     [],       move to index 3 ✓

Level 4:  All base cases reached (index == array.size())
          Results: [1,2,3], [1,2], [1,3], [1], [2,3], [2], [3], []
```

## Code with Comments

```cpp
class Solution {
public:
    void solve(vector<int>& nums, int idx, vector<int>& current, 
               vector<vector<int>>& result) {
        
        // BASE CASE: Reached end of array
        if (idx == nums.size()) {
            result.push_back(current);  // Add current subset to result
            return;
        }
        
        // RECURSIVE CASE 1: TAKE current element
        current.push_back(nums[idx]);       // Include nums[idx]
        solve(nums, idx + 1, current, result);  // Recurse for next index
        current.pop_back();                 // BACKTRACK: Remove nums[idx]
        
        // RECURSIVE CASE 2: NOT TAKE current element
        solve(nums, idx + 1, current, result);  // Recurse without nums[idx]
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        solve(nums, 0, current, result);
        return result;
    }
};
```

## ASCII Tree Diagram

```
                        f(0,[])
                       /      \
                    T /        \ NT
                     /          \
                 f(1,[1])      f(1,[])
                 /     \        /    \
              T /       \ NT T /      \ NT
               /         \   /        \
          f(2,[1,2])  f(2,[1]) f(2,[2]) f(2,[])
           /    \      /   \    /   \    /   \
         T/     \NT  T/    \NT T/   \NT T/   \NT
         /       \   /      \  /     \  /     \
    f(3,[1,2,3]) | f(3,[1,3]) | f(3,[2,3]) | f(3,[3])
        |      f(3,[1,2])  |  f(3,[2])  |  f(3,[])
      RESULT     |     f(3,[1])  |   RESULT  RESULT
               RESULT   RESULT RESULT

Final Results (8 subsets):
[1,2,3], [1,2], [1,3], [1], [2,3], [2], [3], []
```

## Key Observations

1. **Tree Height**: `n + 1` levels (where n = array size)
2. **Total Nodes**: `2^(n+1) - 1` nodes
3. **Leaf Nodes**: `2^n` leaf nodes (all possible subsets)
4. **Branching Factor**: 2 (Take or Not Take)
5. **Time Complexity**: O(2^n × n) - 2^n subsets, n to copy each
6. **Space Complexity**: O(n) - recursion depth

## Example Trace for [1, 2]

```
Call Stack Visualization:

solve(0, [])
├─ Take 1: solve(1, [1])
│  ├─ Take 2: solve(2, [1,2])  → Result: [1,2] ✓
│  │  return
│  └─ Not Take 2: solve(2, [1])  → Result: [1] ✓
│     return
└─ Not Take 1: solve(1, [])
   ├─ Take 2: solve(2, [2])  → Result: [2] ✓
   │  return
   └─ Not Take 2: solve(2, [])  → Result: [] ✓
      return

Final Result: [[1,2], [1], [2], []]
```

This pattern generates all `2^n` possible subsets by making a binary decision (take/not take) at each element!