#include "heap.h"
#include <cstdio>
#include <ctime>

// C++ program to demonstrate the use of priority_queue
#include <iostream>
#include <queue>
#include "arrayHeap.h"

#define RUN_ARRAY_IMPLEMENTATION 1
#define RUN_VARIANTY_IMPLEMENTATION 1
#define RUN_PRIORITY_QUEUE_IMPLEMENTATION 1
#define BENCHMARK_ROUNDS 1'000'000
#define PROB 0.7    // Probability of pushing

using namespace std;

typedef struct testSet
{
    vector<int> inserts;
    vector<uint8_t> push_pop;
}testSet;

void initRand()
{
    srand(time(0));
}

int genRandInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

float genRandFloat(float min, float max)
{
    return (float)rand() / RAND_MAX * (max - min) + min;
}

/* Continuously push first, then continously pop*/
uint8_t test_1(int rounds, int min, int max)
{

    int maxSize = 10;
    int *arrHeap = (int *)malloc(maxSize * sizeof(int));
    int size = 0;
    int arrHeapres = 0;



    priority_queue<int> pq;



    bRootNode* root = NULL;
    popHeapResult res;


    for (int a = 0 ; a < rounds ; a++)
    {
        int rand_num = genRandInt(min, max);

        root = pushHeap(root, rand_num, true);
        pq.push(rand_num);
        arrHeap = pushArrayHeap(rand_num, arrHeap, &size, &maxSize);

        if (arrHeap == NULL)
        {
            printf("Error : Unable to allocate enough memory\n");
        }

    }

    // not checking if heap is empty as no.of insertions == no.of pops == rounds
    for (int a = 0 ; a < rounds; a++)
    {

        arrHeapres = popArrayHeap(arrHeap, &size);

        res = popHeap(root, true);

        if (res.result == 0)
        {
            printf("Unexpected from heap\n");

            free(arrHeap);

            return -1;
        }
        else
        {
            if (res.data != pq.top())
            {
                printf("heap - FAILED\n");

                free(arrHeap);

                return 0;
            }

            if (pq.top() != arrHeapres)
            {
                printf("arrHeap - FAILED\n");
                free(arrHeap);
                return 0;
            }

            pq.pop();
        }
    }

    free(arrHeap);

    // destroybTree((bNode *)root);
    return 1;
}

/* Push and pop randomly*/
uint8_t test_2(int rounds, int min, int max)
{
    
    int maxSize = 10;

    int *arrHeap = (int *)malloc(maxSize * sizeof(int));
    int size = 0;
    int arrHeapres = 0;


	priority_queue<int> pq;

    bRootNode* root = NULL;
    popHeapResult res;

    for (int a = 0 ; a < rounds; a++)
    {
        uint8_t push_pop = genRandInt(0,1);

        if (push_pop == 0 )
        {
            int rand_num = genRandInt(min, max);

            root = pushHeap(root, rand_num, true);

            arrHeap = pushArrayHeap(rand_num, arrHeap, &size, &maxSize);

            pq.push(rand_num);

            // Uncomment the below line and comment the line above pq.push, it fials for some reason, idk why
            // arrHeap = pushArrayHeap(rand_num, arrHeap, &size, &maxSize);
            if (arrHeap == NULL)
            {
                printf("Error : Unable to allocate enough memory\n");
            }

        }
        else
        {
            if (root != NULL)
            {
                res = popHeap(root, true);
                if (res.result == 0)
                {
                    printf("Unexpected from heap\n");

                    free(arrHeap);

                    return -1;
                }
                else
                {

                    arrHeapres = popArrayHeap(arrHeap, &size);
                    if (pq.top() != arrHeapres)
                    {
                        printf("arrHeap Failed\n");
                        return 0;
                    }
                    
                    if (res.data != pq.top())
                    {
                        printf("heap Failed\n");
                        return 0;
                    }
                    if (res.result == 2)
                    {
                        root = NULL;
                    }

                    pq.pop();
                }
            }
            else if ( !pq.empty() )
            {
                printf("heap failed, supposed to be empty\n");
                return -1;
                
            }
        }
    }
    return 1;
}

int no_of_pushes = 0;

testSet genTestSet(int rounds, int max, int min)
{
    testSet res;
    while (rounds != 0)
    {
        if (genRandFloat(0.0, 1.0) < PROB)
        {
            no_of_pushes++;
            res.inserts.push_back(genRandInt(min, max));
            res.push_pop.push_back(0);
        }
        else
        {
            res.push_pop.push_back(1);
        }
        rounds--;
    }
    return res;
}

