// graphexam.cpp
// cmc, 9/30/2017
// non-interactive test program for class graph.
// Run with a test number between 1 and 5 as command line argument
// For example, to run test number 3, type:
//    ./graphexam 3

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include "graph.h"

using namespace std;
using namespace main_savitch_15;

// Descriptions and points for each of the tests:
const size_t MANY_TESTS = 5;
const int POINTS[MANY_TESTS+1] = {
   100,  // Total points for all tests.
    40,  // Test 1 points
    15,  // Test 2 points
    15,  // Test 3 points
    15,  // Test 4 points
    15,  // Test 5 points
};
const string DESCRIPTION[MANY_TESTS+1] = {
    "tests for graph class (directed, non-weighted edge version)",
    "Testing basic constructors and functions",
    "Testing resize, and adjustments to add a vertex after full",
    "Testing neighbors, in combination with resizing",
    "Testing the copy constructor",
    "Testing the assignment operator"
};
const size_t BASIC = 10, MEDIUM = 100, BIG = 2000;

template <class Item>
bool okayVerts(const graph<Item> &g, size_t size,
               const Item vertices[]) {
    for (size_t i = 0; i < size; i++)
        if (g[i] != vertices[i]) {
            cout << "vertex value incorrect at position " << i << endl;
            return false;
        }
    return true;
}

template <class Item>
bool okayEdges(const graph<Item> &g, size_t size, size_t alloc,
               const bool *edges) {
    for (size_t i = 0; i < size; i++)
        for (size_t j = 0; j < size; j++) {
            size_t index = i * alloc + j;
            if (i != j && g.is_edge(i, j) != edges[index]) {
                cout << "edge incorrect at " << i << "," << j << endl;
                return false;
            }
        }
    return true;
}

// **************************************************************************
// int test1( )
//   Performs some basic tests of ctors (except copy ctor), add_vertex,
//   add_ and remove_edge, and constant member functions (except neighbors).
//   Returns POINTS[1] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test1( ) {
    cout << "using no-argument constructor <Item type int>\n";
    graph<int> g;
    if (g.size() > 0) {
        cout << "new graph size is " << g.size()
            << "; should be 0\n";
        return 0;
    }
    cout << "okay\n";

    cout << "adding some random vertices\n";
    int vertices[BASIC];
    size_t i, j;
    srand (time(NULL));
    vertices[0] = rand() % 10000 - 5000;
    g.add_vertex(vertices[0]);
    for (i = 1; i < BASIC; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    cout << "using op[] to check vertices added correctly\n";
    if (!okayVerts(g, BASIC, vertices))
        return 0;
    cout << "okay\n";

    cout << "adding some random edges\n";
    bool edges[BASIC][BASIC];
    int halfway = RAND_MAX / 2;
    for (i = 0; i < BASIC; i++)
        for (j = 0; j < BASIC; j++) {
            if (i == j) continue;
            edges[i][j] = rand() > halfway;
            if (edges[i][j])
                g.add_edge(i, j);
        }
    cout << "using is_edge to verify edges added correctly\n";
    for (i = 0; i < BASIC; i++)
        for (j = 0; j < BASIC; j++) {
            if (i != j && g.is_edge(i, j) != edges[i][j]) {
                cout << "edge incorrect at " << i << "," << j << endl;
                return 0;
            }
        }
    cout << "okay\n";

    cout << "remove some edges, and verify all still correct\n";
    for (i = 0; i < BASIC; i++)
        for (j = 0; j < BASIC; j++)
            if (i != j && edges[i][j])
                if (rand() > halfway) {
                    edges[i][j] = false;
                    g.remove_edge(i, j);
                }
    if (!okayEdges(g, BASIC, BASIC, &edges[0][0]))
        return 0;
    cout << "okay\n";

    cout << "using constructor with small initial allocation"
        << " <Item type string>\n";
    graph<string> g2(4);
    g2.add_vertex("zero");
    g2.add_vertex("one");
    g2.add_vertex("two");
    g2.add_vertex("three");
    if (g2.size() != 4) {
        cout << "new graph size is " << g2.size()
            << "; should be 4\n";
        return 0;
    }
    string sverts[] = {"zero","one","two","three"};
    if (!okayVerts(g2, 4, sverts))
        return 0;
    cout << "okay\n";
    
    cout << "constructing and testing a really big graph\n";
    graph<int> big(BIG);
    int bigvertices[BIG];
    bigvertices[0] = rand() % 10000 - 5000;
    big.add_vertex(bigvertices[0]);
    for (i = 1; i < BIG; i++) {
        bigvertices[i] = bigvertices[i-1] + 1;
        big.add_vertex(bigvertices[i]);
    }
    bool bigedges[BIG][BIG];
    for (i = 0; i < BIG; i++)
        for (j = 0; j < BIG; j++) {
            if (i == j) continue;
            bigedges[i][j] = rand() > halfway;
            if (bigedges[i][j])
                big.add_edge(i, j);
        }
    if (big.size() != BIG) {
        cout << "graph size should be " << BIG
            << "; is " << big.size() << endl;
        return 0;
    }
    if (!okayVerts(big, BIG, bigvertices)
        || !okayEdges(big, BIG, BIG, &bigedges[0][0]))
        return 0;
    cout << "okay\n";
    
    // All tests passed
    cout << "All of the basic tests have been passed." << endl;
    return POINTS[1];
}

