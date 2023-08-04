
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SALES 6
#define PRODUCTIVITY 3
#define INVENTORY 4

typedef struct
{
    int num;
    char * option;
    float (*operation)(void);
}
    menuOption;

char selectOption(menuOption menuOption[], int optionSize);
float sellThroughRate(void);

menuOption operationSelection[] = {
    {1, "sales metrics"},
    {2, "productivity metrics"},
    {3, "inventory metrics"},
};

menuOption salesMetrics[] = {
    {1, "average dollar sales", sellThroughRate},
    {2, "average per week", NULL}, 
    {3, "average order value", NULL},
    {4, "average unit cost", NULL},
    {5, "average unit retail", NULL},
    {6, "cost of goods sold", NULL},
};

menuOption productivityMetrics[] = {
    {1, "sell through rate", sellThroughRate},
    {2, "gross margin", NULL}, 
    {3, "gross margin return on investment", NULL}, 
};

menuOption inventoryMetrics[] = { 
    {1, "average inventory", NULL},
    {2, "stock to sales", NULL}, 
    {3, "turn", NULL}, 
    {4, "weeks of supply", NULL}, 
}; 

int main(void) 
{ 
    while(1) 
    { 
        int optionIndex; 
        char option; 
        option = selectOption(operationSelection, sizeof(operationSelection) / sizeof(operationSelection[0])); 
        
        switch (option) 
        {   
            case '1': 
                option = selectOption(salesMetrics, sizeof(salesMetrics) / sizeof(salesMetrics[0])); optionIndex = option - '0'; 
                
                if (optionIndex >= 0)
                {
                    if (salesMetrics[optionIndex].operation != NULL)
                    {
                        salesMetrics[optionIndex].operation();
                    }
                    else
                    {
                        printf("No operation assigned to this option.\n");
                    }
                }
                else
                {
                    printf("Invalid option.\n");
                }
                break;

            case '5':
                exit(0);
        }
    }

    return 0;
};

char selectOption(menuOption menuOption[], int optionSize)
{
    char selected;

    printf("Please select an option below:\n");
    for (int i = 0; i < optionSize; i++)
    {
        printf("%i. %s\n", menuOption[i].num, menuOption[i].option);
    }


    scanf("%c", &selected);
    
    return selected;
};

float sellThroughRate(void)
{
    int unitsSold, unitsBought;

    printf("How many units have you sold?\n");
    scanf("%i", &unitsSold);

    printf("How many units did you buy in total?\n");
    scanf("%i", &unitsBought);

    printf("Your sell through rate is: %f\n", (float) unitsSold / unitsBought);
    return 1;
};
