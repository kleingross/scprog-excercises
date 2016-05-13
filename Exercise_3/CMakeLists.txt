PROJECT(Exercise3)

SET( CMAKE_BUILD_TYPE Release )

ADD_EXECUTABLE( Exercise3
  Exercise3.cpp
  Point.cpp
  Particle.cpp
  DerivativeArray.cpp
  Force.cpp
  EulerIntegrator.cpp
  FourthOrderRungeKuttaIntegrator.cpp
  SecondOrderRungeKuttaIntegrator.cpp
)
