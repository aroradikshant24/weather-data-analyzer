#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


struct Weather {
    char date[20];
    float temperature;
    int humidity;
    float rainfall;
};

void readData(struct Weather data[], int *n);
void displayData(struct Weather data[], int n);
void analyzeData(struct Weather data[], int n);
void exportReport(struct Weather data[], int n);
void showCharts(struct Weather data[], int n);

int main() {
    struct Weather data[MAX];
    int n = 0, choice;

    while (1) {
        printf("\n_________WEATHER DATA ANALYZER ________\n");
        printf("\t1. Read Data from File\n");
        printf("\t2. Display Data\n");
        printf("\t3. Analyze Data\n");
        printf("\t4. Show Charts\n");
        printf("\t5. Export Report\n");
        printf("\t6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readData(data, &n);
                break;
            case 2:
                displayData(data, n);
                break;
            case 3:
                analyzeData(data, n);
                break;
            case 4:
                showCharts(data, n);
                break;
            case 5:
                exportReport(data, n);
                break;
            case 6:
                printf("Exiting... Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void readData(struct Weather data[], int *n) {
    FILE *fp = fopen("weather_data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char header[50];
    fgets(header, sizeof(header), fp); 

    *n = 0;
    while (fscanf(fp, "%s %f %d %f",
                  data[*n].date,
                  &data[*n].temperature,
                  &data[*n].humidity,
                  &data[*n].rainfall) != EOF) {
        (*n)++;
    }

    fclose(fp);
    printf("Data loaded successfully (%d records).\n", *n);
}

void displayData(struct Weather data[], int n) {
    if (n == 0) {
        printf("No data available.\n");
        return;
    }

    printf("\n%-12s %-12s %-12s %-12s\n", "Date", "Temp(C)", "Humidity(%)", "Rainfall(mm)");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-12s %-12.2f %-12d %-12.2f\n",
               data[i].date, data[i].temperature, data[i].humidity, data[i].rainfall);
    }
}

void analyzeData(struct Weather data[], int n) {
    if (n == 0) {
        printf("No data to analyze.\n");
        return;
    }

    float sumTemp = 0, sumRain = 0;
    int sumHum = 0;
    float maxTemp = data[0].temperature, minTemp = data[0].temperature;
    char hotDay[20], coldDay[20];

    strcpy(hotDay, data[0].date);
    strcpy(coldDay, data[0].date);

    for (int i = 0; i < n; i++) {
        sumTemp += data[i].temperature;
        sumHum += data[i].humidity;
        sumRain += data[i].rainfall;

        if (data[i].temperature > maxTemp) {
            maxTemp = data[i].temperature;
            strcpy(hotDay, data[i].date);
        }
        if (data[i].temperature < minTemp) {
            minTemp = data[i].temperature;
            strcpy(coldDay, data[i].date);
        }
    }

    printf("\n_________ WEATHER ANALYSIS _________\n");
    printf("\tAverage Temperature: %.2f °C\n", sumTemp / n);
    printf("\tAverage Humidity: %.2f %%\n", (float)sumHum / n);
    printf("\tAverage Rainfall: %.2f mm\n", sumRain / n);
    printf("\tHottest Day: %s (%.2f °C)\n", hotDay, maxTemp);
    printf("\tColdest Day: %s (%.2f °C)\n", coldDay, minTemp);
}

void exportReport(struct Weather data[], int n) {
    if (n == 0) {
        printf("No data to export.\n");
        return;
    }

    FILE *fp = fopen("weather_advanced_report.txt", "w");
    if (fp == NULL) {
        printf("Error creating report file!\n");
        return;
    }

    float sumTemp = 0, sumRain = 0;
    int sumHum = 0;

    float maxTemp = data[0].temperature, minTemp = data[0].temperature;
    float maxRain = data[0].rainfall;
    int maxHum = data[0].humidity;

    char hotDay[20], coldDay[20], rainDay[20], humidDay[20];

    strcpy(hotDay, data[0].date);
    strcpy(coldDay, data[0].date);
    strcpy(rainDay, data[0].date);
    strcpy(humidDay, data[0].date);

    int hotDays = 0, humidDays = 0, rainyDays = 0;

    for (int i = 0; i < n; i++) {
        sumTemp += data[i].temperature;
        sumHum += data[i].humidity;
        sumRain += data[i].rainfall;

        if (data[i].temperature > maxTemp) {
            maxTemp = data[i].temperature;
            strcpy(hotDay, data[i].date);
        }
        if (data[i].temperature < minTemp) {
            minTemp = data[i].temperature;
            strcpy(coldDay, data[i].date);
        }
        if (data[i].rainfall > maxRain) {
            maxRain = data[i].rainfall;
            strcpy(rainDay, data[i].date);
        }
        if (data[i].humidity > maxHum) {
            maxHum = data[i].humidity;
            strcpy(humidDay, data[i].date);
        }

        if (data[i].temperature > 30) hotDays++;
        if (data[i].humidity > 80) humidDays++;
        if (data[i].rainfall > 5) rainyDays++;
    }

    fprintf(fp, "========== WEATHER DATA ADVANCED REPORT ==========\n\n");

    fprintf(fp, "Total Days Recorded: %d\n\n", n);

    fprintf(fp, "------ Temperature Analysis ------\n");
    fprintf(fp, "Average Temperature: %.2f °C\n", sumTemp / n);
    fprintf(fp, "Maximum Temperature: %.2f °C (%s)\n", maxTemp, hotDay);
    fprintf(fp, "Minimum Temperature: %.2f °C (%s)\n", minTemp, coldDay);
    fprintf(fp, "Days Above 30°C: %d\n\n", hotDays);

    fprintf(fp, "------ Humidity Analysis ------\n");
    fprintf(fp, "Average Humidity: %.2f %%\n", (float)sumHum / n);
    fprintf(fp, "Highest Humidity: %d %% (%s)\n", maxHum, humidDay);
    fprintf(fp, "Days With Humidity > 80%%: %d\n\n", humidDays);

    fprintf(fp, "------ Rainfall Analysis ------\n");
    fprintf(fp, "Total Rainfall: %.2f mm\n", sumRain);
    fprintf(fp, "Average Rainfall: %.2f mm\n", sumRain / n);
    fprintf(fp, "Highest Rainfall: %.2f mm (%s)\n", maxRain, rainDay);
    fprintf(fp, "Rainy Days (>5mm): %d\n\n", rainyDays);

    fprintf(fp, "------ Raw Data ------\n");
    fprintf(fp, "Date\tTemp(C)\tHumidity(%%)\tRainfall(mm)\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s\t%.2f\t%d\t%.2f\n",
                data[i].date, data[i].temperature, data[i].humidity, data[i].rainfall);
    }

    fclose(fp);
    printf("Advanced report exported successfully to weather_advanced_report.txt\n");
}


void showCharts(struct Weather data[], int n) {
    if (n == 0) {
        printf("No data to display charts.\n");
        return;
    }

    printf("\n--------- TEMPERATURE CHART (°C) --------\n");
    for (int i = 0; i < n; i++) {
        printf("%s | ", data[i].date);
        int bars = (int)data[i].temperature;
        for (int j = 0; j < bars; j++)
            printf("*"); 
        printf(" (%.1f°C)\n", data[i].temperature);
    }

    printf("\n-------HUMIDITY CHART (%%)--------\n");
    for (int i = 0; i < n; i++) {
        printf("%s | ", data[i].date);
        int bars = data[i].humidity / 2; 
        for (int j = 0; j < bars; j++)
            printf("#");
        printf(" (%d%%)\n", data[i].humidity);
    }

    printf("\n--------RAINFALL CHART (mm) -------\n");
    for (int i = 0; i < n; i++) {
        printf("%s | ", data[i].date);
        int bars = (int)data[i].rainfall;
        for (int j = 0; j < bars; j++)
            printf("~");
        printf(" (%.1fmm)\n", data[i].rainfall);
    }
}
