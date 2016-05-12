PROJECT(Exercise3)

SET( CMAKE_BUILD_TYPE Release )

ADD_EXECUTABLE( Exercise3
  Exercise3.cpp
  DerivativeArray.cpp
  EulerIntegrator.cpp
  Force.cpp
  FourthOrderRungeKuttaIntegrator.cpp
  SecondOrderRungeKuttaIntegrator.cpp
)
