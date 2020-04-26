#ifndef SIGNALPROCESS_H
#define SIGNALPROCESS_H
#include<QVector>
#include<QDebug>
#include<QPointF>
#include<memory>
#include<complex>
#include<algorithm>
#include<cmath>

#include <itpp/itbase.h>
#include <itpp/itsignal.h>
#include <itpp/itstat.h>
#include <sigpack.h>
#include <string>
using namespace itpp;
namespace itpp {
    cvec mean(const cmat& in, int dim);
    vec mean(const mat& in, int dim);
    int nextpow2(unsigned int num);
    cmat zip(const vec& v1, const cvec& v2);
    mat zip(const vec& v1, const vec& v2);
    QVector<QPointF> zipVec2QVec(const vec& v1, const vec& v2);
    vec square(const cvec& x);
    vec abs(const cvec& x);
    mat abs(const cmat& x);
}
QVector<QPointF> zipVec2QVecPointF(const QVector<double>& v1, const QVector<double>& v2);
QVector<double> vec2QVec(const itpp::vec& v);
arma::Mat<double> itppVecToArmaMat(const vec& v);
itpp::vec armaMatToItppVec(const arma::Mat<double>& matrix);
vec qVec2Vec(const QVector<double>& v);
mat nSegFFT(const vec& x, int N, long fs);
mat nSecondFFT(const vec& x, long fs, float sec);
cvec hilbert(const vec& xn, int N = 0);
vec EnvelopeSpectrum(const vec& x);
#endif // SIGNALPROCESS_H
