#include<iostream>

void scoreCompare(int pBestStepNum, int bestStepNmu)
{
    int diff_;//difference value，与最佳步数的差值
    diff_ = pBestStepNum - bestStepNmu;
    int diff = diff_ / 10;
    switch (diff)
    {
    case 0:
        printf("Excellent!");
        break;
    case 1:
        printf("Good!");
        break;
    case 2:
        printf("Fine.");
        break;
    case 3:
        printf("Pass.");
        break;
    default:
        if (diff < 0)
        {
            printf("Congrats!You just break the record!");
        }
        else
        {
            printf("Merely pass.");
        }
    }
}
