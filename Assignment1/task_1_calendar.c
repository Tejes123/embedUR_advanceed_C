#include <stdio.h>
#include <string.h>

#define MAX_DAYS 7
#define MAX_TASKS 3
#define MAX_LENGTH 50

// Structure for a day
struct Day {
    char dayName[20];
    char tasks[MAX_TASKS][MAX_LENGTH];
    int taskCount;
};

int main() {
    struct Day week[MAX_DAYS] = {
        {"Monday", {}, 0},
        {"Tuesday", {}, 0},
        {"Wednesday", {}, 0},
        {"Thursday", {}, 0},
        {"Friday", {}, 0},
        {"Saturday", {}, 0},
        {"Sunday", {}, 0}
    };

    int choice;

    while (1) {
        printf("\n===== WEEKLY CALENDAR =====\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int day;

            printf("\nSelect a Day:\n");
            for (int i = 0; i < MAX_DAYS; i++) {
                printf("%d. %s\n", i + 1, week[i].dayName);
            }

            printf("Enter day number (1-7): ");
            scanf("%d", &day);

            if (day < 1 || day > 7) {
                printf("Invalid day!\n");
                continue;
            }

            day--;  // Convert to array index

            if (week[day].taskCount >= MAX_TASKS) {
                printf("Task limit reached for %s!\n",
                       week[day].dayName);
                continue;
            }

            getchar(); // Remove newline from buffer

            printf("Enter task: ");
            fgets(
                week[day].tasks[week[day].taskCount],
                MAX_LENGTH,
                stdin
            );

            week[day].tasks[week[day].taskCount]
                [strcspn(
                    week[day].tasks[week[day].taskCount],
                    "\n"
                )] = '\0';

            week[day].taskCount++;

            printf("Task added successfully!\n");
        }

        else if (choice == 2) {
            printf("\n===== TASK LIST =====\n");

            for (int i = 0; i < MAX_DAYS; i++) {
                printf("\n%s:\n", week[i].dayName);

                if (week[i].taskCount == 0) {
                    printf("  No tasks\n");
                } else {
                    for (int j = 0; j < week[i].taskCount; j++) {
                        printf("  %d. %s\n",
                               j + 1,
                               week[i].tasks[j]);
                    }
                }
            }
        }

        else if (choice == 3) {
            printf("Exiting program...\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}