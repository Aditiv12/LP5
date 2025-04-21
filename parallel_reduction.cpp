#include <iostream>
#include <omp.h>
#include <vector>
#include <climits>

using namespace std;

void min(vector<int> &arr)
{
    int min_val = INT_MAX;
#pragma omp parallel for reduction(min : min_val)
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    cout << "\n min_val= " << min_val << endl;
}

void max(vector<int> &arr)
{
    int max_val = INT_MIN;
#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }
    cout << "\n max_val= " << max_val << endl;
}

void sum(vector<int> &arr)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    cout << "\n sum= " << sum << endl;
}

void avg(vector<int> &arr)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    cout << "\n avg= " << (double)sum / arr.size() << endl;
}

int main()
{
    vector<int> arr;
    arr.push_back(5);
    arr.push_back(9);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(7);

    min(arr);
    max(arr);
    sum(arr);
    avg(arr);
}
