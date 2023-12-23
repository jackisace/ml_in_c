#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// float train_data[5][2] = {
//     {0.0f, 0.0f},
//     {1.0f, 2.0f},
//     {2.0f, 4.0f},
//     {3.0f, 6.0f},
//     {4.0f, 8.0f},
// };

float train_data[4][3] = {
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 1.0f},
    {0.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
};




float cost(size_t j, float w){
    float result = 0.0f;
    float x , y , d = 0.0f;
    size_t train_count = (sizeof(train_data) / sizeof(train_data[0]));
    size_t x_count = (sizeof(train_data[0]) / sizeof(train_data[0][0])) - 1;
    size_t y_pos = x_count + 1;


    for(size_t i = 0; i < train_count; i++){
        x += train_data[i][j];
        y = x*w;
        d = y - train_data[i][y_pos];
        result += d*d;
    }
    result /= train_count;
    printf("result = %f, w = %f\n", result, w);
    return result;
}

void print_weights(float ** w){
    int single = sizeof(train_data[0][0]);
    int train_count = (sizeof(train_data) / sizeof(train_data[0]));
    int x_count = (sizeof(train_data[0]) / sizeof(train_data[0][0])) - 1;
    int train_total = (sizeof(train_data) / sizeof(train_data[0][0]));
    int y_pos = x_count + 1;
    
}


int main(){
    int single = sizeof(train_data[0][0]);
    int train_count = (sizeof(train_data) / sizeof(train_data[0]));
    int x_count = (sizeof(train_data[0]) / sizeof(train_data[0][0])) - 1;
    int train_total = (sizeof(train_data) / sizeof(train_data[0][0]));
    int y_pos = x_count + 1;
    float ** weights = (float**)malloc(train_count*x_count*single);

    for(int h = 0; h < train_count; h++){
        for(int j = 0; j < x_count; j++){
            float w = 1.0f;
            float eps = 1e-3;
            float i = 0.0;
            float last = w;
            float result = w;
            float direction = eps;
            int change_count = 0;
            int ii = 0;
            while(result > 0.01){
                if(change_count == 0){
                    last = (float)result;
                    result = cost(j, w + (eps*i));
                    if(last < result){
                        printf("CHANGE\n");
                        direction *= -1.0f;
                        change_count = 5;
                    } 
                    i += direction;
                } else {
                    change_count--;
                    result = cost(j, w + (eps*i));
                    i += direction;
                }
                printf("i = %f, last = %f ", i, last);
                ii++;
                
            }
            weights[h][j] = w + (eps*i);
        }
    }
    free(weights);
}