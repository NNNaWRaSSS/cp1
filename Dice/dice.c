#include <stdio.h>
#include <stdlib.h>

// Function to recursively find all dice combinations
void findDiceCombinations(int numDice, int targetSum, int* currentCombination, int currentDice) {
    // Base cases
    if (numDice == currentDice) {
        // If we've used all dice, check if sum equals target
        int sum = 0;
        for (int i = 0; i < numDice; i++) {
            sum += currentCombination[i];
        }
        if (sum == targetSum) {
            // Print the valid combination
            printf("[ ");
            for (int i = 0; i < numDice; i++) {
                printf("%d ", currentCombination[i]);
            }
            printf("] = %d\n", sum);
        }
        return;
    }

    // Try all possible values for current die (1-6)
    for (int i = 1; i <= 6; i++) {
        currentCombination[currentDice] = i;
        findDiceCombinations(numDice, targetSum, currentCombination, currentDice + 1);
    }
}

// Wrapper function to initialize and call recursive function
void diceSum(int numDice, int targetSum) {
    if (numDice < 1) {
        printf("Number of dice must be at least 1\n");
        return;
    }

    if (targetSum < numDice || targetSum > numDice * 6) {
        printf("Target sum %d is impossible with %d dice\n", targetSum, numDice);
        return;
    }

    printf("\nAll combinations of %d dice that sum to %d:\n", numDice, targetSum);
    
    // Allocate array to store current combination
    int* currentCombination = (int*)malloc(numDice * sizeof(int));
    
    // Find all combinations
    findDiceCombinations(numDice, targetSum, currentCombination, 0);
    
    // Free allocated memory
    free(currentCombination);
}

int main() {
    // Test cases
    printf("Test Case 1:");
    diceSum(2, 7);
    
    printf("\nTest Case 2:");
    diceSum(3, 7);
    
    return 0;
}