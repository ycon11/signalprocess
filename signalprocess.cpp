#include "signalprocess.h"
namespace itpp {
    cvec mean(const cmat& in, int dim) {
        //dim = 0:行求平均值    dim = 1:列求平均值
        cvec ret;
        if (dim == 0) {
            ret = zeros_c(in.rows());
            for (int i = 0; i < in.rows(); i++) {
                std::complex<double> iRowMean = 0;
                for (int j = 0; j < in.cols(); j++) {
                    iRowMean += in(i, j);
                }
                ret[i] = iRowMean / in.cols();
            }
        }
        else if (dim == 1) {
            ret = zeros_c(in.cols());
            for (int i = 0; i < in.cols(); i++) {
                std::complex<double> iColMean = 0;
                for (int j = 0; j < in.rows(); j++) {
                    iColMean += in(j, i);
                }
                ret[i] = iColMean / in.rows();
            }
        }
        return ret;
    }
    vec mean(const mat& in, int dim) {
        //dim = 0:行求平均值    dim = 1:列求平均值
        vec ret;
        if (dim == 0) {
            ret = zeros(in.rows());
            for (int i = 0; i < in.rows(); i++) {
                double iRowMean = 0;
                for (int j = 0; j < in.cols(); j++) {
                    iRowMean += in(i, j);
                }
                ret[i] = iRowMean / in.cols();
            }
        }
        else if (dim == 1) {
            ret = zeros(in.cols());
            for (int i = 0; i < in.cols(); i++) {
                double iColMean = 0;
                for (int j = 0; j < in.rows(); j++) {
                    iColMean += in(j, i);
                }
                ret[i] = iColMean / in.rows();
            }
        }
        return ret;
    }
    int nextpow2(unsigned int num) {
        int n = 1;
        int i = 0;
        while (n < num) {
            n = n * 2;
            i++;
        }
        return i;
    }
    cmat zip(const vec& v1, const cvec& v2) {
        cmat ret;
        if (v1.size() == v2.size()) {
            ret = zeros_c(v1.size(), 2);
        }
        else {
            int rows = v1.size() < v2.size() ? v1.size() : v2.size();
            ret = zeros_c(rows, 2);
        }
        for (int i = 0; i < ret.rows(); i++) {
            ret(i, 0) = v1(i);
            ret(i, 1) = v2(i);
        }
        return ret;
    }
    mat zip(const vec& v1, const vec& v2) {
        mat ret;
        if (v1.size() == v2.size()) {
            ret = zeros(v1.size(), 2);
        }
        else {
            int rows = v1.size() < v2.size() ? v1.size() : v2.size();
            ret = zeros(rows, 2);
        }
        for (int i = 0; i < ret.rows(); i++) {
            ret(i, 0) = v1(i);
            ret(i, 1) = v2(i);
        }
        return ret;
    }
    QVector<QPointF> zipVec2QVec(const vec& v1, const vec& v2) {
        int size = v1.size() < v2.size() ? v1.size() : v2.size();
        QVector<QPointF> ret;
        for (int i = 0; i < size; i++) {
            ret.append(QPointF(v1[i], v2[i]));
        }
        return ret;
    }
    vec square(const cvec& x) {
        vec ret(x.size());
        for (int i = 0; i < x.size(); i++) {
            ret[i] = std::abs(x[i]);
        }
        return ret;
    }
    vec abs(const cvec& x) {
        vec ret = zeros(x.size());
        for (int i = 0; i < x.size(); i++) {
            ret(i) = std::abs(x(i));
        }
        return ret;
    }
    mat abs(const cmat& x) {
        mat ret = zeros(x.rows(),x.cols());
        for (int i = 0; i < x.rows(); i++) {
            for (int j = 0; j< x.cols(); j++) {
                ret(i,j) = std::abs(x(i,j));
            }
        }
        return ret;
    }


}
QVector<QPointF> zipVec2QVecPointF(const QVector<double>& v1, const QVector<double>& v2) {
    int size = v1.size() < v2.size() ? v1.size() : v2.size();
    QVector<QPointF> ret(size);
    for (int i = 0; i < size;i++) {
        ret[i] = QPointF(v1[i], v2[i]);
    }
    return ret;
}
QVector<double> vec2QVec(const itpp::vec &v) {
    QVector<double> ret(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret[i] = v(i);
    }
    return ret;
}
vec qVec2Vec(const QVector<double> &v) {
    vec ret = zeros(v.size());
    for (int i = 0; i < v.size(); i++) {
        ret(i) = v[i];
    }
    return ret;
}
mat nSegFFT(const vec& x, int N, long fs) {
    int numsOfPoint = x.size();  //输入信号的点数
    int nSeg = numsOfPoint / N;
    if (numsOfPoint % N != 0) {
        nSeg += 1;
    }
    vec axis_x(N /2);
    vec axis_y(N /2);
    mat points(N /2, 2);
    for (int i = 0; i < (N >> 1); i++) {
        axis_x[i] = i * fs / N;
    }
    mat X = zeros(nSeg, N);
    for (int i = 0; i < nSeg; i++) {
        vec sub_x;
        if (i == nSeg-1) {
            sub_x = x(i * N, x.size());
        }
        else {
            sub_x = x(i * N, (i + 1) * N);
        }
        cvec Y = fft_real(sub_x, N);
        vec amp = itpp::abs(Y);
        X.set_row(i, amp);

    }
    axis_y = itpp::mean(X, 1);
    mat point = zip(axis_x, axis_y);
    return point;
}

