/* -*- c++ -*- */
/*
 * Copyright 2019 Derek Kozel.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "latency_manager_impl.h"
#include <boost/thread/thread.hpp>

namespace gr {
  namespace example {

    latency_manager::sptr
    latency_manager::make(int max_tags_in_flight)
    {
      return gnuradio::get_initial_sptr
        (new latency_manager_impl(max_tags_in_flight));
    }

    void latency_manager_impl::add_token(pmt::pmt_t msg)
    {
        d_tokens++;
//        std::cout << "Tokens: " << d_tokens << " : Added one\n";
    }

    latency_manager_impl::latency_manager_impl(int max_tags_in_flight)
      : gr::sync_block("latency_manager",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
        d_tokens = max_tags_in_flight;
        message_port_register_in(pmt::mp("token"));
        set_msg_handler(pmt::mp("token"), boost::bind(&latency_manager_impl::add_token, this, _1));
    }

    latency_manager_impl::~latency_manager_impl()
    {
    }

    int
    latency_manager_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const gr_complex *in = (const gr_complex*) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];
        
      // assumes tags are at the start of bursts they refer to
      get_tags_in_window(d_tags,0, 0, noutput_items);
      int stop_point = 0;
//      std::cout << "At Start:\tStop point: " << stop_point << " Num tags in input: " << d_tags.size() << "Tokens available: " << d_tokens << "\n";
      if (d_tags.size() >= d_tokens && !d_tags.empty()) {
        stop_point = d_tags[d_tokens].offset - nitems_read(0);
        d_tokens = 0;
      } else {
        stop_point = noutput_items;
        d_tokens -= d_tags.size();
      } 
 //     std::cout << "After:\tStop point: " << stop_point << " Num tags: " << d_tags.size() << "Tokens after: " << d_tokens << "\n";
      std::memcpy(out, in, stop_point * sizeof(gr_complex));


      if (stop_point <= 0) {
  //      std::cout << "Tokens exhausted, not outputting\n";
        boost::this_thread::sleep(boost::posix_time::microseconds(long(1000)));
      }
      
      return stop_point;
    }
  } /* namespace example */
} /* namespace gr */

