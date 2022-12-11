//Computing Structures
//Fall 2022
//Project 6
//Author: Aditya Narasimhan

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for(int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
	int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last
	
    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i) 
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                            // the if condition where the comparison happens each time
                if(numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;


        while ((j >= 0) && (arr[j] > temp))
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if(numComp >= D) // checking for number of comparisons
                return arr; // return the not necessarily sorted array = approximately sorted array
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
	return arr;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int inversions(int sortingArr[], int numElements)   // making methods since theyre called twice in main
{
    // inversion uses bubble sort result and (For each element (A[i]) in the array, you count the number 
    // of elements less than A[i] to the right of the element (i to n-1 indices).)

    // https://www.geeksforgeeks.org/inversion-count-in-array-using-merge-sort/
    // trying something like this link

    int inversions = 0;
    for(int i = 0; i < numElements; i++)    // keeps the index the same while other loops through
    {
        for(int j = i + 1; j < numElements; j++)    // loops through the array
        {
            if(sortingArr[i] > sortingArr[j])   // checks if the element at i is greater than the elements being looped
            {
                inversions++;   // if so, increment inversions
            }
        }
    }
    return inversions;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int cheby(int sortingArr[], int sortedArr[], int numElements)
{
    // for chebyshevs distance
    // you take the difference in the positions of the elements in the sorted array and the bubble sort result array
    // it will be the sum of the absolute value of the differences

    int chebyshevs = 0;

    // Adi 11/30/22
    // displacement for every number and find max
    // nested for loop 
    // if i and j are the same, find the abs displacement
    // if greater than the existing displacement, update max difference

    for(int i = 0; i < numElements; i++)    // loop for the initial element
    {
        for(int j = 0; j < numElements; j++)    // loop for the element being compared to
        {
            if(sortingArr[i] == sortedArr[j])   // if the elements are the same
            {
                int displacement = abs(i - j);  // find the displacement
                if(displacement > chebyshevs)   // if the displacement is greater than the current max
                {
                    chebyshevs = displacement;  // update the max
                }
            }
        }
    }

    return chebyshevs;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//main function
int main()
{   
    // 10
    // 11011 1000 1500
    // 10

	int n;
	cin >> n; // read the number of elements
	cout << "Number of elements: " << n << endl;
    // experiment less than 30,000
    // more runs but less than 30,000 -> 5,000 10,000 15,000 20,000 etc. 
    // at least 5 experiments 

	int s, l, u, D;
	
	cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

	// generate n random elements with the seed s, within the lower and upper range 
    // store the randomly generated UNIQUE set of elements in an array 'A'

    // using the unordered_set data structure to generate unique elements
    unordered_set<int> uniqueSet;   // unique set with unordered elements
    srand(s); // making the seed with the given seed value

    int range = u - l + 1;  // Adi

    while(uniqueSet.size() < n) // making the random numbers
    {
        // going off
        // https://stackoverflow.com/questions/19238403/random-function-generator-between-two-integers-c

        //int randomNum = (rand() % range) + l; // generating a random number *** might need to add + l to end of this
        uniqueSet.insert(rand() % range + l); // inserting the random number into the unordered_set
    }

    // copying the unordered_set into an array
    int* A = new int[n];
    int i = 0;
    // https://www.scaler.com/topics/cpp/auto-in-cpp/
    // Im going to start using auto from now on 
    for(auto it = uniqueSet.begin(); it != uniqueSet.end(); it++)   // looping though and adding the elements to the array
    {
        A[i] = *it;
        i++;    // incrementing the index
    }

    // you may use the unordered set to help generate unique elements
	cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
	// display the array A  
    for(int i = 0; i < n; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 

	cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
	// display the completely sorted array 
    int* sortedArr = bubbleSort(A, n, n*n); // manipulating the number of comparisons should allow for everything to be sorted
    for(int i = 0; i < n; i++)  // printing the sorted array
    {
        cout << sortedArr[i] << " ";
    }

    cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << endl << "Bubble Sort Result: ~~~~~~~~~~" << endl;

    // what is the best input for bubble sort -> when numbers are already sorted
    // worst -> when numbers are in reverse order

    // display bubResult
    int* bubResult = bubbleSort(A, n, D);
    for(int i = 0; i < n; i++)  // displaying the bubble sort
    {
        cout << bubResult[i] << " ";
    }
    cout << endl;

    // find both the quality metrics for bubResult
    
    cout << endl << "Number of inversions in bubResult: " << inversions(bubResult, n) << endl; 
    cout << "Chebyshev distance in bubResult: " << cheby(bubResult, sortedArr, n) << endl;
    cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;

    // display shellResult
    int* shellResult = shellSort(A, n, D);
    for(int i = 0; i < n; i++)  // displaying the shell sort
    {
        cout << shellResult[i] << " ";
    }
    cout << endl;

    // find both the quality metrics for shellResult
    // should just be the same thing as before except with shell sort

    cout << endl << "Number of inversions in shellResult: " << inversions(shellResult, n) << endl;
    cout << "Chebyshev distance in shellResult: " << cheby(shellResult, sortedArr, n) << endl;
    cout << endl;

    return 0;

}