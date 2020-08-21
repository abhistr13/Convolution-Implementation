// 2D Convolution

#define H 5
#define W 5
#define C 3
#define K 3
#define NH (H-K+1)
#define NW (W-K+1)
using namespace std;

void display2D3D(int* data, int m, int n, int c)
{
    for(int i=0; i<c; i++)
    {
        for(int j=0; j<m; j++)
        {
            for (int k=0; k<n; k++)
                cout << data[i*m*n + j*n + k] << " ";
            cout << endl;
        }
        cout << endl;        
    }
    cout << endl;
}

void sameConvolve2D(int* input, int* kernel, int* output)
{
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            for(int k=0; k<C; k++)
                for(int l=0; l<K; l++)
                    for(int m=0; m<K; m++)
                    {
                        int val = (((i-K/2+l >= 0) && (i-K/2+l < H)) && ((j-K/2+m >= 0) && (j-K/2+m < W))) ? input[k*H*W + (i-K/2+l)*W + (j-K/2+m)]: 0;
                        output[i*W + j] += kernel[k*K*K + l*K + m]*val;
                    }
}

void validConvolve2D(int* input, int* kernel, int* output)
{
    for(int i=0; i<NH; i++)
        for(int j=0; j<NW; j++)
            for(int k=0; k<C; k++)
                for(int l=0; l<K; l++)
                    for(int m=0; m<K; m++)
                        output[i*NW + j] += kernel[k*K*K + l*K + m]*input[k*H*W + (i+l)*W + (j+m)];
}

int main() {
    // define input
    int* inputData = (int*)malloc(H*W*C*sizeof(int));
    for(int i=0; i<C; i++)
        for(int j=0; j<H; j++)
            for (int k=0; k<W; k++)
                inputData[i*H*W + j*W + k] = rand()%10;
    cout << "Input Data" << endl;
    display2D3D(inputData, H, W, C);
    
    // define kernel
    int* filter = new int[K*K*C];
    for(int i=0; i<C; i++)
        for(int j=0; j<K; j++)
            for(int k=0; k<K; k++)
                filter[i*K*K + j*K + k] = 1;//rand()%10;
    cout << "Filter Data" << endl;
    display2D3D(filter, K, K, C);
    
    
    // Padding, P = (K-1)/2
    // same convolution
    int* outputDataSame = (int*)malloc(H*W*sizeof(int));
    memset(outputDataSame, 0, H*W*sizeof(int));
    sameConvolve2D(inputData, filter, outputDataSame);
    cout << "Same Convolution Result" << endl;
    display2D3D(outputDataSame, H,W,1);
    
    
    // Output Size, NH: ((H−K+2P)/S)+1; NW: ((W−K+2P)/S)+1
    // valid convolution
    int* outputDataValid = (int*)malloc(NH*NW*sizeof(int));
    memset(outputDataValid, 0, NH*NW*sizeof(int));
    validConvolve2D(inputData, filter, outputDataValid);
    cout << "Valid Convolution Result" << endl;
    display2D3D(outputDataValid, NH, NW, 1);
    
    // free memory
    free(inputData);
    free(outputDataSame);
    free(outputDataValid);
    delete[] filter;
    
}
