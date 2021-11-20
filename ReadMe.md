**CENG311 Fall 2021**

# PROGRAMMING ASSIGNMENT 

In this assignment, you are required to implement priority queue construction in C and compare the
performance of your implementation with Java-based implementation.

In your C implementation, you are required to use max binary heap, where the value of parent node
will always be greater than the value of child node, and the value at the root must be maximum
among all the values. Specifically, you need to use array representation of binary heap in your
implementation with the following properties:

The root element will be at Arr[0]
**Arr[(i-1)/2] Returns the parent node**
**Arr[(2*i)+1] Returns the left child node**
**Arr[(2*i)+2] Returns the right child node**

You only need to implement the _queue_ function, which inserts a new element into the queue (no
need for dequeue etc. operations).

You are free to choose the way in your Java code, but it is recommended to use PriorityQueue class.

You can assume that your queue can include up to 2^28 elements. To be able to store that big array,
you may need to create your array by malloc function instead of an array type (If you have
limitations due to your computer settings, you can reduce the array size).

Additionally, in your C code, you will implement a _convert_ function, which converts the array
representation into a data structure represented by pointers and links between the elements. Each
element is to be represented by the following structure:
struct node
{
int data;
struct node* left;
struct node* right;
};

Your program flow should be as follows:

**1)** Read a set of unordered integer values (separated by space) from a text file into an array.

**Example:** A= [45 20 14 12 31 7 11 13]

**2)** Build the priority queue in an array by processing the integer values one by one. Add each
integer by considering that the value is representing the priority. Note that at the end of each
insertion, you should have a priority queue. That is you should not have all values in some structure
(like a binary tree) first, then convert into priority queue.

**Example:**

B= [45]
B= [45 20]
B= [45 20 14]


B= [45 20 14 12]

B= [45 31 14 12 20]

...

B= [45 31 14 13 20 7 11 12]

**3)** Convert your array representation into a data structure with pointers.

**Example:**

Node1: data = 45, left = Node2, right = Node
Node2: data = 31, left = Node4, right = ...
Node3: data = 14 ...
Node4: data = 13 ...
.....

**4)** Traverse the structure, save your array in a text file.

**Example file content:**

45 31 14 13 20 7 11 12

Your program should measure and report the execution time for building the array structure. The
measured time should not include the I/O operations. Time measurement should be done in the
following order:

read the input file into an array // file read operation
start time
build queue (array representation) // the operation we want to measure
stop time
convert your queue array into structure with pointers
print resulting structure by breadth first traversal to the output file // file write operation

You are required to write a report and include both functionality and performance results: 1) A
simple example including ~20 integers showing that your program is building the queue correctly.
2) A test case with ~2^28 integers and timing information for that case.

#REPORT

# Implementation details:

**In C (280201105.c):**

Array pointers are created by malloc function. And the numbers from file are read with
_fscanf_ until it turns EOF. Getting this operation into a while loop helped getting the real size
of the array. So that the operations after reading are being able to work with the real size
and not execute unnecessarily more operations or work with the numbers at the unused
allocated locations.

Then I took this array pointer into **_build_queue_** function. This function creates the arrayHeap
pointer with the counted size and starts giving the values from array to arrayHeap one by
one. And this operation uses **_queue_** function. queue function inserts one value into the heap
by considering that the value is representing the priority. So, it firstly adds the value at the
end of the array and then executes **_heapify_** function to ensure the right place of this
element. With that, at the end of every insertion, you have a priority queue.

When it comes to converting the array representation into a data structure with pointers, I
have created a parent pointer and passed its address into **_convert_** function with the
arrayHeap. In this function I took help from the web and I added the reference at the end.
What it basically does is, takes the parent node pointer as again pointer. And it uses it as
pointer to pointer node, so it is storing the memory address of other pointer. So that it can
change the pointer and the nodes recursively. Since Arr[(2*i) +1] returns the left child node
and Arr[(2*i)+2] returns the right child node, while using recursive convert function we are
giving the matching indexes with the new parent (left or right) node.

When the structure is ready, it starts traversing it by breadth first traversal and prints the
results to the output file **(result.txt)** To make it happen, I’m giving the first parent node
pointer that have been created into **_traverse_** function. This function firstly calculates the
height of the tree and executes **_saveLevel_** function in every level. saveLevel function
recursively searches every node in that level and prints every node it searched into the file.

_(reference for convert function: https://stackoverflow.com/questions/28893017/converting-
an-array-into-binary-tree-using-c )_

# In Java (PerformanceTest.java):

**_PriorityQueue_** class is used in Java implementation.

Since Java gives _java.lang.OutofMemoryError_ while using both 2^28 and 2^27, I created the
array with size 2^26.

And to be able to compare the performance fair, after creating queue with the class
PriorityQueue, I also used **_queue.toArray()_** function to include the time passed for giving an
array, too.


# Functionality Results:

An example including 20 integers:

Input : **_“numbers.txt”_** = 45 31 14 13 20 7 11 12 9 34 17 18 3 9 80 25 19 21 71 66

Output in C : **_“result.txt”_** = 80 71 45 34 66 14 18 19 25 31 17 7 3 9 11 12 13 9 21 20

Output in Java: 80 71 45 34 66 14 18 19 25 31 17 7 3 9 11 12 13 9 21 20

_Program is building the queue correctly._

# Performance Results:

Test case is 2^26 integers. (Using timing_test_numbers.txt)

```
(in C): 2.933000 seconds to execute.
(in Java): 9.998237 seconds to execute.
```
_C executes 3,4 times faster than Java._

