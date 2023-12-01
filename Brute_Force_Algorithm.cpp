#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// This is a global definer or a global variable that sets the value of the variable V to 4 
#define V 6

// Initialization of a void function using function prototype
void BruteForceAlgorithm(int graph[][V], int s);

int main() {
    /*
    V * V graph
        1   2   3   4   5   6
    1   0   10  15  20  15  60
    2   10  0   35  25  15  45
    3   15  35  0   30  40  30
    4   20  25  30  0   35  35
    5   15  25  50  60  0   50
    6   20  25  30  30  25  0
    */

   /*
   This graph array variable represents a travelling salesman problem
   The array within the graph { 0, 10, 15, 20 } is the first city and the cost to go to city 2, 3, and 4.
   The array within the graph { 10, 0, 35, 25 } is the second city and the cost to go to city 1, 3, and 4.
   And so on.
   The 0 in each of the array is the current city.
   */ 
   
    int graph[][V] = { 
                       { 0,  10, 15, 20, 15, 60 },
                       { 10, 0,  35, 25, 15, 45 },
                       { 15, 35, 0,  30, 40, 30 },
                       { 20, 25, 30, 0,  35, 35 },
                       { 15, 25, 50, 60, 0,  50 },
                       { 20, 25, 30, 30, 25, 0  }
                     };  

    // This int variable of starting_point represents which city we start at.
    int starting_point = 1;

    // We then call the Brute Force Algorithm function with the two variables, graph and starting_point.
    // We reduced the value of starting_point by 1 because the an index starts with 0 not 1.
    BruteForceAlgorithm(graph, starting_point - 1);
}

// This is the Brute Force Algorithm function
void BruteForceAlgorithm(int graph[][V], int s) {
    /*
    Below here is the initialization of variables.
    lowest_cost has a 'temporary' value of 10000, because it will be used in the loop later on.
    There are 3 vectors of an int, two of which are going to be used for representation fo the lowest cost froms and tos.
    The vertex vector is going to be used for the loop later on, it is somewhat a necessary for this problem.
    */
    int lowest_cost = 10000;
    vector<int> travel_Cost;
    vector<int> from_to_City;
    vector<int> all_Cost;
    vector<int> vertex;

    // This for loop will be adding values in the vector, the values it'll be putting are from 0 to V (the globally defined variable)
    // except the s (starting_point)
    for (int i = 0; i < V; i++)
    {
        if (i != s)
        {
            vertex.push_back(i);
        }
    }

    /*
    This is where the magic of the algorithm begins...
    What is 'next_permutation' you might ask, it just arranges the vertex in different ways, this is how we check all of the possibilities.
    Example:
    The vertex has values of { 0, 1, 2 }, it will check all the possibilities of rearranging those values like:
    { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0}, { 2, 0, 1 }, { 2, 1, 0 }
    The original value will also be included in the possibilites, the amount of possibilites can be calculated with -> n!,
    where n is the count of the values or the size of the vertex.

    After that, we have the 4 lines that initializes and declares variables, all of which are temporary variables only to be used in within the while loop.
    These variables will be resetted after every permutation or loop.
    Following it is a for loop, it loops from 0 to the size of vertex.
    Within the loop, 'current_cost' variable adds the value from the graph with the temporary variable i and vertex with an index of the for loop 'j'.
    After adding the cost, we then add the cost to the temporary vector.
    After that, we also add the 'from' and 'to' of for loop. So we can see how it was done.
    The value of the variable 'i' will be revalued with the vertex with an index from the loop variable 'j'.

    After that first floop, we then do it again to add the going back to where we started and add those values to the temporary variables.
    Next is an if statement that checks if 'current_cost' is less than the 'lowest_cost', for the first time, it will always be true.
    For the following times, it will be checking with values only true or false.
    If the condition is met, we redefine the value of 'lowest_cost' to the 'current_cost'
    We also add a value to the vectors out the loop.
    */
    while (next_permutation(vertex.begin(), vertex.end()))
    {
        vector<int> temp_travel_Cost;
        vector<int> temp_from_to_City;
        int current_cost = 0;
        int i = s;
        for (int j = 0; j < vertex.size(); j++)
        {
            current_cost += graph[i][vertex[j]];
            temp_travel_Cost.push_back(graph[i][vertex[j]]);
            temp_from_to_City.push_back(i + 1);
            temp_from_to_City.push_back(vertex[j] + 1);
            i = vertex[j];
        }
        current_cost += graph[i][s];
        all_Cost.push_back(current_cost);
        temp_travel_Cost.push_back(graph[i][s]);
        temp_from_to_City.push_back(i + 1);
        temp_from_to_City.push_back(s + 1);
        if (current_cost < lowest_cost)
        {
            lowest_cost = current_cost;
            travel_Cost = temp_travel_Cost;
            from_to_City = temp_from_to_City;
        } 
    }

    // This just prints out a readable representation of the best possibility with a from - to and its cost.
    // The initialization/condition/inc-dec-acc within the for loop looks different?
    // It's a better way to loop a vector instead of the normal way.
    int nth_travel = 0;
    cout << "From\t\tTo\t\tCost\n";
    for (int cost: travel_Cost)
    {
        int from = from_to_City[nth_travel];
        int to = from_to_City[nth_travel + 1];
        cout << "City " << from << "\t\tCity " << to << "\t\tCost: " << cost << endl;
        nth_travel += 2;
    }
    cout << "Lowest possible cost found: " << lowest_cost << endl << endl;

    cout << "Number of all possible costs: " << all_Cost.size() << endl;
    for (int cost: all_Cost)
    {
        cout << cost << ' ';
    }
}
