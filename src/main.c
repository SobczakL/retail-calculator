#include <iso646.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int num;
  char *option;
  float (*operation)(void);
} menuOption;

typedef struct {
  int id;
  char opt[50];
} options;

char selectOption(menuOption menuOption[], int optionSize);
float averageDollarSales(void);
float averagePerWeek(void);
float averageOrderValue(void);
float averageUnitCost(void);
float averageUnitRetail(void);
float cogs(void);

float sellThroughRate(void);
float grossMarginRate(void);
float grossMarginReturnOnInvestment(void);

float averageInventory(void);
float stockToSales(void);
float turns(void);
float weeksOfSupply(void);

menuOption operationSelection[] = {
    {1, "sales metrics"},
    {2, "productivity metrics"},
    {3, "inventory metrics"},
    {0, "exit"},
};

menuOption salesMetrics[] = {
    {1, "average dollar sales", averageDollarSales},
    {2, "average per week", averagePerWeek},
    {3, "average order value", averageOrderValue},
    {4, "average unit cost", averageUnitCost},
    {5, "average unit retail", averageUnitRetail},
    {6, "cost of goods sold", cogs},
};

menuOption productivityMetrics[] = {
    {1, "sell through rate", sellThroughRate},
    {2, "gross margin", grossMarginRate},
    {3, "gross margin return on investment", grossMarginReturnOnInvestment},
};

menuOption inventoryMetrics[] = {
    {1, "average inventory", averageInventory},
    {2, "stock to sales", stockToSales},
    {3, "turn", turns},
    {4, "weeks of supply", weeksOfSupply},
};

int main(void) {
  while (1) {
    char optionIndex, *pOptionIndex, option, *pOption;
    pOptionIndex = &optionIndex;
    pOption = &option;

    option =
        selectOption(operationSelection, sizeof(operationSelection) /
                                             sizeof(operationSelection[0]));

    switch (option) {
    case '1':

      *pOption = selectOption(salesMetrics,
                              sizeof(salesMetrics) / sizeof(salesMetrics[0]));
      *pOptionIndex = option - '0';

      if (optionIndex > 0) {
        salesMetrics[optionIndex - 1].operation();
        break;
      } else {
        printf("failed\n");
        break;
      }
      break;

    case '2':
      *pOption =
          selectOption(productivityMetrics, sizeof(productivityMetrics) /
                                                sizeof(productivityMetrics[0]));
      *pOptionIndex = option - '0';
      if (optionIndex > 0) {
        productivityMetrics[optionIndex - 1].operation();
        break;
      } else {
        printf("failed\n");
        break;
      }
      break;

    case '3':
      *pOption =
          selectOption(inventoryMetrics,
                       sizeof(inventoryMetrics) / sizeof(inventoryMetrics[0]));
      *pOptionIndex = option - '0';
      if (optionIndex > 0) {
        inventoryMetrics[optionIndex - 1].operation();
        break;
      } else {
        printf("failed\n");
        break;
      }
      break;
    case '0':
      exit(0);
    }
  }

  return 0;
};

char selectOption(menuOption menuOption[], int optionSize) {
  char selected;

  printf("Please select an option below:\n");
  for (int i = 0; i < optionSize; i++) {
    printf("%i. %s\n", menuOption[i].num, menuOption[i].option);
  }

  scanf(" %c", &selected);

  return selected;
};

float averageDollarSales(void) {
  int salesGenerated, periods;

  printf("What are your total generated sales?\n");
  scanf("%i", &salesGenerated);

  printf("Over how many periods were the total generated sales?\n");
  scanf("%i", &periods);

  printf("The average dollar sales is: %.2f per period\n",
         (float)salesGenerated / periods);
  return 1;
}

float averagePerWeek(void) {
  int totalUnits, weeks;

  printf("How many total units have you sold?\n");
  scanf("%i", &totalUnits);

  printf("Over how many weeks were those units sold?\n");
  scanf("%i", &weeks);

  printf("Your average units per week is: %.1f%%\n",
         ((float)totalUnits / weeks) * 100);
  return 1;
};

