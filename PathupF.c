
#include <stdio.h>
#include <string.h>

#define MAX_CLASSES 10
#define MAX_TASKS 20

// Structure to store class information
typedef struct {
    char name[50];
    char day[15];
    char time[20];
} ClassInfo;

// Structure to store task information
typedef struct {
    char description[100];
    char dueDate[20]; // e.g., "May 29"
} Task;

// Global arrays and counters for classes and tasks
ClassInfo classes[MAX_CLASSES];
int classCount = 0;

Task tasks[MAX_TASKS];
int taskCount = 0;

// Function declarations
void addClass();
void viewClasses();
void addTask();
void viewTasks();
void saveData();
void loadData();
void logStudyHours();
void viewStudySummary();

int main() {
    int choice;
    loadData();

    // Show a motivational tip when program starts
    printf("\n💡 Tip: Study in 25-minute sessions with 5-minute breaks to stay focused!\n");

    do {
        // Displaying the menu
        printf("\n=== PathUp Menu ===\n");
        printf("1. Add Class\n");
        printf("2. View Classes\n");
        printf("3. Add Task\n");
        printf("4. View Tasks\n");
        printf("5. Log Study Hours\n");
        printf("6. View Study Summary\n");
        printf("7. Save Data\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addClass(); break;
            case 2: viewClasses(); break;
            case 3: addTask(); break;
            case 4: viewTasks(); break;
            case 5: logStudyHours(); break;
            case 6: viewStudySummary(); break;
            case 7: saveData(); break;
            case 0:
                saveData();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Add a new class to the schedule
void addClass() {
    if (classCount >= MAX_CLASSES) {
        printf("Class list is full.\n");
        return;
    }

    printf("Enter class name: ");
    fgets(classes[classCount].name, sizeof(classes[classCount].name), stdin);
    classes[classCount].name[strcspn(classes[classCount].name, "\n")] = 0;

    printf("Enter class day: ");
    fgets(classes[classCount].day, sizeof(classes[classCount].day), stdin);
    classes[classCount].day[strcspn(classes[classCount].day, "\n")] = 0;

    printf("Enter class time: ");
    fgets(classes[classCount].time, sizeof(classes[classCount].time), stdin);
    classes[classCount].time[strcspn(classes[classCount].time, "\n")] = 0;

    classCount++;
    printf("Class added successfully.\n");
}

// View all added classes
void viewClasses() {
    if (classCount == 0) {
        printf("No classes to display.\n");
        return;
    }
    printf("\n--- Class Schedule ---\n");
    for (int i = 0; i < classCount; i++) {
        printf("%d. %s - %s at %s\n", i + 1, classes[i].name, classes[i].day, classes[i].time);
    }
}

// Add a new task with a due date
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full.\n");
        return;
    }

    printf("Enter task description: ");
    fgets(tasks[taskCount].description, sizeof(tasks[taskCount].description), stdin);
    tasks[taskCount].description[strcspn(tasks[taskCount].description, "\n")] = 0;

    printf("Enter due date (e.g., May 29): ");
    fgets(tasks[taskCount].dueDate, sizeof(tasks[taskCount].dueDate), stdin);
    tasks[taskCount].dueDate[strcspn(tasks[taskCount].dueDate, "\n")] = 0;

    taskCount++;
    printf("Task added successfully.\n");
}

// View all tasks and their due dates
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("\n--- Task List ---\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s (Due: %s)\n", i + 1, tasks[i].description, tasks[i].dueDate);
    }
}

// Log hours studied per subject
void logStudyHours() {
    char subject[50];
    int hours;

    printf("Enter subject: ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = 0;

    printf("Enter hours studied today: ");
    scanf("%d", &hours);
    getchar();

    FILE *f = fopen("study_log.txt", "a");
    fprintf(f, "%s: %d hour(s)\n", subject, hours);
    fclose(f);

    printf("Study hours logged.\n");
}

// Display all logged study hours
void viewStudySummary() {
    FILE *f = fopen("study_log.txt", "r");
    if (!f) {
        printf("No study data found.\n");
        return;
    }

    char line[150];
    printf("\n--- Study Log ---\n");
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);
}

// Save all class and task data to a file
void saveData() {
    FILE *f = fopen("pathup_data.txt", "w");
    if (!f) {
        printf("Error saving data.\n");
        return;
    }

    fprintf(f, "%d\n", classCount);
    for (int i = 0; i < classCount; i++) {
        fprintf(f, "%s\n%s\n%s\n", classes[i].name, classes[i].day, classes[i].time);
    }

    fprintf(f, "%d\n", taskCount);
    for (int i = 0; i < taskCount; i++) {
        fprintf(f, "%s\n%s\n", tasks[i].description, tasks[i].dueDate);
    }

    fclose(f);
    printf("Data saved successfully.\n");
}

// Load previously saved class and task data
void loadData() {
    FILE *f = fopen("pathup_data.txt", "r");
    if (!f) return;

    fscanf(f, "%d\n", &classCount);
    for (int i = 0; i < classCount; i++) {
        fgets(classes[i].name, sizeof(classes[i].name), f);
        classes[i].name[strcspn(classes[i].name, "\n")] = 0;

        fgets(classes[i].day, sizeof(classes[i].day), f);
        classes[i].day[strcspn(classes[i].day, "\n")] = 0;

        fgets(classes[i].time, sizeof(classes[i].time), f);
        classes[i].time[strcspn(classes[i].time, "\n")] = 0;
    }

    fscanf(f, "%d\n", &taskCount);
    for (int i = 0; i < taskCount; i++) {
        fgets(tasks[i].description, sizeof(tasks[i].description), f);
        tasks[i].description[strcspn(tasks[i].description, "\n")] = 0;

        fgets(tasks[i].dueDate, sizeof(tasks[i].dueDate), f);
        tasks[i].dueDate[strcspn(tasks[i].dueDate, "\n")] = 0;
    }

    fclose(f);
}

