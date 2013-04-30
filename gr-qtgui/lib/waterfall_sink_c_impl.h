/* -*- c++ -*- */
/*
 * Copyright 2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_QTGUI_WATERFALL_SINK_C_IMPL_H
#define INCLUDED_QTGUI_WATERFALL_SINK_C_IMPL_H

#include <qtgui/waterfall_sink_c.h>
#include <filter/firdes.h>
#include <fft/fft.h>
#include <gnuradio/high_res_timer.h>
#include <gnuradio/thread/thread.h>
#include <qtgui/waterfalldisplayform.h>

namespace gr {
  namespace qtgui {

    class QTGUI_API waterfall_sink_c_impl : public waterfall_sink_c
    {
    private:
      void forecast(int noutput_items, gr_vector_int &ninput_items_required);

      void initialize();

      int d_fftsize;
      float d_fftavg;
      filter::firdes::win_type d_wintype;
      std::vector<float> d_window;
      double d_center_freq;
      double d_bandwidth;
      std::string d_name;
      int d_nconnections;

      bool d_shift;
      fft::fft_complex *d_fft;

      int d_index;
      std::vector<gr_complex*> d_residbufs;
      std::vector<double*> d_magbufs;
      float *d_fbuf;

      QWidget *d_parent;
      WaterfallDisplayForm *d_main_gui;

      gr::high_res_timer_type d_update_time;
      gr::high_res_timer_type d_last_time;

      void windowreset();
      void buildwindow();
      void fftresize();
      void fft(float *data_out, const gr_complex *data_in, int size);

    public:
      waterfall_sink_c_impl(int size, int wintype,
			    double fc, double bw,
			    const std::string &name,
			    int nconnections,
			    QWidget *parent=NULL);
      ~waterfall_sink_c_impl();

      bool check_topology(int ninputs, int noutputs);

      void exec_();
      QWidget*  qwidget();
      PyObject* pyqwidget();

      void clear_data();

      void set_fft_size(const int fftsize);
      int fft_size() const;
      void set_fft_average(const float fftavg);
      float fft_average() const;
      void set_fft_window(const gr::filter::firdes::win_type win);
      gr::filter::firdes::win_type fft_window();

      void set_frequency_range(const double centerfreq, const double bandwidth);
      void set_intensity_range(const double min, const double max);

      void set_update_time(double t);
      void set_title(const std::string &title);
      void set_line_label(int which, const std::string &label);
      void set_line_alpha(int which, double alpha);
      void set_color_map(int which, const int color);

      std::string title();
      std::string line_label(int which);
      double line_alpha(int which);
      int color_map(int which);

      void set_size(int width, int height);

      void auto_scale();
      double min_intensity(int which);
      double max_intensity(int which);

      void enable_menu(bool en);
      void enable_grid(bool en);

      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } /* namespace qtgui */
} /* namespace gr */

#endif /* INCLUDED_QTGUI_WATERFALL_SINK_C_IMPL_H */