#include <stdio.h>

#define MAX 100

int n;
float value[MAX], weight[MAX], ratio[MAX], selected[MAX];
float capacity, maxValue = 0, totalWeight = 0;

void enterDetails()
{
    int i;

    printf("Enter number of packages: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of packages. Please enter a value between 1 and %d.\n", MAX);
        n = 0;
        return;
    }

    for (i = 0; i < n; i++)
    {
        printf("\nPackage %d\n", i + 1);
        printf("Enter value: ");
        scanf("%f", &value[i]);

        printf("Enter weight: ");
        scanf("%f", &weight[i]);

        if (weight[i] <= 0)
        {
            printf("Weight must be positive. Please re-enter package %d.\n", i + 1);
            i--;
        }
        else
        {
            selected[i] = 0;
            ratio[i] = value[i] / weight[i];
        }
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    if (capacity <= 0)
    {
        printf("Capacity must be positive.\n");
        capacity = 0;
    }
}

void displayDetails()
{
    int i;

    if (n <= 0)
    {
        printf("\nNo package details available. Please enter details first.\n");
        return;
    }

    printf("\n-------------------------------------------------\n");
    printf("Package\tValue\tWeight\tRatio\n");
    printf("-------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (weight[i] > 0)
            ratio[i] = value[i] / weight[i];
        else
            ratio[i] = 0;

        printf("%d\t%.2f\t%.2f\t%.2f\n", i + 1, value[i], weight[i], ratio[i]);
    }
}

void calculateRatio()
{
    int i;

    if (n <= 0)
    {
        printf("\nNo package details available.\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (weight[i] > 0)
            ratio[i] = value[i] / weight[i];
        else
            ratio[i] = 0;
    }

    printf("\nValue/Weight Ratios Calculated Successfully.\n");
}

void sortPackages()
{
    int i, j;
    float temp;

    if (n <= 0)
    {
        printf("\nNo package details available.\n");
        return;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (ratio[i] < ratio[j])
            {
                temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                temp = value[i];
                value[i] = value[j];
                value[j] = temp;

                temp = weight[i];
                weight[i] = weight[j];
                weight[j] = temp;
            }
        }
    }

    printf("\nPackages Sorted in Decreasing Order of Ratio.\n");
}

void findMaximumValue()
{
    int i;
    float remaining = capacity;

    if (n <= 0)
    {
        printf("\nNo package details available.\n");
        return;
    }

    maxValue = 0;
    totalWeight = 0;

    for (i = 0; i < n; i++)
        selected[i] = 0;

    for (i = 0; i < n; i++)
    {
        if (weight[i] <= 0)
            continue;

        if (weight[i] <= remaining)
        {
            selected[i] = 1.0;
            remaining -= weight[i];
            totalWeight += weight[i];
            maxValue += value[i];
        }
        else
        {
            selected[i] = remaining / weight[i];
            totalWeight += remaining;
            maxValue += value[i] * selected[i];
            remaining = 0;
            break;
        }
    }

    printf("\nMaximum Value = %.2f\n", maxValue);
    printf("Time Complexity: O(n log n) because sorting dominates the work, and the greedy selection runs in O(n).\n");
}

void displaySelectedPackages()
{
    int i;

    if (n <= 0)
    {
        printf("\nNo package details available.\n");
        return;
    }

    printf("\n--------------------------------------------\n");
    printf("Package\tSelected Fraction\n");
    printf("--------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (selected[i] > 0)
            printf("%d\t%.2f\n", i + 1, selected[i]);
    }

    printf("\nTotal Weight Used = %.2f\n", totalWeight);
    printf("Maximum Value Obtained = %.2f\n", maxValue);
}

int main()
{
    int choice;

    do
    {
        printf("\n\n===== FRACTIONAL KNAPSACK MENU =====\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterDetails();
                break;

            case 2:
                displayDetails();
                break;

            case 3:
                calculateRatio();
                break;

            case 4:
                sortPackages();
                break;

            case 5:
                findMaximumValue();
                break;

            case 6:
                displaySelectedPackages();
                break;

            case 7:
                printf("Exiting Program...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 7);

    return 0;
}