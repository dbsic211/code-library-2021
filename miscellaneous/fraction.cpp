struct Fraction {
    int p, q;
    Fraction operator+(Fraction other) {
        Fraction sum;
        sum.q = lcm(q, other.q);
        sum.p = p * sum.q / q + other.p * sum.q / other.q;
        return sum;
    }
    Fraction operator*(Fraction other) {
        Fraction product;
        product.p = p * other.p;
        product.q = q * other.q;
        return product;
    }
};
