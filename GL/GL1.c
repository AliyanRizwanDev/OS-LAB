#include<stdio.h>
int main()
{
    int arr[20];
    int swap,n;
     
    printf("Enter number of elements");
    scanf("%d",&n);
    printf("Enter %d integers",n);

    for(int i=0 ;i<n;i++)
    {
      scanf("%d",&arr[i]);

    }
    for(int x=0; x<n-1;x++)
    {
        for(int y=0; y<n-x;y++)
        {
            if(arr[y]>arr[y+1])
            {
           swap= arr[y];
           arr[y]=arr[y+1];
           arr[y+1]=swap;
            }

        }
    }
    printf("sorting to ascending order is:");
    for(int s=0; s<n;s++)
    {
        printf("%d",arr[s]);
        return 0;
    }

}