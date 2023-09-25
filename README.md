# data-structures-assignment
##k224072 Muhammad Ali Wasim**

following is the report comparing the average sorting times for bubble sort, insertion sort, and selection sort in both arrays and linked lists at each input size. lastly, we will provide reasons for the efficiency of one implementation over the other.

##BUBBLE SORT:

For small input sizes (100 and 1,000), bubble sort performs reasonably well in both arrays and linked lists, for 100 elements linked lists seem quite faster than arrays but as the size increases to a 1000 linked list take slightly more time tahn arrays.
as the input size increases to 10,000 and 100,000, bubble sort exhibits a significant increase in sorting time, especially in linked lists. This is due to its time complexity of O(n^2), making it inefficient for larger datasets.
Bubble sort's performance degrades rapidly with larger input sizes in both data structures, speaking solely on linked list the time taken substantially increases and clearly proves it inefficient against arrays.

##INSERTION SORT:

Insertion sort also performs reasonably well for small input sizes in both arrays and linked lists.
Similar to bubble sort, insertion sort shows a noticeable increase in sorting time as the input size grows, especially in linked lists It has an average-case time complexity of O(n^2).

##SELECTION SORT:

Selection sort remains a viable option for small to medium-sized datasets but becomes less efficient for very large datasets.
Selection sort demonstrates  slightly better performance than bubble and insertion sort for larger input sizes in linked lists.
Its average-case time complexity is also O(n^2), but it performs better due to fewer comparisons and swaps.

##EFFICIENCY CONCLUSION:

Arrays generally perform better than linked lists for sorting operations, especially when dealing with algorithms that involve frequent element comparisons and swaps.
The contiguous memory storage of arrays and efficient random access make them a preferred choice for sorting large datasets.
In summary, the time trends for linked lists vs. arrays when sorting algorithms are applied show that linked lists tend to exhibit more pronounced increases in sorting time as the input size grows
While arrays offer more efficient access to elements and thus tend to have a more gradual increase in sorting time. 
For sorting tasks, especially with large datasets, arrays are typically the more efficient choice due to their memory layout and access characteristics.
