, # Read what fibonacci number to compute
> # n-2
> # n-1
+ 
# Memory looks like this now: n 0 1
>
[-] # set memory cell #3 to 0
<[->+>+<<] # subtract 1 from #2, add 1 to #3 and #4. After the instruction the data pointer is at #2
<[->>>>+>+<<<<<]
>>>[-<<<+>>>] #4
>[-<<<<+>>>>] #5