// **************************************************************************
// int test2( )
//   Tests resize, and adjustments to add a vertex after full.
//   Returns POINTS[2] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test2( ) {
    graph<int> g(5);
    size_t i, j;
    for (i = 0; i < 5; i++)
        g.add_vertex(i);
    cout << "resizing a graph, then verifying no vertex changes\n";
    g.resize(20);
    for (i = 0; i < 5; i++)
        if (g[i] != static_cast<int>(i)) {
            cout << "mismatched vertex at position " << i << endl;
            return 0;
        }
    cout << "okay\n";
    cout << "adding/checking random data in resized graph\n";
    int vertices[25];
    for (i = 0; i < 5; i++)
        vertices[i] = i;
    srand (time(NULL));
    vertices[5] = 5 + rand() % 2000;
    g.add_vertex(vertices[5]);
    for (i = 6; i < 20; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    if (!okayVerts(g, 20, vertices))
        return 0;
    bool edges[25][25];
    int halfway = RAND_MAX / 2;
    for (i = 0; i < 20; i++)
        for (j = 0; j < 20; j++) {
            if (i == j) continue;
            edges[i][j] = rand() > halfway;
            if (edges[i][j])
                g.add_edge(i, j);
        }
    if (!okayEdges(g, 20, 25, &edges[0][0]))
        return 0;
    cout << "okay\n";
    
    cout << "adding vertices to full graph - should resize\n";
    for (i = 20; i < 25; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    if (g.size() != 25) {
        cout << "graph size should be 25; is " << g.size() << endl;
        return 0;
    }
    if (!okayVerts(g, 25, vertices)
        || !okayEdges(g, 20, 25, &edges[0][0]))
        return 0;
    cout << "okay\n";

    // All tests passed
    cout << "Resize tests have been passed." << endl;
    return POINTS[2];
}

// **************************************************************************
// int test3( )
//   Tests neighbors, in combination with resizing.
//   Returns POINTS[3] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test3( ) {
    graph<int> g(5);
    int vertices[100];
    size_t i, j;
    srand (time(NULL));
    vertices[0] = rand() % 10000 - 5000;
    g.add_vertex(vertices[0]);
    for (i = 1; i < 100; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    bool edges[100][100];
    int halfway = RAND_MAX / 2;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 100; j++) {
            if (i == j) continue;
            edges[i][j] = rand() > halfway;
            if (edges[i][j])
                g.add_edge(i, j);
        }
    // verify neighbors match edge data
    for (i = 0; i < 100; i++) {
        set<size_t> neighbors;
        for (j = 0; j < 100; j++)
            if (i != j && edges[i][j])
                neighbors.insert(j);
        if (neighbors != g.neighbors(i)) {
            cout << "neighbors incorrect for vertex " << i << endl;
            return 0;
        }
    }
    
    // All tests passed
    cout << "Neighbor tests have been passed." << endl;
    return POINTS[3];
}

// **************************************************************************
// int test4( )
//   Tests copy constructor.
//   Returns POINTS[4] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test4( ) {
    graph<int> g(100);
    int vertices[100];
    size_t i, j;
    srand (time(NULL));
    vertices[0] = rand() % 10000 - 5000;
    g.add_vertex(vertices[0]);
    for (i = 1; i < 100; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    bool edges[100][100];
    int halfway = RAND_MAX / 2;
    for (i = 0; i < 100; i++)
        for (j = 0; j < 100; j++) {
            if (i == j) continue;
            edges[i][j] = rand() > halfway;
            if (edges[i][j])
                g.add_edge(i, j);
        }
    
    cout << "creating new copy of random graph, and checking\n";
    graph<int> gcopy(g);
 
    if (g.size() != gcopy.size()) {
        cout << "copy size is " << gcopy.size()
            << ", but original size is " << g.size() << endl;
        return 0;
    }
    if (!okayVerts(gcopy, 100, vertices)
        || !okayEdges(gcopy, 100, 100, &edges[0][0]))
        return 0;
    
    g[50] = g[50] + 9;
    if (g[50] == gcopy[50]) {
        cout << "did not make deep copy of labels\n";
        return 0;
    }
    if (g.is_edge(50, 75))
        g.remove_edge(50, 75);
    else
        g.add_edge(50, 75);
    if (g.is_edge(50, 75) == gcopy.is_edge(50, 75)) {
        cout << "did not make deep copy of edges data\n";
        return 0;
    }
    
    cout << "okay\n";
    
    // All tests passed
    cout << "Copy constructor tests have been passed." << endl;
    return POINTS[4];
}

