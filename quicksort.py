'''
Programming assignment 2:
count the number of comparisons
in the QuickSort algorithm
using 3 different strategies of
picking the pivot element:
  1) First element
  2) Final element
  3) "Median-of-three" pivot rule
     for first, middle, and final elements
@author: Mikhail Dubov
'''

PIVOT_FIRST = 1
PIVOT_FINAL = 2
PIVOT_MEDIAN = 3

comparisons = 0


def swap(ar, i, j):
    t = ar[i]
    ar[i] = ar[j]
    ar[j] = t
    
    
def is_median(ar, i, j, k):
    '''
    Determines whether ar[i] is a median
    of ar[i], ar[j] and ar[k].
    '''
    return (ar[i] < ar[j] and ar[i] > ar[k]) or\
           (ar[i] > ar[j] and ar[i] < ar[k])


def _quickSort(ar, l, r, pivot):
    
    global comparisons
    
    # Base case
    if l >= r:
        return
    
    # Picking the pivot element
    p = 0
    if pivot == PIVOT_FIRST:
        p = ar[l]
    elif pivot == PIVOT_FINAL:
        p = ar[r]
        swap(ar, l, r)
    elif pivot == PIVOT_MEDIAN:
        m = l + ((r-l) >> 1)
        if is_median(ar, l, m, r):
            p = ar[l]
        elif is_median(ar, m, l, r):
            p = ar[m]
            swap(ar, l, m)
        else:
            p = ar[r]
            swap(ar, l, r)
            
    # Updating the comparisons counter
    comparisons += (r-l)
    
    # Partition (see lectures)
    i = l+1
    for j in range(l+1, r+1):
        if ar[j] < p:
            swap(ar, i, j)
            i += 1
    swap(ar, l, i-1)
    
    # Recursive calls
    _quickSort(ar, l, i-2, pivot)
    _quickSort(ar, i, r, pivot)
    


def quickSort(ar, pivot):
    '''
    Sorts the array in place using
    the given pivot picking strategy
    (PIVOT_FIRST/PIVOT_FINAL/PIVOT_MEDIAN).
    
    Expected running time is O(n*log(n)).
    '''
    _quickSort(ar, 0, len(ar)-1, pivot)



def main():
    
    global comparisons
    
    #test
    input_array = [1,3,5,2,4,6]
    quickSort(input_array, PIVOT_FIRST)
    print(input_array)
    
    # Assignment data
    f = open('QuickSort.txt', 'r')
    lst = []
    
    # (!) Better approach to reading lines than in PA1
    for line in f.readlines():
        lst.append(int(line))
        
    
    # Task 1
    input_array = lst[:] # make a copy
    comparisons = 0
    quickSort(input_array, PIVOT_FIRST)
    print(comparisons)
    
    # Task 2
    input_array = lst[:] # make a copy
    comparisons = 0
    quickSort(input_array, PIVOT_FINAL)
    print(comparisons)
    
    # Task 3
    input_array = lst[:] # make a copy
    comparisons = 0
    quickSort(input_array, PIVOT_MEDIAN)
    print(comparisons)
    
    
if __name__ == '__main__':
    main()
