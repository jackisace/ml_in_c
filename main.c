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


int single = sizeof(train_data[0][0]);
int train_count = (sizeof(train_data) / sizeof(train_data[0]));
int x_count = (sizeof(train_data[0]) / sizeof(train_data[0][0])) - 1;
int train_total = (sizeof(train_data) / sizeof(train_data[0][0]));
int y_pos = (sizeof(train_data[0]) / sizeof(train_data[0][0]));

float cost(int i, int j, float w){
    float result = 0.0f;
    float x , y , d = 0.0f;

    x = train_data[i][j];
    y = x*w;
    d = y - train_data[i][y_pos];
    printf("d = %f ", d);
    result = d*d;

    //result /= train_count;
    printf("result = %f, w = %f\n", result, w);
    return result;
}

void set_weights(float * w){
    int t = 0;
    for(int i = 0; i < train_count; i++){
        for(int j = 0; j < x_count; j++){
            if(train_data[i][j] == 0.0f || train_data[i][y_pos] == 0.0f){
                w[t] = 0.0f;
            } else {
                w[t] =  train_data[i][j] / train_data[i][y_pos];
                if(w[t] > 1.0f){
                    w[t] = 1.0f;
                }
            }
  
            printf("%f %f %f \n", w[t], train_data[i][j], train_data[i][y_pos]);
            t++;
        }
    }
}

void print_weights(float * w){
    printf("\n===============================\n");

    int t = 0;
    for(int i = 0; i < train_count; i++){
        for(int j = 0; j < x_count; j++){
            printf("%f ", w[t++]);
        }
        printf("\n");
    }
    printf("===============================\n");
    
}


int main(){
    
    float * weights = calloc(train_count * x_count, single);
    set_weights(weights);
    print_weights(weights);
    return 0;
    int t = 0;
    for(int h = 0; h < train_count; h++){
        for(int j = 0; j < x_count; j++){
            float w = 1.0f;
            float eps = 1e-3;
            float i = 0.0;
            float last = w;
            float result = w;
            float direction = eps;
            int change_count = 0;
            int changes = 0;
            int ii = 0;
            while(result > 0.01){
                if(change_count == 0){
                    last = (float)result;
                    result = cost(h, j, eps*i);
                    if(last <= result){
                        printf("CHANGE\n");

                        direction *= -1.0f;
                        change_count = 5;
                    } 
                    i += direction;
                } else {
                    change_count--;
                    result = cost(h, j, eps*i);
                    i += direction;
                }
                printf("i = %f, last = %f ", i, last);
                ii++;
                
            }
            weights[t++] = eps*i;
        }
    }
    print_weights(weights);
    free(weights);
}