cvec hilbert(const vec& xn, int N) {
    int n = xn.size();
    int fftN = itpp::pow2(nextpow2(xn.size()));
    int nfft = 0;
    if (N >= 2) {
        nfft = std::max(N, fftN);
    }
    else {
        nfft = fftN;
    }
    cvec result = zeros_c(nfft);
    cvec y = itpp::fft_real(xn, nfft);
    int hN = nfft >> 1;
    int numRem = hN;
    for (int i = 1; i < hN; i++) {
        double real = y[i].real();
        double imag = y[i].imag();
        y[i].real(real * 2);
        y[i].imag(imag * 2);
    }
    for (int i = hN + 1; i < xn.size(); i++) {
        y[i].real(0);
        y[i].imag(0);
    }
    auto y2 = ifft(y);
    for (int i = 0; i < nfft; i++) {
        if (i < xn.size()) {
            result[i].real(xn[i]);
        }
        else {
            result[i].real(0);
        }
        result[i].imag(y2(i).imag());
    }
    return result;
}
vec  EnvelopeSpectrum(const vec& x) {
    cvec hx = hilbert(x);
    int N = x.size();
    vec y = itpp::abs(hx);
    y = y - itpp::ones(y.size()) * mean(y);
    vec axis_y = itpp::abs(itpp::fft_real(y, y.size()));
    return axis_y;
}
# if 0
vec de_resonance(const vec &x, long fs,int fl,int fll,int fh,int fhh,std::string window_model) {
 /*    """
     :param x：原信号
     :param fl: 通带起始频率
     :param fll: 阻带截止频率
     :param fh: 通带截止频率
     :param fhh: 阻带起始频率
     :param fs: 原信号采样率
     :param window: 带通滤波器窗函数类型
     :return: 共振解调后得到的信号
     """
*/
    float wl = 2 * pi * fl / fs;
    float wll = 2 * pi * fll / fs;
    float wh = 2 * pi * fh / fs;
    float whh = 2 * pi * fhh / fs;
    float tr_width = std::min((wl - wll), (whh - wh)); // # 过渡带宽度
    std::string model = "hamming";
    model = window_model;
    vec window;
    int N = 0,M = 0;
    if (model == "rectangular") {
        N = ceil(1.8 * pi / tr_width); // 滤波器长度
        M = N + (N + 1) % 2; // 使滤波器为I型(偶数)
        //window = boxcar(M);矩形窗
    }
    else if (model == "triang") {
        N = ceil(1.8 * pi / tr_width);   //  滤波器长度
        M = N + N + 1 % 2;            //   使滤波器为I型(偶数)
        window = triang(M);
    }
    else if (model == "hanning") {
        N = ceil(6.2 * pi / tr_width);        // # 滤波器长度
        M = N + (N + 1) % 2;              // # 使滤波器为I型(偶数)
        window = hanning(M);
    }
    else if (model == "hamming") {
        N = ceil(6.6 * pi / tr_width);//  # 滤波器长度
        M = N + (N + 1) % 2;         // # 使滤波器为I型(偶数)
        window = hamming(M);        //  #
    
    }       
    else if (model == "blackman") {
        N = ceil(11 * pi / tr_width)  ; // # 滤波器长度
        M = N + (N + 1) % 2;  //# 使滤波器为I型(偶数)
        window = blackman(M);  // #
    }
    vec bands = zeros(6);
    bands[1] = fll;
    bands[2] = fl;
    bands[3] = fh;
    bands[4] = fhh;
    bands[5] = fs / 2;
    vec desired = zeros(6);
    desired[2] = 1;
    desired[3] = 1;
    //bm = firls(M, bands, desired, fs = fs)
    //y = lfilter(bm, 1, x)
    vec y = abs(hilbert(y));
    return y;
}
#endif

