##### [scipy.spatial.distance.cdist](https://docs.scipy.org/doc/scipy/reference/generated/scipy.spatial.distance.cdist.html)

Y = cdist(XA, XB, 'euclidean')

Computes the distance between points using Euclidean distance (2-norm) as the distance metric between the points. The points are arranged as -dimensional row vectors in the matrix X.

[Is L2-Norm = Euclidean Distance?](https://medium.com/mlearning-ai/is-l2-norm-euclidean-distance-a9c04be0b3ca)

https://github.com/scipy/scipy/blob/main/scipy/spatial/src/distance_pybind.cpp

Stacktrace of `Y = cdist(XA, XB, 'euclidean')`:

- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/distance.py#L2617
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/distance.py#L2944
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/distance.py#L1835
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_pybind.cpp#L615
  - https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_metrics.h#L198
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_pybind.cpp#L513
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_pybind.cpp#L535
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_pybind.cpp#L311
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_pybind.cpp#L144
- https://github.com/scipy/scipy/blob/v1.8.1/scipy/spatial/src/distance_metrics.h#L198