void benchmark_1(int rounds, int min, int max)
{
    bRootNode* root = NULL;
    priority_queue<int> pq;

    int *tSet = (int *)malloc(rounds * sizeof(int));


    int maxSize = 10;
    int size = 0;
    int *arrHeap = (int *)malloc(maxSize * sizeof(int));

    clock_t end, variant_time, pqTime, arrHeapTime;

    for (int a = 0 ; a < rounds ; a++)
    {
        tSet[a] = genRandInt(min, max);
    }
    // start timer here
    variant_time = clock();

    for (int a = 0 ; a < rounds ; a++)
    {
        root = pushHeap(root, tSet[a], true);
    }

    // end timer here 
    end = clock();
    variant_time = end - variant_time;

    pqTime = clock();
    for (int a = 0 ; a < rounds ; a++)
    {
        pq.push(tSet[a]);
    }

    end = clock();
    pqTime = end - pqTime;


    arrHeapTime = clock();
    for (int a = 0 ; a < rounds ; a++)
    {
        arrHeap = pushArrayHeap(tSet[a], arrHeap, &size, &maxSize);
    }

    end = clock();
    arrHeapTime = end - arrHeapTime;
    free(tSet);

    printf("Insertions time for %d rounds : \n", rounds);
    printf("pqTime : %lf\n",(double)pqTime / CLOCKS_PER_SEC);
    printf("arrHeapTime : %lf\n", (double)arrHeapTime / CLOCKS_PER_SEC);
    printf("variant_time : %lf\n\n", (double)variant_time / CLOCKS_PER_SEC);

    variant_time = clock();
    for (int a = 0 ; a < rounds ; a++)
    {
        popHeap(root, true);
    }

    end = clock();
    variant_time = end - variant_time;

    pqTime = clock();
    for (int a = 0 ; a < rounds ; a++)
    {
        pq.pop();
    }
    
    end = clock();
    pqTime = end - pqTime;


    arrHeapTime = clock();
    for (int a = 0 ; a < rounds ; a++)
    {
        popArrayHeap(arrHeap, &size);
    }
    
    end = clock();
    arrHeapTime = end - arrHeapTime;
 
    printf("Pops time for %d rounds : \n", rounds);
    printf("pqTime : %lf\n",(double)pqTime / CLOCKS_PER_SEC);
    printf("arrHeapTime : %lf\n", (double)arrHeapTime / CLOCKS_PER_SEC);
    printf("variant_time : %lf\n\n", (double)variant_time / CLOCKS_PER_SEC);
}

void benchmark_2(int rounds, int min, int max)
{
    bRootNode* root = NULL;
	priority_queue<int> pq;

    int maxSize = 10;
    int size = 0;
    int *arrHeap = (int *)malloc(maxSize * sizeof(int));

    int index = 0;
    testSet tSet = genTestSet(rounds, min, max);
    printf("No.of pushes : %d\n", no_of_pushes);
    printf("No of pops   : %d\n\n", rounds - no_of_pushes);
    clock_t end, variant_time, pqTime, arrHeapTime;


    // start timer here
    variant_time = clock();

    for (int a = 0 ; a < rounds ; a++)
    {
        if (tSet.push_pop[a] == 0)
        {
            root = pushHeap(root, tSet.inserts[index], true);
            index++;
        }
        else 
        {
            if (root != NULL)
            {
                if(popHeap(root, true).result == 2)
                {
                    root = NULL;
                }
            }
        }
    }

    // end timer here 
    end = clock();
    variant_time = end - variant_time;


    index = 0;
    pqTime = clock();

    for (int a = 0 ; a < rounds ; a++)
    {
        if (tSet.push_pop[a] == 0)
        {
            pq.push(tSet.inserts[index]);
            index++;
        }
        else 
        {
            if (!pq.empty())
            {
                pq.pop();
            }
        }
    }

    end = clock();
    pqTime = end - pqTime;

    index = 0;
    arrHeapTime = clock();

    for (int a = 0 ; a < rounds ; a++)
    {
        if (tSet.push_pop[a] == 0)
        {
            arrHeap = pushArrayHeap(tSet.inserts[index], arrHeap, &size, &maxSize);
            index++;
        }
        else 
        {
            if (size != 0)
            {
                popArrayHeap(arrHeap, &size);
            }
        }
    }
    
    end = clock();
    arrHeapTime = end - arrHeapTime;

    printf("Random insertions and deletions time : \n");
    printf("pqTime : %lf\n",(double)pqTime / CLOCKS_PER_SEC);
    printf("arrHeapTime : %lf\n", (double)arrHeapTime / CLOCKS_PER_SEC);
    printf("variant_time : %lf\n\n", (double)variant_time / CLOCKS_PER_SEC);
}


int main()
{
    printf("pqTime : Time taken by priority_queue\n");
    printf("arrHeapTime : Time taken by arrayHeap\n");
    printf("variant_time : Time taken by variant heap\n\n");
    initRand();
    if (test_1(10000, 1, 1000) == 1)
    {
        printf("Test 1 successful\n");
    }
    else 
    {
        printf("Test 1 failed\n");
        return 0;
    }
    if (test_2(10000, 1, 1000) == 1)
    {
        printf("Test 2 successful\n\n");
    }
    else 
    {
        printf("Test 2 failed\n");
        return 0;
    }
    benchmark_1(BENCHMARK_ROUNDS, 1, 10000);
    benchmark_2(BENCHMARK_ROUNDS, 1, 10000);
    return 1;
}

