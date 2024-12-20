#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX 16 


This program is written by: Nagel Poulose */


struct Garage {
    int x, y;
    char name[21];
} garages[MAX]; 

int bestPerm[MAX]; 
double bestDist = 10001; 

//function that returns the distance between 2 garages
double calcDistance(int i, int j) {
    return sqrt((garages[i].x - garages[j].x) * (garages[i].x - garages[j].x) + 
                (garages[i].y - garages[j].y) * (garages[i].y - garages[j].y));
}

// function that creates all the permutations
void generatePerm(int perm[], int used[], int k, int n) {
    if (k == 2 * n) { 
        double totalDist = 0.0;
        for (int i = 0; i < 2 * n; i += 2) {
            totalDist += calcDistance(perm[i], perm[i + 1]);
        }

        // if this distance is less than previous, update
        if (totalDist < bestDist) {
            bestDist = totalDist;
            for (int i = 0; i < 2 * n; i++) {
                bestPerm[i] = perm[i];
            }
        }
        return;
    }

    // runs through all the permutations 
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i]) {
            used[i] = 1; 
            perm[k] = i; 
            generatePerm(perm, used, k + 1, n);
            used[i] = 0;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n); 

    for (int i = 0; i < 2 * n; i++) {
        scanf("%d %d %s", &garages[i].x, &garages[i].y, garages[i].name);
    }

    int perm[MAX] = {0}; 
    int used[MAX] = {0}; 

    
    generatePerm(perm, used, 0, n);

    
    printf("%.3lf\n", bestDist);

    //prints best distance and respective garage names 
    for (int i = 0; i < 2 * n; i += 2) {
        int from = bestPerm[i];
        int to = bestPerm[i + 1];
        printf("(%s, %s, %.3lf)\n", garages[from].name, garages[to].name, calcDistance(from, to));
    }

    return 0;
}