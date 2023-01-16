#define _CRT_SECURE_NO_WARNINGS
// Author: Noam Karasso
// Score: 100
#include <iostream>

using namespace std;

#define SIZE 10
//limitations written below in /*comments*/
template<typename T>
void QuickSort(T arr[], int size);
template<typename T>
int partition(int start, int end, T arr[]);
template<typename T>
void swap(T arr[], int index1, int index2);
template<typename T, typename K>
bool checkVal(T &arr, K val);//size parameter is required because there is no indicator for the end of the array except for '\0' in strings
template <typename T>
void printArray(T arr[], int arrSize);

int main() {
    int numArray[SIZE] = { 35,33,42,10,14,19,27,44,26,31 };
    QuickSort(numArray, SIZE);
    char** stringArr = new char* [SIZE];
    for (int i = 0; i < SIZE; i++) {
        cout << "enter a string\n";
       stringArr[i] = new char[SIZE];
        cin >> stringArr[i];
    }
    QuickSort(stringArr, SIZE);//compares the addresses(not what we wanted)
    printArray(numArray, SIZE);
    printArray(stringArr, SIZE);
    cout << "enter a number to search for\n";
    int val1;
    cin >> val1;
    cout << checkVal(numArray, val1) << endl;//compares the values
    cout << "enter a string to search for\n";
    char val[SIZE];
    cin >> val;
    cout << checkVal(stringArr, val) << endl;//compares the addresses(not what we wanted and strcmp is required for this instead)
    for (int i = 0; i < SIZE; i++)
        delete[]stringArr[i];
    delete[]stringArr;
	return 0;
}
template<typename T>
void QuickSort(T arr[], int size) {
    int* stack = new int[size];
    int top = -1;
    int right = size - 1;
    int left = 0;
    stack[++top] = left;
    stack[++top] = right;
    while (top >= 0)
    {
        right = stack[top--];
        left = stack[top--];
        int pivot = partition(left, right, arr);
        if (pivot - 1 > left)
        {
            stack[++top] = left;
            stack[++top] = pivot - 1;
        }
        if (pivot + 1 < right)
        {
            stack[++top] = pivot + 1;
            stack[++top] = right;
        }
    }
    delete[]stack;
}
template<typename T>
int partition(int start, int end, T arr[]) {
    int left = start - 1;
    int right = end;
    T pivot = arr[end];
    
    while (true) {  
        while (arr[++left] < pivot) {
            //nothing
        }
        while (right > 0 && arr[--right] > pivot) {
            //nothing
        }
        if (left >= right)
            break;
        else
            swap(arr, left, right);
    }
    swap(arr, left, end);
    return left;
}

template<typename T>
void swap(T arr[], int index1, int index2) {
    T temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}
template<typename T, typename K>
bool checkVal(T &arr, K val) {//size parameter is required because there is no indicator for the end of the array and sizeof doesn't work in some cases
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "size: " << size << endl;
    for (int i = 0; i < size; i++)
        if (val == arr[i])
            return true;
    return false;
}
template <typename T>
void printArray(T arr[], int arrSize) {
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;
}