// **************************************************************************
// int test5( )
//   Tests assignment operator.
//   Returns POINTS[5] if the tests are passed. Otherwise returns 0.
// **************************************************************************
int test5( ) {
    graph<int> g(MEDIUM);
    int vertices[MEDIUM];
    size_t i, j;
    srand (time(NULL));
    vertices[0] = rand() % 10000 - 5000;
    g.add_vertex(vertices[0]);
    for (i = 1; i < MEDIUM; i++) {
        vertices[i] = vertices[i-1] + 1;
        g.add_vertex(vertices[i]);
    }
    bool edges[MEDIUM][MEDIUM];
    int halfway = RAND_MAX / 2;
    for (i = 0; i < MEDIUM; i++)
        for (j = 0; j < MEDIUM; j++) {
            if (i == j) continue;
            edges[i][j] = rand() > halfway;
            if (edges[i][j])
                g.add_edge(i, j);
        }
    
    graph<int> gcopy;
    cout << "assigning random graph to existing one, and checking\n";
    gcopy = g;

    if (g.size() != gcopy.size()) {
        cout << "copy size is " << gcopy.size()
        << ", but original size is " << g.size() << endl;
        return 0;
    }
    if (!okayVerts(gcopy, MEDIUM, vertices)
        || !okayEdges(gcopy, MEDIUM, MEDIUM, &edges[0][0]))
        return 0;
    cout << "okay\n";
    
    cout << "checking result of self-assignment\n";
    gcopy = gcopy;
    
    if (g.size() != gcopy.size()) {
        cout << "new size is " << gcopy.size()
            << ", but should be " << g.size() << endl;
        return 0;
    }
    if (!okayVerts(gcopy, MEDIUM, vertices)
        || !okayEdges(gcopy, MEDIUM, MEDIUM, &edges[0][0]))
        return 0;

    g[50] = g[50] + 9;
    if (g[50] == gcopy[50]) {
        cout << "did not make deep copy of labels\n";
        return 0;
    }
    if (g.is_edge(50, 75))
        g.remove_edge(50, 75);
    else
        g.add_edge(50, 75);
    if (g.is_edge(50, 75) == gcopy.is_edge(50, 75)) {
        cout << "did not make deep copy of edges data\n";
        return 0;
    }
    
    cout << "okay\n";
    
    // All tests passed
    cout << "Assignment operator tests have been passed." << endl;
    return POINTS[5];
}

// runs one test (from Michael Main)
int run_a_test(int number, const string message, int test_function( ), int max)
{
    int result;
    
    cout << endl << "START OF TEST " << number << ":" << endl;
    cout << message << " (" << max << " points)." << endl;
    result = test_function( );
    if (result > 0)
    {
        cout << "Test " << number << " got " << result << " points";
        cout << " out of a possible " << max << "." << endl;
    }
    else
        cout << "Test " << number << " failed." << endl;
    cout << "END OF TEST " << number << "." << endl << endl;
    
    return result;
}

// **************************************************************************
// int main(int argc, char *argv[])
//   The main program calls one test, and prints test ID and the points
//   earned from that test.
// **************************************************************************
int main(int argc, char *argv[]) {
    int result = 0;
    
    typedef int (*testfunc)();
    testfunc tests[MANY_TESTS] =  // array of function pointers
    {test1, test2, test3, test4, test5};
    
    if (argc > 1) {
        size_t testnum = argv[1][0] - '0';
        if (testnum > 0 && testnum <= MANY_TESTS)
            result = run_a_test(testnum, DESCRIPTION[testnum],
                                tests[testnum-1], POINTS[testnum]);
        else {
            cout << "bad test id: " << argv[1] << endl;
            return 1;
        }
        cout << "Completed test " << argv[1]
        << "; result: " << result << endl;
    }
    else {
        cout << "error: missing command line argument" << endl;
        cout << "usage: " << argv[0] << " test_id" << endl;
        return 2;
    }
    return 0;
}