float averageOrderValue(void) {
  int revenue, orders;

  printf("What is your total revenue?\n");
  scanf("%i", &revenue);

  printf("What is your total order amount?\n");
  scanf("%i", &orders);

  printf("The average order value is: $%i\n", (int)revenue / orders);
  return 1;
};

float averageUnitCost(void) {
  int orderValue, unitsBought;

  printf("What is your total buy at cost?\n");
  scanf("%i", &orderValue);

  printf("How many units did you buy?\n");
  scanf("%i", &unitsBought);

  printf("The average unit cost is: $%.2f", (float)orderValue / unitsBought);
  return 1;
}
float averageUnitRetail(void) {
  int revenue, unitsSold;

  printf("What is your total revenue?\n");
  scanf("%i", &revenue);

  printf("How many units did you sell?\n");
  scanf("%i", &unitsSold);

  printf("The average retail cost is: $%.2f\n", (float)revenue / unitsSold);
  return 1;
}
float cogs(void) {
  int bInv, purchases, eInv, total;

  printf("What is the value of your beginning inventory?\n");
  scanf("%i", &bInv);

  printf("What is the value of addition purchases made during this period?\n");
  scanf("%i", &purchases);

  printf("What is the value of your ending inventory?\n");
  scanf("%i", &eInv);

  total = bInv + purchases - eInv;
  printf("The cost of goods sold is $%i\n", (int)total);
  return total;
}

