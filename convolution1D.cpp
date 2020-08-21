// 1D Convolution

#define N 10
#define K 3
#define W (N-K+1)
using namespace std;

void display1D(int* data, int length)
{
    for(int i=0; i<length; i++)
        cout << data[i] << " ";
    cout << endl;
}

void sameConvolve1D(int* input, int* kernel, int* output)
{
    for(int i=0; i<N; i++)
        for(int j=0; j<K; j++)
        {
            int val = ((i-K/2+j >= 0) && (i-K/2+j < N)) ? input[i-K/2+j]: 0;
            output[i] = output[i] + kernel[j]*val;
        }       
}

void validConvolve1D(int* input, int* kernel, int* output)
{
    for(int i=0; i<W; i++)
        for(int j=0; j<K; j++)
            output[i] += kernel[j]*input[i+j];    
}

int main() {
    // define input
    int* inputData = (int*)malloc(N*sizeof(int));
    for(int i=0; i<N; i++)
        inputData[i] = rand()%10;
    cout << "Input Data" << endl;
    display1D(inputData, N);
    
    // define kernel
    int* filter = new int[K];
    for(int i=0; i<K; i++)
        filter[i] = rand()%10;
    cout << "Filter Data" << endl;
    display1D(filter, K);
    
    // Padding, P = (K-1)/2
    // same convolution
    int* outputDataSame = (int*)malloc(N*sizeof(int));
    memset(outputDataSame, 0, N*sizeof(int));
    sameConvolve1D(inputData, filter, outputDataSame);
    cout << "Same Convolution Result" << endl;
    display1D(outputDataSame, N);
    
    //cout << W;
    
    
    // Output Size, N: ((N−K+2P)/S)+1
    // valid convolution
    int* outputDataValid = (int*)malloc(W*sizeof(int));
    memset(outputDataValid, 0, W*sizeof(int));
    validConvolve1D(inputData, filter, outputDataValid);
    cout << "Valid Convolution Result" << endl;
    display1D(outputDataValid, W);
    
    // free memory
    free(inputData);
    free(outputDataSame);
    free(outputDataValid);
    delete[] filter;
    
}
