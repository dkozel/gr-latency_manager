title: gr-latency_manager
brief: A GNU Radio module for controlling the latency in a flowgraph
tags:
  - latency
author:
  - Derek Kozel <derek@bitstovolts.com>
copyright_owner:
  - Derek Kozel
license: GPLv3
gr_supported_version: v3.10
repo: https://github.com/dkozel/gr-latency_manager
#website: <module_website> # If you have a separate project website, put it here
#icon: <icon_url> # Put a URL to a square image here that will be used as an icon on CGRAN
---

The latency manager block acts as a gate for a sample stream, allowing only a specified number of samples to be processed downstream. This will starve the downstream graph preventing a large buildup of samples in the buffers between blocks.