float sellThroughRate(void) {
  int unitsSold, unitsBought;

  printf("How many units have you sold?\n");
  scanf("%i", &unitsSold);

  printf("How many units did you buy in total?\n");
  scanf("%i", &unitsBought);

  printf("Your sell through rate is: %.1f%%\n",
         ((float)unitsSold / unitsBought) * 100);
  return 1;
};
float grossMarginRate(void) {
  int revenue, cogsValue, selection;
  cogsValue = 0;

  options option[] = {{1, "Yes\n"}, {2, "No\n"}};

  printf("To calculate gross margin rate, this formula requires a cost of "
         "goods sold figure. Would you like to "
         "calculate that now?\n");
  for (int i = 0; i < sizeof(option) / sizeof(option[0]); i++) {
    printf("%i. %s", option[i].id, option[i].opt);
  }
  scanf("%i", &selection);

  if (selection == 1) {
    cogsValue = cogs();
  }

  printf("What is your total revenue?\n");
  scanf("%i", &revenue);

  if (cogsValue == 0) {
    printf("What is your cost of goods sold?\n");
    scanf("%i", &cogsValue);
  }

  printf("Your gross margin rate is: %.2f\n",
         (float)((revenue - cogsValue) / revenue) * 100);
  return 1;
}
float grossMarginReturnOnInvestment(void) {
  int gm, aInv, selection, secondSelection;

  options option1[] = {{1, "Yes\n"}, {2, "No\n"}};
  options option2[] = {
      {1, "Gross Margin\n"}, {2, "Average Cost of Inventory\n"}, {3, "Both\n"}};

  printf("To calculate gross margin return on investment, this formula "
         "requires a gross margin and average cost of inventory. "
         "Would you like to calculate them now?\n");
  for (int i = 0; i < sizeof(option1) / sizeof(option1[0]); i++) {
    printf("%i. %s", option1[i].id, option1[i].opt);
  }
  scanf("%i", &selection);

  if (selection == 1) {
    printf("Please select which formula you'd like to run\n");
    for (int i = 0; i < sizeof(option2) / sizeof(option2[0]); i++) {
      printf("%i. %s", option2[i].id, option2[i].opt);
    }
    scanf("%i", &secondSelection);
    switch (secondSelection) {
    case 1:
      gm = grossMarginRate();
      printf("What is your average cost of inventory?\n");
      scanf("%i", &aInv);
      printf("Your GMROI is: %.1f", (float)gm / aInv);
      break;

    case 2:
      printf("What is your gross margin rate?\n");
      scanf("%i", &gm);
      aInv = averageInventory();
      printf("Your GMROI is: %.1f\n", (float)gm / aInv);
      break;

    case 3:
      gm = grossMarginRate();
      aInv = averageInventory();
      printf("Your GMROI is: %.1f\n", (float)gm / aInv);
      break;

    default:
      printf("Invalid selection\n");
      return 1;
    };
  } else {
    printf("What is your gross margin rate?\n");
    scanf("%i", &gm);
    printf("What is your average cost of inventory?\n");
    scanf("%i", &aInv);
    // need stop for a return that is less than zero / something didn't compute
    printf("Your GMROI is: %.1f\n", (float)gm / aInv);
  }

  return 0.0;
}
float averageInventory(void) {
  int bInv, eInv;
  float total;

  printf("What is the value of your beginning inventory?\n");
  scanf("%i", &bInv);
  printf("What is the value of your ending inventory?\n");
  scanf("%i", &eInv);

  total = (bInv / eInv) / 2;
  printf("Your average inventory value is: $%.2f\n", (float)total);

  return total;
}
float stockToSales(void) {
  int aInv, nSales, selection;

  options option[] = {{1, "Yes"}, {2, "No"}};
  printf("To calculate stock-to-sales, the formula requires an average "
         "inventory value. Would you like to calculate that now?\n");
  for (int i = 0; i < sizeof(option) / sizeof(option[0]); i++) {
    printf("%i: %s", option[i].id, option[i].opt);
  }
  scanf("%i", &selection);

  if (selection == 1) {
    aInv = averageInventory();
    printf("What is the value of your net sales?\n");
    scanf("%i", &nSales);
    printf("Your stock-to-sales ratio is: %.1f\n", (float)aInv / nSales);
  } else {
    printf("What is the value of your average inventory?\n");
    scanf("%i", &aInv);
    printf("What is the value of your net sales?\n");
    scanf("%i", &nSales);
    printf("Your stock-to-sales ratio is: %.1f\n", (float)aInv / nSales);
  }
  return 0.0;
}
float turns(void) {
  int cogsValue, aInv, selection, secondSelection;
  options option1[] = {{1, "Yes\n"}, {2, "No\n"}};
  options option2[] = {{1, "Cost of Goods Sold\n"},
                       {2, "Average Cost of Inventory\n"},
                       {3, "Both\n"}};

  printf("To calculate inventory turnover, this formula requires a gross "
         "margin and average cost of inventory. "
         "Would you like to calculate them now?\n");
  for (int i = 0; i < sizeof(option1) / sizeof(option1[0]); i++) {
    printf("%i. %s", option1[i].id, option1[i].opt);
  }
  scanf("%i", &selection);

  if (selection == 1) {
    printf("Please select which formula you'd like to run\n");
    for (int i = 0; i < sizeof(option2) / sizeof(option2[0]); i++) {
      printf("%i. %s", option2[i].id, option2[i].opt);
    }
    scanf("%i", &secondSelection);
    switch (secondSelection) {
    case 1:
      cogsValue = cogs();
      printf("What is your average cost of inventory?\n");
      scanf("%i", &aInv);
      printf("Your inventory turnover is: %.1f", (float)cogsValue / aInv);
      break;

    case 2:
      printf("What is your cost of goods sold?\n");
      scanf("%i", &cogsValue);
      aInv = averageInventory();
      printf("Your inventory turnover is: %.1f\n", (float)cogsValue / aInv);
      break;

    case 3:
      cogsValue = cogs();
      aInv = averageInventory();
      printf("Your inventory turnover is: %.1f\n", (float)cogsValue / aInv);
      break;

    default:
      printf("Invalid selection\n");
      return 1;
    };
  } else {
    printf("What is your cost of goods sold?\n");
    scanf("%i", &cogsValue);
    printf("What is your average cost of inventory?\n");
    scanf("%i", &aInv);
    // need stop for a return that is less than zero / something didn't compute
    printf("Your inventory turnover is: %.1f\n", (float)cogsValue / aInv);
  }
  return 0.0;
}
float weeksOfSupply(void) {
  int aSales, eInv;
  printf("What are your average weekly sales?\n");
  scanf("%i", &aSales);

  printf("What is your ending inventory?\n");
  scanf("%i", &eInv);

  printf("Your weeks of supply is: %.1f\n", (float)eInv / aSales);
  return 0.0;
}
