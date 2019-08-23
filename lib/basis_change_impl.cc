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
#include "basis_change_impl.h"
#include "volk/volk.h"

namespace gr {
  namespace example {

    basis_change::sptr
    basis_change::make(int vlen, bool cir_to_lin)
    {
      return gnuradio::get_initial_sptr
        (new basis_change_impl(vlen, cir_to_lin));
    }


    /*
     * The private constructor
     */
    basis_change_impl::basis_change_impl(int vlen, bool circ_to_lin)
      : gr::sync_block("basis_change",
              gr::io_signature::make(2, 2, sizeof(gr_complex) * vlen),
              gr::io_signature::make(2, 2, sizeof(gr_complex) * vlen))
    {
        d_vlen = vlen;
        d_circ_to_lin = circ_to_lin;
    }

    /*
     * Our virtual destructor.
     */
    basis_change_impl::~basis_change_impl()
    {
    }

    int
    basis_change_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      
      if (d_circ_to_lin) {  
          const gr_complex *left = (const gr_complex *) input_items[0];
          const gr_complex *right = (const gr_complex *) input_items[1];

          gr_complex *vertical = (gr_complex *) output_items[0];
          gr_complex *horizontal = (gr_complex *) output_items[1];

          // Compute the horizontal polarization 
          volk_32f_x2_add_32f((float *) horizontal, (float *) left, (float *) right, noutput_items * d_vlen * 2); 
          volk_32f_s32f_multiply_32f((float *) horizontal, (float *) horizontal, M_SQRT1_2, noutput_items * d_vlen * 2);     

          volk_32f_x2_subtract_32f((float *) vertical, (float *) right, (float *) left, noutput_items * d_vlen * 2);
          volk_32fc_s32fc_multiply_32fc(vertical, vertical, gr_complex(0, M_SQRT1_2), noutput_items * d_vlen);

      } else {
          const gr_complex *vertical = (const gr_complex *) input_items[0];
          const gr_complex *horizontal = (const gr_complex *) input_items[1];

          gr_complex *left = (gr_complex *) output_items[0];
          gr_complex *right = (gr_complex *) output_items[1];


          gr_complex scaled_vertical[noutput_items];
          volk_32fc_s32fc_multiply_32fc(scaled_vertical, vertical, gr_complex(0, M_SQRT1_2), noutput_items * d_vlen);
          
          volk_32f_s32f_multiply_32f((float *) left, (float *) horizontal, M_SQRT1_2, noutput_items * d_vlen * 2);
          
          volk_32f_x2_subtract_32f((float *) right, (float *) left, (float *) scaled_vertical, noutput_items * d_vlen * 2);
          volk_32f_x2_add_32f((float *) left, (float *) left, (float *) scaled_vertical, noutput_items * d_vlen * 2);

//          for (int i = 0; i < noutput_items * d_vlen; i++) {
//              left[i]  = (float)M_SQRT1_2 * (horizontal[i] + gr_complex(0, 1) * vertical[i]);
//              right[i] = (float)M_SQRT1_2 * (horizontal[i] - gr_complex(0, 1) * vertical[i]);
//          }
        
      } 
      
      return noutput_items;
    }

  } /* namespace example */
} /* namespace gr */

