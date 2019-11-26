#include <iostream>
#include "data.h"
#include "result.h"
#include "matrix.h"
#include "link.h"

typedef struct scomplex_s {
    double re;
    double im;
} scomplex_t;

double ipr(scomplex_t* vec);
double revert(double a);

int x_size = 32;
int y_size = 32;
int z_size = 32;
int t_size;

int main(){
    t_size = 32;
    int vec_size = x_size * y_size * z_size * t_size * 2;
    int val_number = 60;
    result vec(vec_size * val_number * 2 + 2 * val_number);
    vec.read("/home/ilya/lattice/IPR/vecs/time_32/mu0.00/eigenvectors_eig=120_0001", vec_size * val_number * 2 + 2 * val_number);
    scomplex_t* src;
    if(!(src = (scomplex_t*) malloc(vec_size * sizeof(scomplex_t)))) cout<<"err malloc src"<<endl;
    result res_ipr(val_number);
    for(int j = 0;j < val_number;j++){
        for(int i = 0;i < vec_size;i++){
            src[i].re = revert(vec.array[(vec_size + 2) * j + i * 2 + 2]);
            src[i].im = revert(vec.array[(vec_size + 2) * j + i * 2 + 3]);
        }


        res_ipr.array.push_back(ipr(src));
        cout<<"ipr = "<<ipr(src)<<endl;
    }
    vec.array.clear();
    free(src);
}

double ipr(scomplex_t* vec){
    int vec_size = x_size * y_size * z_size * t_size * 2;
    double ipr = 0;
    for(int i = 0;i < vec_size;i++){
        ipr += (vec[i].re * vec[i].re + vec[i].im * vec[i].im) * (vec[i].re * vec[i].re + vec[i].im * vec[i].im);
    }
    return ipr * 32*32*32;
}

double revert(double a){
    unsigned char* b = reinterpret_cast<unsigned char*>(&a);
    char t;
    for(int i = 0;i < 4;i++){
        t = b[i];
        b[i] = b[7-i];
        b[7-i] = t;
    }
    return *reinterpret_cast<double*>(b);
}

//testing
    // ifstream stream("eigenvectors_bin");
    // vector<double> test_vec(300);
    // stream.ignore(16);
	// if(!stream.read((char*) &test_vec[0], 300 * sizeof(double))) cout<<"test err"<<endl;
    // for(int i = 0;i < 300;i++){
    //     test_vec[i] = revert(test_vec[i]);
    //     cout<<i<<" "<<test_vec[i]<<endl;
    // }
	// stream.close();
    //testing