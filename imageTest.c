#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

extern int* imageToMat(char* name, int* dims);
extern void matToImage(char* name, int* mat, int* dims);

int main( int argc, char** argv ) {

    int numranks;
    int rank;
    MPI_Status stat;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numranks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int *temp;
    int *dims = (int*)malloc(2*sizeof(int));
    int *matrix;
    int *mystart = (int*)malloc(numranks*sizeof(int));
    int *myend = (int*)malloc(numranks*sizeof(int));
    char *name="image.jpg";

    double startTime = MPI_Wtime();

    if(rank==0){
        //read image
        matrix=imageToMat(name,dims);
        printf("read image\n");
    }

    MPI_Bcast(dims,2,MPI_INT,0,MPI_COMM_WORLD);
    printf("sent dims\n");
    int height=dims[0];
    int width=dims[1];
    int numele = (height*width);
    int rankheight = height/numranks;
    int rankele = rankheight*width;

    if(rank!=0){    matrix = (int*)malloc(numele*sizeof(int));  }

    MPI_Bcast(matrix,numele,MPI_INT,0,MPI_COMM_WORLD);
    printf("sent image\n");

    for(int i=0;i<numranks;i++){
        mystart[i] = i*rankheight;
        myend[i] = mystart[i]+rankheight;
    }
    printf("Rank %d computed start: %d end:%d\n", rank,mystart[rank],myend[rank]);
    //your image processing here    
    temp = (int*)malloc(rankheight*width*sizeof(int));
    int k=10;
    int size = 2*k+1;
    int range = size/2;
    double* kernel = (double*)malloc(size*size*sizeof(double));

    for(int i=0;i<size*size;i++){
        kernel[i]=1;
    }
    
    printf("rank %d started blur\n",rank);
    //pick a pixel
    for(int i=mystart[rank];i<myend[rank];i++){
        for(int j=0;j<width;j++){
            int index = (i-mystart[rank])*width+j;

            double sum = 0;
            int count = 0;
            //convultion sums
            for(int u=-k;u<=k;u++){
                for(int v=-k;v<=k;v++){
                    if(i-u<0 || i-u>height || j-v<0 || j-v>width){
                        continue;
                    }
                    sum+=(kernel[(u+range)*size+(v+range)]*matrix[(i-u)*width+(j-v)]);
                    count++;
                }
            }

            //temp[index] = sum/count
            temp[index]=sum/((2*k+1)*(2*k+1));
        }
    }
    printf("Completed blur\n");

    int *completeTemp = (int*)malloc(numele*sizeof(int));

    MPI_Gather(temp,rankele,MPI_INT,completeTemp,rankele,MPI_INT,0,MPI_COMM_WORLD);

    double endTime = MPI_Wtime();

    if(rank==0){
        printf("Processing time: %f\n", endTime-startTime);
        //save image
        matToImage("processedImage.jpg",completeTemp,dims);
    }
    free(temp);
    free(kernel);
    free(dims);
    free(matrix);
    free(completeTemp);
    free(mystart);
    free(myend);
    MPI_Finalize();
    return 0;
}
