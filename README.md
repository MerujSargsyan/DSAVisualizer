# Data Structs & Algorithms Visualizer (DSAV)

## Clone guide:
compile: ./compile.sh<br>
run: build/main

#### Method: keeps track of a list of blocks which represent array items with an offset from their original positions. When the blocks are swapped, the list of blcoks is updated to match the array. When swapping array elements a, b, we add a process which swaps a and b to the animation queue which is then swapped orderly.


## Tools: Currently using raylib for visuals & C for the code
Note: may switch to a simpler graphics library since raylib is unnecessary for this project

### Current issues / TODO:
<ul>
    <li> struggling to find correct indicies to swap for merge-sort</li>
    <li> getting a seg fault with current indicies</li>
</ul>
<ul>
    <li> TODO: impelement recursive algorithms </li>
</ul>
