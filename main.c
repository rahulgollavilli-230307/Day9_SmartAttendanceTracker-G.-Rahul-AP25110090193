#include<stdio.h>
int main()
 {
    int S,i=1;
    int eligibleCount=0,notEligibleCount=0;
    float totalPercentage=0.00;
    printf("Enter total number of students");
    scanf("%d",&S);
    while(i<=S) 
    {
        int P;
        float percentage;
        printf("Enter attendance for student is %d (out of 30): ", i);
        scanf("%d", &P);
        percentage=(P / 30.0) * 100;
        totalPercentage += percentage;
        printf("Student %d: %.2f%% - ", i, percentage);
        if (percentage>=75.0)
         {
            printf("Eligible\n");
            eligibleCount++;
        } 
        else
         {
            printf("Not Eligible\n");
            notEligibleCount++;
        }
        i++;
    }
    printf("Class Summary:\n");
    printf("Total Students: %d\n", S);
    printf("Eligible Students: %d\n", eligibleCount);
    printf("Not Eligible: %d\n", notEligibleCount);
    printf("Average Attendance: %.2f%%\n", totalPercentage / S);
    return 0;
}