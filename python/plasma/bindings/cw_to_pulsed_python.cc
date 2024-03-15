/*
 * Copyright 2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(cw_to_pulsed.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(87fc0b84fc680816485d0392b44c284f)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/plasma/cw_to_pulsed.h>
// pydoc.h is automatically generated in the build directory
#include <cw_to_pulsed_pydoc.h>

void bind_cw_to_pulsed(py::module& m)
{

    using cw_to_pulsed = gr::plasma::cw_to_pulsed;


    py::class_<cw_to_pulsed, gr::block, gr::basic_block, std::shared_ptr<cw_to_pulsed>>(
        m, "cw_to_pulsed", D(cw_to_pulsed))

        .def(py::init(&cw_to_pulsed::make),
             py::arg("prf"),
             py::arg("samp_rate"),
             D(cw_to_pulsed, make))


        ;
}
