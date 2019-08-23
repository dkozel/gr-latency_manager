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

#ifndef INCLUDED_EXAMPLE_BASIS_CHANGE_IMPL_H
#define INCLUDED_EXAMPLE_BASIS_CHANGE_IMPL_H

#include <example/basis_change.h>

namespace gr {
  namespace example {

    class basis_change_impl : public basis_change
    {
     private:
      int d_vlen = 1;
      bool d_circ_to_lin = true;
     public:
      basis_change_impl(int vlen, bool circ_to_lin);
      ~basis_change_impl();

      // Where all the action really happens
      int work(
              int noutput_items,
              gr_vector_const_void_star &input_items,
              gr_vector_void_star &output_items
      );
    };

  } // namespace example
} // namespace gr

#endif /* INCLUDED_EXAMPLE_BASIS_CHANGE_IMPL_H */

