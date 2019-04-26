#ifndef AS_RANDOM_GENERATOR_GENERATOR_H_
#define AS_RANDOM_GENERATOR_GENERATOR_H_

#include <string>

class UniformGenerator
{
   public:
      UniformGenerator(int kernel);
      virtual ~UniformGenerator();

      // Draws number between <0,1>
      double Rand();
      // Draws number between <start, end>
      double Rand(int start, int end);

      int get_kernel() {return kernel_;};
   private:
      int kernel_;
      double M;
      int A;
      int Q;
      int R;
};

class ExpGenerator
{
    public:
      ExpGenerator(double lambda, UniformGenerator *ug);
      virtual ~ExpGenerator();
      double Rand();
   private:
      double lambda_;
      UniformGenerator *uniform_;
};

#endif /* AS_RANDOM_GENERATOR_GENERATOR_H_ */



































/*
generatory:
rozk³ady(jednorodny -  uniform, 
sposoby generowania
inverse transformation method(exponential, bernoulli, poisson), 
convolution method(erlang, binomial, standard normal) 
rejection method(standard normal, tail of normal dist) 
other methods( poisson, exponential)

wa¿ne - s64(testing generators)
hypothesis testing(2 types of errors - false positive, false negative(is equal to alpha - level of significance))
frequency(monobit) - zera na -1, suma wszytkich 1 i -1, wartosc bezwzgledna z tej sumy podzielona przez sqrt(dlugosci ci¹gu bitów), 
na koniec erfc z wyniku, jesli jest mniejsze o d 0.01 to znaczy ze hipoteza jest akceptowalna
chi-square test - najwazniejszy test który pozwala sprawdziæ wartoœci mierzalne i niemierzalne.
(równanie - (1/(iloœæ wylosowanych próbek))*(suma od 1 do najwyzszej losowanej wartosci z ((ile razy wylosowano liczbe w danym kube³ku/prawdopodobienstwo wylosowania liczby))
frequency test within a block 
kolmogorov-smirnov test - preffered for continuous population distribution
runs test
coupons collector test
autocorrelation test

co zdaje test? - wzór (1-alpha) +/- 3*sqrt((1-alpha)/liczba próbek))
jesli wynik (iloœci testowanych sekwencji podzielonych przez ilosc sekwencji z P-value mniejsz¹ od poziomu ufnosæi) mieœci siê w przedziale
*/