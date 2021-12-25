struct Matrix {
    //change the constants in matrix product function
    int a[101][101];
    Matrix operator*(Matrix other) {
        Matrix product;
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                product.a[i][j] = 0;
            }
        }
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                for(int k=0; k<3; k++) {
                    product.a[i][j] += a[i][k] * other.a[k][j];
                    product.a[i][j] %= MOD;
                }
            }
        }
        return product;
    }
};

Matrix base;
Matrix expo(int P) {
    if(P == 1) return base;
    Matrix R = expo(P>>1);
    if(P&1) return R * R * base;
    return R * R;
}
