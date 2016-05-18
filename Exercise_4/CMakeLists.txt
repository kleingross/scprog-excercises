PROJECT(Exercise4)

SET( CMAKE_BUILD_TYPE Release )

ADD_EXECUTABLE( Exercise4
  Exercise4.cpp
  Point.cpp
  Particle.cpp
  DerivativeArray.cpp
  PendulumEnvironment.cpp
  GravityEnvironment.cpp
  EulerIntegrator.cpp
  FourthOrderRungeKuttaIntegrator.cpp
  SecondOrderRungeKuttaIntegrator.cpp
)
