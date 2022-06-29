#include "range_doppler_window.h"
#include <iostream>

RangeDopplerWindow::RangeDopplerWindow(QWidget* parent) : QWidget(parent)
{
    // Debug Plot
    d_debug_curve = new QwtPlotCurve();
    d_debug_plot = new QwtPlot();
    // d_debug_curve->setSamples(xData, yData, 100);
    d_debug_curve->attach(d_debug_plot);

    // Spectrogram
    d_spectro = new QwtPlotSpectrogram();
    d_data = new QwtMatrixRasterData();
    d_plot = new QwtPlot();
    d_spectro->attach(d_plot);
    d_plot->setAutoReplot();

    // GUI layout
    vLayout = new QVBoxLayout();
    vLayout->addWidget(d_debug_plot);
    vLayout->addWidget(d_plot);
    setLayout(vLayout);

    d_closed = false;
}

RangeDopplerWindow::~RangeDopplerWindow() { d_closed = true; }

bool RangeDopplerWindow::is_closed() const { return d_closed; }

void RangeDopplerWindow::customEvent(QEvent* e)
{
    if (e->type() == RangeDopplerUpdateEvent::Type()) {
        RangeDopplerUpdateEvent* event = (RangeDopplerUpdateEvent*)e;
        auto* data = event->data();
        auto rows = event->rows();
        auto cols = event->cols();

        // Create a new vector
        QVector<double> vec(rows * cols);
        std::copy(data, data + vec.size(), vec.data());
        // Also map the vector to an Eigen array to easily compute the minimum
        // and maximum values
        Eigen::ArrayXd tmp = Eigen::Map<Eigen::ArrayXd>(vec.data(), vec.size());
        d_data->setInterval(Qt::XAxis, QwtInterval(0, cols));
        d_data->setInterval(Qt::YAxis, QwtInterval(0, rows));
        d_data->setInterval(Qt::ZAxis, QwtInterval(tmp.minCoeff(), tmp.maxCoeff()));
        d_data->setValueMatrix(vec, cols);
        d_spectro->setData(d_data);
    }


    // double pulse_width = 20e-6;
    // double samp_rate = 40e6;
    // double bandwidth = 0.75 * samp_rate;
    // double prf = 5e3;
    // size_t num_pulse_cpi = 1024;
    // size_t num_samp_pri = samp_rate / prf;
    // size_t num_samp_cpi = num_samp_pri * num_pulse_cpi;
    // plasma::LinearFMWaveform waveform(bandwidth, pulse_width, 0, samp_rate);
    // Eigen::ArrayXcf mf = waveform.MatchedFilter().cast<std::complex<float>>();
    // // Load the waveform received by the SDR
    // std::vector<std::complex<float>> data =
    //     plasma::read<std::complex<float>>("/home/shane/test.dat", 0, num_samp_cpi);
    // // Reshape the data into pulses
    // Eigen::ArrayXXcf fast_time_slow_time =
    //     Eigen::Map<Eigen::ArrayXXcf>(data.data(), data.size(), 1);
    // fast_time_slow_time.resize(fast_time_slow_time.rows() / num_pulse_cpi,
    // num_pulse_cpi);

    // // Do range processing
    // int num_thread = 10;
    // Eigen::ArrayXXcf range_pulse_map = plasma::conv(fast_time_slow_time, mf,
    // num_thread);

    // // Do doppler processing
    // Eigen::ArrayXXcf range_dopp_map(range_pulse_map.rows(), range_pulse_map.cols());
    // plasma::FFT<std::complex<float>, true> fft(range_pulse_map.cols(), num_thread);
    // for (int i = 0; i < range_pulse_map.rows(); i++) {
    //     Eigen::ArrayXcf row = range_pulse_map.row(i);
    //     range_dopp_map.row(i) = Eigen::Map<Eigen::ArrayXcf, Eigen::Aligned>(
    //         fft.execute(row.data()), row.size());
    // }

    // // Do an fftshift
    // Eigen::ArrayXXcf rdm = plasma::fftshift(range_dopp_map, 1);
    // Eigen::ArrayXXf rdm_db = 20 * log10(abs(rdm));
    // rdm_db = rdm_db - rdm_db.maxCoeff();
    // rdm_db = rdm_db.min(0).max(-80);
    // std::cout << "Event processed" << std::endl;
}